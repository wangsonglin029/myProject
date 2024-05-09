/**
  ***************************************************************
  * @file    test_iwdt.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   
  ***************************************************************
  */

/*Includes ----------------------------*/
#include "test_iwdt.h"

/****************************************************
 * Local type definitions ('typedef')
 ******************************************************/
 /*<interrupt recive data flag*/
volatile uint32_t IWDG_FLAG = 0;   


/**
  * @brief  Config  NVIC of IWDG interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
static void IWDG_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_IWDG_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/**
  * @brief  Config IWDG parameters.
  * @param  None
	* @param  None
  * @retval None
  */
void IWDG_Config(void)
{	
    /*Config IWDG NVIC */
    IWDG_NVIC_Config();
    /*Disable IWDG Protect function*/
    IWDG_WriteAccessCmd(DEBUG_IWDGx,IWDG_WriteAccess_Disable);
    /*Set IWDG Mode*/
    IWDG_SetWdtMode(DEBUG_IWDGx,DEBUG_IWDG_MODE);
    /*Disable IWDG Mask*/
    IWDG_WdtITShieldCmd(DEBUG_IWDGx,DEBUG_IWDG_MASK);
    /*Set IWDG Load*/
    IWDG_SetReload(DEBUG_IWDGx,DEBUG_IWDG_LOAD);
    /*Enable IWDG Function*/
    IWDG_Cmd(DEBUG_IWDGx);
    /*Enable IWDG Protect function*/
    IWDG_WriteAccessCmd(DEBUG_IWDGx,IWDG_WriteAccess_Enable);
}

/**
  * @brief  Config IWDG Feed Function.
  * @param  None
	* @param  None
  * @retval None
  */
void IWDG_Feed(void)
{
	/*Set IWDG Reload refresh cmd*/
	IWDG_ReloadCR(DEBUG_IWDGx);
}


/**
  * @brief  This function handles SPI0COMB_IRQn interrupt request.
  * @param  None
  * @retval None
  */
void DEBUG_IWDG_IRQHandler(void)
{
  /*Disable IWDG Protect function*/
  IWDG_WriteAccessCmd(DEBUG_IWDGx,IWDG_WriteAccess_Disable);
  /*Clear IWDG interrupt flag*/
  IWDG_WdtITClear(DEBUG_IWDGx);
  /*Enable IWDG Protect function*/
  IWDG_WriteAccessCmd(DEBUG_IWDGx,IWDG_WriteAccess_Enable);
  /*Set IWDG FLAG*/
  IWDG_FLAG = 0x1;
  /*System Reset*/
  SystemReset();
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
/************************ (C) COPYRIGHT to AC1003 *****END OF FILE****/





