/**
 * @file    ketCube_ltc2495.c
 * @author  Jan Belohoubek
 * @version pre-alpha
 * @date    2018-09-28
 * @brief   This file contains the LTC2495 driver
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

#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_i2c.h"
#include <math.h>

#include "ketCube_cfg.h"
#include "ketCube_terminal.h"
#include "ketCube_i2c.h"
#include "ketCube_ltc2495.h"

#ifdef KETCUBE_CFG_INC_MOD_LTC2495

ketCube_ltc2495_moduleCfg_t ketCube_ltc2495_moduleCfg;

/**
 * @brief Initialize the LTC2495 sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_ltc2495_Init(ketCube_InterModMsg_t *** msg)
{
    // Init drivers
    if (ketCube_I2C_Init() != KETCUBE_CFG_MODULE_OK) {
        return KETCUBE_CFG_MODULE_ERROR;
    }

    return KETCUBE_CFG_MODULE_OK;
}

/**
 * @brief Initialize the LTC2495 sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_ltc2495_UnInit(void)
{
    // UnInit drivers
    return ketCube_I2C_UnInit();
}

/**
  * @brief Read data from LTC2495 sensor
  *
  * @param buffer pointer to fuffer for storing the result of milivolt mesurement
  * @param len data len in bytes
  *
  * @retval KETCUBE_CFG_MODULE_OK in case of success
  * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
  */
ketCube_cfg_ModError_t ketCube_ltc2495_ReadData(uint8_t * buffer,
                                                uint8_t * len)
{
    uint8_t i;
    uint8_t data[3];
    uint32_t raw;
    uint32_t res_d;
    
    *len = 0;
    for (i = 0; i < KETCUBE_LTC2495_CHANNELS; i++) {
        
        // to prevent race conditions with other modules
        HAL_Delay(KETCUBE_LTC2495_MEAS_TIME_MS);
        
        data[1] = 0x90;
        data[0] = 0xA0 + i;
        if (ketCube_I2C_WriteRawData(KETCUBE_LTC2495_I2C_ADDRESS, &(data[0]), 2)) {
            ketCube_terminal_DebugPrintln("LTC2495 :: E0");
            data[0] = 0xC1;
            //return KETCUBE_CFG_MODULE_ERROR;
        } else {
            HAL_Delay(KETCUBE_LTC2495_MEAS_TIME_MS);
            
            if (ketCube_I2C_ReadRawData(KETCUBE_LTC2495_I2C_ADDRESS, &(data[0]), 3)) {
                ketCube_terminal_DebugPrintln("LTC2495 :: E1");
                //return KETCUBE_CFG_MODULE_ERROR;
                data[0] = 0xC2;
            }
        }
        
        if (data[0] < 0xC0) {
            raw = (((uint32_t) (0x7F & data[0]) << 10) | (((uint32_t) data[1]) << 2) | ((uint32_t) data[2] >> 6));
            res_d = (uint32_t) (raw * 7.6295F);  // Ohm - 0.5*Rn/65535
            ketCube_terminal_DebugPrintln("LTC2495 :: (CH%d) :: RawResistance: %d", i, raw);
            ketCube_terminal_DebugPrintln("LTC2495 :: (CH%d) :: Resistance: %d k", i, res_d/1000);
            buffer[3*i + 0] = (0x7F & data[0]);
            buffer[3*i + 1] = data[1];
            buffer[3*i + 2] = data[2];
        } else {
            ketCube_terminal_DebugPrintln("LTC2495 :: (CH%d) :: Overflow", i);
            buffer[3*i + 0] = data[0];
            buffer[3*i + 1] = data[1];
            buffer[3*i + 2] = data[2];
        }
        
        *len += 3;
    }

    return KETCUBE_CFG_MODULE_OK;
}

#endif                          /* KETCUBE_CFG_INC_MOD_LTC2495 */
