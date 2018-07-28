#include <msp430f2274.h>
#define uchar unsigned char

char outChar;
UCHAR receivedString[7];
UCHAR flexString[4];
int stringReady = 0;

void Setup_UART(void);
void btConfig(void);
void sendString(char* string);

extern int warning;
extern int state;