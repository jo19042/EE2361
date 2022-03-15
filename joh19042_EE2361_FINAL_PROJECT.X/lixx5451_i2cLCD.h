/* 
 * File:   lixx5451_i2cLCD.h
 * Author: lixx5451
 *
 * Created on March 28, 2021, 12:23 PM
 */

#include "xc.h"

#ifndef LIXX5451_I2CLCD_H
#define	LIXX5451_I2CLCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    void init_lcd(int sda_scl_peripheral);
    void lcd_printMeasurements(void);
#ifdef	__cplusplus
}
#endif

#endif	/* LIXX5451_I2CLCD_H */

