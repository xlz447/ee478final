/***************************************************************/
//	Project:	�`�μƾ������w�q	
//	Version:	V1.0
//	Author:		Alan Jeck
//	Date:		2009-09-08
//	MCU:		N/A
//	Crystal:	N/A 
//	�����G		�`�μƾ������w�q		
/**************************************************************/

/********************* Modify History *************************
//	���			����			���e
/---------------------------------------------------------------
//1.	2009-09-08		Version: V 1.0       �s����


***************************************************************/


#if	!defined(__MYTYPE_H)
#define		 __MYTYPE_H

//�L�Ÿ�
typedef	unsigned char byte;
typedef	unsigned char BYTE;
typedef	unsigned char uchar;
typedef	unsigned char UCHAR;
typedef	unsigned char uint8;
typedef	unsigned char UINT8;
typedef unsigned int  uint;
typedef unsigned int  UINT;
typedef unsigned short  WORD;
typedef unsigned short  word;
typedef unsigned short int  uint16;
typedef unsigned short int  UINT16;
typedef unsigned long int	uint32;
typedef unsigned long int	UINT32;
typedef unsigned long		ulong;
typedef unsigned long		ULONG;
typedef unsigned long		DWORD;
typedef unsigned long		dword;
//typedef unsigned long long	uint64;
//typedef unsigned long long	UINT64;
typedef   unsigned short ushort;
typedef   unsigned short USHORT;


//���Ÿ�
typedef	signed char SCHAR;
typedef	signed char schar;
typedef	signed char CHAR;
typedef	signed char int8;
typedef	signed char INT8;
typedef signed short int  int16;
typedef signed short int  INT16;
typedef signed short int  SHORT;
typedef signed long int	int32;
typedef signed long int	INT32;
typedef signed long int	LONG;
//typedef signed long long	int64;
//typedef signed long long	INT64;


//#define	FALSE	(0)
//#define	TRUE	(1)
#define FALSE   0
#define TRUE    (!FALSE)

typedef	UCHAR	BOOL;

//----------------------------------------------------------------------------------------------------------------
// macros
//----------------------------------------------------------------------------------------------------------------
#define		SWAP(x)					((((x) & 0xFF) << 8) | (((x) >> 8) & 0xFF))	//���C�r�`�洫

#define		MSB(x)					(((x) >> 8) & 0xFF)		//�C�r�`
#define		LSB(x)					((x) & 0xFF)			//���r�`


#define		BYTE1(dw)				((BYTE)(dw))							//�q�C�ܰ�:�Ĥ@�r�`
#define		BYTE2(dw)				((BYTE)((((UINT32)(dw))>>8) & 0xFF))	//�q�C�ܰ�:�Ĥ@�r�`
#define		BYTE3(dw)				((BYTE)((((UINT32)(dw))>>16) & 0xFF))	//�q�C�ܰ�:�Ĥ@�r�`
#define		BYTE4(dw)				((BYTE)((((UINT32)(dw))>>24) & 0xFF))	//�q�C�ܰ�:�Ĥ@�r�`



//----------------------------------------------------------------------------------------------------------------
//�q Windows.h ���_��L�Ӫ�
#define		MAKEWORD(a, b)				((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define		MAKELONG(a, b)				((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define		LOWORD(l)					((WORD)(l))
#define		HIWORD(l)					((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define		LOBYTE(w)					((BYTE)(w))
#define		HIBYTE(w)					((BYTE)(((WORD)(w) >> 8) & 0xFF))
//----------------------------------------------------------------------------------------------------------------



//----------------------------------------------------------------------------------------------------------------
// C ��ާ@
#define		Set_Bit(val, bitn)		(val |= (/*1 <<*/(bitn)))		//�m�Y�쬰 1
#define		Clr_Bit(val, bitn)		(val &= ~(/*1<<*/(bitn)))		//�m�Y�쬰 0
#define		Get_Bit(val, bitn)		(val & (1<<(bitn)) )		//���o�Y�쪺��
//----------------------------------------------------------------------------------------------------------------

#define		_BV(bit)				(1<<(bit))					//�m�Y��
#define		_BC(bit)				(0<<(bit))					//�M 0





#endif

