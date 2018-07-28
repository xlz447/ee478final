#include <msp430f2274.h>
#include "I2C.h"

//------------------------------------------I2C SETUP & FUNCTIONS--------------------------------------//

/*********************************************************
*���ƣ�I2C_Init
*���ܣ�I2C��ʼ��
*��ڲ�����SlaveAddr:�ӻ����豸��ַ
*���ڲ�������
*˵��������ΪP1.6��P1.7ΪIICͨ�Ŷ˿ڣ�ʹ��SMCLK��32.768khz��
��Ϊ���ڵ�ʱ�ӣ����ò�����Ϊ9600
**********************************************************/
void I2C_Init (uchar SlaveAddr)
{
  P3DIR |= BIT2;
  P3OUT |= BIT2;
  // ���9��ʱ�� �Իָ�I2C����״̬
  for( uchar i = 0 ; i < 9 ; i++ )
  {
    P3OUT |= BIT2;
    __delay_cycles(16000);
    P3OUT &= ~BIT2;
    __delay_cycles(16000);
  }
  
  P3SEL |= BIT2 | BIT1;                     // I2C pins (3.2-SCL; 3.1-SDA)                
  
  //PM5CTL0 &= ~LOCKLPM5;                   // �ر��ϵ�˿�Ĭ��������迹�Ĺ��ܣ�ʹ���ϵ籣����ʼ����
  
  // Configure USCI_B0 for I2C mode
  UCB0CTL1 |= UCSWRST;                     // Software reset enabled
  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC ;   // Master mode, I2C mode, synchronous
  UCB0CTL1 |= UCSSEL_2;                    // Use SMCLK, keep SW reset
  //UCB0CTLW1 |= UCASTP_2;                 // �Զ�����ֹͣλ��UCB0TBCNT֮��
  UCB0BR0 = 160;                          // fSCL = SMCLK/12 = ~100kHz
  // ������ = SMCLK / 8
  //UCB0TBCNT = 0x0005;                    // number of bytes to be received
  UCB0I2CSA = SlaveAddr;                   // Slave address
  UCB0CTL1 &= ~UCSWRST;                    // Clear SW reset, resume operation
  //UCB0IE |= UCRXIE | UCNACKIE | UCBCNTIE
  
}
/**********************************************************/
//�������ƣ�void I2C_WriteInit
//��ڲ�������
//���ڲ�������
//�������ܣ�I2Cд���ݳ�ʼ��������ģʽ�������жϹرգ������ж�����
/**********************************************************/
void I2C_WriteInit() 
{
  UCB0CTL1  |= UCTR;         // дģʽ
  IFG2      &= ~UCB0TXIFG;   //���������ɱ�־λ
  IE2       &= ~UCB0RXIE;    // disable Receive ready interrupt
  IE2       |=  UCB0TXIE;    // enable Transmit ready interrupt
  UCB0CTL1  |= UCTXSTT;      // ��������λ��д�����ֽ�
  __delay_cycles(10); 
}

/**********************************************************/
//�������ƣ�void I2C_ReadInit
//��ڲ�������
//���ڲ�������
//�������ܣ�I2C�����ݳ�ʼ��������ģʽ�������жϿ����������жϹر�
/**********************************************************/
void I2C_ReadInit()
{
  UCB0CTL1  &= ~UCTR;        // UCTR=0 => Receive Mode (R/W bit = 1) дģʽ  
  IFG2      &= ~UCB0RXIFG;   // ���������ɱ�־λ
  IE2       &= ~UCB0TXIE;    // disable Transmit ready interrupt
  IE2       |=  UCB0RXIE;    // enable Receive ready interrupt
  UCB0CTL1  |=  UCTXSTT;     // ��ʼ��������,��ʼI2Cͨ��
  __delay_cycles(10); 
}

/**********************************************************/
//�������ƣ�unsigned char I2C_Write
//��ڲ�����address->�Ĵ�����ַ��data->Ҫ���Ĵ�����ַ��д�������
//���ڲ���������IICд�Ƿ�ɹ���״̬��1->����ʧ�ܣ�0->���ͳɹ�
//�������ܣ�IIC����data���ݵ��豸��address����Ĵ�����
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
//�������ƣ�unsigned char I2C_Read
//��ڲ�����address->�Ĵ�����ַ��*pword_value->�ѼĴ�����ַ�ж�ȡ�����ݴ������ָ��ָ��ı���
//���ڲ���������IICд�Ƿ�ɹ���״̬��1->��ȡʧ�ܣ�0->��ȡ�ɹ�
//�������ܣ�IIC�����豸��address����Ĵ����е�����
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