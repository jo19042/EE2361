#include "xc.h"
#include "joh19042_lab06_adcLib_v001.h"
#include"joh19042_lab06_bufferLib_v001.h"

void __attribute__((__interrupt__, __auto_psv__)) _ADC1Interrupt(void){
    _AD1IF = 0; // reset timer1 interrupt flag bit
    // Should be a sample since there was an interrupt
    putVal(ADC1BUF0);
}


/**
 * Configures ADC and Timer3.
 */
void adc_init(){

    TRISAbits.TRISA0 = 1; // Setting AN0 to input
    
    AD1PCFGbits.PCFG0 = 0; // setup I/O - analog pin
    
    AD1CON2bits.VCFG = 0b00; // Use AVDD v(3.3V) and AVSS (0V) as max/min
    AD1CON3bits.ADCS = 0b1;  // Want TAD >= 75ms (Tcy = 62.5ns)
    AD1CON1bits.SSRC = 0b010;// Sample on Timer3 events
    AD1CON3bits.SAMC = 0b1; // 2 Auto-Sample Time bits
    AD1CON1bits.FORM = 0b00; /* data output form -- recommended unsigned int
                             * unsigned: 0V = 0b0000000000, 3.3V = 0b1111111111
                             * signed 0V = 0b1000000000, 3.3V = 0b0111111111
                             */
    AD1CON1bits.ASAM = 0b1;  // auto sample
    AD1CON2bits.SMPI = 0;    // Interrupt on every sample
    AD1CON1bits.ADON = 1;    // turn on the ADC
    
    _AD1IF = 0;              // clear IF for ADC
    _AD1IE = 1;              // enable interrupts for ADC
    
    TMR3 = 0;                // setup Timer3
    T3CON = 0;
    T3CONbits.TCKPS = 0b10;
    PR3 = 15624; // 1/16th of a second 15624
    T3CONbits.TON = 1;
    
    
}