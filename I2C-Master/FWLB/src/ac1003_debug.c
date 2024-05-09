/**
  ******************************************************************************
  * @file    ac1003_debug.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides firmware functions to manage the debug peripheral.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_debug.h"


/**
  * @brief  Enables debug function
  * @param  DEBUGx:Select the debug peripheral.
	* @param  DEBUG_InitStruct: pointer to a DEBUG_InitTypeDef structure
  *         which will be configed.
  * @retval None
  */
void  DEBUG_DebugCmd(DEBUG_TypeDef *DEBUGx, DEBUG_InitTypeDef *DEBUG_InitStruct)
{
    /* Check the parameters */
    uint32_t tmpreg = 0, tmp = 0;

    /*The key value */
    uint32_t key = 0x5a690000;

    /*Set debug parameter*/
    tmp = ((DEBUG_InitStruct->TIMER10DEGSTOP << 0) | \
           (DEBUG_InitStruct->TIMER11DEGSTOP << 1) | \
           (DEBUG_InitStruct->LPTIMDEGSTOP << 2) | \
           (DEBUG_InitStruct->PCADEGSTOP << 4) | \
           (DEBUG_InitStruct->TIM1DESTOP << 5) | \
           (DEBUG_InitStruct->RTCDEGSTOP << 6) | \
           (DEBUG_InitStruct->AWKDEGSTOP << 7) | \
           (DEBUG_InitStruct->BEEPDEGSTOP << 8) | \
           (DEBUG_InitStruct->IWDTDEGSTOP << 9) | \
           (DEBUG_InitStruct->WWDTDEGSTOP << 10) | \
           (DEBUG_InitStruct->TIM2DEGSTOP << 11));

    /*The key value */
    tmpreg = key | tmp;

    /*Set the value to the APBFZ register*/
    DEBUGx->APBFZ = tmpreg;
}


/**
  * @}
  */

/**
  * @}
  */
/**
  * @}
  */
/************************ (C) COPYRIGHT AC1003 *****END OF FILE**************/

