#include "lixx5451_i2cLCD.h"
#include "xc.h"
#include <stdio.h>


const float m2f = 3.2808;               // meters to feet
const float tpi = 6.283185307;          // 2*pi
const unsigned short mi2m = 1609.344;   // miles to meters
const unsigned int mi2f = 5280;         // miles to feet

extern char metPerSec[];   
extern char mph[];         
extern char rpm[];          
extern char radPerSec[];    
extern char km[];          
extern char m[];           
extern char ft[];           
extern char mi[];        


// This function takes in the radius in cm, the current value of 
// rpm, and the current running number of revolutions and calculates  
// values required for the LCD functions and updates them.
// Inputs: double radius_in_cm, double rpm_new, double rev
// Outputs: none
void convertVal(double radius_in_cm, double rpm_new, double rev){
    // Distance conversions
    double new_m = (rev*radius_in_cm)/100;
    double new_km = new_m/1000;
    double new_ft = new_m*m2f;
    double new_mi = new_ft/mi2f;

    // Speed conversions
    double new_radps = rpm_new/60 * tpi;                // I think this is correct?
    double new_metps = new_radps*(radius_in_cm/100);    // changed too...please check
    double new_mph = (3600*new_metps)/mi2m; 

    // Update all values
    sprintf(km, "%.2f", new_km);
    sprintf(m, "%.2f", new_m);
    sprintf(ft, "%.2f", new_ft);
    sprintf(mi, "%.2f", new_mi);

    sprintf(rpm, "%.2f", rpm_new);
    sprintf(radPerSec, "%.2f", new_radps);
    sprintf(metPerSec, "%.2f", new_metps);
    sprintf(mph, "%.2f", new_mph);
}