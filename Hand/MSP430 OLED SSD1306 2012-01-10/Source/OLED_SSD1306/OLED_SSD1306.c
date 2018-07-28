/*******************************************************************************
	�M�צW��:	SSD1306 OLED �\����
	MCU		:	MSP430
	�}�o����:	IAR MSP430
	�@��:		Alan Jeck(QQ:18655038 E-mail:lucky_jeck@163.com)
	���:		2012-01-10
	����:		

	Update	History:
	Versio:	Date:		Detail:
	V1.0.0	2012-01-10	��l����
	
*******************************************************************************/


#include	"OLED_SSD1306.h"
#include	"Fonts_SSD1306.h"
#include        "Picture_SSD1306.h"

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteData
//	�J�f�ܶq:	bData			:			�ƾ�
//	��^��:		�L
//	��ƻ���:	�g�@�Ӽƾڨ� OLED
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_WriteData(UCHAR bData)
{
	UCHAR iIndex;
	OLED_SSD1306_CE_L;
	OLED_SSD1306_DC_H;	//�ǰe�ƾ�
	for (iIndex = 0x80;iIndex > 0;iIndex >>= 1)
	{
		if(bData&iIndex)
			OLED_SSD1306_SDIN_H;
		else
			OLED_SSD1306_SDIN_L;
		_NOP();
		OLED_SSD1306_SCLK_L;
		_NOP();
		OLED_SSD1306_SCLK_H;
		_NOP();
	}
	OLED_SSD1306_CE_H;
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteCmd
//	�J�f�ܶq:	bCommand		:			�R�O
//	��^��:		�L
//	��ƻ���:	�g�@�өR�O�� OLED
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_WriteCmd(UCHAR bCommand)
{
	UCHAR iIndex;
	OLED_SSD1306_CE_L;
	OLED_SSD1306_DC_L;	//�ǰe�R�O
	for (iIndex = 0x80;iIndex > 0;iIndex >>= 1)
	{
		if(bCommand&iIndex)
			OLED_SSD1306_SDIN_H;
		else
			OLED_SSD1306_SDIN_L;
		_NOP();
		OLED_SSD1306_SCLK_L;
		_NOP();
		OLED_SSD1306_SCLK_H;
		_NOP();
	}
	OLED_SSD1306_CE_H;
}


typedef	enum
{
	DISP_OFF,
	DISP_ON
}DISP_ON_OFF;
//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_SetDisplayOnOff
//	�J�f�ܶq:	DispOnOff		:			�����άO���
//	��^��:		�L
//	��ƻ���:	���}������ OLED ���
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_SetDisplayOnOff(DISP_ON_OFF DispOnOff)
{
	OLED_SSD1306_WriteCmd(0xAE|DispOnOff);
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_SetStartColumn
//	�J�f�ܶq:	DispOnOff		:			�����άO���
//	��^��:		�L
//	��ƻ���:	���}������ OLED ���
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_SetStartColumn(UCHAR bData)
{
	OLED_SSD1306_WriteCmd(0x00 + bData%16);		// Set Lower Column Start Address for Page Addressing Mode
												//   Default => 0x00
	OLED_SSD1306_WriteCmd(0x10 + bData/16);		// Set Higher Column Start Address for Page Addressing Mode
												//   Default => 0x10
}


void	OLED_SSD1306_SetAddressingMode(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0x20);			// Set Memory Addressing Mode
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x02
	//     0x00 => Horizontal Addressing Mode
	//     0x01 => Vertical Addressing Mode
	//     0x02 => Page Addressing Mode
}
void	OLED_SSD1306_SetColumnAddress(UCHAR a, UCHAR b)
{
	OLED_SSD1306_WriteCmd(0x21);			// Set Column Address
	OLED_SSD1306_WriteCmd(a);			//   Default => 0x00 (Column Start Address)
	OLED_SSD1306_WriteCmd(b);			//   Default => 0x7F (Column End Address)
}

void	OLED_SSD1306_SetPageAddress(UCHAR a, UCHAR b)
{
	OLED_SSD1306_WriteCmd(0x22);			// Set Page Address
	OLED_SSD1306_WriteCmd(a);			//   Default => 0x00 (Page Start Address)
	OLED_SSD1306_WriteCmd(b);			//   Default => 0x07 (Page End Address)
}

void	OLED_SSD1306_SetStartLine(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0x40|d);			// Set Display Start Line
	//   Default => 0x40 (0x00)
}

void	OLED_SSD1306_SetContrastControl(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0x81);			// Set Contrast Control
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x7F
}

