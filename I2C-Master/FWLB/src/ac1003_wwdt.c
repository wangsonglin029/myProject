/**
  ******************************************************************************
  * @file    ac1003_wwdg.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Window watchdog (WWDG) peripheral:
  *           + Prescaler, Refresh window and Counter configuration
  *           + WWDG activation
  *           + Interrupts and flags management
  *
  ****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_wwdt.h"
#include "ac1003_rcc.h"

/**
  * @brief  Deinitializes the WWDG peripheral registers to their default reset values.
  * @param  None
	* @param  None
  * @retval None
  */
void WWDG_DeInit(void)
{
    /*Enable CRC reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_WWDTRST, ENABLE);
    /*Release CRC from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_WWDTRST, DISABLE);
}

/**
  * @brief  Sets the WWDG Prescaler.
  * @param  WWDG_Prescaler: specifies the WWDG Prescaler.
  *   This parameter can be one of the following values:
  *     @arg WWDG_Prescaler_1: WWDG counter clock = (PCLK1/4096)/1
  *     @arg WWDG_Prescaler_2: WWDG counter clock = (PCLK1/4096)/2
  *     @arg WWDG_Prescaler_4: WWDG counter clock = (PCLK1/4096)/4
  *     @arg WWDG_Prescaler_8: WWDG counter clock = (PCLK1/4096)/8
  * @retval None
  */
void WWDG_SetPrescaler(WWDG_TypeDef* WWDGx, uint32_t WWDG_Prescaler)
{
    uint32_t tmpreg = 0;
    /* Check the parameters */
    assert_param(IS_WWDG_PRESCALER(WWDG_Prescaler));
    /* Clear WDGTB[1:0] bits */
    tmpreg = WWDGx->CR & CTL_WDGTB_MASK;
    /* Set WDGTB[1:0] bits according to WWDG_Prescaler value */
    tmpreg |= (WWDG_Prescaler << 8);
    /* Store the new value */
    WWDGx->CR = tmpreg;
}

/**
  * @brief  Sets the WWDG window value.
  * @param  WindowValue: specifies the window value to be compared to the downcounter.
  *   This parameter value must be lower than 0x80.
  * @retval None
  */
void WWDG_SetWindowValue(WWDG_TypeDef* WWDGx, uint8_t WindowValue)
{
    __IO uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_WWDG_WINDOW_VALUE(WindowValue));
    /* Clear W[6:0] bits */

    tmpreg = WWDGx->CR & CTL_W_MASK;

    /* Set W[6:0] bits according to WindowValue value */
    tmpreg |= WindowValue & (uint32_t) BIT_MASK;

    /* Store the new value */
    WWDGx->CR = tmpreg;
}

/**
  * @brief  Enables the WWDG Early Wakeup interrupt(EWI).
  * @note   Once enabled this interrupt cannot be disabled except by a system reset.
  * @param  NewState: new state of the WWDG peripheral.
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_ITCmd(WWDG_TypeDef* WWDGx, FunctionalState NewStatus)
{
    if(NewStatus != DISABLE)
        /* Enables the interrupt */
        WWDGx->INTEN |= WWDG_INT_ENABLE;
    else
        /* Disable the interrupt */
        WWDGx->INTEN &= ~WWDG_INT_ENABLE;
}

/**
  * @brief  Sets the WWDG counter value.
  * @param  Rldcnt: specifies the watchdog counter value.
  * @retval None
  */
void WWDG_SetRldCnt(WWDG_TypeDef* WWDGx, uint8_t Rldcnt)
{
    /* set the vlaue to the RLDCNT*/
    WWDGx->RLOAD = Rldcnt & BIT_MASK;
}


/**
  * @brief  Enables WWDG counter function.
  * @param  NewState: new state of the WWDG peripheral.
  * This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WWDG_Cmd(WWDG_TypeDef* WWDGx, FunctionalState NewStatus)
{
    /* Check the parameters */
    if(NewStatus != DISABLE)
    {
        WWDGx->CR |= WWDG_CTL_ENBLE ;
    }
    else
    {
        WWDGx->CR &= ~WWDG_CTL_ENBLE ;
    }
}
/**
  * @brief  Checks whether the Early Wakeup interrupt flag is set or not.
  * @param  WWDG_FLAG:specifies the WWDG FLAG to check.
  * This parameter can be one of the following values:
  *     @arg WWDG_INT_FLAG: wwdg interrupt flag
  * @retval The new state of the Early Wakeup interrupt flag (SET or RESET)
  */
FlagStatus WWDG_GetFlagStatus(WWDG_TypeDef* WWDGx, uint16_t WWDG_FLAG)
{
    FlagStatus bitstatus = RESET;

    if (((WWDGx->SR)&WWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Clears Early Wakeup interrupt flag.
  * @param  None
  * @retval None
  */
void WWDG_ClearFlag(WWDG_TypeDef* WWDGx)
{
    /*Clear the flag interrupt*/
    WWDGx->INTCLR =  WWDG_CRL_STATUS;
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

/************************ (C) COPYRIGHT AC1003 *****END OF FILE****/
