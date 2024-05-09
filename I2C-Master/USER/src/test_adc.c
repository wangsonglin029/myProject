/**
  **********************************************************************
  * @file    test_adc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    28-5-2019
  * @brief   This file provides APP functions to manage the following
  *          functionalities of the ADC peripheral:
  *            + ADC Interface configuration
  **********************************************************************
  */

/************* Includes *********************/
#include "test_adc.h"
#include "stdbool.h"

/*define parameters*/
/*ADC Interrupt Flag*/
uint32_t ADC_FLAG = 0x00000000;

/**
  * @brief  Config adc parameters of working.
  * @param  None.
	* @param  None.
  * @retval None.
  */
void ADC_Mode_Config(void)
{
    ADC_InitTypeDef ADC_InitStruct;
    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    /*?????ADC??????*/
    ADC_CommonInitStruct.ADC_CircleMode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_CtMode = ADC_Ct_Single;
    ADC_CommonInitStruct.ADC_SetAdcCnt = 0x00000f00;
    ADC_CommonInitStruct.ADC_Trigs0Sel = ADC_Trigs0_DISABLE;
    ADC_CommonInitStruct.ADC_Trigs1Sel = ADC_Trigs1_DISABLE;

    /*?????ADC????*/
    ADC_InitStruct.ADC_ChannelSel = ADC_Channel4;
    ADC_InitStruct.ADC_ClkSel = ADC_Prescaler_Div64;
    ADC_InitStruct.ADC_SamSel = ADC_SAMPLE_8CYCLE;

    /*?????ADC*/
    ADC_Init(ADC, &ADC_InitStruct);
    ADC_CommonInit(ADC, &ADC_CommonInitStruct);

    /*GPIO ??????????*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_AIN4_PD3); //pin confing

    ADC_ITCmd(ADC, ADC_TICHANNEL0_FLAG, ENABLE);

    // ????ADC ??????????
    ADC_Cmd(ADC, ENABLE);
}

/**
  * @brief  Config adc NVIC parameters
  * @param  None.
	* @param  None.
  * @retval None.
  */
void ADC_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    // ?????§Ø??????
    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  This function handles ADC0 Handler.
  * @param  None
  * @param  None
  * @retval None
  */
void ADC_IRQHandler(void)
{
    if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL0_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL0_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL1_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL1_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL2_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL2_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL3_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL3_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL4_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL4_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL5_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL5_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL6_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL6_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICHANNEL7_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICHANNEL7_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TILLT_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TILLT_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TIHHT_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TIHHT_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TIREG_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TIREG_FLAG);
    else if(ADC_GetMISFlagStatus(ADC, ADC_TICONT_FLAG) == SET)
        ADC_ClearFlag(ADC, ADC_TICONT_FLAG);
    ADC_FLAG = 0x01;
}

bool AdcForTemperature(uint16_t *adcvalue)
{
  uint16_t adctemp = 0;

  static uint16_t adcmax = 0;
  static uint16_t adcmin = 4095;
  static uint32_t adcsum = 0;
  static uint8_t counter = 0;
  
  ADC_SoftwareStartConv(ADC);
  while(ADC_GetSoftwareStartConvStatus(ADC) != RESET);
  adctemp = ADC_GetConversionValue(ADC);
  if(adctemp > adcmax)adcmax = adctemp;
  if(adctemp < adcmin)adcmin = adctemp;
  adcsum += adctemp;
  counter ++;
  
  if(counter >= 18)
  {
    adcsum = adcsum - adcmin - adcmax;
    *adcvalue = adcsum >> 4;
    counter = 0;
    adcsum = 0;
    adcmax = 0;
    adcmin = 4095;
    return true;
  }
  else 
  {
    return false;
  }
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

/************************ (C) COPYRIGHT To AC1003 *****END OF FILE****/

