/* This library file is found online from a chinese forum website
 * the thread can be found here: http://www.eyesourcecode.com/thread-23681-1-1.html
 * Author is Alen Jeck, and the date is 01/10/2012
 */


#if			!defined(__FONTS__SSD1306__H__)
#define		__FONTS__SSD1306__H__

#include	<intrinsics.h>
#include        <msp430f2274.h>

#include	"MyType.h"



extern	UCHAR const Fonts_ASCII6x8[][6];
extern	UCHAR const Fonts_Numeric16x32[][60];

extern	UCHAR const Fonts_Chinese16x16[][32];


extern	unsigned char const AnsciiDot8x16[];
extern	unsigned char const GB16X16[];
#endif

