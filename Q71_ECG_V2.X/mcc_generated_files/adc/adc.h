/**
 * ADC Generated Driver API Header File
 * 
 * @file adc.h
 * 
 * @defgroup  adc ADC
 * 
 * @brief This is the generated header file for the ADC driver.
 *
 * @version ADC Driver Version 1.0.2
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

#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdbool.h>

#ifndef int24_t
typedef __int24 int24_t;
#endif

/**
 @ingroup adc
 @typedef adc_result_t
 @brief Displays the result of the Analog-to-Digital (A/D) conversion.
 */
typedef int16_t adc_result_t;

/**
 * @ingroup adc
 * @enum adc_posChannel_t
 * @brief Contains the available ADC positive channels.
*/
typedef enum
{
    poschannel_ADCG1 =  0x36,
    poschannel_OPA1IN_pos =  0x37,
    poschannel_OPA2IN_pos =  0x38,
    poschannel_DAC2 =  0x39,
    poschannel_DAC3 =  0x3a,
    poschannel_VSS =  0x3b,
    poschannel_Temp =  0x3c,
    poschannel_DAC1 =  0x3d,
    poschannel_FVR_Buffer1 =  0x3e,
    poschannel_FVR_Buffer2 =  0x3f,
    poschannel_OPA1IN0_pos =  0x82,
    poschannel_OPA1IN1_pos =  0x84,
    poschannel_OPA1IN2_pos =  0x85,
    poschannel_OPA1IN3_pos =  0x89,
    poschannel_OPA2IN0_pos =  0x4c,
    poschannel_OPA2IN1_pos =  0x41,
    poschannel_OPA2IN2_pos =  0x4b,
    poschannel_OPA2IN3_pos =  0x4a,
    poschannel_ANA4 =  0x4
} adc_posChannel_t;

/**
 * @ingroup adc
 * @enum adc_negChannel_t
 * @brief Contains the available ADC negative channels.
*/
typedef enum
{
    negchannel_OPA1IN_neg =  0x37,
    negchannel_OPA2IN_neg =  0x38,
    negchannel_DAC2 =  0x39,
    negchannel_DAC3 =  0x3a,
    negchannel_VSS =  0x3b,
    negchannel_Temp =  0x3c,
    negchannel_DAC1 =  0x3d,
    negchannel_FVR_Buffer1 =  0x3e,
    negchannel_FVR_Buffer2 =  0x3f,
    negchannel_ANA5 =  0x5
} adc_negChannel_t;

/**
 @ingroup adc
 @enum ADC_context_t
 @brief Contains the available ADC contexts.
 */
typedef enum
{
    context_1 = 0,
} adc_context_t;

/**
 * @ingroup adc
 * @brief Initializes the ADC module. This routine must be called before other ADC APIs.
 * @param None.
 * @return None.
*/
void ADC_Initialize(void);

/**
 * @ingroup adc
 * @brief Selects an ADC context to perform read/write operations on context-specific registers.
 * @param context - Context to be selected. Refer to the @ref adc_context_t enum for the list of available contexts.
 * @return None.
*/
inline void ADC_SelectContext(adc_context_t context);

/**
 * @ingroup adc
 * @brief Includes a channel context in the scan sequence.
 *        Select the correct context using @ref ADC_SelectContext before calling this API.
 * @param context - Context which needs to be included in the scan. Refer to the @ref adc_context_t enum for the list of available contexts.
 * @return None.
*/
void ADC_EnableChannelScan(adc_context_t context);
 
/**
 * @ingroup adc
 * @brief Excludes a channel context from the scan sequence.
 *        Select the correct context using @ref ADC_SelectContext before calling this API.
 * @param context - Context which needs to be excluded from the scan. Refer to the @ref adc_context_t enum for the list of available contexts.
 * @return None.
*/
void ADC_DisableChannelScan(adc_context_t context);

/**
 * @ingroup adc
 * @brief Enables the ADC channel sequencer.
 *        Initialize the ADC module using @ref ADC_Initialize before calling this API.
 * @param None.
 * @return None.
*/
inline void ADC_EnableChannelSequencer(void);

/**
 * @ingroup adc
 * @brief Disables the ADC channel sequencer.
 *        Initialize the ADC module using @ref ADC_Initialize before calling this API.
 * @param None.
 * @return None.
*/
inline void ADC_DisableChannelSequencer(void);    

