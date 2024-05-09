/**
 ******************************************************************************
 * @file    ac1003_gpio.c
 * @author  MCU Application Team
 * @version V0.0.0
 * @date    18-JULY-2018
 * @brief   This file provides all the GPIO firmware functions.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_gpio.h"
#include "ac1003_rcc.h"

/**
  * @brief  Deinitializes the GPIOx peripheral registers
	*         to their default reset values.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
	* @param  None
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef * GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    if (GPIOx == GPIOA)
    {
        /*Enable GPIOA Peripheral Reset*/
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOARST, ENABLE);
        /*Disable GPIOA Peripheral Reset*/
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOARST, DISABLE);
    }
    else if (GPIOx == GPIOB)
    {
        /*Enable GPIOB Peripheral Reset*/
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOBRST, ENABLE);
        /*Disable GPIOB Peripheral Reset*/
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOBRST, DISABLE);
    }
    else if (GPIOx == GPIOC)
    {
        /*Enable GPIOC Peripheral Reset*/
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOCRST, ENABLE);
        /*Disable GPIOC Peripheral Reset*/
        RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIOCRST, DISABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            /*Enable GPIOD Peripheral Reset*/
            RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIODRST, ENABLE);
            /*Disable GPIOD  Peripheral Reset*/
            RCC_PeriphResetCmd(RCC, RCC_AHBPeriph_GPIODRST, DISABLE);
        }
    }
}

/**
  * @brief  Deinitializes the Alternate Functions registers
  *         to their default reset values.
  * @param  None
  * @param  None
  * @retval None
  */
void GPIO_AFIODeInit(void)
{
    GPIOA->AFR = (uint32_t)0x00000000;
    GPIOB->AFR = (uint32_t)0x00000000;
    GPIOC->AFR = (uint32_t)0x00000000;
    GPIOD->AFR = (uint32_t)0x00000000;
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that
  *         contains the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef * GPIO_InitStruct)
{
    uint32_t pinpos = 0x00, pos = 0x00, currentpin = 0x00;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin));
    assert_param(IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode));
    assert_param(IS_GPIO_PUPD(GPIO_InitStruct->GPIO_PuPd));

    /* ------------------------- Configure the port pins ---------------- */
    /*-- GPIO Mode Configuration --*/
    for (pinpos = 0x00; pinpos < 0x08; pinpos++)
    {
        pos = ((uint32_t)0x01) << pinpos;
        /* Get the port pins position */
        currentpin = (GPIO_InitStruct->GPIO_Pin) & pos;

        if (currentpin == pos)
        {
            GPIOx->AFR  &= ~(GPIO_MODER_MODER0 << (pinpos * 4));
            if ((GPIO_InitStruct->GPIO_Mode == GPIO_Mode_OUT) || (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_AF))
            {
                /*set gpio direction to output*/
                GPIOx->DIRCR &= ~(GPIO_PIN_OUT_MODE << (uint8_t)pinpos);
                GPIOx->DIRCR |= (GPIO_PIN_OUT_MODE << (uint8_t)pinpos);
                /*Output mode configuration*/
                GPIOx->OTYPER &= ~((GPIO_OTYPER_OT_0) << ((uint8_t)pinpos)) ;
                GPIOx->OTYPER |= (uint32_t)(((uint32_t)GPIO_InitStruct->GPIO_OType) << ((uint8_t)pinpos));
            }
            else {
                if(GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IN)
                {
                    /*set gpio direction to input*/
                    GPIOx->DIRCR &= ~(GPIO_PIN_OUT_MODE << (uint8_t)pinpos);
                }
            }
            /* Pull-up Pull down resistor configuration*/
            GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << ((uint16_t)pinpos * 2));
            GPIOx->PUPDR |= (((uint32_t)GPIO_InitStruct->GPIO_PuPd) << (pinpos * 2));
        }
    }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct : pointer to a GPIO_InitTypeDef structure which will
  *         be initialized.
  * @param  None
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    /*Reset GPIO init structure parameters values */
    GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_All;
    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct->GPIO_Speed = GPIO_Low_Speed;
    GPIO_InitStruct->GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct->GPIO_PuPd = GPIO_PuPd_NOPULL;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIOPin:  specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIOPin)
{
    uint8_t bitstatus = 0x00;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIOPin));

    /*Read GPIO_Pin_x(x can be 0...7)'s value of the bit*/
    if ((GPIOx->IDR & GPIOPin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    /*Return the value of GPIO_Pin_x's bit*/
    return bitstatus;
}

/**
  * @brief  Reads the specified GPIO input data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  None
  * @retval GPIO input data port value.
  */
uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /*Return the input value of GPIOx and x can be A..D*/
    return ((uint8_t)GPIOx->IDR);
}


