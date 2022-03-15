#include "xc.h"
#include <stdio.h>
#include "lixx5451_i2cLCD.h"
#include "lixx5451_button.h"

#define LCD_SCREEN_WIDTH 8

// Speed Measurements: default 0
char metPerSec[LCD_SCREEN_WIDTH] = "0.00";
char mph[LCD_SCREEN_WIDTH] = "0.00";
char rpm[LCD_SCREEN_WIDTH] = "0.00";
char radPerSec[LCD_SCREEN_WIDTH] = "0.00";

// Distance Measurements: default 0
char km[LCD_SCREEN_WIDTH] = "0.00";
char m[LCD_SCREEN_WIDTH] = "0.00";
char ft[LCD_SCREEN_WIDTH] = "0.00";
char mi[LCD_SCREEN_WIDTH] = "0.00";

extern int speedUnitKey;    // from lixx5451_button.c
extern int distUnitKey;     // from lixx5451_button.c 
extern int button1pressed;  // from lixx5451_button.c
extern int button2pressed;  // from lixx5451_button.c

int sda_scl_number;     // 1 for SDA1/SCL1, 2 for SDA2/SCL2

// This function is a basic delay function, in unit milliseconds.
// Input: unsigned int: duration in milliseconds for delay
// Output: none
void delay_ms(unsigned int ms)
{
    while(ms-- > 0) {
        asm("repeat #15998");
        asm("nop");
    }
}

// This function sets up the basic LCD command line that drives
// the I2C bus, depending on which SDAx/SCLx is used (1 or 2). The 
// function implements the I2C communication standard and the  
// command by writing the data (Package) to the LCD.
// Inputs: char Package: data byte
// Output: none
void lcd_cmd(char Command)
{
    if (sda_scl_number == 1)    // Use SDA1/SCL1
    {
        I2C1CONbits.SEN = 1;         // Initiate Start condition
        IFS1bits.MI2C1IF = 0;        // Clear flag

        while(I2C1CONbits.SEN == 1);  // Wait for SEN == 0. SEN will clear when Start Bit is complete
        IFS1bits.MI2C1IF = 0;        // Clear flag
        // Send address and write (R/nw = 0) command
        I2C1TRN = 0b01111100;       // 8-bits consisting of the slave address and the R/nW bit

        while (IFS1bits.MI2C1IF == 0);
        IFS1bits.MI2C1IF = 0;
        // Send high byte
        I2C1TRN = 0b00000000;       // 8-bits consisting of control byte, always 0x00

        while (IFS1bits.MI2C1IF == 0);
        IFS1bits.MI2C1IF = 0;
        // send Command byte
        I2C1TRN = Command;          // 8-bits consisting of the data byte

        while (IFS1bits.MI2C1IF == 0);
        IFS1bits.MI2C1IF = 0;
        // Send stop
        I2C1CONbits.PEN = 1;
        while(I2C1CONbits.PEN == 1); // PEN will clear when Stop bit is complete
    }
    
    else    // Use SDA2/SCL2
    {
        I2C2CONbits.SEN = 1;         // Initiate Start condition
        IFS3bits.MI2C2IF = 0;        // Clear flag

        while(I2C2CONbits.SEN == 1);  // Wait for SEN == 0. SEN will clear when Start Bit is complete
        IFS3bits.MI2C2IF = 0;        // Clear flag
        // Send address and write (R/nw = 0) command
        I2C2TRN = 0b01111100;       // 8-bits consisting of the slave address and the R/nW bit

        while (IFS3bits.MI2C2IF == 0);
        IFS3bits.MI2C2IF = 0;
        // Send high byte
        I2C2TRN = 0b00000000;       // 8-bits consisting of control byte, always 0x00

        while (IFS3bits.MI2C2IF == 0);
        IFS3bits.MI2C2IF = 0;
        // send Command byte
        I2C2TRN = Command;          // 8-bits consisting of the data byte

        while (IFS3bits.MI2C2IF == 0);
        IFS3bits.MI2C2IF = 0;
        // Send stop
        I2C2CONbits.PEN = 1;
        while(I2C2CONbits.PEN == 1); // PEN will clear when Stop bit is complete
    }
}

// This function initializes the LCD in accordance with its data sheet.
// This function takes in either an integer either 1 or 2 to specify which 
// SDA/SCL pins (SDA1 and SCL1, or SDA2 and SCL2) the user desires.
// Out of scope integers will default to SDA2 and SCL2, but if the hardware
// is not properly wired to those pins (RB2 and RB3), project will not work.
// Restrictions: The pins RB2 & RB3 are the SDA2 and SCL2 
// peripherals and the pins RB8 & RB9  are the SDA1 and
// SCL1 peripherals for the I2C LCD, so please ensure no clashing
// exists between the button and the LCD pins when configuring them.
// (i.e. don't use RB2/RB3 for buttons if using SDA2/SCL2 for LCD config)
// Input: int (1 or 2 depending on which SDAx/SCLx pins used)
// Outputs: none
void init_lcd(int sda_scl_peripheral)
{
    sda_scl_number = sda_scl_peripheral;
    
    if (sda_scl_peripheral == 1)    // Use I2C1 (SDA1 & SCL1)
    {
        I2C1CONbits.I2CEN = 0;
        I2C1BRG = 0x009D;       // Baud Rate: I2C2BRG = 157 = 0x009D
        IFS1bits.MI2C1IF = 0;   // Clear interrupt flag
        I2C1CONbits.I2CEN = 1;  // Enable I2C mode
    }
    
    else  // Use I2C2 (SDA2 & SCL2)
    {
        I2C2CONbits.I2CEN = 0;
        I2C2BRG = 0x009D;       // Baud Rate: I2C2BRG = 157 = 0x009D
        IFS3bits.MI2C2IF = 0;   // Clear interrupt flag
        I2C2CONbits.I2CEN = 1;  // Enable I2C mode
    }
    
    delay_ms(40);
    
    lcd_cmd(0b00111000);    // function set, normal instruction mode
    lcd_cmd(0b00111001);    // function set, extended instruction mode
    lcd_cmd(0b00010100);    // interval osc
    lcd_cmd(0b01110000);    // contrast C3-C0
    lcd_cmd(0b01011110);    // Ion, Bon, C5-C4
    lcd_cmd(0b01101100);    // follower control
    
    delay_ms(200);
    
    lcd_cmd(0b00111000);    // function set, normal instruction mode
    lcd_cmd(0b00001100);    // Display On
    lcd_cmd(0b00000001);    // Clear Display
    
    delay_ms(2);
}