/**
 * @ingroup adc
 * @brief Sets the positive channel as per user selection
 * @pre Initialize the ADC with ADC_Initialize() before calling this API.
 * @param posChannel - Desired positive channel. Refer to the ADC_posChannel_t enum for the list of available positive channels.
 * @return None.
*/
inline void ADC_SetPositiveChannel(adc_posChannel_t posChannel);

/**
 * @ingroup adc
 * @brief Sets the negative channel as per user selection
 * @pre Initialize the ADC with ADC_Initialize() before calling this API.
 * @param negChannel - Desired negative channel. Refer to the ADC_negChannel_t enum for the list of available negative channels.
 * @return None.
*/
inline void ADC_SetNegativeChannel( adc_negChannel_t negChannel);

/**
 * @ingroup adc
 * @brief Discharges the input sample capacitor for the selected context by setting the channel to AVss.
 * Use @ref ADC_SelectContext to select the correct ADC context before calling this API.
 * @param None.
 * @return None.
*/
inline void ADC_DischargeSampleCapacitor(void); 

/**
 * @ingroup adc
 * @brief Starts the A/D conversion on the selected channels.
 * @param posChannel - Positive analog channel number on which the A/D conversion has to be applied.
 *                     Refer to adc_posChannel_t for the list of  available positive channels.
 * @param negChannel - Negative analog channel number on which the A/D conversion has to be applied.
 *                     Refer to adc_ngChannel_t for the list of available negative channels.
 * @return None.
*/
void ADC_StartConversionOnChannel(adc_posChannel_t posChannel,adc_negChannel_t negChannel);

/**
 * @ingroup adc
 * @brief Starts the A/D conversion on the selected channel.
 * @param None.
 * @return None.
*/
inline void ADC_StartConversion(void);

/**
 * @ingroup adc
 * @brief Stops the ongoing A/D conversion.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @return None.
*/
inline void ADC_StopConversion(void);

/**
 * @ingroup adc
 * @brief Checks if the ongoing A/D conversion is complete.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @retval True - Conversion is complete.
 * @retval False - Conversion is ongoing.
*/
inline bool ADC_IsConversionDone(void);

/**
 * @ingroup adc
 * @brief Retrieves the result of the latest A/D conversion.
 * @pre Call ADC_StartConversion() before calling this function and check the completion status using the ADC_IsConversionDone() API.
 * @param None.
 * @return The result of the A/D conversion. Refer to adc_result_t.
*/
inline adc_result_t ADC_GetConversionResult(void);

/**
 * @ingroup adc
 * @brief Retrieves the result of a single A/D conversion on the given channels in Differential mode.
 * @pre Call ADC_DisableContinuousConversion before calling this function.
 * @param posChannel - Positive analog channel on which the A/D conversion has to be applied.
 *                     Refer to adc_posChannel_t for the list of available positive channels.
 * @param negChannel - Negative analog channel on which the A/D conversion has to be applied.
 *                     Refer to adc_negChannel_t for the list of available negative channels.
 * @return The result of the A/D conversion. Refer to adc_result_t.
*/
adc_result_t ADC_GetSingleConversion(adc_posChannel_t posChannel,adc_negChannel_t negChannel);

/**
 * @ingroup adc
 * @brief Retrieves the ADC module cycle multi-stage status.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @return Contents of the ADC Status (ADSTAT) register.
*/
inline uint8_t ADC_GetConversionStageStatus(void);

/**
 * @ingroup adc
 * @brief Enables continuous conversion.
 * @param None.
 * @return None.
*/
inline void ADC_EnableContinuousConversion(void);

/**
 * @ingroup adc
 * @brief Disables continuous conversion.
 * @param None.
 * @return None.
*/
inline void ADC_DisableContinuousConversion(void);

/**
 * @ingroup adc
 * @brief Enables the Stop-on-Interrupt bit.
 * @pre Call ADC_EnableContinuousConversion() before calling this function.
 * @param None.
 * @return None.
*/
inline void ADC_SetStopOnInterrupt(void);

/**
 * @ingroup adc
 * @brief Enables the Double-Sample Enable bit.
 * @param None.
 * @return None.
*/
inline void ADC_EnableDoubleSampling(void);

