/*******************************************************************************
	專案名稱:	OLED 主函數
	MCU		:	MSP430
	開發環境:	IAR MSP430
	作者:		Alan Jeck(QQ:18655038 E-mail:lucky_jeck@163.com)
	日期:		2012-01-10
	說明:		

	Update	History:
	Versio:	Date:		Detail:
	V1.0.0	2012-01-10	初始版本
	
*******************************************************************************/

#include	<io430.h>
#include	"OLED_SSD1306.h"
#include	"Fonts_SSD1306.h"
#include	"Picture_SSD1306.h"





int main( void )
{
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;

	//OLED_SSD1306_Init();
	extern	void	OLED_DemoMain(void);
	OLED_DemoMain();
	
	P1DIR |= BIT6;
	while (1)
	{
		P1OUT ^= BIT6;
		__delay_cycles(500000);
	}
	
	//return 0;
}
