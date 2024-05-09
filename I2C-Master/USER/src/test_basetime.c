/**
  ***************************************************************
  * @file    test_basetime.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief
  ***************************************************************
  */

/*Includes ----------------------------*/
#include "test_basetime.h"
#include "misc.h"


/****************************************************
 * Local type definitions ('typedef')
 ******************************************************/
uint64_t BASIC_TIMFLag = 0;

/**
  * @brief  Config basic time NVIC.
  * @param  None
  * @param  None
  * @retval None
  */
static void TIM_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    // ?????§Ø????
    NVIC_InitStructure.NVIC_IRQChannel = BASIC_TIM_IRQ ;
    // ?????????????3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Config basic tim mode
  * @param  None
  * @param  None
  * @retval None
  * BaseTime ???????????
  */
void BASIC_TIM_Mode_Config(void)
{
    /*define basetime parameters */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

    /*Config basetime parameters*/
    TIM_TimeBaseInitStruct.TIM_ClockDivision = BASIC_TIM_ClKDIV;//???????
    TIM_TimeBaseInitStruct.TIM_TMROS = BASIC_TIM_TMROS;//???????????????????
    TIM_TimeBaseInitStruct.TIM_TMRSZ = BASIC_TIM_TMRSZ;//??????????
    TIM_TimeBaseInitStruct.TIM_TMRMS = BASIC_TIM_TMRMS;//???????????
    TIM_TimeBaseInitStruct.TIM_CounterMode = BASIC_TIM_COUNTERMODE;//???????
    TIM_TimeBaseInitStruct.TIM_GATE = BASIC_TIM_GATE;//????????
    TIM_TimeBaseInitStruct.TIM_GATE_Polarity = BASIC_TIM_GATE_POLARITY;//???GATE???????
    TIM_TimeBaseInit(BASIC_TIM, &TIM_TimeBaseInitStruct);

    /*Config basetime Load Value*/
    TIM_SetTimerLoadRegister(BASIC_TIM, BASIC_TIM_LOAD_VALUE); // BASIC_TIM_LOAD_VALUE  (0xFFFFFFFF - 24*1000*10) /* 10ms */

    /*Enable basetime interrupt function*/
    TIM_ITConfig(BASIC_TIM, BASIC_TIM_TI_ENABLE);
    TIM_NVIC_Config();

    /*Enable basetime function*/
    TIM_Cmd(BASIC_TIM, ENABLE);

    return ;
}



/**
  * @brief  This function handles TIMER0_IRQHandler interrupt request.
  * @param  None
  * @param  None
  * @retval None
  */
void BASIC_TIM_IRQHandler(void)
{
    /*Clear interrupt flag*/
    TIM_ClearITFlag(BASIC_TIM, TIM_IT_FLAG);
    BASIC_TIMFLag ++;
}

// 1ms
uint64_t GetTick(void)
{
  return BASIC_TIMFLag;
}

// ????????????¦Ë??
void SetTick(uint64_t tick_s)
{
  BASIC_TIMFLag = tick_s * 1000;
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