/**
 * @ingroup adc
 * @brief Loads the ADC Acquisition Time Control (ADACQ) register with the specified value.
 * @param acquisitionValue - Value to be loaded in the ADC Acquisition Time Control register.
 * @return None.
*/
void ADC_SetAcquisitionRegister(uint16_t acquisitionValue);

/**
 * @ingroup adc
 * @brief Loads the ADC Precharge Time Control (ADPRE) register with the specified value.
 * @param prechargeTime - Value to be loaded in the ADC Precharge Time Control register.
 * @return None.
*/
void ADC_SetPrechargeRegister(uint16_t prechargeTime);

/**
 * @ingroup adc
 * @brief Sets the value of the ADC Threshold Setpoint (ADSTPT) register.
 * @param setPoint - 16-bit value for the ADC Threshold Setpoint register.
 * @return None.
*/
void ADC_DefineSetPoint(int16_t setPoint);
/**
 * @ingroup adc
 * @brief Sets the value of the ADC Upper Threshold (ADUTH) register.
 * @param upperThreshold - 16-bit value for the ADC Upper Threshold register.
 * @return None.
*/
void ADC_SetUpperThreshold(int16_t upperThreshold);

/**
 * @ingroup adc
 * @brief Sets the value of the ADC Lower Threshold (ADLTH) register.
 * @param lowerThreshold - 16-bit value for the ADC Lower Threshold register.
 * @return None.
*/
void ADC_SetLowerThreshold(int16_t lowerThreshold);
/**
 * @ingroup adc
 * @brief Determines if the ADC error is higher than the upper threshold.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @retval True - ADC error has crossed the upper threshold.
 * @retval False - ADC error has not crossed the upper threshold. 
*/
inline bool ADC_HasErrorCrossedUpperThreshold(void);

/**
 * @ingroup adc
 * @brief Determines if the ADC error is less than the lower threshold.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @retval True - ADC error is less than the lower threshold.
 * @retval False - ADC error is higher than the lower threshold.
*/
inline bool ADC_HasErrorCrossedLowerThreshold(void);

/**
 * @ingroup adc
 * @brief Loads the ADC Repeat Counter (ADCNT) with the specified value.
 * @param repeatCount - Value to be loaded to the ADC Repeat Counter register.
 * @return None.
*/
inline void ADC_SetRepeatCount(uint8_t repeatCount);

/**
 * @ingroup adc
 * @brief Retrieves the current value of the ADC Repeat Counter (ADCNT) register.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @return Current value of the ADC Repeat Counter register.
*/
inline uint8_t ADC_GetCurrentCountofConversions(void);

/**
 * @ingroup adc
 * @brief Retrieves a 24-bit value from the ADC accumulator.
 * @param None.
 * @return Value of the ADC accumulator.
*/
inline int24_t ADC_GetAccumulatorValue(void);
/**
 * @ingroup adc
 * @brief Clears the accumulator.
 * @param None.
 * @return None.
*/
inline void ADC_ClearAccumulator(void);

/**
 * @ingroup adc
 * @brief Determines if the ADC accumulator has overflowed.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @retval True - ADC accumulator has overflowed.
 * @retval False - ADC accumulator has not overflowed.
*/
inline bool ADC_HasAccumulatorOverflowed(void);

/**
 * @ingroup adc
 * @brief Retrieves the value of the ADC Setpoint Error (ADERR) register.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @return 16-bit value obtained from the high byte ADERR (ADERRH) and low byte ADERR (ADERRL) registers.
*/
inline int16_t ADC_GetErrorCalculation(void);

/**
 * @ingroup adc
 * @brief Retrieves the value of the ADC Previous Result (ADPREV) register.
 * @pre Call ADC_StartConversion() before calling this function.
 * @param None.
 * @return 16-bit value obtained from the high byte ADPREV (ADPREVH) and low byte ADPREV (ADPREVL) registers.
*/
inline int16_t ADC_GetPreviousResult(void);

/**
 * @ingroup adc
 * @brief Retrieves the value of the ADC Filter (ADFLTR) register.
 * @param None.
 * @return 16-bit value obtained from the high byte ADFLTR (ADFLTRH) and low byte ADFLTR (ADFLTRL) registers.
*/
inline int16_t ADC_GetFilterValue(void);





#endif //ADC_H