void	OLED_SSD1306_Set_Charge_Pump(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0x8D);			// Set Charge Pump
	OLED_SSD1306_WriteCmd(0x10|d);			//   Default => 0x10
	//     0x10 (0x00) => Disable Charge Pump
	//     0x14 (0x04) => Enable Charge Pump
}

void	OLED_SSD1306_Set_Segment_Remap(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xA0|d);			// Set Segment Re-Map
	//   Default => 0xA0
	//     0xA0 (0x00) => Column Address 0 Mapped to SEG0
	//     0xA1 (0x01) => Column Address 0 Mapped to SEG127
}

void	OLED_SSD1306_Set_Entire_Display(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xA4|d);			// Set Entire Display On / Off
	//   Default => 0xA4
	//     0xA4 (0x00) => Normal Display
	//     0xA5 (0x01) => Entire Display On
}

void	OLED_SSD1306_Set_Inverse_Display(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xA6|d);			// Set Inverse Display On/Off
	//   Default => 0xA6
	//     0xA6 (0x00) => Normal Display
	//     0xA7 (0x01) => Inverse Display On
}

void	OLED_SSD1306_Set_Multiplex_Ratio(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xA8);			// Set Multiplex Ratio
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x3F (1/64 Duty)
}

void	OLED_SSD1306_SetStartPage(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xB0|d);			// Set Page Start Address for Page Addressing Mode
						//   Default => 0xB0 (0x00)
}

void	OLED_SSD1306_Set_Common_Remap(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xC0|d);			// Set COM Output Scan Direction
						//   Default => 0xC0
						//     0xC0 (0x00) => Scan from COM0 to 63
						//     0xC8 (0x08) => Scan from COM63 to 0
}

void	OLED_SSD1306_Set_Display_Offset(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xD3);			// Set Display Offset
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x00
}

void	OLED_SSD1306_Set_Display_Clock(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xD5);			// Set Display Clock Divide Ratio / Oscillator Frequency
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x80
						//     D[3:0] => Display Clock Divider
						//     D[7:4] => Oscillator Frequency
}

void	OLED_SSD1306_Set_Precharge_Period(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xD9);			// Set Pre-Charge Period
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x22 (2 Display Clocks [Phase 2] / 2 Display Clocks [Phase 1])
						//     D[3:0] => Phase 1 Period in 1~15 Display Clocks
						//     D[7:4] => Phase 2 Period in 1~15 Display Clocks
}

void	OLED_SSD1306_Set_Common_Config(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xDA);			// Set COM Pins Hardware Configuration
	OLED_SSD1306_WriteCmd(0x02|d);			//   Default => 0x12 (0x10)
						//     Alternative COM Pin Configuration
						//     Disable COM Left/Right Re-Map
}

void	OLED_SSD1306_Set_VCOMH(UCHAR d)
{
	OLED_SSD1306_WriteCmd(0xDB);			// Set VCOMH Deselect Level
	OLED_SSD1306_WriteCmd(d);			//   Default => 0x20 (0.77*VCC)
}

void	OLED_SSD1306_Set_NOP(void)
{
	OLED_SSD1306_WriteCmd(0xE3);			// Command for No Operation
}

/******************************************************************************
  * @function name : DisplayArea
  * @brief  Display Area
  * @param  :
  * @retval :
  */
