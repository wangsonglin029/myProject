/**
  *****************************************************************************
  * @file    ac1003_exit.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    27-July-2018
  * @brief   This file contains all the functions prototypes for the EXTI
	           firmware  library.
  *****************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_EXTI__H
#define __AC1003_EXTI__H

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"

/** @defgroup GPIO_IRQ_InitTypeDef
  * @{
  */
typedef struct
{
    uint8_t GPIO_IRQ_Pin_Enable;         /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_IRQ_Pin_Enable */

    uint8_t GPIO_IRQ_Pin_Clear;          /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIO_IRQ_Pin_Clear */

    uint8_t GPIO_IRQ_Pin_Type;           /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIO_IRQ_Pin_Type */

    uint8_t GPIO_IRQ_Pin_Polarity;       /*!< Specifies the operating output type for the selected pins.
                                       This parameter can be a value of @ref GPIO_IRQ_Pin_Polarity */

    uint8_t GPIO_IRQ_Pin_Edge;           /*!< Specifies the operating Pull-up/Pull down for the selected pins.
                                       This parameter can be a value of @ref GPIO_IRQ_Pin_Edge */
} GPIO_IRQ_InitTypeDef;


/** @defgroup EXTI_Exported_Functions
  * @{
  */

void GPIO_EXTILineConfig(GPIO_TypeDef* GPIOx, GPIO_IRQ_InitTypeDef* GPIO_IRQ_InitStructure, uint8_t GPIO_Pin);


#ifdef __cplusplus
}
#endif

#endif /*__AC1003_EXTI__H */

/**
  * @}
  */

/**
  * @}
  */

/************************(C)COPYRIGHT AC1003*********END OF FILE***************************************/
