/* 
 * File:   joh19042_lab5_Timerlib.h
 * Author: nacob
 *
 * Created on March 26, 2021, 12:24 PM
 */

#ifndef JOH19042_LAB5_TIMERLIB_H
#define	JOH19042_LAB5_TIMERLIB_H

#ifdef	__cplusplus
extern "C" {
#endif

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);

void initTimer(void);


#ifdef	__cplusplus
}
#endif

#endif	/* JOH19042_LAB5_TIMERLIB_H */

