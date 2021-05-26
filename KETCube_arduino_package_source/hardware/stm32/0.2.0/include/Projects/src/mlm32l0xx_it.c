/*
 / _____)             _              | |
( (____  _____ ____ _| |_ _____  ____| |__
 \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 _____) ) ____| | | || |_| ____( (___| | | |
(______/|_____)_|_|_| \__)_____)\____)_| |_|
    (C)2013 Semtech

Description: Bleeper board GPIO driver implementation

License: Revised BSD License, see LICENSE.TXT file include in the project

Maintainer: Miguel Luis and Gregory Cristian
*/
 /******************************************************************************
  * @file    mlm32l0xx_it.c
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    27-February-2017
  * @brief   manages interupt
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  *
  *
  * @author  Martin Ubl
  * @version 0.1
  * @date    2018-05-07
  * @brief   This file has been modified to fit into the KETCube platform
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
	*
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include "mlm32l0xx_it.h"
#include "low_power.h"
#include "stm32l0xx_hal.h"

#include "ketCube_uart.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup SPI_FullDuplex_ComPolling
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* UART handler declared in "main.c" file */

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */

void NMI_Handler(void)
{
}


/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */


void HardFault_Handler(void)
{
  while(1)
  {
    __NOP();
  }

}


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

#define DEFINE_USART_IRQ_HANDLER(channel) void USART##channel##_IRQHandler(void)\
{\
	UART_HandleTypeDef* huart = ketCube_UART_GetHandle(KETCUBE_UART_CHANNEL_##channel );\
	if (huart != NULL)\
	{\
		HAL_UART_IRQHandler(huart);\
		ketCube_UART_IRQCallback(KETCUBE_UART_CHANNEL_##channel );\
	}\
}

/**
 * @brief USART channel 1 IRQ handler
 */
DEFINE_USART_IRQ_HANDLER(1);

/**
 * @brief USART channel 2 IRQ handler
 */
DEFINE_USART_IRQ_HANDLER(2);

/**
 * @brief USART channel 3 IRQ handler; not available on current build
 */
//DEFINE_USART_IRQ_HANDLER(3);

/**
 * @brief USART channel 4 IRQ handler
 */
DEFINE_USART_IRQ_HANDLER(4);

/**
 * @brief USART channel 5 IRQ handler
 */
DEFINE_USART_IRQ_HANDLER(5);

/**
 * @brief Maps USART instance (register base) to channel number
 * @param instance	USART instance (address of base register set)
 * @return valid channel number or KETCUBE_UART_CHANNEL_COUNT if not found
 */
static ketCube_UART_ChannelNo_t HAL_UART_MapInstanceToChannel(uintptr_t instance)
{
    switch (instance)
    {
        case (uintptr_t)USART1: return KETCUBE_UART_CHANNEL_1;
        case (uintptr_t)USART2: return KETCUBE_UART_CHANNEL_2;
        //case (uintptr_t)USART3: return KETCUBE_UART_CHANNEL_3;
        case (uintptr_t)USART4: return KETCUBE_UART_CHANNEL_4;
        case (uintptr_t)USART5: return KETCUBE_UART_CHANNEL_5;
    }
    
    return KETCUBE_UART_CHANNEL_COUNT;
}

/**
 * @brief USART RX complete HAL callback
 * @param huart		USART handle which triggered callback
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    ketCube_UART_ChannelNo_t channel = HAL_UART_MapInstanceToChannel((uintptr_t)huart->Instance);
    if (channel != KETCUBE_UART_CHANNEL_COUNT) {
        ketCube_UART_ReceiveCallback(channel);
    }
}

/**
 * @brief USART TX complete HAL callback
 * @param huart		USART handle which triggered callback
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    ketCube_UART_ChannelNo_t channel = HAL_UART_MapInstanceToChannel((uintptr_t)huart->Instance);
    if (channel != KETCUBE_UART_CHANNEL_COUNT) {
        ketCube_UART_TransmitCallback(channel);
    }
}

/**
 * @brief USART error HAL callback
 * @param huart		USART handle which triggered callback
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    ketCube_UART_ChannelNo_t channel = HAL_UART_MapInstanceToChannel((uintptr_t)huart->Instance);
    if (channel != KETCUBE_UART_CHANNEL_COUNT) {
        ketCube_UART_ErrorCallback(channel);
    }
}

/**
 * @brief USART wakeup HAL callback
 * @param huart		USART handle which triggered callback
 */
void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
    ketCube_UART_ChannelNo_t channel = HAL_UART_MapInstanceToChannel((uintptr_t)huart->Instance);
    if (channel != KETCUBE_UART_CHANNEL_COUNT) {
        ketCube_UART_WakeupCallback(channel);
    }
}

/**
 * @brief USART initialization HAL callback
 * @param huart		USART handle which triggered callback
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    ketCube_UART_ChannelNo_t channel = HAL_UART_MapInstanceToChannel((uintptr_t)huart->Instance);
    if (channel != KETCUBE_UART_CHANNEL_COUNT) {
        ketCube_UART_IoInitCallback(channel);
    }
}

/**
 * @brief USART deinitialization HAL callback
 * @param huart		USART handle which triggered callback
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    ketCube_UART_ChannelNo_t channel = HAL_UART_MapInstanceToChannel((uintptr_t)huart->Instance);
    if (channel != KETCUBE_UART_CHANNEL_COUNT) {
	    ketCube_UART_IoDeInitCallback(channel);
    }
}

void RTC_IRQHandler( void )
{
  HW_RTC_IrqHandler ( );
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
