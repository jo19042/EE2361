/*
 * File:   joh19042_lab5_main.c
 * Author: nacob
 *
 * Created on March 19, 2021, 1:31 PM
 */

#include "xc.h"
#include "joh19042_lab5_LCDlib_v002.h"
#include "joh19042_lab5_Timerlib.h"


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


/*
 * Sets up main clock frequency and configures all pins to digital.
 */
void pic24_init(){
    _RCDIV = 0; // Set frequency to 16 MHz
    AD1PCFG = 0xffff; // Set all pins to digital
}


/*
 * The main function of lab05.
 */
int main(void){
    pic24_init(); // Initialize the pic24
    lcd_init(); // Initialize the LCD screen for future use
    initTimer(); // initialize the timer
    
    // string of characters 
    char string[] = "Hello World!";
    // find size of characters
    int size = sizeof(string);
    
    lcd_printStr_Scrolling(string, size);
    
    while(1);
    
    return 0;
}