/**
  ******************************************************************************
  * @file    ac1003_syscon.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the syscon firmware functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_syscon.h"
#include "ac1003_rcc.h"

/**
  * @brief  Deinitializes the SYSCTRL Functions
  *         registers to their default reset values.
	* @param  None
  * @param  None
  * @retval None
  */
void SYSCTRL_DeInit(void)
{
    /*Enable reset APB Peipheral Function*/
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_SYSCONRST, ENABLE);
    /*Disable reset APB Peipheral Function*/
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_SYSCONRST, DISABLE);
}

/**
  * @brief  Enables M0 Lock up function
  * @param  SYSCTRLx: Select the SYSCON peripheral.
  * @param  NewState: new state of the CortexM0Lock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_CortexM0LockUpCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState)
{
    uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));

    /*Close M0lock */
    SYSCTRLx->UNLOCK = SYSCTRL_UNLOCKKEY;
    tmp = SYSCTRLx->CFGR0 & SYSCTRL_CFGR0KEY_MASK;
    if(NewState != DISABLE)
    {
        
        tmp |= SYSCTRL_LOCKUP_EN;
        tmp |= SYSCTRL_CFGR0KEY;
        SYSCTRLx->CFGR0 = tmp;
    }
    else
    {
        tmp &= ~SYSCTRL_LOCKUP_EN;
        tmp |= SYSCTRL_CFGR0KEY;        
        SYSCTRLx->CFGR0 = tmp;
    }

    /*Open M0lock */
    SYSCTRLx->UNLOCK = SYSCTRL_LOCKKEY;
}

/**
  * @brief  Enables or Disable Debug Mode go into deep sleep
  * @param  SYSCTRLx: Select the SYSCON peripheral.
  * @param  NewState: new state of the Debug mode.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_DebugModeDeepsleepCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState)
{
    uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));

    SYSCTRLx->UNLOCK = SYSCTRL_UNLOCKKEY;
    tmp = SYSCTRLx->CFGR0 & SYSCTRL_CFGR0KEY_MASK;
    if(NewState != DISABLE)
    {
        tmp &= ~SYSCTRL_DEEPSLEEPDebug_EN;
        tmp |= SYSCTRL_CFGR0KEY;
        SYSCTRLx->CFGR0 = tmp;
        
    }
    else
    {
        tmp |= SYSCTRL_DEEPSLEEPDebug_EN;
        tmp |= SYSCTRL_CFGR0KEY;        
        SYSCTRLx->CFGR0 = tmp;
    }

    SYSCTRLx->UNLOCK = SYSCTRL_LOCKKEY;
}



/**
  * @brief  Enables or disables the Deep sleep Port interrupts.
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  NewState: new state of the Deep sleep Port.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_DeepsleepPortITCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState)
{
    uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));

    SYSCTRLx->UNLOCK = SYSCTRL_UNLOCKKEY;
    tmp = SYSCTRLx->PORTINTCR & SYSCTRL_PORTINTCRKEY_MASK;
    if(NewState != DISABLE)
    {
        tmp |= SYSCTRL_DEEPSLEEPPORTINT_EN;
        tmp |= SYSCTRL_PORTINTCRKEY;
        /*open deep sleep port interrupt*/
        SYSCTRLx->PORTINTCR = tmp;
    }
    else
    {
        tmp &= ~SYSCTRL_DEEPSLEEPPORTINT_EN;
        tmp |= SYSCTRL_PORTINTCRKEY;
        /*close deep sleep port interrupt*/
        SYSCTRLx->PORTINTCR = tmp;
    }
    SYSCTRLx->UNLOCK = SYSCTRL_LOCKKEY;
}

/**
  * @brief  Enables or disables Active Sleep Port interrupts
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  NewState: new state of the Active Sleep Port.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_ActiveSleepPortITCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState)
{
    uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));

    SYSCTRLx->UNLOCK = SYSCTRL_UNLOCKKEY;
    tmp = SYSCTRLx->PORTINTCR & SYSCTRL_PORTINTCRKEY_MASK;
    if(NewState != DISABLE)
    {
        tmp &= ~SYSCTRL_ACTIVESLEEPPORTINT_EN;
        tmp |= SYSCTRL_PORTINTCRKEY;
        /*Enable active sleep port*/
        SYSCTRLx->PORTINTCR = tmp;
    }
    else
    {
        tmp |= SYSCTRL_ACTIVESLEEPPORTINT_EN;
        tmp |= SYSCTRL_PORTINTCRKEY;
        /*Disable active sleep port*/
        SYSCTRLx->PORTINTCR = tmp;
    }
    SYSCTRLx->UNLOCK = SYSCTRL_LOCKKEY;
}

