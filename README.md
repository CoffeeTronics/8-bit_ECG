# 8-bit_ECG
This is the repo for low power PIC-Q71 ECG projects. 

ECG signals have both a positive and negative component (see ECG_anatomy.png). 
From left to right, the P-wave and PR segment are positive. The QRS complex consists of a negative Q-spike, a positive R-spike, a negative S-spike, then finally the T-wave.
To determine the heart rate, the R-R interval is measured and then the heart rate per minute can be calculated.

This project has 2 versions. 

# Version 1:
The first version reads the ECG signal with the integrated ADC, and uses the ADC peripherals derivative feature to determine the ADC error (adc_error), 
then squares it to remove negative component (adc_error_sq). This results in 2 peaks where the negative component squared results in a peak slightly 
smaller than the original positive R-spike. The squared result has the sqrt taken twice (adc_error_sq_sqrt_sqrt) to bring the result into an unsigned 
8-bit range so that levels can be compared using a DAC (Q-71 has 2x8-bit and 1x10-bit DAC). A threshold is set that is larger than the squared negative 
peak, but less than the squared positive peak. This could be problematic as the threshold from person to person may vary significantly.

# Version 2:
The second version also reads the ECG signal with the integrated ADC, and uses the ADC peripherals derivative feature to determine the ADC error (adc_error), 
if the value is less than 0, it is saved as 0. If it is positive, it is saved as the original value but cast as an uint8_t so that levels can be compared using 
a DAC (Q-71 has 2x8-bit and 1x10-bit DAC). A threshold is automatically determined by a defined ratio of the largest R-spike seen.  
***Note: This version does NOT use the computationally expensive sqrt twice.***
