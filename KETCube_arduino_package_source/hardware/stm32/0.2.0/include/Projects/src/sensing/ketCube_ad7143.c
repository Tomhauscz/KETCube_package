/**
 * @file    ketCube_ad7143.c
 * @author  Jan Belohoubek
 * @version pre-alpha
 * @date    2018-09-28
 * @brief   This file contains the AD7143 driver
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
#include "ketCube_ad7143.h"

#ifdef KETCUBE_CFG_INC_MOD_AD7143

ketCube_ad7143_moduleCfg_t ketCube_ad7143_moduleCfg;

/**
 * @brief Initialize the AD7143 sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_ad7143_Init(ketCube_InterModMsg_t *** msg)
{
       
    // Init drivers
    if (ketCube_I2C_Init() != KETCUBE_CFG_MODULE_OK) {
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
        
    if (ketCube_ad7143_I2CWriteReg(
		KETCUBE_AD7143_I2C_ADDRESS,
		KETCUBE_AD7143_REG_SETUP,
		KETCUBE_AD7143_VALREG_RESET) == KETCUBE_CFG_MODULE_ERROR) {
        ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "AD7143 :: clear register fail");
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0001, 0x000F);
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0002, 0x0690);
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0003, 0x0664);
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0004, 0x290F);
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0005, 0x0000);
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0006, 0x0000);
    ketCube_ad7143_I2CWriteReg(KETCUBE_AD7143_I2C_ADDRESS, 0x0007, 0x0000);
    
    //CIN0 setup -- stage 0
    if ((ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE0_CONNECTION1,
    KETCUBE_AD7143_VALREG_STAGE0_CONF1)
    ||
    ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE0_CONNECTION2,
    KETCUBE_AD7143_VALREG_STAGE0_CONF2)) == KETCUBE_CFG_MODULE_ERROR) {
        ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "CIN0 (stage0) init fail");
        
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
    //CIN2 setup -- stage 1
    if ((ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE1_CONNECTION1,
    KETCUBE_AD7143_VALREG_STAGE1_CONF1)
    ||
    ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE1_CONNECTION2,
    KETCUBE_AD7143_VALREG_STAGE1_CONF2)) == KETCUBE_CFG_MODULE_ERROR) {
        ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "CIN2 (stage1) init fail");
        
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
    //CIN4 setup -- stage 2
    if ((ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE2_CONNECTION1,
    KETCUBE_AD7143_VALREG_STAGE2_CONF1)
    ||
    ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE2_CONNECTION2,
    KETCUBE_AD7143_VALREG_STAGE2_CONF2)) == KETCUBE_CFG_MODULE_ERROR) {
        ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "CIN4 (stage2) init fail");
        
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
    //CIN6 setup -- stage 3
    if ((ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE3_CONNECTION1,
    KETCUBE_AD7143_VALREG_STAGE3_CONF1)
    ||
    ketCube_ad7143_I2CWriteReg(
    KETCUBE_AD7143_I2C_ADDRESS,
    KETCUBE_AD7143_REG_STAGE3_CONNECTION2,
    KETCUBE_AD7143_VALREG_STAGE3_CONF2)) == KETCUBE_CFG_MODULE_ERROR) {
        ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "CIN6 (stage3) init fail");
        
        return KETCUBE_CFG_MODULE_ERROR;
    }
    
    return KETCUBE_CFG_MODULE_OK;
}

/**
 * @brief Initialize the AD7143 sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_ad7143_UnInit(void)
{
    // UnInit drivers
    return ketCube_I2C_UnInit();
}

/**
  * @brief Read data from AD7143 sensor
  *
  * @param buffer pointer to fuffer for storing the result of milivolt mesurement
  * @param len data len in bytes
  *
  * @retval KETCUBE_CFG_MODULE_OK in case of success
  * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
  */
