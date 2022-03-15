/*
 * File:   joh1942_lab01_main_v001.c
 * Author: nacob
 *
 * Created on January 22, 2021, 2:47 PM
 */

#include "xc.h"

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


void setup(void){
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 1:2) 32 MHz changes maximum clock rate of PIC24 to 32MHz
    
    AD1PCFG = 0x9fff;            //sets all pins to digital I/O
    TRISA = 0b0000000000011111;  //set port A to inputs, 
    TRISB = 0b0000000000000011;  //and port B to outputs
    LATA = 0xffff;               //Set all of port A to HIGH
    LATB = 0xffff;               //and all of port B to HIGH
    
}

void delay(void) {
    unsigned int curCount = 0;
    
    while(curCount < 65000)
    {
        curCount++;
    }
    
}

int main(void) {

    int flip = 0xff;
    int masked = (flip ^= 0x80);
    
    //    setup(); 
//    LATB = 0x7FFF; //This will turn on the most significant LED
//    int x = 0 ;             
//    while(1) {
//        // Execute repeatedly forever and ever and ever and ever ...
//        while(x < 3){
//            delay(); //This pauses execution so the shifts are visible
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            LATB = LATB >> 1; //This shifts the LATB register
//            LATB |= 0x8000;
//            x++;
//        }
//        while(x > 0){
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            delay();
//            LATB = LATB << 1;
//            //LATB |= 0x8000;
//            x--;
//        }
        
//    }
//    return 0;
}


  
