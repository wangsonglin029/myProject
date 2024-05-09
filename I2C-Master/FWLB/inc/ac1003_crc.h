/**
  ******************************************************************************
  * @file    ac1003_crc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the CRC firmware
  *          library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_CRC_H
#define __AC1003_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"


/******************************************************
 * Local type definitions ('typedef')
 *******************************************************/
#define CRC_DATA8        (*(uint8_t  *)(CRC_BASE+0x80))
/******************************************************
 * Local type definitions ('typedef')
 *******************************************************/
#define CRC_DATA16       (*(uint16_t *)(CRC_BASE+0x80))
/******************************************************
 * Local type definitions ('typedef')
 *******************************************************/
#define CRC_DATA32       (*(uint32_t *)(CRC_BASE+0x80))


/** @defgroup crc_flag_mask
  * @{
  */
#define crc_flag_mask 0x10000

/* Exported functions --------------------------------------------------------*/
void CRC_DeInit(void);
void CRC_init(CRC_TypeDef* CRCx);
uint16_t CRC_CalcCRC8(CRC_TypeDef* CRCx, uint8_t Data);
ErrorStatus CRC_CheckCRC8(CRC_TypeDef* CRCx, uint8_t Data);
uint16_t CRC_MultiCalcCRC8(CRC_TypeDef* CRCx, uint8_t *buffer, uint32_t count);
ErrorStatus CRC_MultiCheckCRC8(CRC_TypeDef* CRCx, uint8_t *buffer, uint32_t count);
uint16_t CRC_CalcCRC16(CRC_TypeDef* CRCx, uint16_t Data);
ErrorStatus CRC_CheckCRC16(CRC_TypeDef* CRCx, uint16_t Data);
uint16_t CRC_MultiCalcCRC16(CRC_TypeDef* CRCx, uint16_t *buffer, uint32_t count);
ErrorStatus CRC_MultiCheckCRC16(CRC_TypeDef* CRCx, uint16_t *buffer, uint32_t count);
uint16_t CRC_CalcCRC32(CRC_TypeDef* CRCx, uint32_t Data);
ErrorStatus CRC_CheckCRC32(CRC_TypeDef* CRCx, uint32_t Data);
uint16_t CRC_MultiCalcCRC32(CRC_TypeDef* CRCx, uint32_t *buffer,  uint32_t count);
ErrorStatus CRC_MultiCheckCRC32(CRC_TypeDef* CRCx, uint32_t *buffer,  uint32_t count);

#ifdef __cplusplus
}
#endif

#endif /* __AC1003_CRC_H */



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
