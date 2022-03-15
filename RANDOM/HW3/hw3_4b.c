/*
 * File:   hw3_4b.c
 * Author: nacob
 *
 * Created on March 23, 2021, 3:10 PM
 */

#include <p24Fxxxx.h>
#include <xc.h>

// PIC24FJ64GA002 Configuration Bit Settings

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

// To test: Window > Simulator > Stimulus. Click on the Pin / Register Actions.
// Click on the top row where it says "Click here to add/remove signals", and add IC1
// (or RB6). Add entries that change the signal to 1 at time 1000, to zero at 1100, and so on.
// You may want to check the checkbox that says "Repeat from action".

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

void __attribute__((__interrupt__,__auto_psv__)) _IC1Interrupt(void)
{

    _IC1IF = 0; // reset interrupt flag bit

    *values[i++] = IC1BUF;
    TMR3 = 0;

}

void setup()
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;  // For digital I/O.  If you want to use analog, you'll
                       // need to change this.
    _TRISB6 = 1;
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    _IC1R = 6 ;   //IC! <- RB6; See Table 10-2 on P108 of the datasheet
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    T3CON = 0;
    PR3 = 65535;
    TMR3 = 0;
    _T3IF = 0;
    T3CON = 0x8000;

    IC1CON = 1; // every edge
    _IC1IF = 0;
    _IC1IE = 1;
}

int main(void)
{
    setup();

    while (1);

    return 0;
}
