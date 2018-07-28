
//#include <msp430.h>
// Global Variables
#include <msp430.h>
#include "flex_adc.h"

extern unsigned int distance;
/*
 * ADC10_ISR()
 *
 * Description: This function is the adc10 interrupt service routine
 *
 * Operation:   This function will be called after adc convertion finishes
 *              it will wake up the MCU from sleep mode
 *
 * Argument: none
 *
 * Return value: none
 *
 */
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

/*
 * Setup_ADC()
 *
 * Description: This function sets up the adc
 *
 * Operation:   This function sets up the adc by the following steps
 *              1. set analog enable to the pin that is passed in
 *              2. set adc10 control registor 1, for the corresponding channal, and clock speed
 *              3. set adc10 control registor 0, to turn on adc10, enable adc10 interrupt and set clock cycle
 *              4. set adc10 control regsitor 0, to start and enable adc conversion
 * 
 * Argument: none
 *
 * Return value: none
 *
 */
void Setup_ADC(void)
{               
  
  ADC10AE0 |= BIT0;
  ADC10CTL1 = INCH_0 + ADC10DIV_3;
  ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;
  
}
   
/*
 * Read_Distance()
 *
 * Description: This function reads the distance sensor values from the adc
 *
 * Operation:   This function reads the adc value by the following steps
 *              1. set adc10 control regsitor 0, to start and enable adc conversion
 *              2. turn MCU into low power mode with interrupts enabled
 *              3. after finishing the conversion, wake up MCU in ISR and copy data from ADC10MEM to veriable data
 * 
 * Argument: none
 *
 * Return value: none
 *
 */
void Read_Distance(void)
{
  ADC10CTL0 |= ENC + ADC10SC;			// Sampling and conversion start
  __bis_SR_register(CPUOFF + GIE);	        // Low Power Mode 0 with interrupts enabled
  distance = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value
}