/**
 * @file    ketCube_ad7143.h
 * @author  Jan Belohoubek
 * @version pre-alpha
 * @date    2018-03-18
 * @brief   This file contains definitions for the AD7143 driver
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KETCUBE_AD7143_H
#define __KETCUBE_AD7143_H


#include "ketCube_cfg.h"
#include "ketCube_common.h"

/** @defgroup KETCube_AD7143 KETCube AD7143
  * @brief KETCube AD7143 module
  * @ingroup KETCube_SensMods
  * @{
  */

/**
* @brief  KETCube module configuration
*/
typedef struct ketCube_ad7143_moduleCfg_t {
    ketCube_cfg_ModuleCfgByte_t coreCfg;           /*!< KETCube core cfg byte */
} ketCube_ad7143_moduleCfg_t;

extern ketCube_ad7143_moduleCfg_t ketCube_ad7143_moduleCfg;

/** @defgroup KETCube_AD7143_regmap KETCube AD7143 regmap
  * @brief AD7143 regmap
  * @{
  */

typedef enum {
    //SETUP REGISTER  
    KETCUBE_AD7143_REG_SETUP               = (uint16_t) 0x0000,    
    
    //RESULT REGISTER
    KETCUBE_AD7143_REG_ADC_STAGE0          = (uint16_t) 0x00B,      
    KETCUBE_AD7143_REG_ADC_STAGE1          = (uint16_t) 0x00C,      
    KETCUBE_AD7143_REG_ADC_STAGE2          = (uint16_t) 0x00D,      
    KETCUBE_AD7143_REG_ADC_STAGE3          = (uint16_t) 0x00E,     
    KETCUBE_AD7143_REG_ADC_STAGE4          = (uint16_t) 0x00F,      
    KETCUBE_AD7143_REG_ADC_STAGE5          = (uint16_t) 0x010,      
    KETCUBE_AD7143_REG_ADC_STAGE6          = (uint16_t) 0x011,     
    KETCUBE_AD7143_REG_ADC_STAGE7          = (uint16_t) 0x012,     
    
    //DEVICE ID REGISTER
    KETCUBE_AD7143_REG_ID                  = (uint16_t) 0x017,      
    
    //STAGEX CONF REG CONNECTION[6-0]
    //STAGEX CONF REG CONNECTION7
    
    KETCUBE_AD7143_REG_STAGE0_CONNECTION1 = (uint16_t) 0x080,       
    KETCUBE_AD7143_REG_STAGE0_CONNECTION2 =	(uint16_t) 0x081,      
    
    KETCUBE_AD7143_REG_STAGE1_CONNECTION1 = (uint16_t) 0x088,       
    KETCUBE_AD7143_REG_STAGE1_CONNECTION2 = (uint16_t) 0x089,      
    
    KETCUBE_AD7143_REG_STAGE2_CONNECTION1 = (uint16_t) 0x090,      
    KETCUBE_AD7143_REG_STAGE2_CONNECTION2 = (uint16_t) 0x091,     
    
    KETCUBE_AD7143_REG_STAGE3_CONNECTION1 = (uint16_t) 0x098,     
    KETCUBE_AD7143_REG_STAGE3_CONNECTION2 = (uint16_t) 0x099,      
    
    KETCUBE_AD7143_REG_STAGE4_CONNECTION1 = (uint16_t) 0x0A0,     
    KETCUBE_AD7143_REG_STAGE4_CONNECTION2 = (uint16_t) 0x0A1,      
    
    KETCUBE_AD7143_REG_STAGE5_CONNECTION1 = (uint16_t) 0x0A8,      
    KETCUBE_AD7143_REG_STAGE5_CONNECTION2 = (uint16_t) 0x0A9,      
    
    KETCUBE_AD7143_REG_STAGE6_CONNECTION1 = (uint16_t) 0x0B0,   
    KETCUBE_AD7143_REG_STAGE6_CONNECTION2 = (uint16_t) 0x0B1,      
    
    KETCUBE_AD7143_REG_STAGE7_CONNECTION1 = (uint16_t) 0x0B8,      
    KETCUBE_AD7143_REG_STAGE7_CONNECTION2 = (uint16_t) 0x0B9,      
    
    //CDC Output
    KETCUBE_AD7143_REG_STAGE0_RAW          = (uint16_t) 0x00B,      
    KETCUBE_AD7143_REG_STAGE1_RAW          = (uint16_t) 0x00C,
    KETCUBE_AD7143_REG_STAGE2_RAW          = (uint16_t) 0x00D,
    KETCUBE_AD7143_REG_STAGE3_RAW          = (uint16_t) 0x00E,

    //STAGEX RESULT 
    KETCUBE_AD7143_REG_STAGE0_RESULTS      = (uint16_t) 0x0E0,      
    KETCUBE_AD7143_REG_STAGE1_RESULTS      = (uint16_t) 0x104,      
    KETCUBE_AD7143_REG_STAGE2_RESULTS      = (uint16_t) 0x128,     
    KETCUBE_AD7143_REG_STAGE3_RESULTS      = (uint16_t) 0x14C,     
    KETCUBE_AD7143_REG_STAGE4_RESULTS      = (uint16_t) 0x170,     
    KETCUBE_AD7143_REG_STAGE5_RESULTS      = (uint16_t) 0x194,     
    KETCUBE_AD7143_REG_STAGE6_RESULTS      = (uint16_t) 0x1B8,      
    KETCUBE_AD7143_REG_STAGE7_RESULTS      = (uint16_t) 0x1DC,     
    
} ketCube_ad7143_reg;

