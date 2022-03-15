/* 
 * File:   joh19042_PIDLib_v001.h
 * Author: nacob
 *
 * Created on April 19, 2021, 4:01 PM
 */

#ifndef JOH19042_PIDLIB_V001_H
#define	JOH19042_PIDLIB_V001_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    extern volatile double newRPM;

    void init_PID(void);

    void __attribute__((interrupt, auto_psv)) _T5Interrupt();

    void PID_loop();

    void calculate(double expectedRPM, double actualRPM);


#ifdef	__cplusplus
}
#endif

#endif	/* JOH19042_PIDLIB_V001_H */

