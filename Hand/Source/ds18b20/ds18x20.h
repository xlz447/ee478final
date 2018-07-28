#ifndef DS18X20_H_
#define DS18X20_H_

#define DS1820_SKIP_ROM             0xCC
#define DS1820_READ_SCRATCHPAD      0xBE
#define DS1820_CONVERT_T            0x44

void InitDS18B20(void);
unsigned int ResetDS1820 ( void );
void DS1820_HI(void);
void DS1820_LO(void);
void WriteZero(void);
void WriteOne(void);
unsigned int ReadBit(void);
void WriteDS1820 (unsigned char,int );
unsigned int ReadDS1820 ( void );
float GetData(void);
#endif /*DS18X20_H_*/
