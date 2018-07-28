/*
 * This file contains some mpu6050 operation.
 * By IC���� (1394024051@qq.com)
 * 2014-12-19 v1.0
 */
#include "MPL3115.h"
#include "I2C.h"
/**********************************************************/
//�������ƣ�void MPL3115Init
//��ڲ�������
//���ڲ�������
//�������ܣ�MPL3115��ʼ��
/**********************************************************/
void MPL3115_Init()
{  
  I2CInit();
  I2CWrite(CTRL_REG1,"10111000", 0x0005); //0xB9
  I2CWrite(PT_DATA_CFG,"00000111",0x0005); //0x07
  I2CWrite(CTRL_REG1,"10111001", 0x0005); //0xB9
}
/**********************************************************/
//�������ƣ�readAltitude
//��ڲ�������
//���ڲ��������غ���
//�������ܣ���ȡMPL3115����
/**********************************************************/
float readAltitude()
{
  uchar statu;
  unsigned char MSB=0,CSB=0,LSB=0;
  I2CRead(STATUS,&statu, 0x0005);
  if(statu & 0x02)
  {
     I2CRead(0x01,&MSB, 0x0005);
     I2CRead(0x02,&CSB, 0x0005);
     I2CRead(0x03,&LSB, 0x0005);
     
     float tempcsb = (LSB>>4)/16.0;

     float altitude = (float)( (MSB << 8) | CSB) + tempcsb;

     return(altitude);
  }
  return 0 ;
}
/**********************************************************/
//�������ƣ�readTemp
//��ڲ�������
//���ڲ����������¶�
//�������ܣ���ȡMPL3115�¶�ֵ
/**********************************************************/
float readTemp()
{
  uchar statu;
  uchar T_MSB=0,T_LSB=0;
  I2CRead(STATUS,&statu, 0x0005);
  if( statu & 0x02)
  {
     I2CRead(0x04,&T_MSB, 0x0005);
     I2CRead(0x05,&T_LSB, 0x0005);

     float temperature = (float)(T_MSB + (float)(T_LSB>>4)/16);

     return(temperature);
  }
  return 0;
}