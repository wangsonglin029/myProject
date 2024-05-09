/**
  ******************************************************************************
  * @file    ac1003_adc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides firmware functions of ADC
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_adc.h"
#include "ac1003_rcc.h"

/**
  * @brief  Deinitializes all ADC peripherals registers to their default reset
  *         values.
  * @param  None
	* @param  None
  * @retval None
  */
void ADC_DeInit(void)
{
    /*Enable ADC Periph reset*/
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ADCRST, ENABLE);

    /*Disable ADC Periph reset*/
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_ADCRST, DISABLE);
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC (
  *         Resolution and Data Alignment), however, the rest of the configuration
  *         parameters are specific to the regular channels group (scan mode
  *         activation, continuous mode activation, External trigger source and
  *         edge, number of conversion in the regular channels group sequencer).
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct)
{
    uint32_t tmpreg1 = 0;


    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_PRESCALER(ADC_InitStruct->ADC_ClkSel));
    assert_param(IS_ADC_CHANNEL(ADC_InitStruct->ADC_ChannelSel));
    assert_param(IS_ADC_SAMPLE_CYCLE(ADC_InitStruct->ADC_SamSel));


    /*---------------------------- ADCx CR0 Configuration -----------------*/
    /* Get the ADCx CR0 value */
    tmpreg1 = ADCx->CR0;

    /* Clear RES and SCAN bits */
    tmpreg1 &=  (~ADC_CR0_MASK);

    /* Configure ADCx: scan conversion mode and resolution */
    tmpreg1 |= (uint32_t)(((uint32_t)ADC_InitStruct->ADC_ClkSel ) | \
                          ((uint32_t)ADC_InitStruct->ADC_ChannelSel) | \
                          ((uint32_t)ADC_InitStruct->ADC_SamSel));

    /* Write to ADCx CR0 */
    ADCx->CR0 = tmpreg1;
    /*---------------------------- ADCx CR2 Configuration -----------------*/
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC (
  *         Resolution and Data Alignment), however, the rest of the configuration
  *         parameters are specific to the regular channels group (scan mode
  *         activation, continuous mode activation, number of conversion
            in the regular channels group sequencer).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will
  *         be initialized.
  * @param  None
  * @retval None
  */
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
    /* Initialize the ADC_ClkSel member*/
    ADC_InitStruct->ADC_ClkSel = 0x00;

    /* Initialize the ADC_SamSel member*/
    ADC_InitStruct->ADC_SamSel = 0x00;

    /* Initialize the ADC_ChannelSel member*/
    ADC_InitStruct->ADC_ChannelSel = 0x00;
}

/**
  * @brief  Initializes the ADCs peripherals according to the specified parameters
  *         in the ADC_CommonInitStruct.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure
  *         that contains the configuration information for  All ADCs peripherals.
  * @retval None
  */
