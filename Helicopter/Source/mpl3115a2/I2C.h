/*
 * This file contains some I2C operation.
 * By IC≈¿≥Ê (1394024051@qq.com)
 * 2014-12-19 v1.0
 */
#ifndef I2C_H_
#define I2C_H_

#include <msp430.h>
#include <stdint.h>

void I2CInit(void);
uint16_t I2CWrite( uint8_t sladdr , uint8_t *data , uint16_t n );
uint16_t I2CRead( uint8_t sladdr , uint8_t *data , uint16_t n );


#endif /* I2C_H_ */