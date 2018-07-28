/*
 * delay_ms()
 *
 * Description: This function delays the code by a given time
 *
 * Operation:   This function uses built-in delay cycle functions to delay certain time
 *              the clock is runing at 16Mhz so 1 ms is 16000 clock cycles
 * 
 * Argument: int ms, time in millsecond that will be delayed
 *
 * Return value: none
 *
 */
void delay_ms(int ms)
{
  while (ms--)
  {
    __delay_cycles(16000);
  }	
  
}

/*
 * delay_us()
 *
 * Description: This function delays the code by a given time
 *
 * Operation:   This function uses built-in delay cycle functions to delay certain time
 *              the clock is runing at 16Mhz so 1 us is 8 clock cycles
 * 
 * Argument: int us, time in microsecond that will be delayed
 *
 * Return value: none
 *
 */
void delay_us(int us)
{
  while (us--)
  {
    __delay_cycles(8);
  }	
  
}