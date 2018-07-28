#include "ds18x20.h"
#include "flex_adc.h"
#include "btUART.h"
#include "I2C.h"
#include "timer.h"

#define DS1820_SKIP_ROM             0xCC
#define DS1820_READ_SCRATCHPAD      0xBE
#define DS1820_CONVERT_T            0x44
void hwSetUp(void);