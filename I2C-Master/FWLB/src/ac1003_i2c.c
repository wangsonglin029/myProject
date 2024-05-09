/**
  ******************************************************************************
  * @file    ac1003_i2c.c
  * @author  mcu Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file provides all the I2C firmware functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_i2c.h"
#include "ac1003_rcc.h"




/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  None
	* @param  None
  * @retval None
  */
void I2C_DeInit(void)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* Enable I2C reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_I2CRST, ENABLE);
    /* Release I2C from reset state */
    RCC_PeriphResetCmd(RCC, RCC_APBPeriph_I2CRST, DISABLE);
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified
  *         parameters in the I2C_InitStruct.
  * @param  I2Cx: select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_CLOCK_SPEED(I2C_InitStruct->I2C_ClockSpeed));
    assert_param(IS_I2C_MODE(I2C_InitStruct->I2C_Mode));
    assert_param(IS_I2C_OWN_ADDRESS(I2C_InitStruct->I2C_OwnAddress));
    assert_param(IS_I2C_ACK_STATE(I2C_InitStruct->I2C_Ack));

    /*----- I2Cx CR Configuration -------*/
    tmpreg = 0;

    /* I2C speed calculate */
    tmpreg = RCC_GetPCLKFreq(RCC) / 1000;
    tmpreg = (uint32_t)((tmpreg - ((I2C_InitStruct->I2C_ClockSpeed / 1000) << 3)) / ((I2C_InitStruct->I2C_ClockSpeed / 1000) << 3));


    /* Write to I2Cx CCR */
    I2Cx->BAUDCR = tmpreg & 0xFF;
    
    /* I2C的波特率最低限制在 20K */
    if(I2C_InitStruct->I2C_ClockSpeed < 200000)
        I2Cx->CR &= 0xfe;
    else
        I2Cx->CR |= 0x01;


    /*---------------------------- I2Cx CR1 Configuration ------------------------*/
    /* Get the I2Cx CR1 value */
    tmpreg = I2Cx->CR;

    /* Set ACK bit according to I2C_Ack value */
    tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | \
                         (uint32_t)I2C_InitStruct->I2C_Ack);
    /* Write to I2Cx CR1 */
    I2Cx->CR = tmpreg;

    /*---------------------------- I2Cx OAR1 Configuration -----------------------*/
    /* Slave set self address */
    if((uint32_t)I2C_InitStruct->I2C_Mode == I2C_Mode_Slave)
        I2Cx->ADDR = I2C_InitStruct->I2C_OwnAddress | \
                     I2C_InitStruct->I2C_BroadcastAddress_Response;
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure
            which will be initialized.
  * @param  None
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* initialize the I2C_ClockSpeed member */
    I2C_InitStruct->I2C_ClockSpeed = 100000;
    /* Initialize the I2C_Mode member */
    I2C_InitStruct->I2C_Mode = I2C_Mode_Slave;
    /* Initialize the I2C_OwnAddress1 member */
    I2C_InitStruct->I2C_OwnAddress = 0;
    /* Initialize the I2C_Ack member */
    I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
    /* Initialize the I2C_AcknowledgedAddress member */
    I2C_InitStruct->I2C_BroadcastAddress_Response = 0x01;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->CR  |= CR_ENS_Set;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->CR  &= ~CR_ENS_Set;
    }
}
/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_MasterSendCmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->TIMRUN |= I2C_TMRUN_TME_Set;
        I2Cx->CR |= CR_STA_Set;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->TIMRUN &= I2C_TMRUN_TME_Reset;
        I2Cx->CR  &= CR_STA_Set;
    }
}

/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx:select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTART(I2C_TypeDef * I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CR |= CR_STA_Set;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CR &=  CR_STA_Reset;
    }
}

/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /* Generate a STOP condition */
        I2Cx->CR |= CR_STO_Set;
    }
    else
    {
        /* Disable the STOP condition generation */
        I2Cx->CR &= CR_STO_Reset;
    }
}

/**
  * @brief  Enables or disables the specified I2C acknowledge feature.
  * @param  I2Cx: select the I2C peripheral.
  * @param  NewState: new state of the I2C Acknowledgement.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None.
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    if (NewState != DISABLE)
    {
        /*Enable the acknowledgement */
        I2Cx->CR |= CR_AA_Set;
    }
    else
    {
        /*Disable the acknowledgement */
        I2Cx->CR &= CR_AA_Reset;
    }
}

/**
  * @brief  Configures the specified I2C own address.
  * @param  I2Cx: select the I2C peripheral.
  * @param  Address: specifies the 7bit I2C own address2.
  * @retval None.
  */
void I2C_OwnAddressConfig(I2C_TypeDef* I2Cx, uint8_t Address)
{
    uint32_t tmpreg = 0;

    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));

    /* Get the old register value */
    tmpreg = I2Cx->ADDR;

    /* Reset I2Cx Own address2 bit [7:1] */
    tmpreg &= I2C_ADDR_Reset;

    /* Set I2Cx Own address2 */
    tmpreg |= (uint32_t)((uint32_t)Address & (uint32_t)0x000000FE);

    /* Store the new register value */
    I2Cx->ADDR = tmpreg;
}



/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Write in the DR register the data to be sent */
    I2Cx->DATA = Data;
}

/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: select the I2C peripheral.
  * @param  None
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    /* Return the data in the DR register */
    return (uint8_t)I2Cx->DATA;
}

/**
  * @brief  Transmits the address byte to select the slave device.
  * @param  I2Cx: select the I2C peripheral.
  * @param  Address: specifies the slave address which will be transmitted
  * @param  I2C_Direction: specifies whether the I2C device will be a
  *   Transmitter or a Receiver. This parameter can be one of the following values
  *     @arg I2C_Direction_Transmitter: Transmitter mode
  *     @arg I2C_Direction_Receiver: Receiver mode
  * @retval None.
  */
void I2C_Send7bitAddress(I2C_TypeDef* I2Cx, \
                         uint8_t Address, \
                         uint8_t I2C_Direction)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_I2C_DIRECTION(I2C_Direction));
    /* Test on the direction to set/reset the read/write bit */
    if (I2C_Direction != I2C_Direction_Transmitter)
    {
        /* Set the address bit0 for read */
        Address |= I2C_ADDR_Set;
    }
    else
    {
        /* Reset the address bit0 for write */
        Address &= I2C_ADDR_Reset;
    }
    /* Send the address */
    I2Cx->DATA = Address;
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx:   select the I2C peripheral.
  * @param  NewState: new state of the specified I2C interrupts.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_I2C_ALL_PERIPH(I2Cx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->CR |= I2C_IT_ENABLE;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->CR &= (uint32_t)~I2C_IT_ENABLE;
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

/******************* (C) COPYRIGHT 2018 AC1003 *****END OF FILE****/

