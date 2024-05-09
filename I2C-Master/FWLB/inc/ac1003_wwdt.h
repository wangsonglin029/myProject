/**
  ******************************************************************************
  * @file    ac1003_wwdt.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the wwdt firmware
  *          library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -----------*/
#ifndef __AC1003_WWDG_H
#define __AC1003_WWDG_H


#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"



/* --------------------- WWDG registers bit mask ------------------------ */
/* CFR register bit mask */
#define CTL_WDGTB_MASK    ((uint32_t)0xF00000FF)
#define CTL_W_MASK        ((uint32_t)0xFFFFFF00)
#define BIT_MASK          ((uint32_t)0x000000FF)



#define  WWDG_CTL_ENBLE                       ((uint32_t)0x10000000)               /*!< Activation bit */
#define  WWDG_CRL_STATUS                      ((uint32_t)0x00000001)               /*!< Activation bit */
#define  WWDG_INT_FLAG                        ((uint32_t)0x00000001)               /*!< Activation bit */
#define  WWDG_INT_ENABLE                      ((uint32_t)0x00000001)               /*!< Activation bit */


/** @defgroup WWDG_Prescaler
  * @{
  */

#define IS_WWDG_PRESCALER(PRESCALER)   (((PRESCALER) >= 0) && ((PRESCALER)<= 0xfffff))



/* Exported functions -----------------------------*/
void WWDG_DeInit(void);
void WWDG_SetPrescaler(WWDG_TypeDef* WWDGx, uint32_t WWDG_Prescaler);
void WWDG_SetWindowValue(WWDG_TypeDef* WWDGx, uint8_t WindowValue);
void WWDG_ITCmd(WWDG_TypeDef* WWDGx, FunctionalState NewStatus);
void WWDG_SetRldCnt(WWDG_TypeDef* WWDGx, uint8_t Rldcnt);
void WWDG_Cmd(WWDG_TypeDef* WWDGx, FunctionalState NewStatus);
FlagStatus WWDG_GetFlagStatus(WWDG_TypeDef* WWDGx, uint16_t WWDG_FLAG);
void WWDG_ClearFlag(WWDG_TypeDef* WWDGx);

#ifdef __cplusplus
}
#endif

#endif /*__AC1003_WWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT AC1003 *****END OF FILE****/
