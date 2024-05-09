/**
  ******************************************************************************
  * @file    ac1003_uart.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    13-July-2018
  * @brief   This file contains all the functions prototypes for the UART
  *          firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_UART_H
#define __AC1003_UART_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"
#include "stdio.h"

/**
  * @brief  UART Init Structure definition
  */
typedef struct
{
    uint32_t UART_BaudRate;            /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint8_t UART_BaudRateDbaud_Enable; /*!< Baud Rate double enable*/

    uint8_t UART_BaudRateTimer_Selected; /*!< Select Baud Rate Clock */


    uint8_t UART_Mode;                /*!< Specifies wether the Receive or Transmit mode is enabled or disabled.
                                         This parameter can be a value of UART_Mode */

    uint32_t Parity;                  /*!< Specifies the parity mode.*/
} UART_InitTypeDef;

/**
  * @brief  UART_IRD Init Structure definition
  */
typedef struct
{
    uint32_t UART_IRDIRLPMOD;            /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint32_t UART_IRDIRRXINV;            /*!<IRD  receiving Data Flip Control Bit*/

    uint32_t UART_IRDIRTXINV;            /*!<IRD  send Data Flip Control Bit*/

    uint32_t UART_IRDPSC;                /*!< UART IRD PSC
                                           This parameter can be a value of UART_Mode */
} UART_IRDInitTypeDef;


/** @defgroup UART_Exported_Constants
  * @{
  */
#define IS_UART_ALL_PERIPH(PERIPH) (((PERIPH) == UART0) ||\
                                    ((PERIPH) == UART1))

/** @defgroup UART_Clock
  * @{
  */
#define UART_Clock_Disable                  ((uint32_t)0x00000000)
#define UART_Clock_Enable                   ((uint32_t)0x00000800)
#define IS_UART_CLOCK(CLOCK) (((CLOCK) == UART_Clock_Disable) ||\
                               ((CLOCK) == UART_Clock_Enable))


/** @defgroup UART_MODE
  * @{
  */
#define  UART_MODE0   (uint32_t)0x00000000
#define  UART_MODE1   (uint32_t)0x00000001
#define  UART_MODE2   (uint32_t)0x00000002
#define  UART_MODE3   (uint32_t)0x00000003
#define IS_UART_MODE(MODE) (((MODE) == UART_MODE_0) ||\
                            ((MODE) == UART_MODE_1) ||\
                            ((MODE) == UART_MODE_2) ||\
														((MODE) == UART_MODE_3))



#define IS_UART_BAUDRATE(BAUDRATE) (((BAUDRATE) > 0) && ((BAUDRATE) < 0x0044AA21))
#define UART_Address_Mask          ((uint32_t)0x0000FF00)  /*!< USART address Mask */
#define IS_UART_ADDRESS(ADDRESS) ((ADDRESS) <= 0xFF)

#define  UART_IRDACR_IRLP      (uint32_t)0x00000800
#define  UART_IRDACR_IRRXINV   (uint32_t)0x00000400
#define  UART_IRDACR_IRTXINV   (uint32_t)0x00000200
#define  UART_IRDACR_IREN      (uint32_t)0x00000100

/** @defgroup UART_Parity  UART Parity
  * @{
  */
#define UART_PARITY_NONE                    (0x00000000U)
#define UART_PARITY_EVEN                    (0x00000001U)
#define UART_PARITY_ODD                     (0x00000002U) 


/******************  Bit definition for USART_SCON register  *******************/
#define  UART_SCON_RIEN                        0x00000001
#define  UART_SCON_TIEN                        0x00000002
#define  UART_SCON_RB8                         0x00000004
#define  UART_SCON_TB8                         0x00000008
#define  UART_SCON_REN                         0x00000010
#define  UART_SCON_SM2                         0x00000020
#define  UART_SCON_SM1                         0x00000040
#define  UART_SCON_SM0                         0x00000080
#define  UART_SCON_FEEN                        0x00000100
#define  UART_SCON_DBAUD                       0x00000200

#define  UART_SCON_MODE0                       ~(UART_SCON_SM1|UART_SCON_SM0)
#define  UART_SCON_MODE1                       UART_SCON_SM1
#define  UART_SCON_MODE2                       UART_SCON_SM0
#define  UART_SCON_MODE3                       UART_SCON_SM1|UART_SCON_SM0

/******************  Bit definition for USART_ISR register  *******************/
#define  UART_ISR_RI                       0x00000001
#define  UART_ISR_TI                       0x00000002
#define  UART_ISR_FEI                      0x00000004

/******************  Bit definition for USART_ICR register  *******************/
#define  UART_ICR_RI                       0x00000001
#define  UART_ICR_TI                       0x00000002
#define  UART_ICR_FEI                      0x00000004
#define  UART_ICR_ALL                      UART_ICR_RI|UART_ICR_TI|UART_ICR_FEI


#define  UART_SELF_BRG                     (uint32_t)0x00010000
#define  UART_RXEN_EABLE                   (uint32_t)0x00000001
#define  UART_TXEN_EABLE                   (uint32_t)0x00000002

#define  UART_RIEN_EABLE                   (uint32_t)0x00000001
#define  UART_TIEN_EABLE                   (uint32_t)0x00000002
#define  IS_UART_IT(IT)                    ((IT == UART_RIEN_EABLE)||\
                                            (IT == UART_TIEN_EABLE))

#define  UART_TIM_EABLE                    (uint32_t)0x000000E0



/** @defgroup UART_Exported_Functions
  * @{
  */
void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, TIM_TypeDef* TIMERx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);
void UART_Cmd(UART_TypeDef* UARTx, uint16_t FuncState, FunctionalState NewState);
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);
void UART_SetAddress(UART_TypeDef* UARTx, uint8_t UART_Address, uint8_t UART_Address_Enable);
void UART_ReciveCmd(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct, FunctionalState NewState);
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReceiveData(UART_TypeDef* UARTx);
void UART_IrDAConfig(UART_TypeDef* UARTx, UART_IRDInitTypeDef* UART_IRDInitStruct);
void UART_IrDACmd(UART_TypeDef* UARTx, FunctionalState NewState);
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, uint16_t UART_IT);
void UART_ClearITBit(UART_TypeDef* UARTx, uint16_t UART_IT);
void UART_TB8Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_RB8Cmd(UART_TypeDef* UARTx, FunctionalState NewState);
void UART_SendData_WithParity(UART_TypeDef* UARTx, uint8_t Data);
int8_t UART_ReceiveData_WithParity(UART_TypeDef* UARTx,  uint8_t *rxdata);

#ifdef __cplusplus
}
#endif

#endif /* __AC1003_UART_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2018 AC1003 *****END OF FILE****/
