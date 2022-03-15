/* 
 * File:   joh19042_lab06_adcLib_v001.h
 * Author: nacob
 *
 * Created on April 1, 2021, 2:47 PM
 */

#ifndef JOH19042_LAB06_ADCLIB_V001_H
#define	JOH19042_LAB06_ADCLIB_V001_H

#ifdef	__cplusplus
extern "C" {
#endif

void adc_init();
void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* JOH19042_LAB06_ADCLIB_V001_H */

