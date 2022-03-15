#include "xc.h"
#include <stdio.h>
#include "joh19042_lab06_lcdLib_v001.h"
#include"joh19042_lab06_bufferLib_v001.h"

char dataStr[8];
unsigned int data;

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void){
    _T1IF = 0; // reset timer1 interrupt flag bit
    data = getAvg();
    sprintf(dataStr, "%6.4f V", (3.3 * data) / 1024);
    lcd_printString(dataStr, 0);
}

/*
 * Delays for ms milliseconds. Uses asm code to do so.
 */
void delay_ms(unsigned int ms){
    while(ms-- > 0){
        // Repeat no operation 16000 times
        asm("repeat #15998");
        asm("nop");
    }
}

/**
 * Sets the cursor to the next location on the LCD screen.
 * 
 * @param x - the x location of the address
 * @param y - the y location of the address
 */
void lcd_set_cursor(char y, char x){
    lcd_cmd(0x80 + (0x40 * (y)) + (x));
}


/**
 * Prints a string whose size is less than or equal to 8.
 * 
 * @param string - list of characters to be printed
 * @param size - size of the string to be printed
 * @param row - which row to be printed on
 */
void lcd_printString(const char string[], int row){
    int i = row;
    int j;
    
    for(j = 0; j < 8; j++){
        // set the cursor to the next location
        lcd_set_cursor(i, j);
        // print the character at string[x]
        lcd_printChar(string[j]);
    }
}


/**
 * Initializes I2C for the LCD and then the LCD itself.
 */
void lcd_init(void){
    I2C2BRG = 0x9D; // set to a clock frequency of 100 MHz
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    I2C2CONbits.I2CEN = 1; // Enable I2C Mode
    
    delay_ms(40);
    
    lcd_cmd(0b00111000); // function set
    lcd_cmd(0b00111001); // function set, advance instruction mode
    lcd_cmd(0b00010100); // interval OSC
    lcd_cmd(0b01110000); // contrast low
    lcd_cmd(0b01010110);
    lcd_cmd(0b01101100); // follower control
    
    delay_ms(200);
    
    lcd_cmd(0b00111000); // function set
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    
    delay_ms(1);
    
    // Setup Timer1
    TMR1 = 0; // reset timer
    T1CON = 0; // set control register to 0
    T1CONbits.TCKPS = 0b10; // Set pre-scalar to 1:64
    PR1 = 24999; // Period 1 set to 100 ms
    
    _T1IF = 0; // Reset timer1 interrupt flag
    _T1IE = 1; // Enable timer1 interrupt
    
    T1CONbits.TON = 1; // start timer 1
}


/**
 * This sends a command sequence to the I2C protocol defined in the setup func.
 * 
 * @param Package - the data byte to be sent to I2C protocol
 */
void lcd_cmd(char Package){
    // Send START
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    I2C2CONbits.SEN = 1; // Initialize the send command
    // Once .SEN == 0, the start sequence has completed, wait until then
    while(I2C2CONbits.SEN == 1);
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    // Send Address and Write Command
    I2C2TRN = 0b01111100; // 8-bits consisting of slave address and R/nW bit
    while(IFS3bits.MI2C2IF == 0); // wait for interrupt flag
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    
    // Send high byte (always 0x00)
    I2C2TRN = 0x0000; // Address High Byte
    while(IFS3bits.MI2C2IF == 0); // wait for interrupt flag
    IFS3bits.MI2C2IF = 0; // clear interrupt flag
    
    // Send Package
    I2C2TRN = Package;
    while(IFS3bits.MI2C2IF == 0); // wait for interrupt flag
    IFS3bits.MI2C2IF = 0; // clear interrupt flag
    
    // Send STOP
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN == 1); // PEN will clear when stop bit is complete
}


/**
 * Outputs a character to the LCD screen. THis will be used to output all
 * characters in a sequence except the final bit. Hence, in control bit, RS = 1
 * and CO = 1;
 * 
 * @param Package - the character to be output to the LCD screen.
 */
void lcd_printChar(char Package){
    // Send START
    I2C2CONbits.SEN = 1; // set SEN bit to 1
    while(I2C2CONbits.SEN == 1); // SEN clears upon completion of instruction
    
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    I2C2TRN = 0b01111100; // 8-bits consisting of slave address & R/nW bit
    while(IFS3bits.MI2C2IF == 0); // until acknowledgment
    
    IFS3bits.MI2C2IF = 0; // reset interrupt flag
    I2C2TRN = 0b11000000; // control byte with RS = 1, CO = 1
    while(IFS3bits.MI2C2IF == 0); // wait for acknowledgment
    
    IFS3bits.MI2C2IF = 0; // reset interrupt flag
    I2C2TRN = Package; // send character
    while(IFS3bits.MI2C2IF == 0); // wait for acknowledgment
    
    // Send STOP
    I2C2CONbits.PEN = 1; // set PEN bit to 1
    while(I2C2CONbits.PEN == 1); // wait for interrupt flag cleared
}


/**
 * Outputs a character to the LCD screen. This will be used to output the final
 * character as RS = 1 and CO = 0.
 * 
 * @param Package - the character to be output to the LCD screen
 */
void lcd_printCharFinal(char Package){
    // Send START
    I2C2CONbits.SEN = 1; // set SEN bit to 1
    while(I2C2CONbits.SEN == 1); // SEN clears upon completion of instruction
    
    IFS3bits.MI2C2IF = 0; // Clear interrupt flag
    I2C2TRN = 0b01111100; // 8-bits consisting of slave address & R/nW bit
    while(IFS3bits.MI2C2IF == 0); // until acknowledgment
    
    IFS3bits.MI2C2IF = 0; // reset interrupt flag
    I2C2TRN = 0b01000000; // control byte with RS=1
    while(IFS3bits.MI2C2IF == 0); // wait for acknowledgment
    
    IFS3bits.MI2C2IF = 0; // reset interrupt flag
    I2C2TRN = Package; // send character
    while(IFS3bits.MI2C2IF == 0); // wait for acknowledgment
    
    // Send STOP
    I2C2CONbits.PEN = 1; // set PEN bit to 1
    while(I2C2CONbits.PEN == 1); // wait for interrupt flag cleared
}