void ADC_CommonInit(ADC_TypeDef* ADCx, ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
    uint32_t tmpreg1 = 0;
    /* Check the parameters */
    assert_param(IS_ADC_CT(ADC_CommonInitStruct->ADC_CtMode));
    assert_param(IS_ADC_TRIG0_EDGE(ADC_CommonInitStruct->ADC_Trigs0Sel));
    assert_param(IS_ADC_TRIG1_EDGE(ADC_CommonInitStruct->ADC_Trigs1Sel));
    assert_param(IS_ADC_MODE(ADC_CommonInitStruct->ADC_CircleMode));
    assert_param(IS_ADC_SAMPLE_TIMES(ADC_CommonInitStruct->ADC_SetAdcCnt));

    /*---------------------------- ADC CR1 Configuration -----------------*/
    /* Get the ADC CR1 value */
    tmpreg1 = ADCx->CR1;

    /* Clear MULTI, DELAY, DMA and ADCPRE bits */
    tmpreg1 &= (~ADC_CR1_MASK);

    /* Set CR1 bits according to ADC_CtMode value */
    /* Set CR1 bits according to ADC_Trigs0Sel value */
    /* Set CR1 bits according to ADC_Trigs1Sel value */
    tmpreg1 |= (uint32_t)(ADC_CommonInitStruct->ADC_CtMode | \
                          ADC_CommonInitStruct->ADC_Trigs0Sel | \
                          ADC_CommonInitStruct->ADC_Trigs1Sel);


    /* Write to ADC CR1 */
    ADCx->CR1 = tmpreg1;

    /*---------------------------- ADC CR2 Configuration -----------------*/
    /* Get the ADC CR2 value */
    tmpreg1 = ADCx->CR2;

    /* Clear CircleMode, SetAdcCnt bits */
    tmpreg1 &= (~ADC_CR2_MASK);


    /* Set CR2 bits according to ADC_CircleMode value */
    /* Set CR2 bits according to ADC_SetAdcCnt value */

    tmpreg1 |= (uint32_t)((ADC_CommonInitStruct->ADC_CircleMode) |
                          (ADC_CommonInitStruct->ADC_SetAdcCnt));

    /* Write to ADC CR2 */
    ADCx->CR2  =  tmpreg1;
}

/**
  * @brief  Fills each ADC_CommonInitStruct member with its default value.
  * @param  ADC_CommonInitStruct: pointer to an ADC_CommonInitTypeDef structure
  *         which will be initialized.
  * @param  None
  * @retval None
  */
void ADC_CommonStructInit(ADC_CommonInitTypeDef* ADC_CommonInitStruct)
{
    /* Initialize the ADC_CtMode member */
    ADC_CommonInitStruct->ADC_CtMode = ADC_Ct_Single;

    /* initialize the ADC_Trigs0Sel member */
    ADC_CommonInitStruct->ADC_Trigs0Sel = ADC_Trigs0_DISABLE;

    /* Initialize the ADC_Trigs1Sel member */
    ADC_CommonInitStruct->ADC_Trigs1Sel = ADC_Trigs1_DISABLE;

    /* Initialize the ADC_TwoSamplingDelay member */
    ADC_CommonInitStruct->ADC_CircleMode = ADC_Mode_Independent;

    /* Initialize the ADC_TwoSamplingDelay member */
    ADC_CommonInitStruct->ADC_SetAdcCnt = 0x00;
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx:  select the ADC peripheral.
  * @param  NewState: new state of the ADCx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected adc peripheral*/
        ADCx->CR0 |= (uint32_t)ADC_CR0_ADON;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADCx->CR0 &= (uint32_t)(~ADC_CR0_ADON);
    }
}

/**
  * @brief  Configures for the selected ADC regular channel its corresponding
  *         rank in the sequencer and its sample time.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure.
  *          This parameter can be one of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *
  * @param  ADC_SampleTime: The sample time value to be set for the selected channel.

  * @retval None
  */
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, \
                              uint32_t ADC_Channel, \
                              uint32_t ADC_CircleMode, \
                              uint32_t ADC_SampleTime)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(ADC_Channel));
    assert_param(IS_ADC_MODE(ADC_CycleMode));
    assert_param(IS_ADC_SAMPLE_TIMES(ADC_SampleTime));

    /*Set channel mask*/
    ADCx->CR0 &=  (~ADC_ChannelEL_MASK);
    /*Select adc channel*/
    ADCx->CR0 |=  ADC_Channel;

    /*Set circle mask*/
    ADCx->CR2 &=  (~ADC_CIRCLEMODE_MASK);
    ADCx->CR2 |=   ADC_CircleMode;

    /*set sample times*/
    ADCx->CR2 &=  (~ADC_ADCCNT_MASK);
    ADCx->CR2 |=   ADC_SampleTime;
}

/**
  * @brief  Enables the selected ADC software start conversion of the regular channels.
  * @param  ADCx:  select the ADC peripheral.
  * @param  None
  * @retval None
  */
