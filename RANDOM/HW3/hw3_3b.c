/*
 * File:   hw3_3b.c
 * Author: nacob
 *
 * Created on March 23, 2021, 3:10 PM
 */

#include <p24Fxxxx.h>
#include <xc.h>

// PIC24FJ64GA002 Configuration Bit Settings
// 'C' source line config statements

// CONFIG2
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled)
#pragma config I2C1SEL = PRI            // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF            // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = OFF           // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as CLKO (FOSC/2))
#pragma config FCKSM = CSECME           // Clock Switching and Monitor (Clock switching is enabled, Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL           // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
#pragma config SOSCSEL = SOSC           // Sec Oscillator Select (Default Secondary Oscillator (SOSC))
#pragma config WUTSEL = LEG             // Wake-up timer Select (Legacy Wake-up Timer)
#pragma config IESO = ON                // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)

// CONFIG1
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler (1:32,768)
#pragma config FWPSA = PR128            // WDT Prescaler (Prescaler ratio of 1:128)
#pragma config WINDIS = ON              // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config ICS = PGx1               // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config GWRP = OFF               // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF                // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)

// This program measures the duty cycle (i.e., duration of a signal being 1) in
// terms of num cycles.
// INT0 pin has the external sig. T1 counts #cycles.
// Both programmed as interrupts.

unsigned int high, low, high2, low2, ignoreThisVariable;
volatile int i = 0; // keep track of index in values[]

// an array of pointers to the highs and lows.
unsigned int *values[]={
    &ignoreThisVariable,
    &high,
    &low,
    &high2,
    &low2
};

void __attribute__((__interrupt__,__auto_psv__)) _INT0Interrupt(void)
{
    _INT0IF = 0; // reset interrupt flag bit
    _INT0EP = 1 - _INT0EP; // alternate between rising and falling edges.

    *values[i] = TMR1;
    TMR1 = 0;

    i++;
}

void setup(void)
{
    CLKDIVbits.RCDIV = 0; // make 16MHz
    // setup INT0 (RB7) pin as input
    AD1PCFG = 0x9fff;
    LATBbits.LATB7 = 1;

    T1CON = 0;
    PR1 = 15999;
    TMR1 = 0;
    T1CONbits.TON = 1;

    _INT0EP = 0;
    _INT0IF = 0;
    _INT0IE = 1;

}


int main(void)
{
    setup();

    //only interrupt until low2 is set to something.
    while (1);

    return 0;
}
