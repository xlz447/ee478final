


#if			!defined(__OLED__SSD1306__H__)
#define		__OLED__SSD1306__H__

#include	<io430.h>
#include	<in430.h>
#include	<intrinsics.h>

#include	"MyType.h"




//----------------------------------------------------------------------------------
//OLED SSD1306 SPI ����: SCK
#define		OLED_SSD1306_SCLK_DIR			(P1DIR)
#define		OLED_SSD1306_SCLK_OUT			(P1OUT)
#define		OLED_SSD1306_SCLK_PIN_NUM		(BIT3)

#define		OLED_SSD1306_SCLK_IO_INIT		(Set_Bit(P1DIR,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SSD1306_SCLK_H				(Set_Bit(P1OUT,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SSD1306_SCLK_L				(Clr_Bit(P1OUT,OLED_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 SPI �ƾڿ�J�� LCD: MOSI
#define		OLED_SSD1306_SDIN_DIR			(P1DIR)
#define		OLED_SSD1306_SDIN_OUT			(P1OUT)
#define		OLED_SSD1306_SDIN_PIN_NUM		(BIT4)

#define		OLED_SSD1306_SDIN_IO_INIT		(Set_Bit(P1DIR,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SSD1306_SDIN_H				(Set_Bit(P1OUT,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SSD1306_SDIN_L				(Clr_Bit(P1OUT,OLED_SSD1306_SDIN_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 �R�O����: D/C
#define		OLED_SSD1306_DC_DIR				(P1DIR)
#define		OLED_SSD1306_DC_OUT				(P1OUT)
#define		OLED_SSD1306_DC_PIN_NUM			(BIT2)

#define		OLED_SSD1306_DC_IO_INIT			(Set_Bit(P1DIR,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_SSD1306_DC_H				(Set_Bit(P1OUT,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_SSD1306_DC_L				(Clr_Bit(P1OUT,OLED_SSD1306_DC_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 ����: CS
#define		OLED_SSD1306_CE_DIR				(P1DIR)
#define		OLED_SSD1306_CE_OUT				(P1OUT)
#define		OLED_SSD1306_CE_PIN_NUM			(BIT0)

#define		OLED_SSD1306_CE_IO_INIT			(Set_Bit(P1DIR,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_SSD1306_CE_H				(Set_Bit(P1OUT,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_SSD1306_CE_L				(Clr_Bit(P1OUT,OLED_SSD1306_CE_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 �_��: RST
#define		OLED_SSD1306_RST_DIR			(P1DIR)
#define		OLED_SSD1306_RST_OUT			(P1OUT)
#define		OLED_SSD1306_RST_PIN_NUM		(BIT1)

#define		OLED_SSD1306_RST_IO_INIT		(Set_Bit(P1DIR,OLED_SSD1306_RST_PIN_NUM))
#define		OLED_SSD1306_RST_H				(Set_Bit(P1OUT,OLED_SSD1306_RST_PIN_NUM))
#define		OLED_SSD1306_RST_L				(Clr_Bit(P1OUT,OLED_SSD1306_RST_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 �I�� LED: LED
#define		OLED_SSD1306_LED_DIR			(P1DIR)
#define		OLED_SSD1306_LED_OUT			(P1OUT)
#define		OLED_SSD1306_LED_PIN_NUM		(BIT5)

#define		OLED_SSD1306_LED_IO_INIT		(Set_Bit(P1DIR,OLED_SSD1306_LED_PIN_NUM))
#define		OLED_SSD1306_LED_ON				(Set_Bit(P1OUT,OLED_SSD1306_LED_PIN_NUM))
#define		OLED_SSD1306_LED_OFF			(Clr_Bit(P1OUT,OLED_SSD1306_LED_PIN_NUM))






#define		XLevelL							(0x00)
#define		XLevelH							(0x10)
#define		XLevel							(((XLevelH&0x0F)*16+XLevelL))
#define		Max_Column						(128)
#define		Max_Row							(64)
#define		Brightness						(0xCF)




#define		OLED_SSD1306_CMD_FUN_SET		()



//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Init
//	�J�f�ܶq:	�L
//	��^��:		�L
//	��ƻ���:	LCD ��l��
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Init();

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteData
//	�J�f�ܶq:	bData			:			�ƾ�
//	��^��:		�L
//	��ƻ���:	�g�@�Ӽƾڨ� LCD
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteData(UCHAR bData);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteCmd
//	�J�f�ܶq:	bCommand		:			�R�O
//	��^��:		�L
//	��ƻ���:	use SPI send byte
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteCmd(UCHAR bCommand);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Set_xy
//	�J�f�ܶq:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//	��^��:		�L
//	��ƻ���:	�]�m�N�n�g�ƾڪ��q��
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Set_xy(UCHAR x,UCHAR y);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Clear
//	�J�f�ܶq:	�L
//	��^��:		�L
//	��ƻ���:	�M�� LCD
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Clear(void);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteChar
//	�J�f�ܶq:	c				:			�ҭn�g���r��
//	��^��:		�L
//	��ƻ���:	display a asciifont6*8
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteChar(UCHAR c);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteStringxy
//	�J�f�ܶq:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�r�Ŧ�w�R�ϫ��w
//	��^��:		�L
//	��ƻ���:	��ܭ^��r�Ŧ�
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteStringxy(UCHAR x,UCHAR y,UCHAR *pszString);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteString
//	�J�f�ܶq:	pszString		:			�r�Ŧ�w�R�ϫ��w
//	��^��:		�L
//	��ƻ���:	��ܭ^��r�Ŧ�,�H�e���g�ƾڪ��ƾڦa�}�}�p�g.
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteString(UCHAR *pszString);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteChinese
//	�J�f�ܶq:	iColumn			:			�C
//				iLine			:			��
//				bCharIndex		:			����r�Ū�����
//	��^��:		�L
//	��ƻ���:	��ܤ���r�Ŧ�.
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteChinese(UCHAR iColumn,UCHAR iLine,UCHAR bCharIndex);

//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_WriteChinese
//	�J�f�ܶq:	pPic			:			�Ϥ��w�R�ϫ��w
//				iLen			:			�Ϥ��w�R�Ϥj�p
//	��^��:		�L
//	��ƻ���:	��ܹϤ�
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_DisplayPicture(UCHAR const *pPic,UINT16 iLen);



//extern	char static number_array[];  //�K����ܼƦr,�P�U��LCD_Disp_Num()��Ʀ���
//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Disp_Numeric
//	�J�f�ܶq:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�r�Ŧ�w�R�ϫ��w
//	��^��:		�L
//	��ƻ���:	��� 6x8 ���Ʀr
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Disp_Numeric(UCHAR x,UCHAR y,UINT16 Num);
 
//--------------------------------------------------------------------------------------
//	��ƭ쫬:	OLED_SSD1306_Disp_Num
//	�J�f�ܶq:	x				:			x ����(0 -- 83)
//				y				:			y ����(0 -- 5)
//				pszString		:			�r�Ŧ�w�R�ϫ��w
//	��^��:		�L
//	��ƻ���:	��� 16x32 ���Ʀr
//--------------------------------------------------------------------------------------
extern	void	LCD_Disp_BigNumeric(UCHAR x,UCHAR y,UCHAR n);


extern	void	LCD_Disp_clkdot();

extern	void	LCD_Disp_clkdot_blank();

extern	void OLED_SSD1306_Displaypicturefull(UINT16 const Pic_SSD1306[],UCHAR page,UCHAR column);


#endif




