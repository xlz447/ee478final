void I2C_Init(uchar);
void I2C_WriteInit();
void I2C_ReadInit();
unsigned char I2C_Write(uchar,uchar);
unsigned char I2C_Read(uchar address,uchar *pword_value);