#include "xc.h"
#include "lixx5451_button.h"
#include "lixx5451_i2cLCD.h"

volatile unsigned long int tmr2_overflow = 0;   // for button 1
volatile unsigned long int tmr3_overflow = 0;   // for button 2

// Speed Unit Key:
// 0 = rpm
// 1 = mph
// 2 = m/s
// 3 = rad/s (angular speed)
volatile int speedUnitKey = 0; // default m/s

// Distance Unit Key:
// 4 = m
// 5 = km
// 6 = ft
// 7 = mi (miles)
volatile int distUnitKey = 4;  // default m

// Status of which button is pressed
volatile int button1pressed = 1;    // display speed (Button 1) - default
volatile int button2pressed = 0;    // ...or display distance (Button 2)


// --------------Button 1 config & interrupt setup----------------
// This function initializes Button 1, the button that toggles
// speed and speed units shown on the LCD screen. 
// Restrictions: Only PORTB bits (RB0-RB15) can be configured
// for the buttons since PORTB is the only register that has
// the RPx peripheral attached to them for input capture. Thus
// the function takes an integer x between 0 to 15 and configures
// RBx to Input Capture 1. Out of scope integers or wiring to an RA
// pin or wrong RB pin will do nothing and thus won't make the project work.
// NOTE: Please be aware that pins RB2 & RB3 are the SDA2 and SCL2 
// peripherals and the pins RB8 & RB9  are the SDA1 and
// SCL1 peripherals for the I2C LCD, so please make sure there isn't
// clashing between the button and the LCD pins when configuring them.
// (i.e. don't use RB2/RB3 for buttons if using SDA2/SCL2 for LCD config)
// Input: int (RB pin for Button 1, i.e. 8 is for RB8)
// Outputs: none
void init_button1(int button1_RBx_bit)
{
    // Bitmask to set the appropriate RB bit as input
    TRISB |= (1 << button1_RBx_bit); 
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC1R = button1_RBx_bit;      // Use inputted pin for Input Capture 1 (Table 10-2)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    
    T2CON = 0;
    T2CONbits.TCKPS = 0b11; // 256 prescaler
    TMR2 = 0;
    PR2 = 62500 - 1;        // 1s; prescaler = 256
    
    _T2IE = 1;  // enable interrupt
    _T2IF = 0;  // clear interrupt flag
    
    T2CONbits.TON = 1;      // turn on timer
    
    // Setup IC1
    IFS0bits.IC1IF = 0; // Clear the IC1 interrupt status flag
    IEC0bits.IC1IE = 1; // Enable IC1 interrupts

    IC1CON = 0; // Turn off and reset internal state of IC1
    IC1CONbits.ICTMR = 1; // Use Timer 2 for capture source
    IC1CONbits.ICM = 0b010; // Turn on and capture every falling edge
}

// This is the timer 2 interrupt, associated with Button 1. It
// tracks the number of overflows used to compute the period
// for the purposes of debouncing in the IC1 interrupt.
void __attribute__((interrupt, auto_psv)) _T2Interrupt()
{    
    _T2IF = 0;
    tmr2_overflow++;
}

// This is the interrupt for input capture 1 (button 1). This 
// interrupt handles debouncing and then toggles button 1, 
// which controls what speed units appear on the LCD screen.
// The order of units is: rpm -> mph -> m/s -> rad/s -> rpm -> mph -> ... etc.
void __attribute__((interrupt, auto_psv)) _IC1Interrupt(void)
{
    static unsigned long int prevEdge = 0;
    unsigned long int curEdge;
    
    _IC1IF = 0;
    curEdge = IC1BUF;
    curEdge = curEdge + ((long int)(PR2+1)*tmr2_overflow); // reads TMR2 value
        
    // Debounce ~200ms = 12500
    if (curEdge - prevEdge < 12500) {}   // do nothing
    
    else { 
        button1pressed = 1;
        button2pressed = 0;
    
        // Toggle distance units
        if (speedUnitKey == 3)
            speedUnitKey = 0;
        else speedUnitKey++;
        
        TMR2 = 0;
        tmr2_overflow = 0;
        curEdge = 0;
    }
    prevEdge = curEdge;
}


