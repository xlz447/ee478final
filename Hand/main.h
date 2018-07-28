#include <string.h>
#include "flex_adc.h"
#include "Fonts_SSD1306.h"
#include "OLED_SSD1306.h"
#include "Picture_SSD1306.h"

#define TAKEOFFCOUNT    2381
#define LANDCOUNT       20000
#define HIGHDC          60
#define LOWDC           36
#define HOVTIME         49

float temperature = 0;
int warning = 0;
int state = 0;

UCHAR temp[13];
void displayOLED (void);
void hwSetUp(void);
float readTemp(void);
void tempConversion(void);
