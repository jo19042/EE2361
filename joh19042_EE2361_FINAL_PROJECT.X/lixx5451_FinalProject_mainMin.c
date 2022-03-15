// Main file: For testing only! This is more to
// check the functionality of the LCD and buttons and make sure
// values are showing up correctly. Please reach out to me (Amanda)
// if you have any questions about any part regarding LCD display and 
// button toggling. 

#include "xc.h"
//#include "lixx5451_button.h"
#include "xc.h"
#include "lixx5451_button.h"
#include "lixx5451_i2cLCD.h"
#include "karam003_conversion_v001.h"
#include "joh19042_rotationsLib_v001.h"
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)
// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,
 // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void init_pic24(void)
{
    CLKDIVbits.RCDIV = 0; //Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16M
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
    
}


int main(void) {

    init_pic24();
    init_lcd(2);        // initialize SDA2/SCL2 for i2c lcd 
    init_buttons(8,9);  // initialize buttons 1 & 2 to RB8, RB9 respectively
    init_RPM();

    while(1)
    {    
        lcd_printMeasurements();  // continously display measurements based on the global keys telling what should be displayed.
      
        // Test assuming a 50cm radius wheel 
        convertVal (50, newRPM, 100); //setting proper vals to all the distance and speed char arrays (of different units) that could be printed to the LCD.

    }
    return 0;
}