#include "main.h"

void main()
{
  hwSetUp();
  
  for(;;)
  {	
    displayOLED();          //oled display (temp, state, warning, trigger)
    flexTrigger();          //read flex sensor check trigger 
    //flexTriggerDebug();   //use to debug
  }
}

/*
 * hwSetUp()
 *
 * Description: This function initiates the hardware: system timer, UART and OLED screen
 *
 * Operation:   This function did the initialization for the hardware through the following steps: 
 *              1.Stop watch dog timer
 *	        2.set system master timer
 *		3.open port 4.7 as output for our power led
 *  		4.call uart set up function
 *              5.call oled initialization function
 *		6.call oled clear function 
 * Argument: none
 *
 * Return value: none
 *
 */
void hwSetUp(void) {
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
  
  //setup DCO to 1MHZ
  BCSCTL1 = CALBC1_16MHZ;       //16mhz timer
  DCOCTL = CALDCO_16MHZ; 
  P4DIR |= BIT1;                // Set 4.7 (Power LED) as output
  P4OUT |= BIT1;                // Set 4.7 high
  
  Setup_UART();                 //set up uart for blue tooth
  OLED_SSD1306_Init();          //initiate oled 
  OLED_SSD1306_Clear();
  //btConfig();                 //blue tooth config, only need to run once
}


/*
 * displayOLED()
 *
 * Description: This function displays information of the system onto the oled
 *
 * Operation:   This function displays the system state, triggers, temperature sensor feedback
 *              and distence warnings according to the following conditions
 *              The display can print 2 lines of 16 characters,
 *	        the first line displays temperature sensor feedback in Celsius (Temp: 22.47C)
 *              the second line displays the current system states (Idle, take off, slow up, slow down)
 *              the trigers, left, right, forward, backward will be abbreviated as L,R,F,B 
 *              since L & R or F & B cannot happen in the same time, they will be printed on the end of each line.
 *              lastly the distance sensor warning will be displayed on the center of the screen
 * 
 * Argument: none
 *
 * Return value: none
 *
 */
void displayOLED (void) {
  if (stringReady) {
    stringReady = 0;
    if (warning) {
      OLED_SSD1306_Clear();  //clear screen for warning to show
      OLED_SSD1306_Display8x16Str(1, 0, "   WARNING!!!  ");
    } else {
      tempConversion();  //get temperature string
      OLED_SSD1306_Display8x16Str(0,0, temp);
      switch (state) { //print each state
      case 0:
        OLED_SSD1306_Display8x16Str(2, 0, "Idle     ");
        break;
      case 1:
        OLED_SSD1306_Display8x16Str(2, 0, "Take Off ");
        break;
      case 2:
        OLED_SSD1306_Display8x16Str(2, 0, "Slow Up  ");
        break;        
      case 3:
        OLED_SSD1306_Display8x16Str(2, 0, "Slow Down");
        break;        
      }
    }
    if (trigger[1] == '1') { //print F or B if applied
      OLED_SSD1306_Display8x16Str(2,120,"F");
    } else if (trigger[2] == '1') {
      OLED_SSD1306_Display8x16Str(2,120,"B");
    } else {
      OLED_SSD1306_Display8x16Str(2,120," ");
    }
    
    if (trigger[3] == '1') {  // print L or R if applied
      OLED_SSD1306_Display8x16Str(0,120,"L");
    } else if (trigger[4] == '1') {
      OLED_SSD1306_Display8x16Str(0,120,"R");
    } else {
      OLED_SSD1306_Display8x16Str(0,120," ");
    }
  }
}

/*
 * tempConversion()
 *
 * Description: This function converts the 4 digit number to the decimal temperature
 *
 * Operation:   This function will get the 4 digit number from the bluetooth recive string
 *              and convert it into a 2 digit decimal number in celsius by adding a decimal
 *              point in the middle of the 4 digit number, and then adding a C at the end
 * 
 * Argument: none
 *
 * Return value: none
 *
 */
void tempConversion(void) {
  int i = 0;
  char string[6] = "Temp: ";
  while (string[i]) {
    temp[i] = string[i];
    i++;
  }
  temp[6] = receivedString[0];
  temp[7] = receivedString[1];
  temp[8] = '.';
  temp[9] = receivedString[2];
  temp[10] = receivedString[3];
  temp[11] = 'C';
  temp[12] = '\0';
}

