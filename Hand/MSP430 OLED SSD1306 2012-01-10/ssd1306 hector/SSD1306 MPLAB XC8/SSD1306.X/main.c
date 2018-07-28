/*
 * File:   main.c
 * Author: |H_e_c_t_o_r|
 * 
 */

#include <xc.h>
#include <p18f46k22.h>
#include <stdio.h>
#include <stdlib.h>
#include <plib/spi.h>
#include "bit_settings.h"
#include "my_delays.h"
#include "font.h"
#include "bitmap.h"
#include "ssd1306.h"

void main(void){
unsigned char i;
char buffer2[20];
OSCCON = 0b01110000;
OSCTUNEbits.PLLEN = 1; // turn on the PLL 64 MHz
ANSELA = 0; ANSELB = 0;   ANSELC = 0;   ANSELD = 0;   ANSELE = 0;
PORTA  = 0; PORTB  = 0;   PORTC  = 0;   PORTD  = 0;   PORTE  = 0;
TRISA  = 0; TRISB  = 0;   TRISC  = 0;   TRISD  = 0;   TRISE  = 0;
CloseSPI1();
OpenSPI1(SPI_FOSC_16, MODE_00, SMPEND);
Oled_Init();
Oled_SetFont(Terminal12x16, 12, 16, 32,127);
Oled_ConstText("library for", 0, 0);
Oled_ConstText("Graphic", 0, 2);
Oled_ConstText("OLED 128x64", 0, 4);
Oled_ConstText("SSD1306", 0, 6);

Delay_ms(5000);
Oled_FillScreen(0x00);
Oled_ConstText("Fonts", 35, 0);
for(i = 0; i < 113; i++)
   {
    sprintf(buffer2,"%03d",i);
    Oled_SetFont(Segment_25x40, 25, 40, 46, 58);
    Oled_Text(buffer2, 0, 3);
    Oled_SetFont(Terminal12x16, 12, 16, 32 ,127);
    Oled_Text(buffer2, 90, 3);
    Oled_SetFont(Font_6x8, 6, 8, 32, 127);
    Oled_Text(buffer2, 99, 6);
    Delay_ms(200);
   }

Delay_ms(5000);
Oled_FillScreen(0x00);
Oled_Image(truck_bmp);

Delay_ms(5000);
Oled_FillScreen(0x00);
Oled_SetFont(Terminal12x16, 12, 16, 32,127);
Oled_WriteChar('O', 10, 3); Delay_ms(2000);
Oled_WriteChar('L', 30, 3); Delay_ms(2000);
Oled_WriteChar('E', 50, 3); Delay_ms(2000);
Oled_WriteChar('D', 70, 3); Delay_ms(2000);
Right_HorizontalScroll(0, 4, FRAME_3);
Activate_Scroll();
while(1){}
}