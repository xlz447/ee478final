/* This library file is found online at www.karvn.in
 * the source code can be found here: http://karve.in/wp-content/uploads/2012/06/MSP430G2452_DS18B20.zip
 * Author is Ishan Karve, and the date is 01/26/2012
 */

#include "ishan.h"
#include <intrinsics.h>

void delay_ms(int ms)
{
	while (ms--)
	{
		__delay_cycles(16000); // set for 16Mhz change it to 1000 for 1 Mhz
	}	
	
}


void delay_us(int us)
{
	while (us--)
	{
		__delay_cycles(8); // set for 16Mhz change it to 1000 for 1 Mhz
	}	
	
}