void	OLED_SSD1306_FillArea(UCHAR spage, UCHAR epage,UCHAR scolumn, UCHAR ecolumn,UCHAR pt)
{
    UCHAR i = 0,j = 0,h = 0,w = 0;

    h = epage - spage + 1;
    w = ecolumn - scolumn;

    while ( j < h )
    {
        OLED_SSD1306_SetStartPage(spage + j);
        OLED_SSD1306_SetStartColumn(scolumn);
        for (i=0; i<w; i++)
        {
              OLED_SSD1306_WriteData(pt);
        }
        j++;
    }
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_CheckOutline
//	�J�f�ܶq:	�L
//	��^��:		�L
//	��ƻ���:	�b�������� OLED �W��ܨ�Ӱϰ쪺�~��
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_CheckOutline(void)
{		
    UCHAR i,j;
    OLED_SSD1306_FillArea(0,7,0,128,0);

    OLED_SSD1306_SetStartPage(0x00);
    OLED_SSD1306_SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        OLED_SSD1306_WriteData(0x01);
    }

    OLED_SSD1306_SetStartPage(0x01);
    OLED_SSD1306_SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        OLED_SSD1306_WriteData(0x80);
    }

    OLED_SSD1306_SetStartPage(0x02);
    OLED_SSD1306_SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        OLED_SSD1306_WriteData(0x01);
    }

    OLED_SSD1306_SetStartPage(0x07);
    OLED_SSD1306_SetStartColumn(XLevel);

    for(i=0;i<Max_Column;i++)
    {
        OLED_SSD1306_WriteData(0x80);
    }

    for(i=0;i<8;i++)
    {
        OLED_SSD1306_SetStartPage(i);

        for(j=0;j<Max_Column;j+=(Max_Column-1))
        {
            OLED_SSD1306_SetStartColumn(XLevel+j);
            OLED_SSD1306_WriteData(0xFF);
        }
    }
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Init
//	�J�f�ܶq:	�L
//	��^��:		�L
//	��ƻ���:	OLED ��l��
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_Init()
{
	OLED_SSD1306_SCLK_IO_INIT;
	OLED_SSD1306_SDIN_IO_INIT;
	OLED_SSD1306_DC_IO_INIT;
	OLED_SSD1306_CE_IO_INIT;
	OLED_SSD1306_RST_IO_INIT;
	OLED_SSD1306_LED_IO_INIT;
	
	OLED_SSD1306_LED_OFF;

	OLED_SSD1306_RST_L;
	__delay_cycles(10000);
	OLED_SSD1306_RST_H;

	__delay_cycles(50000);

    //�q�W�q��U���}�l��l�ƭn���������ɶ��A�Y����RC�_�짹��
    OLED_SSD1306_SetDisplayOnOff(DISP_OFF);			// Display Off (0x00/0x01)
    OLED_SSD1306_Set_Display_Clock(0xf0);			// Set Clock as 100 Frames/Sec
    OLED_SSD1306_Set_Multiplex_Ratio(0x3F);			// 1/64 Duty (0x0F~0x3F)
    OLED_SSD1306_Set_Display_Offset(0x00);			// Shift Mapping RAM Counter (0x00~0x3F)
    OLED_SSD1306_SetStartLine(0x00);				// Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_SSD1306_Set_Charge_Pump(0x04);				// Enable Embedded DC/DC Converter (0x00/0x04)
    OLED_SSD1306_SetAddressingMode(0x02);			// Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_SSD1306_Set_Segment_Remap(0x01);			// Set SEG/Column Mapping (0x00/0x01)
    OLED_SSD1306_Set_Common_Remap(0x08);			// Set COM/Row Scan Direction (0x00/0x08)
    OLED_SSD1306_Set_Common_Config(0x10);			// Set Sequential Configuration (0x00/0x10)
    OLED_SSD1306_SetContrastControl(Brightness);	// Set SEG Output Current
    OLED_SSD1306_Set_Precharge_Period(0xF1);		// Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_SSD1306_Set_VCOMH(0x40);					// Set VCOM Deselect Level
    OLED_SSD1306_Set_Entire_Display(0x00);			// Disable Entire Display On (0x00/0x01)
    OLED_SSD1306_Set_Inverse_Display(0x00);			// Disable Inverse Display On (0x00/0x01)
    OLED_SSD1306_FillArea(0,7,0,128,0);				// Clear Screen
	
    OLED_SSD1306_SetDisplayOnOff(DISP_ON);			// Display On (0x00/0x01)

	//OLED_SSD1306_CheckOutline();
	//while (1);
}


void	OLED_SSD1306_Display8x16Str(UCHAR page, UCHAR column, UCHAR *str) //8x16Ascii�r��
{
    UCHAR i = 0;
    //UCHAR temp = 0;
    UINT16 padd= 0;
    while(*str != '\0')
    {
        OLED_SSD1306_SetStartPage(page);
        OLED_SSD1306_SetStartColumn(column);
        padd = (*str-32)*16;
        for (i = 0; i < 8; i++)
        {
             OLED_SSD1306_WriteData(AnsciiDot8x16[padd+i]);
        }

        OLED_SSD1306_SetStartPage(page+1);
        OLED_SSD1306_SetStartColumn(column);
        for (i = 8; i < 16; i++)
        {
           OLED_SSD1306_WriteData(AnsciiDot8x16[padd+i]);
        }
        str++;
        column += 8;
   }
}

void	OLED_SSD1306_DisplayChinese(UCHAR page, UCHAR column, UINT16 location)//16x16����r��
{ 	
		UCHAR i = 0;
		location=location*32;
        OLED_SSD1306_SetStartPage(page);
        OLED_SSD1306_SetStartColumn(column);
        for (i = 0; i < 16; i++)
        {
             OLED_SSD1306_WriteData(GB16X16[location+i]);
        }
        OLED_SSD1306_SetStartPage(page+1);
        OLED_SSD1306_SetStartColumn(column);
        for (i = 16; i < 32; i++)
        {
           OLED_SSD1306_WriteData(GB16X16[location+i]);
        }
}
  
