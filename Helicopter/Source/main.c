#include "main.h"

void main()
{
  hwSetUp();
  for(;;)
  {	
    Read_Flex();
    Read_Distance();
    delay_ms(200);
    temperature=readTemp(); 
    tempToString(temperature);
    sendData(sendString);
  }
}

/*
 * hwSetUp()
 *
 * Description: This function initiates the hardware: timer, UART and ADC
 *
 * Operation:   This function did the initialization for the hardware through the following steps: 
 *              1.Stop watch dog timer
 *	        2.set system master timer
 *		3.open port 4.7 as output for our power led
 *  		4.call uart set up function
 *              5.call timer initialization function
 *		6.call adc initialization function
 * Argument: none
 *
 * Return value: none
 *
 */
void hwSetUp(void) {
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  
  //setup DCO to 1MHZ
  BCSCTL1 = CALBC1_16MHZ;       
  DCOCTL = CALDCO_16MHZ; 
  P4DIR |= BIT7;                // Set 4.7 (Power LED) as output
  P4OUT |= BIT7;                // Set 4.7 high
  P1DIR |= BIT1 + BIT2 + BIT3;                
  P1OUT &= ~(BIT1 + BIT2 + BIT3);
  
  Setup_Timer();
  Setup_ADC();
  Setup_UART();
  //btConfig();
}