/**
  * @brief  Config the SPI peripheral CS singnal
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  SPINssPin : selects the GPIO port pin to be used as
            SPI peripheral cs signal
  * @retval None
  */
void SYSCTRL_SPICSConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t SPINssPin)
{
    /*Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_SPINSS_PORT_PIN(SPINSS_PIN));
    /*Set spi cs pin to mask value*/
    SYSCTRLx->PORTCR  &= ~SPINSS_SEL_MASK;
    /*Select spi cs pin*/
    SYSCTRLx->PORTCR  |= SPINssPin;
}

/**
  * @brief  Config TIM10 GATE singnal
  * @param  SYSCTRLx:Select the  the SYSCON peripheral.
  * @param  TIM10Gate: TIM10 GATE signal parameter
  * @retval None
  */
void SYSCTRL_TIM10_GateConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t TIM10Gate)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_TIM0_GATE_SEL(SYSCTRL_TIM0_GATE));
    /*Configure TIM0 GATE selection pin to mask value */
    SYSCTRLx->PORTCR  &=  ~TIM10_GATE_MASK;
    /*Configure TIM0 GATE selection pin value */
    SYSCTRLx->PORTCR  |=  TIM10Gate;
}


/**
  * @brief  Config TIM11 GATE singnal
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  TIM11Gate: TIM11 GATE signal parameter
  * @retval None
  */
void SYSCTRL_TIM11_GateConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t TIM11Gate)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_TIM1_GATE_SEL(SYSCTRL_TIM11_GATE));

    /*Configure TIM1 GATE selection pin to mask value */
    SYSCTRLx->PORTCR  &=  ~TIM11_GATE_MASK;
    /*Configure TIM1 GATE selection pin value */
    SYSCTRLx->PORTCR  |=  TIM11Gate;
}

/**
  * @brief  Config LPTIM GATE singnal
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  LptimeGate: LPTIM GATE signal parameter
  * @retval None
  */
void SYSCTRL_IPTIM_GateConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t LptimeGate)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_IPTIM_GATE_SEL(SYSCTRL_IPTIM_GATE));

    /*Configure IPTIM GATE selection pin to mask value */
    SYSCTRLx->PORTCR  &=  ~IPTIM_GATE_MASK;
    /*Configure IPTIM GATE selection pin value */
    SYSCTRLx->PORTCR  |=  LptimeGate;
}

/**
  * @brief  Config PCA Capture mux config
  * @param  SYSCTRLx:Select the  SYSCON peripheral.
  * @param  CapChannel: PCA Capture channel
  * @param  CapSignal:  PCA Capture singnal
  * @retval None
  */
void SYSCTRL_PCACapMuxConfig(SYSCON_TypeDef *SYSCTRLx, \
                             uint32_t CapChannel, \
                             uint32_t CapSignal)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_PCA_CHANNEL_SET(SYSCTRL_CAP_CHANNEL));
    assert_param(IS_CAP_CHANNEL_SEL(SYSCTRL_CAP_SINGNAL));

    /*Configure PCA MUX selection pin to mask value */
    SYSCTRLx->PCACR &= ~(uint32_t)(PCA_CH_MASK << (CapChannel * 2));
    /*Configure PCA MUX selection pin value */
    SYSCTRLx->PCACR |= (CapSignal << (CapChannel * 2));
}

/**
  * @brief  Config tim1 input signal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  InputChannel: SYSCTRL INPUT CHANNEL PARAMETER
  * @param  InputSignal:  SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None
  */
void SYSCTRL_TIM1_InputSignalConfig(SYSCON_TypeDef *SYSCTRLx, \
                                    uint32_t InputChannel, \
                                    uint32_t InputSignal)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_TIM_CHANNEL_SET(InputChannel));
    assert_param(IS_TIM_INPUTSIGNAL_SEL(InputSignal));

    /* Set TIM1 CHINMUX TO MASK VALUE */
    SYSCTRLx->TIM1CR &= ~(uint32_t)(TIM_CH_MASK << (InputChannel * 4));
    /* Set TIM1 CHINMUX TO SECTION VALUE */
    SYSCTRLx->TIM1CR |= (InputSignal << (InputChannel * 4));
}

/**
  * @brief  Config tim1 ETR signal
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  InputSignal: SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None
  */
void SYSCTRL_TIM1_ETRSignalConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t InputSignal)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_TIMETR_ETR_SET(InputSignal));

    /* Set TIM1 CHINMUX to Mask Value */
    SYSCTRLx->TIM1CR &= ~TIM_ETR_MASK;
    /* Set TIM1 CHINMUX to Mask Select Value */
    SYSCTRLx->TIM1CR |= InputSignal;
}

/**
  * @brief  Config tim1 Break Stm
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @retval None
  */
