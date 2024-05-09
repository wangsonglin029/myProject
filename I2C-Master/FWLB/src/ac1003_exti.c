/**
  *****************************************************************************
  * @file    ac1003_exti.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file provides all the EXTI firmware functions.
  *****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_exti.h"
#include "ac1003_rcc.h"
#include "misc.h"

/**
  * @brief  Selects the GPIO pin used as EXTI Line.
  * @param  GPIOx: selects the GPIO port to be used as source for EXTI lines.
  *         This parameter can be  GPIOx where x can be (A..D).
  * @param  GPIO_IRQ_InitStructure: pointer to a GPIO_IRQ_InitTypeDef structure which will
  *         be initialized.
	* @param  GPIO_Pin: specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_EXTILineConfig(GPIO_TypeDef * GPIOx, \
                         GPIO_IRQ_InitTypeDef* GPIO_IRQ_InitStructure, \
                         uint8_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));
    assert_param(IS_FUNCTIONAL_STATE(GPIO_InitStructure->GPIO_IRQPin_Enable));

    /*!<Specifies the speed for the selected pins*/
    if(GPIO_IRQ_InitStructure->GPIO_IRQ_Pin_Type)
        GPIOx->INTTYPCR |= GPIO_Pin;
    else
        GPIOx->INTTYPCR &= ~GPIO_Pin;

    /*!<Specifies the operating output type for the selected pins*/
    if(GPIO_IRQ_InitStructure->GPIO_IRQ_Pin_Polarity)
        GPIOx->INTPOLCR |= GPIO_Pin;
    else
        GPIOx->INTPOLCR &= ~GPIO_Pin;

    /*<Specifies the operating Pull-up/Pull down for the selected pins*/
    if(GPIO_IRQ_InitStructure->GPIO_IRQ_Pin_Edge)
        GPIOx->INTANY |= GPIO_Pin;
    else
        GPIOx->INTANY &= ~GPIO_Pin;

    /*<Specifies the operating mode for the selected pins*/
    if(GPIO_IRQ_InitStructure->GPIO_IRQ_Pin_Clear)
        GPIOx->INTCLR |= GPIO_Pin;
    else
        GPIOx->INTCLR &= ~GPIO_Pin;

    /*<Specifies the GPIO pins to be configured*/
    if(GPIO_IRQ_InitStructure->GPIO_IRQ_Pin_Enable)
        GPIOx->INTEN |= GPIO_Pin;
    else
        GPIOx->INTEN &= ~GPIO_Pin;
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



