/**
  ******************************************************************************
  * @file    ac1003_crc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the CRC firmware functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include  "ac1003_crc.h"
#include  "ac1003_rcc.h"

/**
  * @brief  Deinitializes the CRC peripheral registers to their default reset values.
  * @param  : None
	* @param  : None
  * @retval : None
  */
void CRC_DeInit(void)
{
    /*Enable CRC reset state */
    RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_CRCRST, ENABLE);
    /*Release CRC from reset state */
    RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_CRCRST, DISABLE);
}

/**
  * @brief  Resets the CRC RESULT register .
  * @param  CRCx: Selects the CRC peripheral
  * @param  None
  * @retval None
  */
void CRC_init(CRC_TypeDef* CRCx)
{
    /* Reset CRC Result init */
    CRCx->RESULT = 0xffff;
}

/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  Selects the CRC peripheral
  * @param  Data: data word(8-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_CalcCRC8(CRC_TypeDef* CRCx, uint8_t Data)
{
    uint16_t crc_result;

    /*Set the value to the CRC_DATA_8 resgister*/
    CRC_DATA8 = Data;

    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRC->RESULT;

    return  (uint16_t)crc_result;
}


/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(8-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_CheckCRC8(CRC_TypeDef* CRCx, uint8_t Data)
{
    uint32_t crc_result;

    /*Set the value to the CRC_DATA_8 resgister*/
    CRC_DATA8 = Data;

    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRC->RESULT;

    /*Set the value to the CRC_DATA_16 resgister*/
    CRC_DATA16 = CRC->RESULT & 0xffff;

    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRC->RESULT;

    /*Check the flag of the crc_result*/
    if(crc_result & crc_flag_mask)
        return SUCCESS;

    return ERROR;
}


/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  buffer: data word(16-bit) buffer to compute its CRC
  * @param  count:  data word(16-bit) count to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_MultiCalcCRC8(CRC_TypeDef* CRCx, \
                           uint8_t *buffer, \
                           uint32_t count)
{
    uint32_t i;
    uint32_t crc_result;
    /*Set the value to the CRC_DATA_8*/
    for(i = 0; i < count; i++)
        CRC_DATA8 = buffer[i];
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRC->RESULT;

    return  (uint16_t)crc_result;
}

/**
  * @brief  Computes the 8-bit CRC of a given data word(8-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  buffer: data word(16-bit) buffer to compute its CRC
  * @param  count:  data word(16-bit) count to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_MultiCheckCRC8(CRC_TypeDef* CRCx, \
                               uint8_t *buffer, \
                               uint32_t count)
{
    uint32_t i;
    uint32_t crc_result;

    /*Set the value to the CRC_DATA_8*/
    for(i = 0; i < count; i++)
        CRC_DATA8 = buffer[i];
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;

    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = CRCx->RESULT & 0xffff;

    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;

    /*Check the flag of the crc_result*/
    if(crc_result & crc_flag_mask)
        return SUCCESS;

    return ERROR;
}


/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(16-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_CalcCRC16(CRC_TypeDef* CRCx, uint16_t Data)
{
    uint16_t crc_result;

    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = Data;

    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;

    /*Return the value of the CRC_RESULT */
    return  (uint16_t)crc_result;
}

/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(16-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_CheckCRC16(CRC_TypeDef* CRCx, uint16_t Data)
{
    uint32_t crc_result;
    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = Data;
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = CRCx->RESULT & 0xffff;
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Check the flag of the crc_result*/
    if(crc_result & crc_flag_mask)
        return SUCCESS;

    return ERROR;
}


/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  buffer: data word(16-bit) buffer to compute its CRC
  * @param  count:  data word(16-bit) count to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_MultiCalcCRC16(CRC_TypeDef* CRCx, \
                            uint16_t *buffer, \
                            uint32_t count)
{
    uint32_t i;
    uint16_t crc_result;
    /*Set the value to the CRC_DATA_16*/
    for(i = 0; i < count; i++)
        CRC_DATA16 = buffer[i];
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Return the value of the CRC_RESULT */
    return  (uint16_t)crc_result;
}
/**
  * @brief  Computes the 16-bit CRC of a given data word(16-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  buffer: data word(16-bit) buffer to compute its CRC
  * @param  count:  data word(16-bit) count to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_MultiCheckCRC16(CRC_TypeDef* CRCx, \
                                uint16_t *buffer, \
                                uint32_t count)
{
    uint32_t i = 0, crc_result = 0;
    /*Set the value to the CRC_DATA_16*/
    for(i = 0; i < count; i++)
        CRC_DATA16 = buffer[i];
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result =  CRCx->RESULT;
    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = CRCx->RESULT & 0xffff;
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;

    /*Check the flag of the crc_result*/
    if(crc_result & crc_flag_mask)
        return SUCCESS;

    return ERROR;

}


/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_CalcCRC32(CRC_TypeDef* CRCx, uint32_t Data)
{
    uint16_t crc_result = 0;
    /*Set the value to the CRC_DATA_32*/
    CRC_DATA32 = Data;

    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;

    /*Return the value of the CRC_RESULT */
    return  (uint16_t)crc_result;
}

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_CheckCRC32(CRC_TypeDef* CRCx, uint32_t Data)
{
    uint32_t crc_result = 0;
    /*Set the value to the CRC_DATA_32*/
    CRC_DATA32 = Data;
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = CRCx->RESULT & 0xffff;
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Check the flag of the crc_result*/
    if(crc_result & crc_flag_mask)
        return SUCCESS;
    return ERROR;

}



/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval 16-bit CRC
  */
uint16_t CRC_MultiCalcCRC32(CRC_TypeDef* CRCx, \
                            uint32_t *buffer, \
                            uint32_t count)
{
    uint32_t i = 0, crc_result = 0;
    /*Set the value to the CRC_DATA_32*/
    for(i = 0; i < count; i++)
        CRC_DATA32 = buffer[i];
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;

    /*Return the value of the CRC_RESULT */
    return  (uint16_t)crc_result;
}

/**
  * @brief  Computes the 32-bit CRC of a given data word(32-bit).
  * @param  CRCx: Selects the CRC peripheral
  * @param  Data: data word(32-bit) to compute its CRC
  * @retval ErrorStatus of flag
  */
ErrorStatus CRC_MultiCheckCRC32(CRC_TypeDef* CRCx, \
                                uint32_t *buffer, \
                                uint32_t count)
{
    uint32_t i = 0, crc_result = 0;
    /*Set the value to the CRC_DATA_32*/
    for(i = 0; i < count; i++)
        CRC_DATA32 = buffer[i];
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Set the value to the CRC_DATA_16*/
    CRC_DATA16 = CRCx->RESULT & 0xffff;
    /*Gets the value to the CRC_RESULT resgister*/
    crc_result = CRCx->RESULT;
    /*Check the flag of the crc_result*/
    if(crc_result & crc_flag_mask)
        return SUCCESS;
    return ERROR;
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
/******************* (C) COPYRIGHT 2018 AC1003*****END OF FILE****/


