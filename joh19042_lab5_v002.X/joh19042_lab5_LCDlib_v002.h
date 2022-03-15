/* 
 * File:   joh19042_lab5_LCDlib_v002.h
 * Author: nacob
 *
 * Created on March 19, 2021, 1:28 PM
 */

#ifndef JOH19042_LAB5_LCDLIB_V002_H
#define	JOH19042_LAB5_LCDLIB_V002_H

#ifdef	__cplusplus
extern "C" {
#endif

void delay_ms(unsigned int ms);
    
void lcd_init(void);

void lcd_printChar(char Package);

void lcd_printCharFinal(char Package);

void lcd_cmd(char Package);

void lcd_set_cursor(char x, char y);

void lcd_printString(const char string[], int size, int row);

void lcd_printStr_Scrolling(const char string[], int size);



#ifdef	__cplusplus
}
#endif

#endif	/* JOH19042_LAB5_LCDLIB_V002_H */

