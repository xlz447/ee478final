/* This library file is found online at www.karvn.in
 * the source code can be found here: http://karve.in/wp-content/uploads/2012/06/MSP430G2452_DS18B20.zip
 * Author is Ishan Karve, and the date is 01/26/2012
 */

  
#ifndef DS18X20_H_
#define DS18X20_H_

#define DS1820_SKIP_ROM             0xCC
#define DS1820_READ_SCRATCHPAD      0xBE
#define DS1820_CONVERT_T            0x44

unsigned int ResetDS1820 ( void );
void DS1820_HI(void);
void DS1820_LO(void);
void WriteZero(void);
void WriteOne(void);
unsigned int ReadBit(void);
void WriteDS1820 (unsigned char,int );
unsigned int ReadDS1820 ( void );
float GetData(void);

float temperature = 0;
#endif /*DS18X20_H_*/