void	OLED_SSD1306_Displaypicture1(UCHAR page ,UCHAR column)  //�R�ߡ]�Ϥ��^
{ 	
	UCHAR i = 0;
    UCHAR const picture1[]=
	{
		0XFE,0XFE,0XFE,0XFE,0XFE,0XF8,0XC0,0X62,0X96,0XF6,0XEE,0XDE,0XDE,0XCE,0XEE,0XF6,
0X66,0X12,0XC0,0XFC,0XFE,0XFE,0XFE,0XFE,0XFF,0XDF,0XCF,0XD7,0XE7,0XFB,0XF9,0XDE,
0XCF,0X83,0X79,0XFD,0X7D,0XBD,0X3B,0XB3,0XD8,0XD8,0XD9,0XD3,0XD7,0XCF,0XCF,0XDF,
0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3C,0X23,0X00,0X31,0X3E,0X3F,
0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,0X3F,
	};
        OLED_SSD1306_SetStartPage(page);
        OLED_SSD1306_SetStartColumn(column);
        for (i=0; i<24; i++){OLED_SSD1306_WriteData(picture1[i]);}
		OLED_SSD1306_SetStartPage(page+1);
        OLED_SSD1306_SetStartColumn(column);
		for (i=24; i<48; i++){OLED_SSD1306_WriteData(picture1[i]);}
		OLED_SSD1306_SetStartPage(page+2);
        OLED_SSD1306_SetStartColumn(column);
		for (i=48; i<72; i++){OLED_SSD1306_WriteData(picture1[i]);}
}

void	OLED_SSD1306_Displaypictureclear1(UCHAR page ,UCHAR column)  //�R��(�Ϥ��M��)
{ 	
	UCHAR i = 0;
        OLED_SSD1306_SetStartPage(page);
        OLED_SSD1306_SetStartColumn(column);
        for (i=0; i<24; i++){OLED_SSD1306_WriteData(0x00);}
		OLED_SSD1306_SetStartPage(page+1);
        OLED_SSD1306_SetStartColumn(column);
		for (i=24; i<48; i++){OLED_SSD1306_WriteData(0x00);}
		OLED_SSD1306_SetStartPage(page+2);
        OLED_SSD1306_SetStartColumn(column);
		for (i=48; i<72; i++){OLED_SSD1306_WriteData(0x00);}
}	

void	OLED_DemoMain(void)
{
	UCHAR i = 0;
    OLED_SSD1306_Init();
	while(1)
   {
   		/*if(i==0)
		{
			i=1;
			//OLED_SSD1306_Displaypictureclear1(5 ,52);
			OLED_SSD1306_Displaypicture1(0,0);
                        OLED_SSD1306_Displaypicture1(0,104);
                        OLED_SSD1306_Displaypicture1(6,52);
			OLED_SSD1306_Displaypicture1(3,104);
		}
		/*else
		{
			i=0;
			OLED_SSD1306_Displaypictureclear1(0,0);
			OLED_SSD1306_Displaypictureclear1(0,104);
			OLED_SSD1306_Displaypicture1(5,52);
		}*/
                OLED_SSD1306_DisplayChinese(0,15,0);
                OLED_SSD1306_DisplayChinese(0,30,1);	
                OLED_SSD1306_DisplayChinese(0,45,2);	
                OLED_SSD1306_DisplayChinese(0,60,3);	
                OLED_SSD1306_DisplayChinese(0,75,4);	
		OLED_SSD1306_Display8x16Str(3,80, "~");
		OLED_SSD1306_Display8x16Str(3,30, "DRAGON");
                OLED_SSD1306_Displaypicturefull(Pic_SSD1306,0,15);
        __delay_cycles(100000);
   }
}