/**
  * @brief  Enable the specified GPIO port DB of SYNC_EN.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  NewState: new state of the sync_en.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_DBSyncCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE)
    {
        /*Enable GPIOx DB function*/
        GPIOx->INDBEN |= GPIO_DIDB_SYNCEN;
    }
    else
    {
        /*Enable GPIOx DB function*/
        GPIOx->INDBEN &= ~GPIO_DIDB_SYNCEN;
    }
}

/**
  * @brief  Set the specified GPIOx peripheral pins DB function .
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  DBPin: GPIO_Pin_x to select the pin of GPIO peripheral.
  * @param  NewState: new state of DB function.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_DBPinSyncCmd(GPIO_TypeDef* GPIOx, \
                       uint32_t DBPin, \
                       FunctionalState NewState)
{
    /*Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIOPin));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE)
    {
        /*Enable Pin of DB*/
        GPIOx->INDBEN |= DBPin;
    }
    else
    {
        /*Disable Pin of DB*/
        GPIOx->INDBEN &= ~DBPin;
    }
}

/**
  * @brief  Open the specified GPIO port DB Clock enable.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  NewState: new state of DB CLock enable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void GPIO_DBClkCmd(GPIO_TypeDef* GPIOx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState != DISABLE)
    {
        /*Open the DB clock of GPIO_Pin_x*/
        GPIOx->DBCLKCR  |= GPIO_DBCLK_EN;
    }
    else
    {
        /*Close the DB clock of GPIO_Pin_x*/
        GPIOx->DBCLKCR  &= ~GPIO_DBCLK_EN;
    }
}
/**
  * @brief  Set the specified GPIO port DB Clock
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  DBClk: DB Clock of cycle .
  * @retval None.
  */
void GPIO_SetDBClk(GPIO_TypeDef* GPIOx, uint32_t DBClk)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx)) ;
    assert_param(IS_GPIO_DBCLK_CYCLE(DBClk));
    /*Set the specified GPIO port DB Clock */
    GPIOx->DBCLKCR  &= ~GPIO_DBCLK_CYCLEMASK;
    GPIOx->DBCLKCR  |= DBClk;
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIOPin:  specifies the port bit to read.
  *         This parameter can be GPIO_Pin_x where x can be (0..7).
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIOPin)
{
    uint8_t bitstatus = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIOPin));

    if ((( GPIOx->ODR) & GPIOPin) != (uint32_t)Bit_RESET)
    {
        bitstatus = (uint8_t)Bit_SET;
    }
    else
    {
        bitstatus = (uint8_t)Bit_RESET;
    }
    /*Return the bit value of port*/
    return bitstatus;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  None
  * @retval GPIO output data port value.
  */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /*Return the output value of data port*/
    return ((uint8_t) GPIOx->ODR);
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIOPin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIOPin)
{
    /*Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIOPin));

    /*Set the bit of port bit*/
    GPIOx->ODSET = GPIOPin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIOPin: specifies the port bits to be written.
  *         This parameter can be any combination of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIOPin)
{
    /*Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(GPIOPin));

    /*Clear the bit of port bit*/
    GPIOx->ODCLR = GPIOPin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  GPIOPin: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  BitValue: specifies the value to be written to the selected bit.
  *         This parameter can be one of the BitAction enum values:
  * @arg    Bit_RESET: to clear the port pin
  * @arg    Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, \
                   uint16_t GPIOPin, \
                   BitAction BitValue)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIOPin));
    assert_param(IS_GPIO_BIT_ACTION(BitValue));

    if (BitValue != Bit_RESET)
    {
        /*Set the bit of port bit*/
        GPIOx->ODSET = GPIOPin;
    }
    else
    {
        /*Clear the bit of port bit*/
        GPIOx->ODCLR = GPIOPin ;
    }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral.
  * @param  Value: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t Value)
{
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /*Set the value to the DO register of port*/
    GPIOx->ODR = Value;
}