/**
* @}
*/

/** @defgroup KETCube_AD7143_bank2 KETCube AD7143 BANK2
  * @brief AD7143 common register values
  * @{
  */
typedef enum {
    //AD7143 RESET REGISTER
    KETCUBE_AD7143_VALREG_RESET       = (uint16_t) 0x0030,  /* 0x0030 == 4 conversion stages */
    
    //STAGE 0 CONF
    KETCUBE_AD7143_VALREG_STAGE0_CONF1 = (uint16_t) 0xFFF0 | ((0x2 << 0) | (0x1 << 2)),
    KETCUBE_AD7143_VALREG_STAGE0_CONF2 = (uint16_t) 0xFFFF,
    
    //STAGE 1 CONF
    KETCUBE_AD7143_VALREG_STAGE1_CONF1 = (uint16_t) 0xFF0F | (((0x2 << 0) | (0x1 << 2)) << 4),
    KETCUBE_AD7143_VALREG_STAGE1_CONF2 = (uint16_t) 0xFFFF,
    
    //STAGE 2 CONF
    KETCUBE_AD7143_VALREG_STAGE2_CONF1 = (uint16_t) 0xF0FF | (((0x2 << 0) | (0x1 << 2)) << 8),
    KETCUBE_AD7143_VALREG_STAGE2_CONF2 = (uint16_t) 0xFFFF,
    
    //STAGE 3 CONF
    KETCUBE_AD7143_VALREG_STAGE3_CONF1 = (uint16_t) 0x0FFF | ((0x2 << 0) << 12),
    KETCUBE_AD7143_VALREG_STAGE3_CONF2 = (uint16_t) 0xFFF0 | (0x1 << 2),

} ketCube_ad7143_configuration;

/**
* @}
*/


/**
* @brief  I2C slave (AD7143) address.
* @note Watch AD7143 datasheet for I2C address options
*/
#define KETCUBE_AD7143_I2C_ADDRESS  (uint8_t) (0x2E << 1)

/**
* @brief  I2C Timeout.
*/
#define KETCUBE_AD7143_I2C_TIMEOUT 0x1000      /*<! Value of Timeout when I2C communication fails */

/**
* @addtogroup KETCUBE_AD7143_Registers
* @{
*/

/**
* @}
*/


/** @defgroup KETCUBE_AD7143_fn Public Functions
* @{
*/

extern ketCube_cfg_ModError_t ketCube_ad7143_Init(ketCube_InterModMsg_t *** msg);
extern ketCube_cfg_ModError_t ketCube_ad7143_UnInit(void);
extern ketCube_cfg_ModError_t ketCube_ad7143_ReadData(uint8_t * buffer, uint8_t * len);

/**
* @}
*/

/**
* @}
*/

#endif                          /* __KETCUBE_AD7143_H */
