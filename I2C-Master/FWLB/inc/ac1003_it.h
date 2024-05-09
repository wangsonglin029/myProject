/**
  ******************************************************************************
  * @file    
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_IT_H
#define __AC1003_IT_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
	 
//extern char I2C_buffer[128];
//extern int I2C_SEND_START ;
//extern int I2C_REVCIVE_START;
//extern int I2C_SEND_END ;
//extern int I2C_REVCIVE_END ;
char I2C_DATA_DIRECTION =0;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif

/******************* (C) COPYRIGHT 2018 Ascendchip *****END OF FILE****/