void ADC_SoftwareStartConv(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Enable the selected ADC conversion for regular group */
    ADCx->CR0 |= (uint32_t)ADC_CR0_SWSTART;
}

/**
  * @brief  Gets the selected ADC Software start regular conversion Status.
  * @param  ADCx: select the ADC peripheral.
  * @param  None
  * @retval The new state of ADC software start conversion (SET or RESET).
  */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef* ADCx)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Check the status of SWSTART bit */
    if ((ADCx->CR0 & ADC_CR0_SWSTART) != (uint32_t)RESET)
    {
        /* SWstart bit is set */
        bitstatus = SET;
    }
    else
    {
        /* SWstart bit is reset */
        bitstatus = RESET;
    }

    /* Return the SWstart bit status */
    return  bitstatus;
}


/**
  * @brief  Enables or disables the ADC continuous conversion mode
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC continuous conversion mode
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC continuous conversion mode */
        ADCx->CR1 |= (uint32_t)ADC_Ct_Contine;
    }
    else
    {
        /* Disable the selected ADC continuous conversion mode */
        ADCx->CR1 &= (uint32_t)(~ADC_Ct_Contine);
    }
}


/**
  * @brief  Enables or disables the ADC continuous conversion mode
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC continuous conversion mode
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ContinuousConverChannelCmd(ADC_TypeDef* ADCx, \
                                    uint32_t Channel_Enable, \
                                    FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_CHANNEL_CMD(Channel_Enable));

    if (NewState != DISABLE)
    {
        /* Enable the selected ADC continuous channel */
        ADCx->CR2 |= (uint32_t)Channel_Enable;
    }
    else
    {
        /* Disable the selected ADC continuous channel*/
        ADCx->CR2 &= (uint32_t)(~Channel_Enable);
    }
}

/**
  * @brief  Enables or disables the ADC continuous convert Rst
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC continuous conversion mode
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ContinuousConverRstCmd(ADC_TypeDef* ADCx, uint32_t NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));


    if (NewState != DISABLE)
    {
        /* Enable the selected ADC continuous conversion Rest */
        ADCx->CR0 |= (uint32_t)ADC_CR0_STATERST;
    }
    else
    {
        /* Disable the selected ADC continuous conversion Rest*/
        ADCx->CR0 &= (uint32_t)(~ADC_CR0_STATERST);
    }
}



/**
  * @brief  Enables or disables the discontinuous mode on regular group channel
  *         for the specified ADC
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the selected ADC discontinuous mode on
  *         regular group channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_DisContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Disable the selected ADC continuous conversion mode */
        ADCx->CR1 &= (uint32_t)(~ADC_Ct_Contine);
    }
    else
    {
        /* Enable the selected ADC continuous conversion mode */
        ADCx->CR1 |= (uint32_t)ADC_Ct_Contine;
    }
}

/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: select the ADC peripheral.
  * @param  None
  * @retval The Data conversion value.
  */
uint32_t ADC_GetConversionValue(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Return the selected ADC conversion value */
    return (uint16_t) ADCx->RESULT;
}

/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: select the ADC peripheral.
  * @param  Channel: select the ADC peripheral channel.
  * @retval The Data conversion value.
  */
uint32_t ADC_GetChannelConversionValue(ADC_TypeDef* ADCx, uint32_t Channel)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_CHANNEL(Channel));

    /* Return ADC channel0 conversion value */
    if(Channel == ADC_Channel0)
        return (uint32_t) ADCx->RESULT0;

    /* Return ADC channel1 conversion value */
    else if(Channel == ADC_Channel1)
        return (uint32_t) ADCx->RESULT1;

    /* Return ADC channel2 conversion value */
    else if(Channel == ADC_Channel2)
        return (uint32_t) ADCx->RESULT2;

    /* Return ADC channel3 conversion value */
    else if(Channel == ADC_Channel3)
        return (uint32_t) ADCx->RESULT3;

    /* Return ADC channel4 conversion value */
    else if(Channel == ADC_Channel4)
        return (uint32_t) ADCx->RESULT4;

    /* Return ADC channel5 conversion value */
    else if(Channel == ADC_Channel5)
        return (uint32_t) ADCx->RESULT5;

    /* Return ADC channel6 conversion value */
    else if(Channel == ADC_Channel6)
        return (uint32_t) ADCx->RESULT6;

    else {
        /* Return ADC channel7 conversion value */
        if(Channel == ADC_Channel7)
            return (uint32_t) ADCx->RESULT7;
    }
    return (uint32_t)0;
}


