/**
 *****************************************************************************
 * @file    ac1003_iwdt.c
 * @author  MCU Application Team
 * @version V0.0.0
 * @date    2019-8
 * @brief   This file provides firmware functions to manage the following
 *          functionalities of the Independent watchdog (IWDG) peripheral:
 *           + Prescaler and Counter configuration
 *           + IWDG activation
 *           + Flag management
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_iwdt.h"
#include "ac1003_rcc.h"


/** @defgroup IWDG_Group1 Prescaler and Counter configuration functions
 *  @brief   Prescaler and Counter configuration functions
 *
@verbatim
 ===============================================================================
              ##### Prescaler and Counter configuration functions #####
 ===============================================================================
  *
  * @brief  Enables or disables write access to IWDG_PR and IWDG_RLR registers.
  * @param  IWDG_WriteAccess: new state of write access to IWDG_PR and IWDG_RLR registers.
  *          This parameter can be one of the following values:
  *            @arg IWDG_WriteAccess_Enable: Enable write access to IWDG_PR and IWDG_RLR registers
  *            @arg IWDG_WriteAccess_Disable: Disable write access to IWDG_PR and IWDG_RLR registers
	* @param  None
  * @retval None
  */
void IWDG_WriteAccessCmd(IWDG_TypeDef *IWDGx, uint32_t IWDG_WriteAccess)
{
    /* Check the parameters */
    assert_param(IS_IWDG_WRITE_ACCESS(IWDG_WriteAccess));
    IWDGx->UNLOCK = IWDG_WriteAccess;
}


/**
  * @brief  Sets IWDG Reload value.
  * @param  Reload: specifies the IWDG Reload value.
  *          This parameter must be a number between 0 and 0x0FFF.
  * @param  None
  * @retval None
  */
void IWDG_SetReload(IWDG_TypeDef *IWDGx, uint32_t Reload)
{
    /* Check the parameters */
    assert_param(IS_IWDG_RELOAD(Reload));
    /*Set the value to the RLOAD Register*/
    IWDGx->RLOAD = Reload;
}


/**
  * @brief  Sets the mode of IWDG
  * @param  Mode: specifies the IWDG Mode.
  * @param  None
  * @retval None
  */
void IWDG_SetWdtMode(IWDG_TypeDef *IWDGx, uint32_t Mode)
{
    /* Check the parameters */
    if(Mode == COMMAND_WDT_INT)
        IWDGx->CFGR |= COMMAND_WDT_INT;
    else
        IWDGx->CFGR &= ~COMMAND_WDT_INT;
}

/**
  * @brief  Gets IWDG Reload value.
  * @param  None
  * @param  None
  * @retval None
  */
uint32_t IWDG_GetReload(IWDG_TypeDef *IWDGx)
{
    /* Check the parameters */
    return  (uint32_t)(IWDGx->CNTVAL);
}

/**
  * @brief  Reloads IWDG counter with value defined in the reload register
  *         (write access to IWDG_PR and IWDG_RLR registers disabled).
  * @param  None
  * @retval None
  */
void IWDG_ReloadCR(IWDG_TypeDef *IWDGx)
{
    IWDGx->CMDCR = COMMAND_IWDT_RELOAD;
}


/**
  * @brief  Enables IWDG (write access to Command registers disabled).
  * @param  None
  * @param  None
  * @retval None
  */
void IWDG_Cmd(IWDG_TypeDef *IWDGx)
{
    /*Set the vlaue to the command*/
    IWDGx->CMDCR = COMMAND_IWDT_ENABLE;
}

/**
  * @brief  Checks whether the specified IWDG flag is set or not.
  * @param  IWDG_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg IWDG_INT_FLAG: IWDG Interrupt Flags
  * @param  None
  * @retval The new state of IWDG_FLAG (SET or RESET).
  */
FlagStatus IWDG_GetFlagStatus(IWDG_TypeDef *IWDGx, uint16_t IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    if ((IWDGx->SR & IWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
  * @brief  Enable interrupt shield  function
  * @param  NewState: new state of the WWDG peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @param  None
  * @retval None
  */
void IWDG_WdtITShieldCmd(IWDG_TypeDef *IWDGx, FunctionalState NewStatus)
{
    /*Enables the flag of iwdt interrupt*/
    if(NewStatus != DISABLE)
        IWDGx->CFGR |= COMMAND_WDTINTSHIELD_ENBLE;
    else
        /*Disables the flag of iwdt interrupt*/
        IWDGx->CFGR &= ~COMMAND_WDTINTSHIELD_ENBLE;
}

/**
  * @brief  Clears the flag of IWDG
  * @param  None
  * @param  None
  * @retval None
  */
void IWDG_WdtITClear(IWDG_TypeDef *IWDGx)
{
    /*Clears the flag of IWDG*/
    IWDGx->INTCLR = COMMAND_WDTINTCLR_ENBLE;
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

/************************ (C) COPYRIGHT Ascendchip *****END OF FILE****/

