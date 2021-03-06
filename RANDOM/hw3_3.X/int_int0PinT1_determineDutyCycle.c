/*
 * File:   int_first-t1.c
 * Author: nacob
 *
 * Created on March 22, 2021, 5:34 PM
 */


#include <p24Fxxxx.h>
#include <xc.h>

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void setup(void)
{
    _RCDIV = 0; // make 16MHz

    T1CON = 0;
    T1CONbits.TCKPS = 0b11; // Prescaler 1 : 256
    PR1 = 65535; // Maximum # cycles

    IFS0bits.T1IF = 0; // Reset T1 Interrupt Flag
    IPC0bits.T1IP = 3; // Interrupt is priority 7 (highest priority)

    /* enable Timer 1 interrupt */
    IEC0bits.T1IE = 1;

    T1CONbits.TON = 1;
}


int main(void)
{
    
    setup();
    
    while(1){
        while(IFS0bits.T1IF == 0);
        IFS0bits.T1IF = 0;
    }
    
}