/**
 * @file    ketCube_adpd188.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __KETCUBE_ADPD188_H
#define __KETCUBE_ADPD188_H

#include "ketCube_cfg.h"
#include "ketCube_common.h"

/** @defgroup KETCube_ADPD188 KETCube ADPD188
  * @brief KETCube ADPD188 module
  * @ingroup KETCube_SensMods
  * @{
  */

/**
* @brief  I2C slave (FDC2214) address.
* @note See FDC2214 datasheet for I2C address options
*/
#define KETCUBE_ADPD188_I2C_ADDRESS  (uint8_t) (0x64 << 1)

/** @defgroup KETCube_ADPD188_defs Public Defines
  * @brief Public defines
  * @{
  */

/**
* @brief  KETCube module configuration
*/
typedef struct ketCube_adpd188_moduleCfg_t {
    ketCube_cfg_ModuleCfgByte_t coreCfg;           /*!< KETCube core cfg byte */
} ketCube_adpd188_moduleCfg_t;

extern ketCube_adpd188_moduleCfg_t ketCube_adpd188_moduleCfg;


/**
 * @brief Register map
 * 
 */
typedef enum {
    KETCUBE_ADPD188_REG_STATUS        = 0x00,   /*!< Status register */
    KETCUBE_ADPD188_REG_INT_MASK      = 0x01,   /*!< Mask Interrupt */
    KETCUBE_ADPD188_REG_GPIO_DRV      = 0x02,   /*!< */
    KETCUBE_ADPD188_REG_BG_STATUS     = 0x04,   /*!< */
    KETCUBE_ADPD188_REG_FIFO_THRESH   = 0x06,   /*!< */
    KETCUBE_ADPD188_REG_DEVID         = 0x08,   /*!< Device ID */
    /* Add next register s here ...*/
    
    
} ketCube_adpd188_regs_t;

/**
* @}
*/


/** @defgroup KETCube_ADPD188_fn Public Functions
  * @brief Public functions
  * @{
  */

extern ketCube_cfg_ModError_t ketCube_adpd188_Init(ketCube_InterModMsg_t
                                                   *** msg);
extern ketCube_cfg_ModError_t ketCube_adpd188_UnInit(void);
extern ketCube_cfg_ModError_t ketCube_adpd188_ReadData(uint8_t * buffer,
                                                       uint8_t * len);

/**
* @}
*/

/**
* @}
*/

#endif                          /* __KETCUBE_ADPD188_H */
