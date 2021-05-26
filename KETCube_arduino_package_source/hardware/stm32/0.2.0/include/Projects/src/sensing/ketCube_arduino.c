/**
 * @file    ketCube_arduino.c
 * @author  Tomáš Hák
 * @version 0.1
 * @date    2019-9-17
 * @brief   This file contains definitions for the Arduino driver
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
#include "ketCube_arduino.h"

#ifdef KETCUBE_CFG_INC_MOD_ARDUINO

ketCube_arduino_moduleCfg_t ketCube_arduino_moduleCfg; /*!< Module configuration storage */


__weak void setup(void)
{
    //doing nothing
}

/**
 * @brief Initialize the Arduino sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_arduino_Init(ketCube_InterModMsg_t *** msg)
{

    // Init Drivers
    
    
    // Custom Init Code
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ARDUINO, "Executing extern function setup():");
    setup();
    
    return KETCUBE_CFG_MODULE_OK;
}

/**
 * @brief Initialize the Arduino sensor
 *
 * @retval KETCUBE_CFG_MODULE_OK in case of success
 * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
 */
ketCube_cfg_ModError_t ketCube_arduino_UnInit(void)
{
    // UnInit drivers
    
    
    return KETCUBE_CFG_MODULE_OK;
}

// extern loop will be over this weak implementation
__weak void loop(void)
{
    // do nothing
}

/**
  * @brief Read data from Arduino sensor
  *
  * @param buffer pointer to fuffer for storing the result of measurements
  * @param len data len in bytes
  *
  * @retval KETCUBE_CFG_MODULE_OK in case of success
  * @retval KETCUBE_CFG_MODULE_ERROR in case of failure
  */
ketCube_cfg_ModError_t ketCube_arduino_ReadData(uint8_t * buffer,
                                                uint8_t * len)
{
    
    ketCube_terminal_InfoPrintln(KETCUBE_LISTS_MODULEID_ARDUINO, "Executing extern function loop():");
    loop();

    return KETCUBE_CFG_MODULE_OK;
}

#endif                          /* KETCUBE_CFG_INC_MOD_ARDUINO */