//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Set_xy
//	�J�f�ܶq:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//	��^��:		�L
//	��ƻ���:	�]�m�N�n�g�ƾڪ��q��
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_Set_xy(UCHAR x,UCHAR y)
{
	OLED_SSD1306_WriteCmd(0x20);		//H=0
	OLED_SSD1306_WriteCmd(0x80|x);		//x-0 to 83
	OLED_SSD1306_WriteCmd(0x40|y);		//y-0 to 5
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Clear
//	�J�f�ܶq:	�L
//	��^��:		�L
//	��ƻ���:	�M�� OLED
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_Clear(void)
{
	UCHAR i,j;
	OLED_SSD1306_WriteCmd(0x0c);	//�]�w��ܼҦ��A���`���	
	OLED_SSD1306_WriteCmd(0x80);	//�]�mRAM�_�l�a�}
	for(j=0;j<6;j++)
	{
		for(i=0;i<84;i++)
		{
			OLED_SSD1306_WriteData(0);
		}
	}
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteChar
//	�J�f�ܶq:	c				:			�ҭn�g���r��
//	��^��:		�L
//	��ƻ���:	display a asciifont6*8
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_WriteChar(UCHAR c)
{
	UCHAR line;
	c -= 32;
	for(line = 0;line < 6;line++)
		OLED_SSD1306_WriteData(Fonts_ASCII6x8[c][line]);
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteStringxy
//	�J�f�ܶq:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�r�Ŧ�w�R�ϫ��w
//	��^��:		�L
//	��ƻ���:	��ܭ^��r�Ŧ�
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_WriteStringxy(UCHAR x,UCHAR y,UCHAR *pszString)
{
	OLED_SSD1306_Set_xy(x,y);
	while(*pszString)
	{
		OLED_SSD1306_WriteChar(*pszString);
		pszString++;
	}
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteString
//	�J�f�ܶq:	pszString		:			�r�Ŧ�w�R�ϫ��w
//	��^��:		�L
//	��ƻ���:	��ܭ^��r�Ŧ�,�H�e���g�ƾڪ��ƾڦa�}�}�p�g.
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_WriteString(UCHAR *pszString)
{
	while(*pszString)
	{
		OLED_SSD1306_WriteChar(*pszString);
		pszString++;
	}
}

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteChinese
//	�J�f�ܶq:	iColumn			:			�C
//				iLine			:			��
//				bCharIndex		:			����r�Ū�����
//	��^��:		�L
//	��ƻ���:	��ܤ���r�Ŧ�.
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_WriteChinese(UCHAR iColumn,UCHAR iLine,UCHAR bCharIndex)
{
	UCHAR iIndex;

	OLED_SSD1306_Set_xy(iColumn*8,iLine);
	for(iIndex = 0; iIndex < 16;iIndex++)
	{
		OLED_SSD1306_WriteData(Fonts_Chinese16x16[bCharIndex][iIndex]); 
	}
	
    OLED_SSD1306_Set_xy(iColumn*8, iLine+1);
	for(iIndex = 16; iIndex < 32;iIndex++)
	{
		OLED_SSD1306_WriteData(Fonts_Chinese16x16[bCharIndex][iIndex]);
	}
}


//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteChinese
//	�J�f�ܶq:	pPic			:			�Ϥ��w�R�ϫ��w
//				iLen			:			�Ϥ��w�R�Ϥj�p
//	��^��:		�L
//	��ƻ���:	��ܹϤ�
//--------------------------------------------------------------------------------------
void	OLED_SSD1306_DisplayPicture(UCHAR const *pPic_SSD1306,UINT16 iLen)
{
	UINT16 iIndex;
	OLED_SSD1306_Set_xy(0,0);
	for (iIndex = 0;iIndex < iLen;iIndex++)
	{
		OLED_SSD1306_WriteData(pPic_SSD1306[iIndex]);
	}
}


void	OLED_SSD1306_Displaypicturefull(UINT16 const *pPic_SSD1306,UCHAR page,UCHAR column)  //�R�ߡ]�Ϥ��^
{ 	
	UINT16 i = 0;
        OLED_SSD1306_SetStartPage(page);
        OLED_SSD1306_SetStartColumn(column);
        for (i=0; i<100; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
		OLED_SSD1306_SetStartPage(page+1);
        OLED_SSD1306_SetStartColumn(column);
		for (i=100; i<200; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
		OLED_SSD1306_SetStartPage(page+2);
        OLED_SSD1306_SetStartColumn(column);
		for (i=200; i<300; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
                OLED_SSD1306_SetStartPage(page+3);
        OLED_SSD1306_SetStartColumn(column);
		for (i=300; i<400; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
                OLED_SSD1306_SetStartPage(page+4);
        OLED_SSD1306_SetStartColumn(column);
		for (i=400; i<500; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
                OLED_SSD1306_SetStartPage(page+5);        
        OLED_SSD1306_SetStartColumn(column);
		for (i=500; i<600; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
                OLED_SSD1306_SetStartPage(page+6);  
        OLED_SSD1306_SetStartColumn(column);
		for (i=600; i<700; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
               OLED_SSD1306_SetStartPage(page+7);  
        OLED_SSD1306_SetStartColumn(column);
		for (i=700; i<800; i++){OLED_SSD1306_WriteData(Pic_SSD1306[i]);}
                OLED_SSD1306_SetStartPage(page+8); 
                
                
                
                
}









