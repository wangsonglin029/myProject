/**
  ******************************************************************************
  * @file    ac1003_iwdg.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file contains all the functions prototypes for the IWDG
  *          firmware library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_IWDG_H
#define __AC1003_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"

/** @defgroup IWDG_WriteAccess
  * @{
  */
#define IWDG_WriteAccess_Enable     0x55AA6698
#define IWDG_WriteAccess_Disable    0x55AA6699
#define IS_IWDG_WRITE_ACCESS(ACCESS) (((ACCESS) == IWDG_WriteAccess_Enable)||\
                                      ((ACCESS) == IWDG_WriteAccess_Disable))


/* KR register bit mask */
#define COMMAND_IWDT_RELOAD     ((uint32_t)0x000000AA)
#define COMMAND_IWDT_ENABLE     ((uint32_t)0x00000055)
#define COMMAND_WDTINTCLR_ENBLE ((uint32_t)0x00000001)
#define COMMAND_WDTINTSHIELD_ENBLE ((uint32_t)0x00000002)
#define COMMAND_WDT_RESET ((uint32_t)0x00000000)
#define COMMAND_WDT_INT ((uint32_t)0x00000001)
#define IWDG_INT_FLAG  (uint32_t)0x00000001
#define IS_IWDG_RELOAD(RELOAD) ((RELOAD) <= 0x000FFFFF)


/* Exported functions --------------------------------------------------------*/
/* Prescaler and Counter configuration functions ******************************/
void IWDG_WriteAccessCmd(IWDG_TypeDef *IWDGx, uint32_t IWDG_WriteAccess);
void IWDG_SetReload(IWDG_TypeDef *IWDGx, uint32_t Reload);
void IWDG_SetWdtMode(IWDG_TypeDef *IWDGx, uint32_t Mode);
uint32_t IWDG_GetReload(IWDG_TypeDef *IWDGx);
void IWDG_ReloadCR(IWDG_TypeDef *IWDGx);
void IWDG_Cmd(IWDG_TypeDef *IWDGx);
void IWDG_RELOAD(IWDG_TypeDef *IWDGx);
FlagStatus IWDG_GetFlagStatus(IWDG_TypeDef *IWDGx, uint16_t IWDG_FLAG);
void IWDG_WdtITShieldCmd(IWDG_TypeDef *IWDGx, FunctionalState NewStatus);
void IWDG_WdtITClear(IWDG_TypeDef *IWDGx);

#ifdef __cplusplus
}
#endif

#endif /* __AC1003_IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT Ascendchip *****END OF FILE****/
