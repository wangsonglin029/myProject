/**
  ******************************************************************************
  * @file    ac1003_awk.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides all the awk firmware functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_awk.h"
#include "ac1003_rcc.h"


/**
  * @brief  Initializes the AWK peripheral according to the specified
  *         parameters in the AWK_InitStruct.
  * @param  AWKx:selects the AWK peripheral
  * @param  AWK_InitStruct:pointer to a AWK_InitTypeDef structure which will
  *         be initialized.
  * @retval None
  */
void AWK_Init(AWK_TypeDef *AWKx, AWK_InitTypeDef* AWK_InitStruct)
{
    int tmpreg = 0;
    /*Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));
    /*read the value of CR*/
    tmpreg = AWKx->CR;

    /*Clear the function bits to zero*/
    tmpreg &= AWK_CR_MASK;

    /*---------------------------- AWK CR Configuration ------------------------*/
    /*set the specified parameters */
    /*set AWK_XTLPRSC to the XTLPRSC*/
    /*set AWK_SeleteClkSource to the TCLKSEL*/
    /*set AWK_CounterClkDiv to the DIVSEL*/

    tmpreg |= ((AWK_InitStruct->AWK_XTLPRSC << 8) | \
               (AWK_InitStruct->AWK_SeleteClkSource << 5) | \
               (AWK_InitStruct->AWK_CounterClkDiv));

    /*set the value to CR register*/
    AWKx->CR = tmpreg;
}

/**
  * @brief  Enables or disables the specified AWK peripheral function.
  * @param  AWKx:selects the AWK peripheral
  * @param  NewState: new state of the AWK peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void AWK_Cmd(AWK_TypeDef *AWKx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /*---------------------------- AWK CMD ENABLE------------------------*/
    if(NewState != DISABLE)
        /*Enable the awk peripheral*/
        AWKx->CR |= AWK_ENABLE;
    else
        /*Disalbe the awk peripheral*/
        AWKx->CR &= ~AWK_ENABLE;
}

/**
  * @brief  Set the clk of AWK
  * @param  AWKx:selects the AWK peripheral
  * @param  AWKClk: select the AWK clock
  * @retval None
  */
void AWK_SelClk(AWK_TypeDef *AWKx, uint8_t AWKClk)
{
    /* Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));
    assert_param(IS_AWK_SELCLK(AWKClk));

    /*Select the awk clk*/
    AWKx->CR &= ~AWK_CLKMASK;
    AWKx->CR |= AWKClk;
}

/**
  * @brief  Setting up overloaded data registers
  * @param  AWKx:  selects the AWK peripheral
  * @param  value: set the value to the register of Rload
  * @retval None
  */
void AWK_SetRldval(AWK_TypeDef *AWKx, uint8_t value)
{
    /* Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));

    /*Set the value to the register of RLDVAL*/
    AWKx->RLOAD = value;
}

/**
  * @brief  Clear the IT Flag
  * @param  AWKx: selects the AWK peripheral
  * @param  None
  * @retval None
  */
void AWK_ClearITFlag(AWK_TypeDef *AWKx)
{
    /*Check the parameters */
    assert_param(IS_AWK_ALL_PERIPH(AWKx));

    /*Clear the TI Flag*/
    AWKx->INTCLR = AWK_TI_CLEAR;
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
/******************* (C) COPYRIGHT 2018 AC1003 *****END OF FILE****/


