/* 
 * File:   ketCube_arduino_i2c.h
 * Author: Tomáš Hák
 *
 * Created on 24. září 2019, 20:12
 */

#ifndef KETCUBE_ARDUINO_I2C_H
#define KETCUBE_ARDUINO_I2C_H

#include <stdarg.h>
#include "ketCube_i2c.h"


static inline ketCube_cfg_DrvError_t ketCube_I2CInit(void)
{
    return ketCube_I2C_Init();
}

static inline ketCube_cfg_DrvError_t ketCube_I2CUnInit(void)
{
    return ketCube_I2C_UnInit();
}

static inline ketCube_cfg_DrvError_t ketCube_I2CReadData(uint8_t Addr, uint8_t Reg, uint8_t * pBuffer, uint16_t Size)
{
	return ketCube_I2C_ReadData(Addr, Reg, pBuffer, Size);
}

static inline ketCube_cfg_DrvError_t ketCube_I2CWriteData(uint8_t Addr, uint8_t Reg, uint8_t * pBuffer, uint16_t Size)
{
	return ketCube_I2C_WriteData(Addr, Reg, pBuffer, Size);
}

static inline ketCube_cfg_DrvError_t ketCube_I2CWriteRawData(uint8_t Addr, uint8_t * pBuffer, uint16_t Size)
{
	return ketCube_I2C_WriteRawData(Addr, pBuffer, Size);
}

static inline ketCube_cfg_DrvError_t ketCube_I2CReadRawData(uint8_t Addr, uint8_t * pBuffer, uint16_t Size)
{
	return ketCube_I2C_ReadRawData(Addr, pBuffer, Size);
}

static inline uint8_t crc8(const uint8_t *data, int len)
{
	const uint8_t POLYNOMIAL = 0x31;
	uint8_t crc = 0xFF;
	
	for (uint8_t j = len; j; --j) {
		crc ^= *data++;
		
		for (uint8_t i = 8; i; --i) {
			crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
		}
	}	
	
	return crc;
}

#endif /* KETCUBE_ARDUINO_I2C_H */

