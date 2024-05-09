/**
  ****************************************************************************
  * @file    ac1003_debug.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the DEBUG
	           firmware library.
  ****************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_DEBUG_H
#define __AC1003_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"

/** @defgroup DEBUG_InitTypeDef
  * @{
  */
typedef struct
{
    uint8_t TIMER10DEGSTOP;   /*!< TIMER10 DEBUG */
    uint8_t TIMER11DEGSTOP;   /*!< TIMER11 DEBUG */
    uint8_t LPTIMDEGSTOP;     /*!< LPTIMER DEBUG */
    uint8_t PCADEGSTOP;       /*!< PCA DEBUG */
    uint8_t TIM1DESTOP;       /*!< TIM1 DEBUG */
    uint8_t RTCDEGSTOP;       /*!< RTC DEBUG */
    uint8_t AWKDEGSTOP;       /*!< RTC DEBUG */
    uint8_t BEEPDEGSTOP;      /*!< RTC BEEP DEBUG */
    uint8_t IWDTDEGSTOP;      /*!< IWDT BEEP DEBUG */
    uint8_t WWDTDEGSTOP;      /*!< WWDT BEEP DEBUG */
    uint8_t TIM2DEGSTOP;      /*!< TIM2 BEEP DEBUG */
} DEBUG_InitTypeDef;


/**
  *
  */
void  DEBUG_DebugCmd(DEBUG_TypeDef *DEBUGx, DEBUG_InitTypeDef *DEBUG_InitStruct);

#ifdef __cplusplus
}
#endif

#endif /*__AC1003_DEBUG_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT AC1003 *****END OF FILE*************/
