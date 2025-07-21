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

/*
    Main application
*/
volatile bool SEND_FRAME = false;

// This version takes the derivative (adc_error), then squares it to remove negative component (adc_error_sq). This results 
// in 2 peaks where the negative component squared results in a peak slightly smaller than the original positive R-spike.
// The squared result has the sqrt taken twice (adc_error_sq_sqrt_sqrt) to bring the result into an unsigned 8-bit range so that levels 
// can be compared using a DAC (Q-71 has 2x8-bit and 1x10-bit DAC). A threshold is set that is larger than the squared negative peak, but 
// less than the squared positive peak. This could be problematic as the threshold from person to person may vary significantly.
void DS_Frame_Update(void){
    ADC_StartConversion();
    while(!(ADC_IsConversionDone()));
    DataStreamer.adc_result = ADC_GetConversionResult();
    DataStreamer.adc_error = ADC_GetErrorCalculation();
    DataStreamer.adc_error_sq = (uint32_t)DataStreamer.adc_error * (uint32_t)DataStreamer.adc_error;
    DataStreamer.adc_error_sq_sqrt_sqrt = (uint8_t) sqrt(DataStreamer.adc_error_sq);
    SEND_FRAME = true;
    DAC3_SetOutput(DataStreamer.adc_error_sq_sqrt_sqrt);
}

int main(void)
{
    SYSTEM_Initialize();
    

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    
    //ADC_SetChannel(channel_ANA4);

    while(1)
    {
        
        
        DS_Frame_Update();      // write the result of an ADC read to the Data Streamer struct
        if(SEND_FRAME)  {       // if the Data Streamer frame has been updated
            WriteFrame();       // Write the new frame 
            SEND_FRAME = false; // Set the boolean back to false for next time
        }
    }    
}