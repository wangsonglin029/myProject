/**
  ******************************************************************************
  * @file    bsp_exti.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I/O???§Ø????bsp
  ******************************************************************************
  */

/* Includes ------------------------*/
#include "test_exti.h"
#include "misc.h"

/****************************************************
 * Local type definitions ('typedef')
 ******************************************************/
uint8_t EXTI_IT_FLAG = 0;
uint32_t WAKEUP_STATS = 0;

#if 0
/**
  * @brief  Config NVIC of GPIOA interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
static void GPIOA_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /* ?????§Ø????????1 */
    NVIC_InitStructure.NVIC_IRQChannel = GPIOA_IRQn;
    /* ??????????? */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* ????§Ø???? */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Config NVIC of GPIOB interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
static void GPIOB_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* ?????§Ø????????1 */
    NVIC_InitStructure.NVIC_IRQChannel = GPIOB_IRQn;
    /* ??????????? */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* ????§Ø???? */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Config NVIC of GPIOC interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
static void GPIOC_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* ?????§Ø????????1 */
    NVIC_InitStructure.NVIC_IRQChannel = GPIOC_IRQn;
    /* ??????????? */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* ????§Ø???? */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
#endif

/**
  * @brief  Config NVIC of GPIOD interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
static void GPIOD_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* ????USART??§Ø?? */
    NVIC_InitStructure.NVIC_IRQChannel = GPIOD_IRQn;
    /* ??????? */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* ????§Ø? */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* ?????????NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Config EXIT interrupt parameters.
  * @param  None
	* @param  None
  * @retval None
  */
void EXTI_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_IRQ_InitTypeDef  GPIO_IRQ_InitStruct;

    /* ???? NVIC ?§Ø?*/
    /// GPIOA_NVIC_Configuration();
    /// GPIOB_NVIC_Configuration();
    /// GPIOC_NVIC_Configuration();
    GPIOD_NVIC_Configuration();

#if 0
    /*--------------------------KEY1????-----------------------------*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStruct);

    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Enable = KEY1_IRQ_Pin_Enable;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Type = KEY1_IRQ_Pin_Type;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Polarity = KEY1_IRQ_Pin_Polarity;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Edge =  KEY1_IRQ_Pin_Edge;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Clear = KEY1_IRQ_Pin_Clear;

    /* ???EXTI?????? */
    GPIO_EXTILineConfig(KEY1_INT_GPIO_PORT, &GPIO_IRQ_InitStruct, KEY1_INT_GPIO_PIN);
#endif
#if 0
    /*--------------------------KEY2????-----------------------------*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStruct);

    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Enable = KEY2_IRQ_Pin_Enable;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Type = KEY2_IRQ_Pin_Type;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Polarity = KEY2_IRQ_Pin_Polarity;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Edge =  KEY2_IRQ_Pin_Edge;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Clear = KEY2_IRQ_Pin_Clear;

    /* ???EXTI?????? */
    GPIO_EXTILineConfig(KEY2_INT_GPIO_PORT, &GPIO_IRQ_InitStruct, KEY2_INT_GPIO_PIN);
#endif
#if 0
    /*--------------------------KEY3????-----------------------------*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = KEY3_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(KEY3_INT_GPIO_PORT, &GPIO_InitStruct);

    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Enable = KEY3_IRQ_Pin_Enable;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Type = KEY3_IRQ_Pin_Type;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Polarity = KEY3_IRQ_Pin_Polarity;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Edge =  KEY3_IRQ_Pin_Edge;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Clear = KEY3_IRQ_Pin_Clear;

    /* ???EXTI?????? */
    GPIO_EXTILineConfig(KEY3_INT_GPIO_PORT, \
                        &GPIO_IRQ_InitStruct, \
                        KEY3_INT_GPIO_PIN);
