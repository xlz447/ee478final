/* This library file is found online from a chinese forum website
 * the thread can be found here: http://www.eyesourcecode.com/thread-23681-1-1.html
 * Author is Alen Jeck, and the date is 01/10/2012
 */


#if			!defined(__OLED__SSD1306__H__)
#define		__OLED__SSD1306__H__

//#include	<io430.h>
//#include	<in430.h>
#include	<intrinsics.h>
#include <msp430f2274.h>

#include	"MyType.h"




//----------------------------------------------------------------------------------
//OLED SSD1306 SPI �r�: SCK
#define		OLED_SSD1306_SCLK_DIR			(P3DIR)
#define		OLED_SSD1306_SCLK_OUT			(P3OUT)
#define		OLED_SSD1306_SCLK_PIN_NUM		(BIT3)

#define		OLED_SSD1306_SCLK_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SSD1306_SCLK_H			(Set_Bit(P3OUT,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SSD1306_SCLK_L			(Clr_Bit(P3OUT,OLED_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 SPI ����ݔ�뵽 LCD: MOSI
#define		OLED_SSD1306_SDIN_DIR			(P3DIR)
#define		OLED_SSD1306_SDIN_OUT			(P3OUT)
#define		OLED_SSD1306_SDIN_PIN_NUM		(BIT1)

#define		OLED_SSD1306_SDIN_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SSD1306_SDIN_H			(Set_Bit(P3OUT,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SSD1306_SDIN_L			(Clr_Bit(P3OUT,OLED_SSD1306_SDIN_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 �������: D/C
#define		OLED_SSD1306_DC_DIR			(P4DIR)
#define		OLED_SSD1306_DC_OUT			(P4OUT)
#define		OLED_SSD1306_DC_PIN_NUM			(BIT2)

#define		OLED_SSD1306_DC_IO_INIT			(Set_Bit(P4DIR,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_SSD1306_DC_H			(Set_Bit(P4OUT,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_SSD1306_DC_L		        (Clr_Bit(P4OUT,OLED_SSD1306_DC_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 Ƭ�x: CS
#define		OLED_SSD1306_CE_DIR			(P3DIR)
#define		OLED_SSD1306_CE_OUT			(P3OUT)
#define		OLED_SSD1306_CE_PIN_NUM			(BIT0)

#define		OLED_SSD1306_CE_IO_INIT			(Set_Bit(P3DIR,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_SSD1306_CE_H		        (Set_Bit(P3OUT,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_SSD1306_CE_L			(Clr_Bit(P3OUT,OLED_SSD1306_CE_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 ��λ: RST
#define		OLED_SSD1306_RST_DIR			(P4DIR)
#define		OLED_SSD1306_RST_OUT			(P4OUT)
#define		OLED_SSD1306_RST_PIN_NUM		(BIT1)

#define		OLED_SSD1306_RST_IO_INIT		(Set_Bit(P4DIR,OLED_SSD1306_RST_PIN_NUM))
#define		OLED_SSD1306_RST_H			(Set_Bit(P4OUT,OLED_SSD1306_RST_PIN_NUM))
#define		OLED_SSD1306_RST_L			(Clr_Bit(P4OUT,OLED_SSD1306_RST_PIN_NUM))
//----------------------------------------------------------------------------------





#define		XLevelL							(0x00)
#define		XLevelH							(0x10)
#define		XLevel							(((XLevelH&0x0F)*16+XLevelL))
#define		Max_Column						(128)
#define		Max_Row							(64)
#define		Brightness						(0xCF)




#define		OLED_SSD1306_CMD_FUN_SET		()



//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_Init
//	���׃��:	�o
//	����ֵ:		�o
//	�����f��:	LCD ��ʼ��
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Init();

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteData
//	���׃��:	bData			:			����
//	����ֵ:		�o
//	�����f��:	��һ�������� LCD
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteData(UCHAR bData);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteCmd
//	���׃��:	bCommand		:			����
//	����ֵ:		�o
//	�����f��:	use SPI send byte
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteCmd(UCHAR bCommand);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_Set_xy
//	���׃��:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//	����ֵ:		�o
//	�����f��:	�O�Ì�Ҫ�������ďĘ�
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Set_xy(UCHAR x,UCHAR y);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_Clear
//	���׃��:	�o
//	����ֵ:		�o
//	�����f��:	��� LCD
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Clear(void);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteChar
//	���׃��:	c				:			��Ҫ�����ַ�
//	����ֵ:		�o
//	�����f��:	display a asciifont6*8
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteChar(UCHAR c);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteStringxy
//	���׃��:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�ַ������_�^ָ�
//	����ֵ:		�o
//	�����f��:	�@ʾӢ���ַ���
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteStringxy(UCHAR x,UCHAR y,UCHAR *pszString);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteString
//	���׃��:	pszString		:			�ַ������_�^ָ�
//	����ֵ:		�o
//	�����f��:	�@ʾӢ���ַ���,��ǰ�Ό������Ĕ�����ַ�_�猑.
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteString(UCHAR *pszString);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteChinese
//	���׃��:	iColumn			:			��
//				iLine			:			��
//				bCharIndex		:			�����ַ�������
//	����ֵ:		�o
//	�����f��:	�@ʾ�����ַ���.
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteChinese(UCHAR iColumn,UCHAR iLine,UCHAR bCharIndex);

//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_WriteChinese
//	���׃��:	pPic			:			�DƬ���_�^ָ�
//				iLen			:			�DƬ���_�^��С
//	����ֵ:		�o
//	�����f��:	�@ʾ�DƬ
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_DisplayPicture(UCHAR const *pPic,UINT16 iLen);



//extern	char static number_array[];  //����@ʾ����,�c����LCD_Disp_Num()�������P
//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_Disp_Numeric
//	���׃��:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�ַ������_�^ָ�
//	����ֵ:		�o
//	�����f��:	�@ʾ 6x8 �Ĕ���
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Disp_Numeric(UCHAR x,UCHAR y,UINT16 Num);
 
//--------------------------------------------------------------------------------------
//	����ԭ��:	OLED_SSD1306_Disp_Num
//	���׃��:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�ַ������_�^ָ�
//	����ֵ:		�o
//	�����f��:	�@ʾ 16x32 �Ĕ���
//--------------------------------------------------------------------------------------
extern	void	LCD_Disp_BigNumeric(UCHAR x,UCHAR y,UCHAR n);


extern	void	LCD_Disp_clkdot();

extern	void	LCD_Disp_clkdot_blank();

extern	void OLED_SSD1306_Displaypicturefull(UINT16 const Pic_SSD1306[],UCHAR page,UCHAR column);

void	OLED_SSD1306_Display8x16Str(UCHAR page, UCHAR column, UCHAR *str);

#endif




