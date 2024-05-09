/**
  ***************************************************************
  * @file    test_wwdt.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief
  ***************************************************************
  */

/*Includes ----------------------------*/
#include "test_wwdt.h"

/****************************************************
 * Local type definitions ('typedef')
 ******************************************************/
volatile uint32_t WWDG_FLAG;

/**
  * @brief  Config  NVIC of WWDG interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
static void WWDG_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_WWDG_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Config  WWDG parameters.
  * @param  None
	* @param  None
  * @retval None
  */
void WWDG_Config(void)
{
    /*Config WWDG Prescaler*/
    WWDG_SetPrescaler(WWDG, WWDG_PRESCALER);

    /*Config WWDG Window Value*/
    WWDG_SetWindowValue(WWDG, WWDG_WINDOWVALUE);

    /*Clear WWDG Flag*/
    WWDG_ClearFlag(WWDG);

    /*Config WWDG NVIC Parameters*/
    WWDG_NVIC_Config();

    /*Enable the WWDG Interrupt*/
    WWDG_ITCmd(WWDG, WWDG_CMD_TI);

//	/*Open WWDG Function*/
//   WWDG_Cmd(WWDG,WWDG_CMD_ENABLE);
}

/**
  * @brief  Config  WWDG Feed parameters.
  * @param  None
	* @param  None
  * @retval None
  */
void WWDG_Feed(void)
{
    //Feed the WWDG: The max of WWDG_CNT=0X7F
    WWDG_SetRldCnt(WWDG, WWDG_CNT);
}


/**
  * @brief  DEBUG WWDG IRQHandler.
  * @param  None
	* @param  None
  * @retval None
  */
void DEBUG_WWDG_IRQHandler(void)
{
    /*Clear wwdg flag*/
    WWDG_ClearFlag(WWDG);
    
    /*Feed wwdg*/
    WWDG_Feed();

    WWDG_FLAG = 0x1;
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
