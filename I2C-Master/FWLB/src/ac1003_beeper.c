/**
  ******************************************************************************
  * @file    ac1003_beeper.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    15-10-2018
  * @brief   This file provides all the Beeper firmware functions.
  *****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include  "ac1003_beeper.h"
#include  "ac1003_rcc.h"

/**
  * @brief  Deinitializes the BEEPER peripheral registers
	          to their default reset values.
  * @param  None
	* @param  None
  * @retval None
  */
void BEEPER_DeInit(void)
{
    /*Enable Beeper reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_BEEPRST, ENABLE);
    /*Release Beeper from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_BEEPRST, DISABLE);
}



/** @brief  Set Beeper_Prescaler
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  BeeperPrescaler: Selects the BEEPER Prescaler
  * @retval None
  */
void BEEPER_SetPrescaler(BEEPER_TypeDef *BEEPERx, uint32_t BeeperPrescaler)
{
    /* Check the parameters */
    assert_param(IS_BEEPER_ALL_PERIPH(BEEPERx));
    assert_param(IS_BEEPER_PRESCALER(BeeperPrescaler));
    /*Set the bits to the CSR register to 0*/
    BEEPERx->CSR &= ~BEEPERDIV_MASK;

    /*Set the vlaue to bits of the CSR register */
    BEEPERx->CSR |= BeeperPrescaler;
}


/** @brief  BEEPER select prescaler
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  PreClk:  Selects the BEEPER peripheral output frequency
  * @retval None
  */
void BEEPER_SelectPrescaler(BEEPER_TypeDef *BEEPERx, uint32_t PreClk)
{
    /* Check the parameters */
    assert_param(IS_BEEPER_ALL_PERIPH(BEEPERx));
    assert_param(IS_BEEPER_CLOCKSEL(PreClk));

    /*Set the output frequency bits of beeper to 0*/
    BEEPERx->CSR &= ~BEEPERSELECT_MASK;

    /*Set the output frequency bits of beeper*/
    BEEPERx->CSR |= PreClk;
}

/** @brief  Enables BEEPER peripheral
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  NewState: new state of the WWDG peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void BEEPER_Cmd(BEEPER_TypeDef *BEEPERx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE)
    {
        /* Enable beeper function */
        BEEPERx->CSR |= BEEPER_ENABLE;
    }
    else
    {
        /* Disable beeper function */
        BEEPERx->CSR &= ~BEEPER_ENABLE;
    }
}


/** @brief  Set Beeper Clock
  * @param  BEEPERx: Selects the BEEPER peripheral
  * @param  CLK: Selects the BEEPER peripheral
  * @retval None
  */
void BEEPER_SetClock(BEEPER_TypeDef *BEEPERx, uint32_t CLK)
{
    /* Check the parameters */
    assert_param(IS_BEEPER_SELECLOCK(CLK));

    /* Set the bits of CSR register to 0*/
    BEEPERx->CSR  &=  ~BEEPERCLOCK_MASK;

    /*Set the clk bits of beeper*/
    BEEPERx->CSR  |=  CLK;
}
/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 AC1003 *****END OF FILE****/
