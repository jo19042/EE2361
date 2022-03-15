/* 
 * File:   joh19042_rotationsLib_v001.h
 * Author: nacob
 *
 * Created on March 28, 2021, 12:19 PM
 */

#include "xc.h"

#ifndef JOH19042_ROTATIONSLIB_V001_H
#define	JOH19042_ROTATIONSLIB_V001_H

#ifdef	__cplusplus
extern "C" {
#endif


    void __attribute__((__interrupt__, __auto_psv__)) _T5Interrupt();
    void __attribute__((__interrupt__, __auto_psv__)) _IC3Interrupt(void);
    void init_RPM(void);
    extern volatile double newRPM;


#ifdef	__cplusplus
}
#endif

#endif	/* JOH19042_ROTATIONSLIB_V001_H */

