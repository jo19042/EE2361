#include "xc.h"
#include <stdio.h>
#include <stdlib.h>

// DEFINE VARAIBLES
    double expectedRPM = 3000; // expected RPM, the goal
    double kp = 1; // Proportional Constant
    double ki = 1; // Integral constant
    double kd = 1; // Derivative constant
    double intErr; // integral error (ki + err)
    double dErr; // differential error (err - err previous)
    double dt; // the time for each sampling
    double prevErr = 0; // the last error, start it at 0
    double max = 3500; // max rpm
    double min = 0; // min rpm
    volatile double newRPM;


    /**
     * Initialization function for PID function of IR library.
     */
void init_PID(void){
    
    // CONFIG O/C for CONTINUOUS PWM SIGNAL
    TRISBbits.TRISB6 = 0; // RB6 set to output
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR3bits.RP6R = 18;  // Use Pin RP6 for Output Compare 1 = "18" (Table 10-3)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    OC1CON = 0; // Initialize all the bits in OC1CON to 0
    OC1CONbits.OCTSEL = 1; // Use timer3 as clock source, already initialized
    OC1CONbits.OCM = 6; // OC1 set to PWM mode
    
    // Timer setup: TMR3 for Button 2
    T5CON = 0;
    T5CONbits.TCKPS = 0b11; // 256 prescaler
    TMR5 = 0;
    PR5 = 6250 - 1;        // 100ms
    
    // Timer interrupts
    _T5IE = 1;  // enable interrupt
    _T5IF = 0;  // clear interrupt flag
    
    T5CONbits.TON = 1;      // turn on timer 5
    
}


/**
 * Calculates the next duty cycle increment using a PID algorithm and 
 * increments OC1RS by that value.
 * 
 * @param expectedRPM - the RPM we want to get to
 * @param actualRPM - the current RPM
 * @return - the new duty cycle
 */
void calculate(double expectedRPM, double actualRPM){
    
    // Calculate the error
    double err = expectedRPM - actualRPM;
    
    // Calculate the proportional term
    double p = kp * err;
    
    // Calculate Integral term
    intErr = err * dt; // Getting the integral error
    double i = ki * intErr;
    
    // Calculate derivative term
    dErr = (err - prevErr) / dt; // derivative of error calculation
    double d = kd * dErr;
    
    // Get the increment in RPM
    double output = p + i + d;
    
    // Get the next RPM 
    double target_rpm = abs(actualRPM + output);
    
    // Make sure target RPM is obtainable
    if(target_rpm > max)
        target_rpm = max;
    else if(target_rpm < min)
        target_rpm = min;
    
    // Keeping track of previous error for calculations.
    prevErr = err;
    
    // Return the duty cycle by mapping from target RPM to duty cycle percentage
    OC1RS = (int)(PR3 * (target_rpm / (max - min)));
    
}

/**
 * Timer5 Interrupt.
 */
void __attribute__((interrupt, auto_psv)) _T5Interrupt()
{    
    // Get a dt value in minutes using the following conversion
    dt = TMR5 * (double)(1 / 600);
    _T5IF = 0;
    // Call the PID calculate function with the expected rpm and the most
    // recent rpm value.
    calculate((double)expectedRPM, (double)newRPM);
}


/**
 * The main PID loop
 */
void PID_loop(){
    
    OC1RS = 0; // start PWM signal at 0% voltage
    
    /*
     * The goal within this loop is to get the motors RPM within a certain
     * error that we will have to tune manually before the presentation.
     * We do nothing while Timer5 interrupts continuously trigger and the PID
     * element is put into action.
     */
    while(1){
        
    }
    
}