#endif
#if 1
    /*--------------------------KEY4????-----------------------------*/
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = KEY4_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(KEY4_INT_GPIO_PORT, &GPIO_InitStruct);

    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Enable = KEY4_IRQ_Pin_Enable;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Type = KEY4_IRQ_Pin_Type;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Polarity = KEY4_IRQ_Pin_Polarity;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Edge =  KEY4_IRQ_Pin_Edge;
    GPIO_IRQ_InitStruct.GPIO_IRQ_Pin_Clear = KEY4_IRQ_Pin_Clear;

    /* ???EXTI?????? */
    GPIO_EXTILineConfig(KEY4_INT_GPIO_PORT, \
                        &GPIO_IRQ_InitStruct, \
                        KEY4_INT_GPIO_PIN);
#endif                        
}


/**
  * @brief  This function handles  GPIO_IRQHandler.
  * @param  None
  * @param  None
  * @retval None
  */
static void GPIO_IRQHandler(GPIO_TypeDef* GPIOx)
{
    WAKEUP_STATS = GPIOx->RAWINTSR;
    if((GPIOx->RAWINTSR & GPIO_Pin_0) && (GPIOx->MSKINTSR & GPIO_Pin_0))
    {
        GPIOx->INTCLR |= GPIO_Pin_0;
    }
    else if((GPIOx->RAWINTSR & GPIO_Pin_1) && (GPIOx->MSKINTSR & GPIO_Pin_1))
    {
        GPIOx->INTCLR |= GPIO_Pin_1;
    }
    else if((GPIOx->RAWINTSR & GPIO_Pin_2) && (GPIOx->MSKINTSR & GPIO_Pin_2))
    {
        GPIOx->INTCLR |= GPIO_Pin_2;
    }
    else if((GPIOx->RAWINTSR & GPIO_Pin_3) && (GPIOx->MSKINTSR & GPIO_Pin_3))
    {
        GPIOx->INTCLR |= GPIO_Pin_3;
    }
    else if((GPIOx->RAWINTSR & GPIO_Pin_4) && (GPIOx->MSKINTSR & GPIO_Pin_4))
    {
        GPIOx->INTCLR |= GPIO_Pin_4;
    }
    else if((GPIOx->RAWINTSR & GPIO_Pin_5) && (GPIOx->MSKINTSR & GPIO_Pin_5))
    {
        GPIOx->INTCLR |= GPIO_Pin_5;
    }
    else if((GPIOx->RAWINTSR & GPIO_Pin_6) && (GPIOx->MSKINTSR & GPIO_Pin_6))
    {
        GPIOx->INTCLR |= GPIO_Pin_6;
    }
    if((GPIOx->RAWINTSR & GPIO_Pin_7) && (GPIOx->MSKINTSR & GPIO_Pin_7))
    {
        GPIOx->INTCLR |= GPIO_Pin_7;
    }
}

/**
  * @brief  This function handles GPIOA Handler.
  * @param  None
  * @param  None
  * @retval None
  */
void GPIOA_IRQHandler(void)
{
    /*Set exti flag*/
    EXTI_IT_FLAG = 0x01;
    /*GPIOA interrupt treat*/
    GPIO_IRQHandler(GPIOA);
}

/**
  * @brief  This function handles GPIOB Handler.
  * @param  None
  * @param  None
  * @retval None
  */
void GPIOB_IRQHandler(void)
{
    /*Set exti flag*/
    EXTI_IT_FLAG = 0x01;
    /*GPIOB interrupt handle*/
    GPIO_IRQHandler(GPIOB);
}

/**
  * @brief  This function handles GPIOC Handler.
  * @param  None
  * @param  None
  * @retval None
  */
void GPIOC_IRQHandler(void)
{
    /*Set exti flag*/
    EXTI_IT_FLAG = 0x01;
    /*GPIOC interrupt handle*/
    GPIO_IRQHandler(GPIOC);
}

/**
  * @brief  This function handles GPIOD Handler.
  * @param  None
  * @param  None
  * @retval None
  */
void GPIOD_IRQHandler(void)
{
    /*Set exti flag*/
    EXTI_IT_FLAG = 0x01;
    /*GPIOD interrupt handle*/
    GPIO_IRQHandler(GPIOD);
}

/// ????????????
void Enter_DeepSleep(void)
{
  SCB->SCR |= 0x04;   
  __WFI();
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

