#include "xc.h"
#include "joh19042_lab5_LCDlib_v002.h"


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
 * Prints a string whose size is greater than 8. Prints on both the bottom
 * and top of the lcd screen.
 * 
 * @param string
 * @param size
 */
void lcd_printStr_Scrolling(const char string[], int size){
    
    // first 8 characters of the string
    char temp[8];
    char temp1[8];
    
    int k;
    int j;
    int i;
    int x = 0, y = 0;
    
    while(1){
        
        // set temp to empty string
        for(j = 0; j < 8; j++){
            temp[j] = 0b00000010;
        }
        // set temp1 to empty string
        for(j = 0; j < 8; j++){
            temp1[j] = 0b00000010;
        }
        
        x = 0;
        y = 0;
        
        while(x < (2 * size)){
            TMR1 = 0;
            
            //print the 8 letters on top row
            lcd_printString(temp, 8, 0);
            //print the 8 letters on bottom row
            lcd_printString(temp1, 8, 1);
            
            while(_T1IF == 0); // wait for timer1 interrupt, this is a delay
            
            //shift to left
            for(i = 0; i < 7; i++){
                temp[i] = temp[i+1];
            }
            
            //if not end of string, get next character, otherwise a space
            if(x < size){
                temp[7] = string[x];//set it to next char in string[]]
            }
            else{
                temp[7] = 0b00000010;//set it to an empty space
            }
            
            x++;
            
            //shift bottom row ones to the left
            for(k = 0; k < 7; k++){
                temp1[k] = temp1[k+1];
            }
            
            //if not end of string, get next character, otherwise a space
            if(x > 8 && y < size){
                temp1[7] = string[y];
                y++;
            }
            else{
                temp1[7] = 0b00000010;
            }
            
            
            
        }
        
    }
    
}


/**
 * Prints a string whose size is less than or equal to 8.
 * 
 * @param string
 * @param size
 */
void lcd_printString(const char string[], int size, int row){
    int x = 0;
    int i = row;
    int j;
    
    for(j = 0; j < 8; j++){
        if(x < size){ // if still in string of characters
            // set the cursor to the next location
            lcd_set_cursor(i, j);
            // print the character at string[x]
            lcd_printChar(string[x]);
            // increment x
            x++;
        }
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
