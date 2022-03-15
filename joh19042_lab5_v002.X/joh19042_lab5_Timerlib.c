/*
 * File:   joh19042_lab5_main.c
 * Author: nacob
 *
 * Created on March 19, 2021, 1:31 PM
 */

#include "xc.h"
#include "joh19042_lab5_Timerlib.h"

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void){
    _T1IF = 0; // reset timer1 interrupt flag bit
    
}

void initTimer(void){
    
    T1CON = 0; // Initialize all bits in Timer1 Control Register to 0
    
    T1CONbits.TCKPS = 0b11; // pre scalar to 256
    
    PR1 = 12500;
    TMR1 = 0; // Initialize Timer1 value to 0
    
    _T1IF = 0; // set interrupt flag to unset
    _T1IE = 1; // enable timer1 interrupt
    
    T1CONbits.TON = 1; // Enable Timer1, basically turn it on and start counting
   
}