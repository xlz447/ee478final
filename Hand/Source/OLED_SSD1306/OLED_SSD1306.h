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
//OLED SSD1306 SPI 時鐘: SCK
#define		OLED_SSD1306_SCLK_DIR			(P3DIR)
#define		OLED_SSD1306_SCLK_OUT			(P3OUT)
#define		OLED_SSD1306_SCLK_PIN_NUM		(BIT3)

#define		OLED_SSD1306_SCLK_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SSD1306_SCLK_H			(Set_Bit(P3OUT,OLED_SSD1306_SCLK_PIN_NUM))
#define		OLED_SSD1306_SCLK_L			(Clr_Bit(P3OUT,OLED_SSD1306_SCLK_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 SPI 數據輸入到 LCD: MOSI
#define		OLED_SSD1306_SDIN_DIR			(P3DIR)
#define		OLED_SSD1306_SDIN_OUT			(P3OUT)
#define		OLED_SSD1306_SDIN_PIN_NUM		(BIT1)

#define		OLED_SSD1306_SDIN_IO_INIT		(Set_Bit(P3DIR,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SSD1306_SDIN_H			(Set_Bit(P3OUT,OLED_SSD1306_SDIN_PIN_NUM))
#define		OLED_SSD1306_SDIN_L			(Clr_Bit(P3OUT,OLED_SSD1306_SDIN_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 命令控制: D/C
#define		OLED_SSD1306_DC_DIR			(P4DIR)
#define		OLED_SSD1306_DC_OUT			(P4OUT)
#define		OLED_SSD1306_DC_PIN_NUM			(BIT2)

#define		OLED_SSD1306_DC_IO_INIT			(Set_Bit(P4DIR,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_SSD1306_DC_H			(Set_Bit(P4OUT,OLED_SSD1306_DC_PIN_NUM))
#define		OLED_SSD1306_DC_L		        (Clr_Bit(P4OUT,OLED_SSD1306_DC_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 片選: CS
#define		OLED_SSD1306_CE_DIR			(P3DIR)
#define		OLED_SSD1306_CE_OUT			(P3OUT)
#define		OLED_SSD1306_CE_PIN_NUM			(BIT0)

#define		OLED_SSD1306_CE_IO_INIT			(Set_Bit(P3DIR,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_SSD1306_CE_H		        (Set_Bit(P3OUT,OLED_SSD1306_CE_PIN_NUM))
#define		OLED_SSD1306_CE_L			(Clr_Bit(P3OUT,OLED_SSD1306_CE_PIN_NUM))

//----------------------------------------------------------------------------------
//OLED SSD1306 復位: RST
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
//	函數原型:	OLED_SSD1306_Init
//	入口變量:	無
//	返回值:		無
//	函數說明:	LCD 初始化
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Init();

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteData
//	入口變量:	bData			:			數據
//	返回值:		無
//	函數說明:	寫一個數據到 LCD
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteData(UCHAR bData);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteCmd
//	入口變量:	bCommand		:			命令
//	返回值:		無
//	函數說明:	use SPI send byte
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteCmd(UCHAR bCommand);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_Set_xy
//	入口變量:	x				:			x 坐標(0 -- 83)
//				y				:			y 坐標(0 -- 5)
//	返回值:		無
//	函數說明:	設置將要寫數據的從標
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Set_xy(UCHAR x,UCHAR y);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_Clear
//	入口變量:	無
//	返回值:		無
//	函數說明:	清空 LCD
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Clear(void);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteChar
//	入口變量:	c				:			所要寫的字符
//	返回值:		無
//	函數說明:	display a asciifont6*8
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteChar(UCHAR c);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteStringxy
//	入口變量:	x				:			x 坐標(0 -- 83)
//				y				:			y 坐標(0 -- 5)
//				pszString		:			字符串緩沖區指針
//	返回值:		無
//	函數說明:	顯示英文字符串
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteStringxy(UCHAR x,UCHAR y,UCHAR *pszString);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteString
//	入口變量:	pszString		:			字符串緩沖區指針
//	返回值:		無
//	函數說明:	顯示英文字符串,以前次寫數據的數據地址開如寫.
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteString(UCHAR *pszString);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteChinese
//	入口變量:	iColumn			:			列
//				iLine			:			行
//				bCharIndex		:			中文字符的索引
//	返回值:		無
//	函數說明:	顯示中文字符串.
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_WriteChinese(UCHAR iColumn,UCHAR iLine,UCHAR bCharIndex);

//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_WriteChinese
//	入口變量:	pPic			:			圖片緩沖區指針
//				iLen			:			圖片緩沖區大小
//	返回值:		無
//	函數說明:	顯示圖片
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_DisplayPicture(UCHAR const *pPic,UINT16 iLen);



//extern	char static number_array[];  //便於顯示數字,與下面LCD_Disp_Num()函數有關
//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_Disp_Numeric
//	入口變量:	x				:			x 坐標(0 -- 83)
//				y				:			y 坐標(0 -- 5)
//				pszString		:			字符串緩沖區指針
//	返回值:		無
//	函數說明:	顯示 6x8 的數字
//--------------------------------------------------------------------------------------
extern	void	OLED_SSD1306_Disp_Numeric(UCHAR x,UCHAR y,UINT16 Num);
 
//--------------------------------------------------------------------------------------
//	函數原型:	OLED_SSD1306_Disp_Num
//	入口變量:	x				:			x 坐標(0 -- 83)
//				y				:			y 坐標(0 -- 5)
//				pszString		:			字符串緩沖區指針
//	返回值:		無
//	函數說明:	顯示 16x32 的數字
//--------------------------------------------------------------------------------------
extern	void	LCD_Disp_BigNumeric(UCHAR x,UCHAR y,UCHAR n);


extern	void	LCD_Disp_clkdot();

extern	void	LCD_Disp_clkdot_blank();

extern	void OLED_SSD1306_Displaypicturefull(UINT16 const Pic_SSD1306[],UCHAR page,UCHAR column);

void	OLED_SSD1306_Display8x16Str(UCHAR page, UCHAR column, UCHAR *str);

#endif




