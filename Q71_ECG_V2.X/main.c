 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <math.h>

// This threshold is used along with the Max R-peak level to determine when the CMP should trigger an interrupt
#define THRESHOLD_RATIO_OF_MAX 0.7
#define UTM_PERIOD 24E-6    // based off TU16A clock source and prescaler

// variable used in CMP ISR
static volatile uint16_t timeSpent = 0;
uint16_t heart_rate;
/*
    Main application
*/
volatile bool SEND_FRAME = false;

void GetHeartRate(void) {
    static uint16_t timeLast = 0;
    uint16_t timeNow = TU16A_OnCommandCapture();
    
    // in case timeNow has rolled over
    if (timeNow <= timeLast)    {
        timeSpent = timeNow + (UINT16_MAX - timeLast);
    } 
    else timeSpent = timeNow - timeLast;
    
    // save for next time
    timeLast = timeNow;
    heart_rate = (1/(timeSpent * UTM_PERIOD)) * 60;
}

// This 2nd version takes the derivative (adc_error), if the value is less than 0, it is saved as 0. 
// If it is positive, it is saved as the original value but cast as an uint8_t so that levels 
// can be compared using a DAC (Q-71 has 2x8-bit and 1x10-bit DAC). A threshold is automatically 
// determined by a defined ratio of the largest R-spike seen.
// This version does NOT use the computationally expensive sqrt twice. 
void DS_Frame_Update(void){
    ADC_StartConversion();
    while(!(ADC_IsConversionDone()));
    
    DataStreamer.adc_result = ADC_GetConversionResult();
    DataStreamer.adc_error = ADC_GetErrorCalculation();
    DataStreamer.adc_error_sq = DataStreamer.adc_error * DataStreamer.adc_error;
    
    if (DataStreamer.adc_error >= 0)  {
        DataStreamer.adc_error_pos = (uint8_t)DataStreamer.adc_error;
    }
    else DataStreamer.adc_error_pos = (uint8_t)0;
    
    if (DataStreamer.adc_error_pos > DataStreamer.adc_error_pos_max)    {
        DataStreamer.adc_error_pos_max = DataStreamer.adc_error_pos;
    }
    
    SEND_FRAME = true;
    DAC3_SetOutput(DataStreamer.adc_error_pos);
    
    DAC2_SetOutput(THRESHOLD_RATIO_OF_MAX * DataStreamer.adc_error_pos_max);
    
    DataStreamer.heart_rate = heart_rate; 
}

int main(void)
{
    SYSTEM_Initialize();
    // initialize variables for first run through
    DataStreamer.adc_error_pos_max = 0;
    // Custom CMP function callback uses GetHeartrate function
    CMP1_InterruptCallbackRegister(&GetHeartRate);
    

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    while(1)
    {
        DS_Frame_Update();      // write the result of an ADC read to the Data Streamer struct
        if(SEND_FRAME)  {       // if the Data Streamer frame has been updated
            WriteFrame();       // Write the new frame 
            SEND_FRAME = false; // Set the boolean back to false for next time
        }
    }    
}