/**
 * @file    ketCube_adpd188.c
 * @author  Jan Bělohoubek, Ondřej Růžička
 * @version 0.1
 * @date    2019-5-2
 * @brief   This file contains definitions for the ADPD188 driver
 * 
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2018 University of West Bohemia in Pilsen
 * All rights reserved.</center></h2>
 *
 * Developed by:
 * The SmartCampus Team
 * Department of Technologies and Measurement
 * www.smartcampus.cz | www.zcu.cz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), 
 * to deal with the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software 
 * is furnished to do so, subject to the following conditions:
 *
 *    - Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimers.
 *    
 *    - Redistributions in binary form must reproduce the above copyright notice, 
 *      this list of conditions and the following disclaimers in the documentation 
 *      and/or other materials provided with the distribution.
 *    
 *    - Neither the names of The SmartCampus Team, Department of Technologies and Measurement
 *      and Faculty of Electrical Engineering University of West Bohemia in Pilsen, 
 *      nor the names of its contributors may be used to endorse or promote products 
 *      derived from this Software without specific prior written permission. 
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE CONTRIBUTORS OR COPYRIGHT HOLDERS 
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS WITH THE SOFTWARE. 
 */

#include "ketCube_cfg.h"
#include "ketCube_terminal.h"
#include "ketCube_adpd188.h"

#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_i2c.h"
#include "ketCube_i2c.h"

#ifdef KETCUBE_CFG_INC_MOD_ADPD188

ketCube_adpd188_moduleCfg_t ketCube_adpd188_moduleCfg; /*!< Module configuration storage */
extern I2C_HandleTypeDef KETCUBE_I2C_Handle;

/**
 * @brief  Read AnalogDevices I2C periph 8-bit register
 * @param  devAddr I2C Address
 * @param  regAddr register address
 * @param  data pointer to a 16-bit storage
 * 
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
static ketCube_cfg_ModError_t ketCube_adpd188_readReg(uint8_t devAddr,
                                                      uint8_t regAddr,
                                                      uint16_t * data)
{
    uint8_t try = 3;
    uint8_t buffer[2];

    while (try > 0) {
        HAL_StatusTypeDef status =
            HAL_I2C_Master_Transmit(&KETCUBE_I2C_Handle, devAddr,
                                    &(regAddr),
                                    1, KETCUBE_I2C_TIMEOUT);
        if (status != HAL_OK) {
            try--;
            continue;
        }
        //HAL_Delay(1);
        status =
            HAL_I2C_Master_Receive(&KETCUBE_I2C_Handle, devAddr, &(buffer[0]),
                                   2, KETCUBE_I2C_TIMEOUT);
        if (status == HAL_OK) {
            *data = (buffer[0] << 8) | (buffer[1]);
            
            return KETCUBE_CFG_MODULE_OK;
        }
        try--;
    }

    return KETCUBE_CFG_MODULE_ERROR;
}


/**
 * @brief  Write AnalogDevices I2C periph 8-bit register
 * @param  devAddr I2C Address
 * @param  regAddr register address
 * @param  data pointer to a 16-bit storage
 * 
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
static ketCube_cfg_ModError_t ketCube_adpd188_writeReg(uint8_t devAddr,
                                                       uint8_t regAddr,
                                                       uint16_t * data)
{
    uint8_t buffer[3];
    
    buffer[0] = regAddr;
    
    buffer[1] = (uint8_t) (((*data) >> 8) & 0xFF);
    buffer[2] = (uint8_t) (((*data) >> 0) & 0xFF);
    
    if (ketCube_I2C_WriteData(devAddr, buffer[0], &(buffer[1]), 2)) {
        return KETCUBE_CFG_MODULE_ERROR;
    } else {
        return KETCUBE_CFG_MODULE_OK;
    }
    return KETCUBE_CFG_MODULE_ERROR;
}

/**
 * @brief Initialize the ADPD188 sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_adpd188_Init(ketCube_InterModMsg_t *** msg)
{

    // Init drivers
    if (ketCube_I2C_Init() != KETCUBE_CFG_MODULE_OK) {
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
    // Custom Init Code

    return KETCUBE_CFG_MODULE_OK;
}

/**
 * @brief Initialize the ADPD188 sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_adpd188_UnInit(void)
{
    // UnInit drivers
    
    
    return KETCUBE_CFG_MODULE_OK;
}


/**
  * @brief Read data from ADPD188 sensor
  *
  * @param buffer pointer to fuffer for storing the result of measurements
  * @param len data len in bytes
  *
  * @retval KETCUBE_CFG_MODULE_OK in case of success
  * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
  */
ketCube_cfg_ModError_t ketCube_adpd188_ReadData(uint8_t * buffer,
                                                uint8_t * len)
{
    uint8_t i = 0;
    uint16_t data;
    uint16_t devID;

    // Get Device ID
    if (ketCube_adpd188_readReg(KETCUBE_ADPD188_I2C_ADDRESS, KETCUBE_ADPD188_REG_DEVID, &devID) == KETCUBE_CFG_MODULE_OK) {
        ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "Device ID: 0x%04X", devID);
    } else {
        ketCube_terminal_ErrorPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "Unable to read devID!");
    }
    
    // Test WriteReg + readBack
    if (ketCube_adpd188_readReg(KETCUBE_ADPD188_I2C_ADDRESS, 0x18, &data) == KETCUBE_CFG_MODULE_OK) {
        ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "Read: 0x%04X", data);
    } else {
        ketCube_terminal_ErrorPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "Unable to read!");
    }
    data = 0x1234;
    if (ketCube_adpd188_writeReg(KETCUBE_ADPD188_I2C_ADDRESS, 0x18, &data) != KETCUBE_CFG_MODULE_OK) {
        ketCube_terminal_ErrorPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "Unable to wite reg!");
    }
    if (ketCube_adpd188_readReg(KETCUBE_ADPD188_I2C_ADDRESS, 0x18, &data) == KETCUBE_CFG_MODULE_OK) {
        ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "ReadBack: 0x%04X", data);
    } else {
        ketCube_terminal_ErrorPrintln(KETCUBE_LISTS_MODULEID_ADPD188, "Unable to readBack!");
    }
    
    // Get sensor data
    // Insert code here ...
    
    
    // Insert measured data to buffer
    buffer[i++] = (data >> 8) & 0xFF;
    buffer[i++] = (data & 0xFF);
    
    *len = i;

    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ADPD188,
                                 "Measured data: %04X", data);

    return KETCUBE_CFG_MODULE_OK;
}

#endif                          /* KETCUBE_CFG_INC_MOD_ADPD188 */
