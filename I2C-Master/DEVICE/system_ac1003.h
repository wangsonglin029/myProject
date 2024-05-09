/**
  ******************************************************************************
  * @file    system_AC1003.h
  * @author  MCD Application Team
  * @version V0.0.0
  * @date    05-December-2014
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer System Header File.
  ******************************************************************************
  */

#include "stdint.h"

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup AC1003_system
  * @{
  */

/**
  * @brief Define to prevent recursive inclusion
  */
#ifndef __SYSTEM_AC1003_H
#define __SYSTEM_AC1003_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup AC1003_System_Includes
  * @{
  */

/**
  * @}
  */


/** @addtogroup AC1003_System_Exported_types
  * @{
  */

extern uint32_t SystemCoreClock;          /*!< System Clock Frequency (Core Clock) */
extern uint32_t ApbClock;
extern uint32_t AhbClock;
/**
  * @}
  */

/** @addtogroup AC1003_System_Exported_Constants
  * @{
  */

/**
  * @}
  */

/** @addtogroup AC1003_System_Exported_Macros
  * @{
  */

/**
  * @}
  */

/** @addtogroup AC1003_System_Exported_Functions
  * @{
  */

extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__SYSTEM_AC1003_H */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT Ascendchip *****END OF FILE****/