/**
  * @brief  Enables or disables pu pd
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral
  * @param  GPIOPinSource: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  GPIOPupd: set the GPIO peripheral port pin Pu or Pd
  * @retval None
  */
void GPIO_PinPuPdCmd(GPIO_TypeDef* GPIOx, \
                     uint8_t GPIOPinSource, \
                     uint8_t GPIOPupd)
{
    /*Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIOPinSource));
    assert_param(IS_GPIO_PUPD(GPIOPupd));

    /*clear the bit of pin Pu or Pd*/
    GPIOx->PUPDR &= ~(GPIO_PuPd_ALL << (GPIOPinSource * 2));
    /*set the GPIO peripheral port pin Pu or Pd*/
    GPIOx->PUPDR |= (GPIOPupd << (GPIOPinSource * 2));
}

/**
  * @brief  Enables or disables DR
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral
	* @param  GPIOPinSource: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @param  NewState: new state of Port DRIVER enable.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_PortDRCmd(GPIO_TypeDef* GPIOx, \
                    uint8_t GPIOPinSource, \
                    FunctionalState NewState)
{
    /*Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIOPinSource));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if(NewState == DISABLE)
    {
        GPIOx->DRVCR |= ((uint32_t)0x01 << GPIOPinSource);
    }
    else
    {
        GPIOx->DRVCR &= ~((uint32_t)0x01 << GPIOPinSource);
    }
}


/**
  * @brief  Changes the mapping of the specified pin.
  * @param  GPIOx: where x can be (A..D) to select the GPIO peripheral
  * @param  GPIOAFR: new state of the port pin remapping.
  * @param  GPIOPinSource: specifies the port bit to be written.
  *         This parameter can be one of GPIO_Pin_x where x can be (0..7).
  * @retval None
  */
void GPIO_PinRemapConfig(GPIO_TypeDef* GPIOx, \
                         uint8_t GPIOAFR, \
                         uint8_t GPIOPinSource)
{
    uint32_t temp = 0x00, tmp = 0x00;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param( IS_GPIO_AFR(GPIOAFR));
    assert_param(IS_GPIO_PIN_SOURCE(GPIOPinSource));

    /*Changes the mapping of the specified pin*/
    temp = GPIOx->AFR & (~((uint32_t)0x0f << GPIOPinSource));
    tmp = temp | (GPIOAFR << (GPIOPinSource * 4));
    GPIOx->AFR  = tmp;
}

/**
  * @brief   Changes the mapping of the specified pin.
  * @param   GPIOx: where x can be (A..D) to select the GPIO peripheral
  * @param   GPIOPinSource: specifies the pin for the Alternate function.
  *          This parameter can be GPIO_PinSourcex where x can be (0..7).
  * @param   GPIOAF: selects the pin to used as Alternate function.
  *          This parameter can be can be (0..7,0x0F):
  * @retval  None
  */
void GPIO_PinAFConfig(GPIO_TypeDef* GPIOx, \
                      uint16_t GPIOPinSource, \
                      uint8_t GPIOAF)
{
    uint32_t temp = 0x00, tmp = 0x00;

    /*Check the parameters*/
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN_SOURCE(GPIO_PinSource));
    assert_param(IS_GPIO_AFR(GPIO_AF));

    temp = ((uint32_t)(GPIOAF) << ((uint32_t)((uint32_t)GPIOPinSource & (uint32_t)0x07) * 4)) ;
    GPIOx->AFR &= ~((uint32_t)0xF << ((uint32_t)((uint32_t)GPIOPinSource & (uint32_t)0x07) * 4)) ;
    tmp = (GPIOx->AFR ) | temp;
    GPIOx->AFR  = tmp;
}

/**
  * @}
  */
/******************* (C) COPYRIGHT 2018 Ascendchip *****END OF FILE****/

