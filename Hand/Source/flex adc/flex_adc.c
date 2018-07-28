#include "flex_adc.h"

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
 * flexTrigger()
 *
 * Description: This function reads the 5 flex sensor values and determines the triggers
 *
 * Operation:   This function first checks the 5 flex values one by one with a delay of 500us by calling readflex method
 *              because we need to wait until the conversion of the adc finishes then read the
 *              next one. After all the data has been taken, this function will determine each trigger
 *              base on the flex data and the threshold.
 *              At the end, this funtion will call a sent trigger funtion, which will sent the triggers
 *              to helicopter via bluetooth.
 * Argument: none
 *
 * Return value: none
 *
 */
void flexTrigger(void) {
  flex1 = readFlex(INCH_15, BIT15); //reading each sensor
  delay_us(500);
  flex2 = readFlex(INCH_6, BIT6);
  delay_us(500);
  flex3 = readFlex(INCH_7, BIT7);
  delay_us(500);
  flex4 = readFlex(INCH_3, BIT3);
  delay_us(500);
  flex5 = readFlex(INCH_4, BIT4);
  delay_us(500);
  
  //determining tiggers
  if (flex1 > 20 && flex1 < 100) {
    trigger[0] = 1 + '0';
  } else {
    trigger[0] = 0 + '0';
  }
  if (flex2 > 20 && flex2 < 100) {
    trigger[1] = 1 + '0';
  } else {
    trigger[1] = 0 + '0';
  }
  if (flex3 > 20 && flex3 < 100) {
    trigger[2] = 1 + '0';
  } else {
    trigger[2] = 0 + '0';
  }
  if (flex4 > 20 && flex4 < 50) {
    trigger[3] = 1 + '0';
  } else {
    trigger[3] = 0 + '0';
  }
  if (flex5 > 20 && flex5 < 100) {
    trigger[4] = 1 + '0';
  } else {
    trigger[4] = 0 + '0';
  }
  trigger[5] = '\0';
  sendString(trigger);  //sending to helicopter
}


/*
 * readFlex()
 *
 * Description: This function reads the flex sensor values from the given adc channel and
 *              returns the convered numeric value
 *
 * Operation:   This function reads the adc value by the following steps
 *              1. set analog enable to the pin that is passed in
 *              2. set adc10 control registor 1, for the corresponding channal, and clock speed
 *              3. set adc10 control registor 0, to turn on adc10, enable adc10 interrupt and set clock cycle
 *              4. set adc10 control regsitor 0, to start and enable adc conversion
 *              5. turn MCU into low power mode with interrupts enabled
 *              6. after finishing the conversion, wake up MCU in ISR and copy data from ADC10MEM to veriable data
 *              7. disable adc10 conversion
 *              8. return acquired data.
 * 
 * Argument: int channel, the channel that data is coming from
 *           int bit, the pin number of that channel
 *
 * Return value: int data, the converted numerical value of the adc of the given channel
 *
 */
int readFlex(unsigned int channel, unsigned int bit) {
      int data = 0;
      ADC10AE0 |= bit;
      ADC10CTL1 = channel + ADC10DIV_3;
      ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;
      ADC10CTL0 |= ENC + ADC10SC;	        // Sampling and conversion start
      __bis_SR_register(CPUOFF + GIE);	        // Low Power Mode 0 with interrupts enabled
      data = ADC10MEM;				// Assigns the value held in ADC10MEM to the integer called ADC_value
      ADC10CTL0 &= ~ENC;
      return data;
}

/*
 * flexTriggerDebug()
 *
 * Description: This function is a debugging function used to display 
 *              adc values and trigger levels on the oled display to find a proper threshold
 *
 * Operation:   This function displays all five adc valuse and triggers on the oled
 * 
 * Argument: none
 *
 * Return value: none
 *
 */
void flexTriggerDebug (void) {
  if (trigger[4] == '1') {
    OLED_SSD1306_Display8x16Str(2,80,"1");
  } else {
    OLED_SSD1306_Display8x16Str(2,80,"0");
  }
  if (trigger[3] == '1') {
    OLED_SSD1306_Display8x16Str(2,88,"1");
  } else {
    OLED_SSD1306_Display8x16Str(2,88,"0");
  }
  if (trigger[2] == '1') {
    OLED_SSD1306_Display8x16Str(2,96,"1");
  } else {
    OLED_SSD1306_Display8x16Str(2,96,"0");
  }
  if (trigger[1] == '1') {
    OLED_SSD1306_Display8x16Str(2,104,"1");
  } else {
    OLED_SSD1306_Display8x16Str(2,104,"0");
  }
  if (trigger[0] == '1') {
    OLED_SSD1306_Display8x16Str(2,112,"1");
  } else {
    OLED_SSD1306_Display8x16Str(2,112,"0");
  }
  
  flexToString(flex1);
  OLED_SSD1306_Display8x16Str(0,0,flexString);
  flexToString(flex2);
  OLED_SSD1306_Display8x16Str(0,48,flexString);
  flexToString(flex3);
  OLED_SSD1306_Display8x16Str(2,0,flexString);
  flexToString(flex4);
  OLED_SSD1306_Display8x16Str(2,48,flexString);
  flexToString(flex5);
  OLED_SSD1306_Display8x16Str(2,96,flexString);
}

/*
 * flexToString()
 *
 * Description: This function is a debugging function used to convert 
 *              integers to strings that can be displayed
 *
 * Operation:   This function converts integers by dividing and mod by 10
 * 
 * Argument: int flexdata, the integer that is going to convert to string
 *
 * Return value: none
 *
 */
void flexToString(unsigned int flexData)
{
  if (flexData < 10) {
    flexString[0] = flexData + '0';
    flexString[1] = ' ';
    flexString[2] = ' ';
    flexString[3] = '\0';
  } else if (flexData < 100){
    flexString[0] = (flexData / 10) + '0';
    flexString[1] = (flexData % 10) + '0';
    flexString[2] = ' ';
    flexString[3] = '\0';
  } else {
    flexString[0] = (flexData / 100) + '0';
    flexString[1] = ((flexData / 10) % 10) + '0';
    flexString[2] = (flexData % 10) + '0';
    flexString[3] = '\0';
  }
}  