// -------------Button 2 config and interrupt setup-----------------
// This function initializes Button 2, the button that toggles
// distance and distance units shown on the LCD screen. 
// Restrictions: Only PORTB bits (RB0-RB15) can be configured
// for the buttons since PORTB is the only register that has
// the RPx peripheral attached to them for input capture. Thus
// the function takes an integer x between 0 to 15 and configures
// RBx to Input Capture 2. Out of scope integers or wiring to an RA
// pin or wrong RB pin will do nothing and thus won't make the project work.
// NOTE: Please be aware that pins RB2 & RB3 are the SDA2 and SCL2 
// peripherals and the pins RB8 & RB9  are the SDA1 and
// SCL1 peripherals for the I2C LCD, so please make sure there isn't
// clashing between the button and the LCD pins when configuring them.
// (i.e. don't use RB2/RB3 for buttons if using SDA2/SCL2 for LCD config)
// Inputs: int (the RB pin for Button 2, i.e. 8 is for RB8)
void init_button2(int button2_RBx_bit)
{
    // Bitmask to set the appropriate RB bit as input
    TRISB |= (1 << button2_RBx_bit); 
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR7bits.IC2R = button2_RBx_bit;      // Use inputted pin for Input Capture 2 (Table 10-2)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
    
    // Timer setup: TMR3 for Button 2
    T3CON = 0;
    T3CONbits.TCKPS = 0b11; // 256 prescaler
    TMR3 = 0;
    PR3 = 62500 - 1;        // 1s; prescaler = 256 (16M cycles/256=625k)
    
    // Timer interrupts
    _T3IE = 1;  // enable interrupt
    _T3IF = 0;  // clear interrupt flag
    
    T3CONbits.TON = 1;      // turn on timer
    
    
    // Setup IC2
    IFS0bits.IC2IF = 0; // Clear the IC2 interrupt status flag
    IEC0bits.IC2IE = 1; // Enable IC2 interrupts

    IC2CON = 0; // Turn off and reset internal state of IC2
    IC2CONbits.ICTMR = 0; // Use Timer 3 for capture source
    IC2CONbits.ICM = 0b010; // Turn on and capture every falling edge
}

// This is the interrpupt for timer 3, associated with button 
// 2 (distance and distance units). It tracks the number of 
// overflows used to compute the period for the purposes of
// debouncing in the IC2 interrupt.
void __attribute__((interrupt, auto_psv)) _T3Interrupt()
{    
    _T3IF = 0;
    tmr3_overflow++;
}

// This is the interrupt for input capture 2 (button 2). This 
// interrupt handles debouncing and then toggles button 2, 
// which controls what distance units appear on the LCD screen.
// The order of units is: m -> km -> ft -> mi -> m -> km -> ... etc.
void __attribute__((interrupt, auto_psv)) _IC2Interrupt(void)
{
    static unsigned long int prevEdge = 0;
    unsigned long int curEdge;
    
    _IC2IF = 0;
    curEdge = IC2BUF;
    curEdge = curEdge + ((long int)(PR3+1)*tmr3_overflow); 

    // Debouncing ~200ms = 12500
    if (curEdge - prevEdge > 12500)
    {
        button1pressed = 0;
        button2pressed = 1;
        
        // Toggle distance units
        if (distUnitKey == 7)
            distUnitKey = 4;
        else distUnitKey++;
        
        TMR3 = 0;
        tmr3_overflow = 0;
        curEdge = 0;        
    }
    prevEdge = curEdge;
}

// This function initialize both buttons at the same time.
// Restrictions: Only PORTB bits (RB0-RB15) can be configured
// for the buttons since PORTB is the only register that has
// the RPx peripheral attached to them for input capture. Thus
// this function takes two integers x and y, each between 0 to 15, 
// and configures RBx and RBy to Input Capture 1 and 2 respectively. 
// Out of scope integers or wiring to an RA pin or wrong/equal RB pin will 
// do nothing and thus won't make the project work.
// NOTE: Please be aware that pins RB2 & RB3 are the SDA2 and SCL2 
// peripherals and the pins RB8 & RB9  are the SDA1 and
// SCL1 peripherals for the I2C LCD, so please make sure there isn't
// clashing between the button and the LCD pins when configuring them.
// (i.e. don't use RB2/RB3 for buttons if using SDA2/SCL2 for LCD config)
// Inputs: int, int (RB pins for the two buttons, i.e. (8,9) initializes
// button 1 to RB8 and button 2 to RB9.
// Outputs: none
void init_buttons(int button1_RBx_bit, int button2_RBx_bit)
{
    // Enable pull-up resistors
    CNPU1 = 0xffff; 
    CNPU2 = 0xffff;
    
    init_button1(button1_RBx_bit);
    init_button2(button2_RBx_bit);
}