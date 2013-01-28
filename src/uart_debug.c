#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "uart_debug.h"

//USART2

#define COM_USART			USART2
#define COM_TX_PORT			GPIOA
#define COM_RX_PORT			GPIOA

#define COM_USART_CLK		RCC_APB1Periph_USART2
#define COM_TX_PORT_CLK		RCC_AHB1Periph_GPIOA
#define COM_RX_PORT_CLK		RCC_AHB1Periph_GPIOA
#define COM_TX_PIN			GPIO_Pin_2
#define COM_RX_PIN			GPIO_Pin_3
#define COM_TX_PIN_SOURCE	GPIO_PinSource2
#define COM_RX_PIN_SOURCE	GPIO_PinSource3
#define COM_TX_AF			GPIO_AF_USART2
#define COM_RX_AF			GPIO_AF_USART2

const USART_InitTypeDef DEBUG_InitStructure = {
	230400,
	USART_WordLength_8b,
	USART_StopBits_1,
	USART_Parity_No,
	USART_Mode_Tx | USART_Mode_Rx,
	USART_HardwareFlowControl_None
};

const GPIO_InitTypeDef DEBUG_TX_InitStructure = {
	COM_TX_PIN,
	GPIO_Mode_AF,
	GPIO_Speed_100MHz,
	GPIO_OType_OD,
	GPIO_PuPd_UP
};

const GPIO_InitTypeDef DEBUG_RX_InitStructure = {
	COM_RX_PIN,
	GPIO_Mode_AF,
	GPIO_Speed_100MHz,
	GPIO_OType_PP,
	GPIO_PuPd_UP
};

void uart_debug_init(void)
{
	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(COM_TX_PORT_CLK | COM_RX_PORT_CLK, ENABLE);

	/* Enable UART clock */
	RCC_APB1PeriphClockCmd(COM_USART_CLK, ENABLE);

	/* Connect PXx to USARTx_Tx*/
	GPIO_PinAFConfig(COM_TX_PORT, COM_TX_PIN_SOURCE, COM_TX_AF);

	/* Connect PXx to USARTx_Rx*/
	GPIO_PinAFConfig(COM_RX_PORT, COM_RX_PIN_SOURCE, COM_RX_AF);

	/* Configure USART pins */
	GPIO_Init(COM_TX_PORT, (GPIO_InitTypeDef *) &DEBUG_TX_InitStructure);
	GPIO_Init(COM_RX_PORT, (GPIO_InitTypeDef *) &DEBUG_RX_InitStructure);

	/* USART configuration */
	USART_Init(COM_USART, (USART_InitTypeDef *) &DEBUG_InitStructure);

	/* Enable USART */
	USART_Cmd(COM_USART, ENABLE);
	USART_SendData(COM_USART, (uint8_t) 'o');

	/* Attach ChaN's xprintf interface */
	xdev_out(uart_debug_putc);
}

void uart_debug_putc(unsigned char c)
{
	while (USART_GetFlagStatus(COM_USART, USART_FLAG_TXE) == RESET)
	{ }
	USART_SendData(COM_USART, (uint8_t) c);
	/* Loop until the end of transmission */
	//! while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	//! { }
}

/**
  ******************************************************************************
  * @file    uart_debug.c
  * @author  Yuuichi Akagawa
  * @version V1.0.0
  * @date    2012/02/27
  * @brief   UART debug out utility
  ******************************************************************************
  * @attention
  *
  * Licensed under the Apache License, Version 2.0 (the "License");
  * you may not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  *      http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  * <h2><center>&copy; COPYRIGHT (C)2012 Yuuichi Akagawa</center></h2>
  *
  ******************************************************************************
  */