void SYSCTRL_TIM1_SetBreakSTM(SYSCON_TypeDef *SYSCTRLx)
{
    /*Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    /* Set TIM1 CHINMUX TO ZERO*/
    SYSCTRLx->TIM1CR &= TIM1_BREAK_ZERO;
    /* Set TIM1 CHINMUX TO STM*/
    SYSCTRLx->TIM1CR |= TIM1_BREAK_STM;
}

/**
  * @brief  Config Break Zero
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  None
  * @retval None
  */
void SYSCTRL_TIM1_SetBreakZERO(SYSCON_TypeDef *SYSCTRLx)
{
    /*Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    /*Set TIM1 CHINMUX TO ZERO*/
    SYSCTRLx->TIM1CR &= TIM1_BREAK_ZERO;
}

/**
  * @brief  Config tim2 input signal
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  InputChannel: SYSCTRL INPUT CHANNEL PARAMETER
  * @param  InputSignal:  SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None
  */
void SYSCTRL_TIM2_InputSignalConfig(SYSCON_TypeDef *SYSCTRLx, \
                                    uint32_t InputChannel, \
                                    uint32_t InputSignal)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_TIM_CHANNEL_SET(SYSCTRL_INPUT_CHANNEL));
    assert_param(IS_TIM_INPUTSIGNAL_SEL(SYSCTRL_INPUT_SINGNAL));

    /* Set TIM1 CHINMUX TO MASK Value*/
    SYSCTRLx->TIM2CR &= ~(uint32_t)(TIM_CH_MASK << (InputChannel * 4));
    /* Set TIM1 CHINMUX TO Signal Value*/
    SYSCTRLx->TIM2CR |= (InputSignal << (InputChannel * 4));
}

/**
  * @brief  Config tim2 ETR signal
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  InputSignal: SYSCTRL INPUT SINGNAL PARAMETER
  * @retval None
  */
void SYSCTRL_TIM2_ETRSignalConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t InputSignal)
{
    /* Check the parameters */
    assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
    assert_param(IS_TIMETR_ETR_SET(SYSCTRL_INPUT_SINGNAL));

    /* Set TIM2 CHINMUX To Mask Value*/
    SYSCTRLx->TIM2CR &= ~TIM_ETR_MASK;
    /* Set TIM2 CHINMUX To input signal Value*/
    SYSCTRLx->TIM2CR |= InputSignal;
}

/**
  * @brief  Config Lpuart clock
  * @param  SYSCTRLx:Select the SYSCON peripheral.
  * @param  LpuartClk: Config lpuart clock
  * @retval None
  */
void SYSCTRL_LPUART_CLKConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t LpuartClk)
{
//	uint32_t tmpreg=0;
//  /* Check the parameters */
//	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
//	assert_param(IS_LPUART_CLK_SEL(LpuartClk));
//
//	/*Close Syscon Lock */
//  SYSCTRLx->UNLOCK = SYSCTRL_UNLOCKKEY;
//
//	/*Config LpuartClk value*/
//	tmpreg = (((SYSCTRLx->LPUARTCON)&SYSCTRL_LPUARTKEY_MASK)|SYSCTRL_LPUARTKEY);
//	tmpreg  = ((tmpreg&(~LPUARTCLK_MASK))|LpuartClk);
//
//	/* Set LpuartClk */
//	SYSCTRLx->LPUARTCON = tmpreg;

//	/*open lock */
//  SYSCTRLx->UNLOCK = SYSCTRL_LOCKKEY;
}

/**
  * @brief  Enables SYSCTRL LPUART Clock
  * @param  SYSCTRLx:Select the LPUART or the SYSCON peripheral.
  * @param  NewState: new state of the LPUARTx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYSCTRL_LPUART_CLKCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState)
{
//	uint32_t tmpreg=0;
//  /*Check the parameters */
//	assert_param(IS_SYSCTRL_ALL_PERIPH(SYSCTRLx));
//  assert_param(IS_FUNCTIONAL_STATE(NewState));
//
//		/*Close Syscon lock */
//  SYSCTRLx->UNLOCK = SYSCTRL_UNLOCKKEY;
//	tmpreg = (((SYSCTRLx->LPUARTCON)&SYSCTRL_LPUARTKEY_MASK)|SYSCTRL_LPUARTKEY);
//
//	if(NewState != DISABLE)
//	{
//		/*Enable Lpuart clk */
//		tmpreg |= (uint32_t)LPUARTCLK_EN;
//		SYSCTRLx->LPUARTCON = tmpreg;
//	}
//	else
//	{
//		/*Disalbe Lpuart clk */
//		tmpreg &= ~(uint32_t)LPUARTCLK_EN;
//		SYSCTRLx->LPUARTCON = tmpreg;
//	}
//	/*Open Syscon lock */
//  SYSCTRLx->UNLOCK = SYSCTRL_LOCKKEY;
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
