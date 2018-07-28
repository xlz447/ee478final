/* 
 * File:   ssd1306.h
 * Author: |H_e_c_t_o_r|
 *
 * Library to control a 128x64 graphical display OLED. Driver SSD1306.
 * Interface: SPI.
 * This library can only be used for educational and hobbyist purposes.
 * Website https://www.youtube.com/user/Hector8389/videos
 * Version 1.0
 *
 * Note:
 * As this module oled not have the MISO pin,
 * not available graphics routines (pixel, line, rectangle, circle).
 * Manufacturer fuck you!
 * 
 */

#ifndef SSD1306_H
#define	SSD1306_H
#include <xc.h>
#define _XTAL_FREQ 20000000 // Select your XTAL

//------------------------------------------------------------------------------
// Connection of module OLED.
//
// VCC         <<<>>> 3.3 V.
// GND         <<<>>> GND.
// OLED_SCK    <<<>>> Connect to SCK MCU.
// OLED_MOSI   <<<>>> Connect to SDO MCU.
// OLED_CS     <<<>>> You can change this pin.
// OLED_D/C    <<<>>> You can change this pin.

// OLED_MISO   <<<>>> The module not have this pin.
// OLED:RESET  <<<>>> The module not have this pin.
//------------------------------------------------------------------------------
#define OLED_CS             LATBbits.LATB2
#define TRIS_CS             TRISBbits.TRISB2

#define OLED_DC             LATBbits.LATB3
#define TRIS_DC             TRISBbits.TRISB3

#define OLED_RES            LATBbits.LATB4
#define TRIS_RES            TRISBbits.TRISB4
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Those are pages and frames that you can use.
//------------------------------------------------------------------------------
#define PAGE0         0
#define PAGE1         1
#define PAGE2         2
#define PAGE3         3
#define PAGE4         4
#define PAGE5         5
#define PAGE6         6
#define PAGE7         7
#define FRAME_2       7
#define FRAME_3       4
#define FRAME_4       5
#define FRAME_5       0
#define FRAME_25      6
#define FRAME_64      1
#define FRAME_128     2
#define FRAME_256     3
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// New name for data types.
// Declaration of global variables.
//------------------------------------------------------------------------------
typedef char                     schar;
typedef unsigned char            uchar;
typedef const char               cschar;
typedef const unsigned char      cuchar;
typedef int                      sint;
typedef unsigned int             uint;

