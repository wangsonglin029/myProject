/**
  ************************************************************************
  * @file    test_uart.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    13-July-2018
  * @brief   This file contains all the functions prototypes for the uart
  ************************************************************************
  */

#ifndef __AC1003_TEST_UART_H
#define __AC1003_TEST_UART_H


/* Includes --------------------------*/
#include "ac1003_uart.h"
#include "ac1003_gpio.h"
#include "ac1003_rcc.h"

#if 1
#define  PRINTFUART                     UART1
#else
#define  PRINTFUART                     UART0
#endif

// ´®¿Ú-UART1
#define  DEBUG_UART1_BAUDRATE           115200

#define  DEBUG_UART1_MODE               UART_MODE1
#define  DEBUG_TIM11                    TIM11

#define  DEBUG_UART1_TX_GPIO_PORT       GPIOD
#define  DEBUG_UART1_TX_GPIO_PIN        GPIO_Pin_5
#define  DEBUG_UART1_TX_PIN_SOURCE      GPIO_PinSource5
#define  DEBUG_UART1_RX_GPIO_PORT       GPIOD
#define  DEBUG_UART1_RX_GPIO_PIN        GPIO_Pin_6
#define  DEBUG_UART1_RX_PIN_SOURCE      GPIO_PinSource6

#define  DEBUG_UART1_RX_AF_VALUE        GPIO_AF_UART1_RX_PD6
#define  DEBUG_UART1_TX_AF_VALUE        GPIO_AF_UART1_TX_PD5




// ´®¿Ú-UART0
#define  DEBUG_UART0_BAUDRATE           9600

#define  DEBUG_UART0_MODE               UART_MODE1
#define  DEBUG_TIM10                    TIM10

#define  DEBUG_UART0_TX_GPIO_PORT       GPIOD
#define  DEBUG_UART0_TX_GPIO_PIN        GPIO_Pin_4
#define  DEBUG_UART0_TX_PIN_SOURCE      GPIO_PinSource4
#define  DEBUG_UART0_RX_GPIO_PORT       GPIOD
#define  DEBUG_UART0_RX_GPIO_PIN        GPIO_Pin_3
#define  DEBUG_UART0_RX_PIN_SOURCE      GPIO_PinSource3

#define  DEBUG_UART0_RX_AF_VALUE        GPIO_AF_UART0_RX_PD3
#define  DEBUG_UART0_TX_AF_VALUE        GPIO_AF_UART0_TX_PD4




/******define functions***************/
void UART1_Config(void);
void UART0_Config(void);
void Uart_SendByte( UART_TypeDef * pUARTx, uint8_t ch);
void Uart_SendString( UART_TypeDef * pUSARTx, unsigned char *str, uint32_t size);
#endif

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT To AC1003 *****END OF FILE****/