/**
  * @brief  set compare ht value
  * @param  ADCx: select the ADC peripheral.
  * @param  HtValue: the value of ht.
  * @retval The Data conversion value.
  */
uint32_t ADC_SetCompareHtValue(ADC_TypeDef* ADCx, uint32_t HtValue)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_COMPARE_VALUES(HtValue));

    /*set ADC ht value */
    ADCx->HT = HtValue;

    return (uint32_t)0;
}

/**
  * @brief  set compare lt value
  * @param  ADCx: select the ADC peripheral.
  * @param  LtValue: the value of lt.
  * @retval The Data conversion value.
  */
uint32_t ADC_SetCompareLtValue(ADC_TypeDef* ADCx, uint32_t LtValue)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_COMPARE_VALUES(LtValue));

    /*set ADC Lt value */
    ADCx->LT = LtValue;

    return (uint32_t)0;
}



/**
  * @brief  Returns the last ADCx conversion result data for regular channel.
  * @param  ADCx: select the ADC peripheral.
  * @param  ControlCmd: ADC control enable
  * @param  NewState: new state of the selected ADC discontinuous mode on
  *         regular group channel.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval The Data conversion value.
  */
uint32_t ADC_CompareControlCmd(ADC_TypeDef* ADCx, \
                               uint32_t ControlCmd, \
                               FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_CR1_CMD(ControlCmd));

    if (NewState != DISABLE)
    {

        /* Enable the compare control*/
        ADCx->CR1 |= (uint32_t)ControlCmd;
    }
    else
    {
        /* Disable the compare control*/
        ADCx->CR1 &= (uint32_t)(~ControlCmd);
    }

    return  (uint32_t)0;
}
/**
 * @brief  Configures the ADCx external trigger for injected channels conversion.
 * @param  ADCx: select the ADC peripheral.
 * @param  ExternalTrigInjecConv: specifies the ADC trigger to start injected conversion.
 *          This parameter can be one of the following values:
 * @retval None
 */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef* ADCx, \
                                        uint32_t ExternalTrigInjecConv)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    /* Get the old register value */
    tmpreg = ADCx->CR1;

    /* Clear the old external event selection for injected group */
    tmpreg &= ~ADC_TRIGS1_MASK;
    tmpreg &= ~ADC_TRIGS0_MASK;

    /* Set the external event selection for injected group */
    tmpreg |= ExternalTrigInjecConv;

    /* Store the new register value */
    ADCx->CR1 = tmpreg;
}
/**
  * @brief  Enables or disables the specified ADC interrupts.
  * @param  ADCx: select the ADC peripheral.
  * @param  ADC_IT: specifies the ADC interrupt sources to be enabled or disabled.
  *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG         ((uint32_t)0x0800)
  * @param   NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval  None
  */
void ADC_ITCmd(ADC_TypeDef* ADCx, \
               uint32_t _ADC_FLAG, \
               FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    assert_param(IS_ADC_FLAG(ADC_FLAG));

    /* Get the ADC IT index */
    if (NewState != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->INTEN |= (uint32_t)_ADC_FLAG;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->INTEN &= (~(uint32_t)_ADC_FLAG);
    }
}


