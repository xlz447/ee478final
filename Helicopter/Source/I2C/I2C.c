#include <msp430f2274.h>
#include "I2C.h"

//------------------------------------------I2C SETUP & FUNCTIONS--------------------------------------//

/*********************************************************
*名称：I2C_Init
*功能：I2C初始化
*入口参数：SlaveAddr:从机的设备地址
*出口参数：无
*说明：设置为P1.6和P1.7为IIC通信端口，使用SMCLK（32.768khz）
作为串口的时钟，配置波特率为9600
**********************************************************/
void I2C_Init (uchar SlaveAddr)
{
  P3DIR |= BIT2;
  P3OUT |= BIT2;
  // 输出9个时钟 以恢复I2C总线状态
  for( uchar i = 0 ; i < 9 ; i++ )
  {
    P3OUT |= BIT2;
    __delay_cycles(16000);
    P3OUT &= ~BIT2;
    __delay_cycles(16000);
  }
  
  P3SEL |= BIT2 | BIT1;                     // I2C pins (3.2-SCL; 3.1-SDA)                
  
  //PM5CTL0 &= ~LOCKLPM5;                   // 关闭上电端口默认输出高阻抗的功能，使能上电保持起始设置
  
  // Configure USCI_B0 for I2C mode
  UCB0CTL1 |= UCSWRST;                     // Software reset enabled
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC ;   // Master mode, I2C mode, synchronous
  UCB0CTL1 |= UCSSEL_2;                    // Use SMCLK, keep SW reset
  //UCB0CTLW1 |= UCASTP_2;                 // 自动产生停止位在UCB0TBCNT之后
  UCB0BR0 = 160;                          // fSCL = SMCLK/12 = ~100kHz
  // 波特率 = SMCLK / 8
  //UCB0TBCNT = 0x0005;                    // number of bytes to be received
  UCB0I2CSA = SlaveAddr;                   // Slave address
  UCB0CTL1 &= ~UCSWRST;                    // Clear SW reset, resume operation
  //UCB0IE |= UCRXIE | UCNACKIE | UCBCNTIE
  
}
/**********************************************************/
//函数名称：void I2C_WriteInit
//入口参数：无
//出口参数：无
//函数功能：I2C写数据初始化，发送模式，接收中断关闭，发送中断启用
/**********************************************************/
void I2C_WriteInit() 
{
  UCB0CTL1  |= UCTR;         // 写模式
  IFG2      &= ~UCB0TXIFG;   //清除发送完成标志位
  IE2       &= ~UCB0RXIE;    // disable Receive ready interrupt
  IE2       |=  UCB0TXIE;    // enable Transmit ready interrupt
  UCB0CTL1  |= UCTXSTT;      // 发送启动位和写控制字节
  __delay_cycles(10); 
}

/**********************************************************/
//函数名称：void I2C_ReadInit
//入口参数：无
//出口参数：无
//函数功能：I2C读数据初始化，接收模式，接收中断开启，发送中断关闭
/**********************************************************/
void I2C_ReadInit()
{
  UCB0CTL1  &= ~UCTR;        // UCTR=0 => Receive Mode (R/W bit = 1) 写模式  
  IFG2      &= ~UCB0RXIFG;   // 清除发送完成标志位
  IE2       &= ~UCB0TXIE;    // disable Transmit ready interrupt
  IE2       |=  UCB0RXIE;    // enable Receive ready interrupt
  UCB0CTL1  |=  UCTXSTT;     // 开始条件产生,开始I2C通信
  __delay_cycles(10); 
}

/**********************************************************/
//函数名称：unsigned char I2C_Write
//入口参数：address->寄存器地址，data->要往寄存器地址中写入的数据
//出口参数：返回IIC写是否成功的状态，1->发送失败，0->发送成功
//函数功能：IIC发送data数据到设备的address这个寄存器中
/**********************************************************/
unsigned char I2C_Write(uchar address,uchar data)
{
  while(UCB0CTL1 & UCTXSTP);
  UCB0CTL1 |= UCTXSTT + UCTR;
  UCB0TXBUF = address;
  while((IFG2 & UCB0TXIFG) == 0);
  UCB0TXBUF = data;
  while((IFG2 & UCB0TXIFG) == 0);
  UCB0CTL1 |= UCTXSTP + UCTXNACK;
  while((UCB0CTL1 & UCTXSTP) == 1);
  return 0;
}

/**********************************************************/
//函数名称：unsigned char I2C_Read
//入口参数：address->寄存器地址，*pword_value->把寄存器地址中读取的数据存入这个指针指向的变量
//出口参数：返回IIC写是否成功的状态，1->读取失败，0->读取成功
//函数功能：IIC接收设备的address这个寄存器中的数据
/**********************************************************/
unsigned char I2C_Read(uchar address,uchar *pword_value)
{
  while(UCB0CTL1 & UCTXSTP);
  UCB0CTL1 |= UCTXSTT + UCTR;
  UCB0TXBUF = address;
  while((IFG2 & UCB0TXIFG) == 0);
  IFG2 &= ~UCB0TXIFG;
  
  UCB0CTL1 &= ~UCTR;
  while(UCB0CTL1 & UCTXSTP);
  
  UCB0CTL1 |= UCTXSTT;
  while((UCB0CTL1 & UCTXSTT)==1);
  while((IFG2 & UCB0RXIFG)==0);
  *pword_value = UCB0RXBUF;
  
  delay_us(500);
  UCB0CTL1 |= UCTXSTP +UCTXNACK;
  while((UCB0CTL1 & UCTXSTP)==1);
  
  return 0;
}