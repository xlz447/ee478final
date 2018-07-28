#include <msp430f2274.h>
#include "OLED_SSD1306.h"
#include "delay.h"
//Function Prototypes
void Setup_ADC(void);   // Setup watchdog timer, clockc, ADC ports
int readFlex(unsigned int data, unsigned int bit);	// This function reads the ADC and stores the x, y and z values
void Read_Distance(void);
void flexTrigger(void);
void flexToString(unsigned int flexData);
void flexTriggerDebug (void);
void sendString(char* string);

unsigned int flex1 = 0;
unsigned int flex2 = 0;
unsigned int flex3 = 0;
unsigned int flex4 = 0;
unsigned int flex5 = 0;
extern UCHAR flexString[4];
char trigger[6] = {'0','0','0','0','0',0};