ketCube_cfg_ModError_t ketCube_ad7143_ReadData(uint8_t * buffer,
                                                uint8_t * len)
{
    uint16_t raw0;
    uint16_t raw1;
    uint16_t raw2;
    uint16_t raw3;
    uint16_t id;
    
    float capacity0, capacity1, capacity2, capacity3;

    ketCube_ad7143_I2CReadReg(KETCUBE_AD7143_I2C_ADDRESS,
                                  KETCUBE_AD7143_REG_STAGE0_RAW,
                                  &raw0);
    ketCube_ad7143_I2CReadReg(KETCUBE_AD7143_I2C_ADDRESS,
                                  KETCUBE_AD7143_REG_STAGE1_RAW,
                                  &raw1);
    ketCube_ad7143_I2CReadReg(KETCUBE_AD7143_I2C_ADDRESS,
                                  KETCUBE_AD7143_REG_STAGE2_RAW,
                                  &raw2);
    ketCube_ad7143_I2CReadReg(KETCUBE_AD7143_I2C_ADDRESS,
                                  KETCUBE_AD7143_REG_STAGE3_RAW,
                                  &raw3);
        
    ketCube_ad7143_I2CReadReg(KETCUBE_AD7143_I2C_ADDRESS,
                                  KETCUBE_AD7143_REG_ID,
                                  &id);

    
    ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "ID: 0x%04X", id);
    
    ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "RawCapacity CIN0: 0x%04X", raw0);
    ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "RawCapacity CIN2: 0x%04X", raw1);
    ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "RawCapacity CIN4: 0x%04X", raw2);
    ketCube_terminal_NewDebugPrintln(KETCUBE_LISTS_MODULEID_AD7143, "RawCapacity CIN6: 0x%04X", raw3);
    
    // mereni kanalu 0 vuci zemi:
    // 6p8 == 0x8A00 == cca 35000
    // 68p == 0x7E00 == cca 32000
    
    // mereni kanalu 0 vuci shield:
    // 6p8 == 0x7765 == cca 30550
    // 68p == 0x6CA5 == cca 27800
    
    // mereni kanalu 1 vuci shield:
    // 6p8 == 0x754E == cca 32300
    // 68p == 0x6F65 == cca 28500
    
    // kanaly maji, zda se, jiny offset ...
    // hodnoty v rovnici primky jsou urcene tak, aby stejne hodnoy co nejlepe fungovaly na vsech kanalech.
    
    // Neni linearni !!! ... tak snad alespon v malem rozsahu .... linearizace ve 2 bodech:

//     capacity = -0.0222*raw0 + 1400;
//     
//     ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage0): %.2f pF", capacity);
//     
//     capacity = -0.0222*raw1 + 1400;
//     
//     ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage1): %.2f pF", capacity);
//     
//     capacity = -0.0222*raw2 + 1400;
//     
//     ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage2): %.2f pF", capacity);
//     
//     capacity = -0.0222*raw3 + 1400;
//     
//     ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage3): %.2f pF", capacity);
    
    
    // mereni kanalu 0 vuci shield:
    // 6p8 == 0xDCF0 == cca 56600
    // 68p == 0xD860 == cca 55400
    
    // 1/C = 1/33 + 1/C_2
    // C = k * RAW + q
    // C_68 = k * RAW_68 + q   =>  22.2 = k * 55400 + q
    // C_6.8 = k * RAW_6.8 + q =>  5.65 = k * 56600 + q
    // k = 0.014; q = 798 (approx)
    // C_2 = 1/(1/(k*raw+q) - 1/33)
    
    // C1, c2 nd c3 have different parameters!
    
    capacity0 = 1.0/(1.0/(-0.014*raw0 + 798) - 1.0/33.0);
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage0): %.2f pF", capacity0);
    
    capacity1 = 1.0/(1.0/(-0.014*raw1 + 798) - 1.0/33.0);
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage1): %.2f pF", capacity1);
    
    capacity2 = 1.0/(1.0/(-0.014*raw2 + 798) - 1.0/33.0);
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage2): %.2f pF", capacity2);
    
    capacity3 = 1.0/(1.0/(-0.014*raw3 + 798) - 1.0/33.0);
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_AD7143, "Capacity (stage3): %.2f pF", capacity3);
    
    return KETCUBE_CFG_MODULE_OK;
}

#endif
/* KETCUBE_CFG_INC_MOD_AD7143 */
