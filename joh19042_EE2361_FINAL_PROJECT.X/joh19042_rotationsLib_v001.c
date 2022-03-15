#include "xc.h"
#include "joh19042_rotationsLib_v001.h"
#include "lixx5451_i2cLCD.h"

/*RPM will basically just be number of detections per minute. All I have to do
 is attach an input pin to an Input compare and interrupt everything something
 detected. I will then use a timer maybe every second that will calculate the 
 current rpm. I will have to scale this up so if I measure 5 detections in 1 
 second then */



//note: DC motors don't have RPM faster than 5000

//Number of rotations for this second
int rotations;

int totalrotations;
// the newRPM variable from the main function




/**
 * Initialization function to establish Timer5 and Input Compare for 
 */
void init_RPM(void){
    
    
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPINR8bits.IC3R = 7;  // Use Pin RP7 = "7", for Input Capture 1 (Table 10-2)
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    _IC3IP = 1;// Set module interrupt priority as 1
    
    IC3CON = 0; // Turn off and reset internal state of IC1
    IC3CONbits.ICTMR = 0; // Use Timer 3 for capture source
    IC3CONbits.ICM = 0b010; // Turn on and capture every rising edge
    
    //IC3 Configuration for IR Sensing
    _IC3IF = 0; // Clear the IC1 interrupt status flag
    _IC3IE = 1; // Enable IC1 interrupts

    
}





/**
 * Input Capture 3 Interrupt. Will occur every time the IR sensor detects,
 * increments rotations as this means there was a rotation.
 */
void __attribute__((__interrupt__, __auto_psv__)) _IC3Interrupt(void){
    _IC3IF = 0; // Reset interrupt flag or IC3
    totalrotations++; // increment number of rotations for the current second
    rotations++;
}
