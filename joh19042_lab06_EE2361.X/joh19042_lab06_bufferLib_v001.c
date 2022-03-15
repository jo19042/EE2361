#include "xc.h"
#include"joh19042_lab06_bufferLib_v001.h"

#define BUFSIZE 1024 // size of the buffer
#define NUMSAMPLES 128 // how many samples per second are gathereds

// Initialize the buffer to size BUFSIZE defined above
int adc_buffer[BUFSIZE];
// Initialize the index to the beginning of the buffer
int buffer_index = 0;


/**
 * Set all buffer entries to defualt values of 0;
 */
void initBuffer(){
    int i;
    for(i = 0; i < BUFSIZE; i++){
        adc_buffer[i] = 0;
    }
}

/**
 * Puts ADCvalue at buffer_index of adc_buffer.
 * 
 * @param ADCvalue - the value being put into the buffer
 */
void putVal(int ADCvalue){
    // set index i of buffer to ADCvalue
    adc_buffer[buffer_index++] = ADCvalue;
    // if it's the end of the buffer then reset the index to the beginning
    if(buffer_index >= BUFSIZE){
        buffer_index = 0;
    }
}

/**
 * Calculate the average voltage over the last 128 samples.
 * 
 * @return - average
 */
int getAvg(){
    long sum = 0;
    int i;
    
    if(buffer_index < NUMSAMPLES){
        // add the data after 0
        for(i = 0; i < buffer_index; i++){
            sum += adc_buffer[i];
        }
        // add the data before 1024
        for(i = BUFSIZE - 1 - (NUMSAMPLES - buffer_index); i < BUFSIZE; i++){
            sum += adc_buffer[i];
        }
    }
    else if(buffer_index >= NUMSAMPLES){
        for(i = buffer_index; i > buffer_index - NUMSAMPLES; i--){
            sum += adc_buffer[i];
        }
    }
   
    // return the average over 128 samples
    return (sum / NUMSAMPLES);
    
}