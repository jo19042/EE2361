/* 
 * File:   joh19042_lab06_lcdLib_v001.h
 * Author: nacob
 *
 * Created on April 1, 2021, 3:19 PM
 */

#ifndef JOH19042_LAB06_LCDLIB_V001_H
#define	JOH19042_LAB06_LCDLIB_V001_H

#ifdef	__cplusplus
extern "C" {
#endif

void delay_ms(unsigned int ms);
void lcd_set_cursor(char y, char x);
void lcd_printString(const char string[], int row);
void lcd_init(void);
void lcd_cmd(char Package);
void lcd_printChar(char Package);
void lcd_printCharFinal(char Package);
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* JOH19042_LAB06_LCDLIB_V001_H */

