/* 
 * File:   my_delays.h
 * Author: |H_e_c_t_o_r|
 *
 * Library to generate delays
 * 
 */

#ifndef MY_DELAYS_H
#define	MY_DELAYS_H
#include <xc.h>
#define _XTAL_FREQ 20000000 // Select your XTAL

void Delay_ms(unsigned int data_ms);
void Delay_us(unsigned int data_us);

void Delay_ms(unsigned int data_ms){
unsigned int data_ms1;
for(data_ms1 = 0; data_ms1 < data_ms; data_ms1++){
__delay_ms(1);
}
}

void Delay_us(unsigned int data_us){
unsigned int data_us1;
for(data_us1 = 0; data_us1 < data_us; data_us1++){
__delay_us(1);
}
}
#endif	/* MY_DELAYS_H */

