/*
 * File:   disc08_UART.c
 * Author: joh19042
 *
 * Created on April 13, 2021, 8:10 AM
 */


#include <p24Fxxxx.h>
#include <xc.h>
#include <stdlib.h>

// PIC24FJ64GA002 Configuration Bit Settings
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled. 
					// Primary Oscillator refers to an external osc connected to the OSC1 and OSC2 pins)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // OSC2/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

// Q is T, so the code is offset by 3
#define offSet 3

volatile unsigned char buffer[64]; //64 byte buffer
volatile unsigned char front = 0; //pointers to front
volatile unsigned char back = 0; // pointer to back

// U1RXIF is set
void __attribute__((__interrupt__,__auto_psv__)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0;
    buffer[front++] = U1RXREG;
    front &= 63;
}

// Transmit stuff; wait until U1TXIF is set (ready to be written to))
void PPutch(const unsigned char c)
{
    while (!IFS0bits.U1TXIF) ;
    IFS0bits.U1TXIF = 0;
    U1TXREG = c;
}

// Get stuff from input
unsigned char PGetch(void)
{
    unsigned char x;

    while (front == back) ;
    x = buffer[back++];
    back &= 63;
    return x;
}


void setup(void)
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;  // For digital I/O.
    
    // I think the following two lines are irrelevant. The UART doc
    // Page 3, when describing the UARTEN bit in UxMODE says that when UARTEN
    // is set, TRISx are ignored and instead UEN and UTXEN control pins.
    _TRISB6 = 0;  // U1TX output
    _TRISB10 = 1; // U1RX input

    U1MODE = 0;  // UEN<1:0> bits control the pins
    // U1BRG = 34; // 115200 baud,
    // U1MODEbits.BRGH = 1;
    U1MODEbits.BRGH = 0;
    U1BRG = 25; // 38400 baud (check the calculation with the datasheet)
    U1MODEbits.UEN = 0;
    U1MODEbits.UARTEN = 1; // Enables receiving
    U1STAbits.UTXEN = 1; // Enables transmitting

    // Peripheral Pin Select 
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    _RP6R = 0x0003;   //RB6->UART1:U1TX; See Table 10-3 on P109 of the datasheet
    _U1RXR = 10;   //RB10->UART1:U1RX;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    IFS0bits.U1RXIF = 0;
    IEC0bits.U1RXIE = 1;
}

int main(int argc, char *argv[])
{

    setup();

    int i;

    // waste some time
    for (i = 0; i < 30000; i++) i = i;

    // This is where we receive
    while (1)
    {
        unsigned int x;
        //get the letters from the input file
        x = PGetch();
        // if it's before xyz and after a, add 3
        if (x >= 'A' && x <= 'Z' - offSet)
            x += offSet;
        else if (x > 'Z' - offSet)
            x -= 26 - offSet;
        PPutch(x);

            
        
    }

    return 0; // never reached (we hope)
}