/**
  * @brief  Enables or disables the specified ADC Acc.
  * @param  ADCx:select the ADC peripheral.
  * @param  NewState: new state of the specified ADC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AccCmd(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Get the ADC IT index */
    if (NewState != DISABLE)
    {
        /*Enable the ADC Acc Function */
        ADCx->CR1 |= (uint32_t)ADC_ACC_EN;
    }
    else
    {
        /*Disable the ADC Acc Function*/
        ADCx->CR1 &= (~(uint32_t)ADC_ACC_EN);
    }
}

/**
  * @brief  Clear the acc result
  * @param  ADCx: select the ADC peripheral.
  * @param  NewState: new state of the specified ADC interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_AccResultClear(ADC_TypeDef* ADCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE)
    {
        /*Enable acc result clear*/
        ADCx->CR1 |= ADC_ACCResult_Clear;
    }
    else
    {
        /*Disable acc result clear*/
        ADCx->CR1  &= ~ADC_ACCResult_Clear;
    }
}


/**
  * @brief  Gets acc result
  * @param  ADCx: select the ADC peripheral.
  * @param  None
  * @retval the value of acc result
  */
uint32_t ADC_GetAccResult(ADC_TypeDef* ADCx)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));

    return  (uint32_t)ADCx->RESULTACC;
}


/**
  * @brief  Gets Ris flag status
  * @param  ADCx: select the ADC peripheral.
  * @param  Flag: specifies the flag to check.
 *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG        ((uint32_t)0x0800)
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetRISFlagStatus(ADC_TypeDef* ADCx, uint32_t Flag)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_FLAG(ADC_FLAG));

    /* Check the status of the specified ADC flag */
    if ((ADCx->RAWINTSR & Flag) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return  bitstatus;
}

/**
  * @brief  Gets MIS Flag Status
  * @param  ADCx: select the ADC peripheral.
  * @param  ADCx: select the ADC peripheral.
  *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG         ((uint32_t)0x0800)
  * @retval The new state of ADC_FLAG (SET or RESET).
  */
FlagStatus ADC_GetMISFlagStatus(ADC_TypeDef* ADCx, uint32_t Flag)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_FLAG(ADC_FLAG));

    /* Check the status of the specified ADC flag */
    if ((ADCx->MSKINTSR & Flag) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /*Return the Flag status */
    return  bitstatus;
}

/**
  * @brief  Clears the ADCx's pending flags.
  * @param  ADCx: select the ADC peripheral.
  * @param  Flag: specifies the flag to clear.
  *          This parameter can be one of the following values:
	*						@arg ADC_TICHANNEL0_FLAG    ((uint32_t)0x0001)
	*						@arg ADC_TICHANNEL1_FLAG    ((uint32_t)0x0002)
	*						@arg ADC_TICHANNEL2_FLAG    ((uint32_t)0x0004)
	*						@arg ADC_TICHANNEL3_FLAG    ((uint32_t)0x0008)
	*						@arg ADC_TICHANNEL4_FLAG    ((uint32_t)0x0010)
	*						@arg ADC_TICHANNEL5_FLAG    ((uint32_t)0x0020)
	*						@arg ADC_TICHANNEL6_FLAG    ((uint32_t)0x0040)
	*						@arg ADC_TICHANNEL7_FLAG    ((uint32_t)0x0080)
	*						@arg ADC_TILLT_FLAG         ((uint32_t)0x0100)
	*						@arg ADC_TIHHT_FLAG         ((uint32_t)0x0200)
	*						@arg ADC_TIREG_FLAG         ((uint32_t)0x0400)
	*						@arg ADC_TICONT_FLAG        ((uint32_t)0x0800)
  * @retval None
  */
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t Flag)
{
    /* Check the parameters */
    assert_param(IS_ADC_ALL_PERIPH(ADCx));
    assert_param(IS_ADC_FLAG(Flag));

    /* Clear the selected ADC flags */
    ADCx->INTCLR |= (uint32_t)Flag;
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

/************************ (C) COPYRIGHT ac1003 *****END OF FILE****/