cuchar *font, *font2;
uchar width, height, min, max;
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Prototypes.
//------------------------------------------------------------------------------
void Oled_Init(void);
void Oled_Reset(void);
void Oled_Command(uchar cmd);
void Oled_WriteRam(uchar dat);
void Oled_SetPointer(uchar seg, uchar pag);
void Oled_SetFont(cuchar *_font, uchar _width, uchar _height, uchar _min, uchar _max);
void Oled_WriteChar(uchar c, uchar seg, uchar pag);
void Oled_ConstText(cschar *buffer, uchar seg, uchar pag);
void Oled_Text(schar *buffer, uchar seg, uchar pag);
void Oled_FillScreen(uchar pattern);
void Oled_Image(cuchar *buffer);
void Right_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time);
void Left_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time);
void VerticalRight_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time);
void VerticalLeft_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time);
void Deactivate_Scroll(void);
void Activate_Scroll(void);
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Initializes the OLED module.
//------------------------------------------------------------------------------
void Oled_Init(void){
TRIS_CS = 0; TRIS_DC = 0; TRIS_RES = 0;
OLED_CS = 1; OLED_DC = 0; OLED_RES = 0;
Delay_ms(500);
Oled_Reset();
Oled_Command(0xAE);                     // Set Display OFF
Oled_Command(0x81); Oled_Command(0xCF); // Set Contrast Control
Oled_Command(0xA4);                     // Entire Display ON
Oled_Command(0xA6);                     // Set Normal

Oled_Command(0x20); Oled_Command(0x02); // Set Memory Addressing Mode
Oled_Command(0x00);                     // Set Lower Column
Oled_Command(0x10);                     // Set Higher Column
Oled_Command(0xB0);                     // Set Page Start

Oled_Command(0x40);                     // Set Display Start Line
Oled_Command(0xA1);                     // Set Segment Re-map
Oled_Command(0xA8); Oled_Command(0x3F); // Set Multiplex Ratio
Oled_Command(0xC8);                     // Set COM Output
Oled_Command(0xD3); Oled_Command(0x00); // Set Display Offset
Oled_Command(0xDA); Oled_Command(0x12); // Set COM Pins Hardware Configuration

Oled_Command(0xD5); Oled_Command(0x80); // Set Display Clock
Oled_Command(0xD9); Oled_Command(0xF1); // Set Pre-charge Period
Oled_Command(0xDB); Oled_Command(0x40); // Set VCOMH Deselect Level
Oled_Command(0x8D); Oled_Command(0x14); // Charge Pump Setting

Oled_Command(0xAF);                     // Set Display ON
Oled_FillScreen(0x00);                  // Clear screen
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Reset the OLED module.
//------------------------------------------------------------------------------
void Oled_Reset(void){
OLED_RES = 0;
Delay_ms(1000);
OLED_RES = 1;
Delay_ms(500);
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Write command.
//------------------------------------------------------------------------------
void Oled_Command(uchar cmd){
OLED_CS = 0; OLED_DC = 0;
while(WriteSPI(cmd));
OLED_CS = 1;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Write ram.
//------------------------------------------------------------------------------
void Oled_WriteRam(uchar dat){
OLED_CS = 0; OLED_DC = 1;
while(WriteSPI(dat));
OLED_CS = 1;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Set  pointer in frame memory where MCU can access.
// seg: set segment
// pag: set page
//------------------------------------------------------------------------------
void Oled_SetPointer(uchar seg, uchar pag){
uchar low_column, hig_column;
low_column = (seg & 0b00001111);
hig_column = (seg & 0b11110000)>>4;
hig_column = hig_column | 0b00010000;
pag = (pag & 0b00000111);
pag = (pag | 0b10110000);
Oled_Command(low_column); // Set Lower Column
Oled_Command(hig_column); // Set Higher Column
Oled_Command(pag);        // Set Page Start
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Sets font that will be used.
// _font: byte of array
// _width: char width (pixels)
// _height: char height (pixels)
// _min: range minimum
// _max: range maximum
//
// Note: only fonts with multiples of 8 pixels in height.
//------------------------------------------------------------------------------
void Oled_SetFont(cuchar *_font, uchar _width, uchar _height, uchar _min, uchar _max){
font2  = _font;
width  = _width;
height = _height / 8;
min    = _min;
max    = _max;
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Writes a char on the OLED at coordinates (x, y).
// c: char to be written
// seg: set segment. Valid values: 0..127
// pag: set page. Valid values: 0..7
//------------------------------------------------------------------------------
void Oled_WriteChar(uchar c, uchar seg, uchar pag){
uint i,j;
uchar x_seg, y_pag;
x_seg = seg;
y_pag = pag;
font = font2;
j = c - min;
j = j * (width * height);
for(i = 0; i < j; i++){font++;}
for(i = 0; i < width; i++)
   {
    y_pag = pag;
    for(j = 0; j < height; j++)
       {
        if(x_seg < 128)
          {
           Oled_SetPointer(x_seg, y_pag);
           Oled_WriteRam(*font);
          }
        y_pag++;
        font++;
       }
    x_seg++;
   }
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Prints text  constant on OLED.
// buffer: byte of array
// seg: set segment. Valid values: 0..127
// pag: set page. Valid values: 0..7
//------------------------------------------------------------------------------
void Oled_ConstText(cschar *buffer, uchar seg, uchar pag){
uchar x_seg = seg;
while(*buffer)
     {
      Oled_WriteChar(*buffer, x_seg, pag);
      x_seg = x_seg + width;
      buffer++;
     }
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Prints text  variable on OLED.
// buffer: byte of array
// seg: set segment. Valid values: 0..127
// pag: set page. Valid values: 0..7
//------------------------------------------------------------------------------
void Oled_Text(schar *buffer, uchar seg, uchar pag){
uchar x_seg = seg;
while(*buffer)
     {
      Oled_WriteChar(*buffer, x_seg, pag);
      x_seg = x_seg + width;
      buffer++;
     }
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Fills OLED memory.
// pattern: byte to fill OLED memory
//------------------------------------------------------------------------------
void Oled_FillScreen(uchar pattern){
unsigned char i,j;
for(i = 0; i < 8; i++)
   {
    Oled_SetPointer(0, i);
    for(j = 0; j < 128; j++)
       {
        Oled_WriteRam(pattern);
       }
   }
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Displays bitmap on OLED.
// buffer: byte of array
//------------------------------------------------------------------------------
void Oled_Image(cuchar *buffer){
unsigned char i,j;
for(i = 0; i < 8; i++)
   {
    Oled_SetPointer(0, i);
    for(j = 0; j < 128; j++)
       {
        Oled_WriteRam(*buffer);
        buffer++;
       }
   }
}
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Extra routines for configuration and start the Scroll function.
// start_page: start page. Valid values: 0..7
// end_page: end page. Valid values: 0..7
// set_time: set time. Valid values: 0..7
//------------------------------------------------------------------------------
void Right_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time){
Deactivate_Scroll();
Oled_Command(0x26);
Oled_Command(0x00);
Oled_Command(start_page);
Oled_Command(set_time);
Oled_Command(end_page);
Oled_Command(0x00);
Oled_Command(0xFF);
Activate_Scroll();
}

void Left_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time){
Deactivate_Scroll();
Oled_Command(0x27);
Oled_Command(0x00);
Oled_Command(start_page);
Oled_Command(set_time);
Oled_Command(end_page);
Oled_Command(0x00);
Oled_Command(0xFF);
Activate_Scroll();
}

void VerticalRight_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time){
Deactivate_Scroll();
Oled_Command(0x29);
Oled_Command(0x00);
Oled_Command(start_page);
Oled_Command(set_time);
Oled_Command(end_page);
Oled_Command(0x01); //scrolling_offset
Activate_Scroll();
}

void VerticalLeft_HorizontalScroll(uchar start_page, uchar end_page, uchar set_time){
Deactivate_Scroll();
Oled_Command(0x2A);
Oled_Command(0x00);
Oled_Command(start_page);
Oled_Command(set_time);
Oled_Command(end_page);
Oled_Command(0x01); //scrolling_offset
Activate_Scroll();
}

void Deactivate_Scroll(void){
Oled_Command(0x2E);
}

void Activate_Scroll(void){
Oled_Command(0x2F);
}
//------------------------------------------------------------------------------
#endif	/* SSD1306_H */