// This function sets the LCD cursor to write at
// location column x, row y on the 2x8 LCD screen.
// Inputs: char, char (column, row cursor coordinate)
// Output: none
void lcd_setCursor(char x, char y)
{   
    char ddramAdr = (0x40*y) + x;           // equation to set coordinates
    char ddramCmd = ddramAdr | 0b10000000;  // MSB = 1 for instruction code
    
    lcd_cmd(ddramCmd);
}

// This function prints a string of characters. The string will
// truncate its row if it overflows past the 8-column screen,
// unless the string is greater than 40 characters, in which
// case it will wrap onto the second line.
// Input: const char s[]: The string to be printed, i.e. ?Hello?
// Output: none
void lcd_printStr(const char s[]) 
{
    char ctrlByte = 0b11000000;  // control byte - multiple writes
    int i = 0; //index

    if (sda_scl_number == 1) // Use SDA1/SCL1
    {
        // Start
        I2C1CONbits.SEN = 1; 
        IFS1bits.MI2C1IF = 0; 

        while(I2C1CONbits.SEN == 1);  
        IFS1bits.MI2C1IF = 0;
        // Send address and write (R/nw = 0) command
        I2C1TRN = 0b01111100; 

        // Parse through string
        while(s[i] != '\0')     // pointer reaches null once end of string reached
        {
            if (i+1 == '\0')    // Reached the last char in string
                ctrlByte = 0b01000000;

            while (IFS1bits.MI2C1IF == 0);
            IFS1bits.MI2C1IF = 0;
            // Send control byte
            I2C1TRN = ctrlByte;  

            while (IFS1bits.MI2C1IF == 0);
            IFS1bits.MI2C1IF = 0;
            // send myChar byte
            I2C1TRN = s[i]; 

            i++;
        }

        // Stop
        I2C1CONbits.PEN = 1;
        while(I2C1CONbits.PEN == 1);
    }
    
    else // Use SDA2/SCL2
    {
        // Start
        I2C2CONbits.SEN = 1; 
        IFS3bits.MI2C2IF = 0; 

        while(I2C2CONbits.SEN == 1);  
        IFS3bits.MI2C2IF = 0;
        // Send address and write (R/nw = 0) command
        I2C2TRN = 0b01111100; 

        // Parse through string
        while(s[i] != '\0')     // pointer reaches null once end of string reached
        {
            if (i+1 == '\0')    // Reached the last char in string
                ctrlByte = 0b01000000;

            while (IFS3bits.MI2C2IF == 0);
            IFS3bits.MI2C2IF = 0;
            // Send control byte
            I2C2TRN = ctrlByte;  

            while (IFS3bits.MI2C2IF == 0);
            IFS3bits.MI2C2IF = 0;
            // send myChar byte
            I2C2TRN = s[i]; 

            i++;
        }

        // Stop
        I2C2CONbits.PEN = 1;
        while(I2C2CONbits.PEN == 1);
    }
}

// This function continuously prints the current measurement 
// of the tachometer on the LCD, depending on the current  
// state of each of the two buttons. If Button 1 is pressed, 
// the speed will be displayed. If Button 2 is pressed, the
// distance will be displayed. Subsequent button clicks
// of each button will toggle among its respective units.
// Inputs: none
// Outputs: none
void lcd_printMeasurements()
{
    lcd_setCursor(0, 0);
    
    if (button1pressed) {
        // Print speed and speed units
        switch(speedUnitKey)
        {
            case 0:
                lcd_printStr(rpm);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("  rpm");
                break;
            case 1:
                lcd_printStr(mph);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("  mph");
                break;
            case 2:
                lcd_printStr(metPerSec);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("  m/s");
                break;
            case 3:
                lcd_printStr(radPerSec);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("rad/s");
                break;
            default:
                lcd_printStr(metPerSec);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("  m/s");
                break;
        }
    }
    
    else {  // button 2 pressed
        // Print distance and distance units
        switch(distUnitKey)
        {
            case 4:
                lcd_printStr(km);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("   km");
                break;
            case 5:
                lcd_printStr(m);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("    m");
                break;
            case 6:
                lcd_printStr(ft);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("   ft");
                break;
            case 7:
                lcd_printStr(mi);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("   mi");
                break;
            default:
                lcd_printStr(km);
                lcd_printStr("        ");
                lcd_setCursor(3, 1);
                lcd_printStr("   km");
                break;
        }
    }
}