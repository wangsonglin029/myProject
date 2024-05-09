/**
  ****************************************************************************
  * @file    ac1003_rtc.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    18-JULY-2018
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the Real-Time Clock (RTC) peripheral:
  *           + Initialization
  *           + Calendar (Time and Date) configuration
  *           + Alarms (Alarm A and Alarm B) configuration
  *           + WakeUp Timer configuration
  *           + 1HZ Output pin Configuration
  *****************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ac1003_rtc.h"
#include "ac1003_rcc.h"


/** @defgroup RTC_Private_Constants RTC Private Constants
  * @{
  */
#define RTC_READ_TIMEOUT					0x08U
#define RTC_TIMEOUT_VALUE					0X10000U


/**
  * @brief  Converts a 2 digit decimal to BCD format.
  * @param  Value: Byte to be converted.
	* @param  None
  * @retval Converted byte
  */
static uint8_t RTC_ByteToBcd2(uint8_t Value)
{
    uint8_t bcdhigh = 0;

    while (Value >= 10)
    {
        bcdhigh++;
        Value -= 10;
    }

    return  ((uint8_t)(bcdhigh << 4) | Value);
}

/**
  * @brief  Convert from 2 digit BCD to Binary.
  * @param  Value: BCD value to be converted.
  * @param  None
  * @retval Converted word
  */
static uint8_t RTC_Bcd2ToByte(uint8_t Value)
{
    uint8_t tmp = 0;
    tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
    return (tmp + (Value & (uint8_t)0x0F));
}


/**
  * @brief  Deinitializes the RTC registers to their default reset values.
  * @note   This function doesn't reset the RTC Clock source and RTC Backup Data
  *         registers.
  * @param  RTCx: selects the RTC peripheral
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are deinitialized
  *          - ERROR: RTC registers are not deinitialized
  */
ErrorStatus RTC_DeInit(void)
{
    __IO uint32_t wutcounter = 0x00;

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    {
        /* Reset all RTC CR register bits */
        RTC->CR        =   (uint32_t)0x00000000;
        RTC->CLKCR     =   (uint32_t)0x00000000;
        RTC->TIME      =   (uint32_t)0x00000000;
        RTC->DATE      =   (uint32_t)0x00000000;
        RTC->ALM1TIME  =   (uint32_t)0x00000000;
        RTC->ALM1DATE  =   (uint32_t)0x00000000;
        RTC->ALM2PRD   =   (uint32_t)0x00000000;
        RTC->CLK_TRIM  =   (uint32_t)0x00000000;
        RTC->INTCLR    =   (uint32_t)0x00000000;
        RTC->ISR      &=  ~(uint32_t)0x00000007;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);

    return SUCCESS;
}

/**
  * @brief  Initializes the RTC registers according to the specified parameters
  *         in RTC_InitStruct.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure that contains
  *         the configuration information for the RTC peripheral.
  * @note   The RTC Prescaler register is write protected and can be written in
  *         initialization mode only.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are initialized
  *          - ERROR: RTC registers are not initialized
  */
ErrorStatus RTC_Init(RTC_TypeDef *RTCx, RTC_InitTypeDef* RTC_InitStruct)
{

    /* Check the parameters */
    assert_param(IS_RTC_HOUR_FORMAT(RTC_InitStruct->RTC_HourFormat));
    assert_param(IS_RTC_ASYNCH_PREDIV(RTC_InitStruct->RTC_AsynchPrediv));


    /* Clear Flags Bits */
    RTC_WriteProtectionCmd(RTCx, DISABLE);
    RTCx->INTCLR = 0x00;
    RTCx->ISR = 0x00;

    if(RTC_InitStruct->RTC_ClkSelect == RTC_CLK_FHXT)
    {
        /* RTC clk F=Fhxt/(HXTDIV[9:0]),set HXTDIV */
        RTCx->CLKCR &= ~RTC_AsynchPrediv_mask;
        RTCx->CLKCR |= (uint32_t)(RTC_InitStruct->RTC_AsynchPrediv);
    }
    else
    {
        RTCx->CLKCR &= ~(RTC_CLK_FHXT);
    }

    RTCx->CLKCR &= ~RTC_ClkSelMask;
    RTCx->CLKCR |= (uint32_t)(RTC_InitStruct->RTC_ClkSelect);

    /* Enable the RTC clock output */
    RTCx->CLKCR |= (uint32_t)RTC_Clk_Enable;

    if(ERROR == RTC_EnterInitMode(RTCx))
    {
        return ERROR;
    }

    /* set hour format Bits */
    if(RTC_InitStruct->RTC_HourFormat != RTC_HourFormat_12)
        RTCx->CR |= RTC_HourFormat_24;
    else
        RTCx->CR &= ~RTC_HourFormat_24;

    RTCx->CLK_TRIM = 0x00;

    RTCx->CR |= RTC_Count_Enable;

    RTC_WriteProtectionCmd(RTCx, ENABLE);

    return SUCCESS;
}

/**
  * @brief  Fills each RTC_InitStruct member with its default value.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_InitStruct: pointer to a RTC_InitTypeDef structure which will be
  *         initialized.
  * @retval None
  */
void RTC_StructInit(RTC_TypeDef *RTCx, RTC_InitTypeDef* RTC_InitStruct)
{
    /* Initialize the RTC_HourFormat member */
    RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24;

    /* Initialize the RTC_AsynchPrediv member */
    RTC_InitStruct->RTC_AsynchPrediv = (uint32_t)0x3FF;

    /* Initialize the RTC_SynchPrediv member */
    RTC_InitStruct->RTC_ClkSelect = (uint32_t)RTC_CLK_LXT;
}

/**
  * @brief  Enables or disables the RTC registers write protection.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the write protection.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_WriteProtectionCmd(RTC_TypeDef *RTCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the write protection for RTC registers */
        RTCx->WPR = 0xFF;
    }
    else
    {
        /* Disable the write protection for RTC registers */
        RTCx->WPR = 0xCA;
        RTCx->WPR = 0x53;
    }
}

/**
  * @brief  Enters the RTC Initialization mode.
  * @note   The RTC Initialization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  RTCx: selects the RTC peripheral
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC is in Init mode
  *          - ERROR: RTC is not in Init mode
  */
ErrorStatus RTC_EnterInitMode(RTC_TypeDef *RTCx)
{
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status = ERROR;
    uint32_t initstatus = 0x00;

    /* Set the Initialization mode */
    RTCx->ISR  &= ~(uint32_t)RTC_ISR_WAIT;
    RTCx->ISR  |=  (uint32_t)RTC_ISR_WAIT;

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    do
    {
        initstatus = RTCx->ISR & RTC_ISR_WAITF;
        initcounter++;
    } while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x00));

    if (initcounter >= INITMODE_TIMEOUT)
    {
        status = ERROR;
    }
    else
    {
        status = SUCCESS;
    }

    return (status);
}

/**
  * @brief  Exits the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts
  *         counting after 4 RTCCLK cycles.
  * @note   The RTC Initialization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  RTCx: selects the RTC peripheral
  * @retval None
  */
ErrorStatus RTC_ExitInitMode(RTC_TypeDef *RTCx)
{
    __IO uint32_t initcounter = 0x00;
    ErrorStatus status = ERROR;
    uint32_t initstatus = 0x00;

    /* Exit Initialization mode */
    RTCx->ISR &= (uint32_t)~RTC_ISR_WAIT;

    /* Wait till RTC is in INIT state and if Time out is reached exit */
    do
    {
        initstatus = RTCx->ISR & RTC_ISR_WAITF;
        initcounter++;
    } while((initcounter != INITMODE_TIMEOUT) && (initstatus == 0x01));

    if (initcounter >= INITMODE_TIMEOUT)
    {
        status = ERROR;
    }
    else
    {
        status = SUCCESS;
    }

    return (status);
}

/**
  * @brief  Waits until the RTC Time and Date registers (RTC_TR and RTC_DR) are
  *         synchronized with RTC APB clock.
  * @note   The RTC Resynchronization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @note   To read the calendar through the shadow registers after Calendar
  *         initialization, calendar update or after wakeup from low power modes
  *         the software must first clear the RSF flag.
  *         The software must then wait until it is set again before reading
  *         the calendar, which means that the calendar registers have been
  *         correctly copied into the RTC_TR and RTC_DR shadow registers.
  * @param  RTCx: selects the RTC peripheral
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC registers are synchronised
  *          - ERROR: RTC registers are not synchronised
  */
ErrorStatus RTC_WaitForSynchro(RTC_TypeDef *RTCx)
{
    __IO uint32_t synchrocounter = 0;
    ErrorStatus status = ERROR;
    uint32_t synchrostatus = 0x00;

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Clear RSF flag */
    RTCx->ISR &= (uint32_t)RTC_RSF_MASK;

    /* Wait the registers to be synchronised */
    do
    {
        synchrostatus = RTCx->ISR & RTC_ISR_RSF;
        synchrocounter++;
    } while((synchrocounter != SYNCHRO_TIMEOUT) && (synchrostatus == 0x00));

    if ((RTCx->ISR & RTC_ISR_RSF) != RESET)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);

    return (status);
}
/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the digital calibration Output.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_RtcClkCmd(RTC_TypeDef *RTCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    if (NewState != DISABLE)
    {
        /* Enable the RTC clock output */
        RTCx->CLKCR |= (uint32_t)RTC_Clk_Enable;
    }
    else
    {
        /* Disable the RTC clock output */
        RTCx->CLKCR &= (uint32_t)~RTC_Clk_Enable;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}


/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTCClk: set the rtc clk parameter
  * @retval None
  */
void RTC_SelRtcClk(RTC_TypeDef *RTCx, uint32_t RTCClk)
{
    /* Check the parameters */
    assert_param(IS_RTC_CLK_SEL(RTCClk));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Enable the RTC clock output */
    RTCx->CLKCR  &= ~(uint32_t)RTC_ClkSelMask;
    RTCx->CLKCR  |= (uint32_t)RTCClk;
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}
/**
  * @brief  Enables or Disables the Bypass Shadow feature.
  * @note   When the Bypass Shadow is enabled the calendar value are taken
  *         directly from the Calendar counter.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the Bypass Shadow feature.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
*/
void RTC_BypassShadowCmd(RTC_TypeDef *RTCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    if (NewState != DISABLE)
    {
        /* Set the BYPSHAD bit */
        RTCx->CR |= (uint32_t)RTC_CR_BYPSHAD;
    }
    else
    {
        /* Reset the BYPSHAD bit */
        RTCx->CR &= (uint32_t)~RTC_CR_BYPSHAD;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}

/**
  * @brief  Set the RTC current time.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that contains
  *                        the time configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Time register is configured
  *          - ERROR: RTC Time register is not configured
  */
ErrorStatus RTC_SetTime(RTC_TypeDef *RTCx, \
                        uint32_t RTC_Format, \
                        RTC_TimeTypeDef* RTC_TimeStruct)
{
    uint32_t tmpreg = 0;
    ErrorStatus status = ERROR;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    if (RTC_Format == RTC_Format_BIN)
    {
        if ((RTCx->CR & RTC_HourFormat_24) == (uint32_t)RESET)
        {
            assert_param(IS_RTC_HOUR12(RTC_TimeStruct->RTC_Hours));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));

        }
        else
        {
            assert_param(IS_RTC_HOUR24(RTC_TimeStruct->RTC_Hours));
        }
        assert_param(IS_RTC_MINUTES(RTC_TimeStruct->RTC_Minutes));
        assert_param(IS_RTC_SECONDS(RTC_TimeStruct->RTC_Seconds));
    }
    else
    {
        if ((RTCx->CR & RTC_HourFormat_24) == (uint32_t)RESET)
        {
            assert_param(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours));
            assert_param(IS_RTC_HOUR12(tmpreg));
            assert_param(IS_RTC_H12(RTC_TimeStruct->RTC_H12));
        }
        else
        {
            assert_param(IS_RTC_HOUR24(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours)));
        }
        assert_param(IS_RTC_MINUTES(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes)));
        assert_param(IS_RTC_SECONDS(RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds)));
    }

    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
        tmpreg = (((uint32_t)(RTC_TimeStruct->RTC_WeekDay) << 24) |
                  ((uint32_t)(RTC_TimeStruct->RTC_Hours) << 16) | \
                  ((uint32_t)(RTC_TimeStruct->RTC_Minutes) << 8) | \
                  ((uint32_t)(RTC_TimeStruct->RTC_Seconds)) | \
                  ((uint32_t)(RTC_TimeStruct->RTC_H12) << 21));
    }
    else
    {
        tmpreg = (uint32_t)(((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_WeekDay) << 24) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Hours) << 16) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Minutes) << 8) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_Seconds)) | \
                            ((uint32_t)RTC_ByteToBcd2(RTC_TimeStruct->RTC_H12) << 21));
    }

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Set Initialization mode */
    if (RTC_EnterInitMode(RTC) == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Set the RTC_TR register */
        RTCx->TIME = (uint32_t)(tmpreg & RTC_TR_RESERVED_MASK);

        /* Exit Initialization mode */
        RTC_ExitInitMode(RTC);

        /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
        if ((RTCx->CR & RTC_CR_BYPSHAD) == RESET)
        {
            if(RTC_WaitForSynchro(RTC) == ERROR)
            {
                status = ERROR;
            }
            else
            {
                status = SUCCESS;
            }
        }
        else
        {
            status = SUCCESS;
        }
    }
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);

    return status;
}

/**
  * @brief  Fills each RTC_TimeStruct member with its default value
  *         (Time = 00h:00min:00sec).
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure which will be
  *         initialized.
  * @retval None
  */
void RTC_TimeStructInit(RTC_TypeDef *RTCx, RTC_TimeTypeDef* RTC_TimeStruct)
{
    /* Time = 00h:00min:00sec */
    RTC_TimeStruct->RTC_H12 = RTC_H12_AM;
    RTC_TimeStruct->RTC_Hours = 0;
    RTC_TimeStruct->RTC_Minutes = 0;
    RTC_TimeStruct->RTC_Seconds = 0;
    RTC_TimeStruct->RTC_WeekDay = 0;
}

/**
  * @brief  Get the RTC current Time.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_TimeStruct: pointer to a RTC_TimeTypeDef structure that will
  *                        contain the returned current time configuration.
  * @retval None
  */
ErrorStatus RTC_GetTime(RTC_TypeDef *RTCx, \
                        uint32_t RTC_Format, \
                        RTC_TimeTypeDef* RTC_TimeStruct)
{
    uint32_t tmpreg = 0;
    uint32_t time1_reg = 0, date1_reg = 0, time2_reg = 0, date2_reg = 0;
    uint32_t counter_times = 0;
    ErrorStatus  read_ok = ERROR;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    if(1 == (RTCx->CR & RTC_CR_BYPSHAD)) //BYPSHAD = 1
    {
        counter_times = RTC_READ_TIMEOUT;
        do
        {
            time1_reg = RTCx->TIME;
            date1_reg = RTCx->DATE;
            time2_reg = RTCx->TIME;
            date2_reg = RTCx->DATE;

            if((time1_reg == time2_reg) && (date1_reg == date2_reg))
                read_ok = SUCCESS;

        } while((read_ok != SUCCESS) && (counter_times-- > 0));

        if(read_ok != SUCCESS)
        {
            return ERROR;
        }
    }
    else        //BYPSHAD = 0
    {
        while( (RTC->ISR & RTC_ISR_RSF) != RTC_ISR_RSF);

        time1_reg = RTCx->TIME;
        date1_reg = RTCx->DATE;

        /* Disable the write protection for RTC registers */
        RTC_WriteProtectionCmd(RTC, DISABLE);
        RTCx->ISR &= ~(RTC_ISR_RSF);
        RTC_WriteProtectionCmd(RTCx, ENABLE);
    }


    /* Get the RTC_TR register */
    tmpreg = (uint32_t)(time1_reg & RTC_TR_RESERVED_MASK);

    if((RTCx->CR & RTC_HourFormat_24) == RTC_HourFormat_24)
    {
        RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & RTC_TR_HU_24) >> 16);
    } else {
        RTC_TimeStruct->RTC_Hours = (uint8_t)((tmpreg & RTC_TR_HU) >> 16);
    }
    /* Fill the structure fields with the read parameters */
    RTC_TimeStruct->RTC_WeekDay = (uint8_t)((tmpreg & RTC_TR_WEEKDAY) >> 24);
    RTC_TimeStruct->RTC_Minutes = (uint8_t)((tmpreg & RTC_TR_MNU) >> 8);
    RTC_TimeStruct->RTC_Seconds = (uint8_t)(tmpreg & RTC_TR_SU);
    RTC_TimeStruct->RTC_H12 = (uint8_t)((tmpreg & (RTC_TTME_H20PA)) >> 21);


    if (RTC_Format == RTC_Format_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_TimeStruct->RTC_WeekDay = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_WeekDay);
        RTC_TimeStruct->RTC_Hours = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Hours);
        RTC_TimeStruct->RTC_Minutes = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Minutes);
        RTC_TimeStruct->RTC_Seconds = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_Seconds);
        RTC_TimeStruct->RTC_H12 = (uint8_t)RTC_Bcd2ToByte(RTC_TimeStruct->RTC_H12);
    }

    return SUCCESS;
}



/**
  * @brief  Set the RTC current date.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the entered parameters.
  *          This parameter can be  one of the following values:
  *            @arg RTC_Format_BIN:  Binary data format
  *            @arg RTC_Format_BCD:  BCD data format
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure that contains
  *                         the date configuration information for the RTC.
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Date register is configured
  *          - ERROR: RTC Date register is not configured
  */
ErrorStatus RTC_SetDate(RTC_TypeDef *RTCx, \
                        uint32_t RTC_Format, \
                        RTC_DateTypeDef* RTC_DateStruct)
{
    uint32_t tmpreg = 0;
    ErrorStatus status = ERROR;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    if ((RTC_Format == RTC_Format_BIN) && ((RTC_DateStruct->RTC_Month & 0x10) == 0x10))
    {
        RTC_DateStruct->RTC_Month = (RTC_DateStruct->RTC_Month & (uint32_t)~(0x10)) + 0x0A;
    }
    if (RTC_Format == RTC_Format_BIN)
    {
        assert_param(IS_RTC_YEAR(RTC_DateStruct->RTC_Year));
        assert_param(IS_RTC_MONTH(RTC_DateStruct->RTC_Month));
        assert_param(IS_RTC_DATE(RTC_DateStruct->RTC_Date));
    }
    else
    {
        assert_param(IS_RTC_YEAR(RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year)));
        tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
        assert_param(IS_RTC_MONTH(tmpreg));
        tmpreg = RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
        assert_param(IS_RTC_DATE(tmpreg));
    }


    /* Check the input parameters format */
    if (RTC_Format != RTC_Format_BIN)
    {
        tmpreg = ((((uint32_t)RTC_DateStruct->RTC_Year) << 16) | \
                  ((uint32_t)RTC_DateStruct->RTC_Century << 15) | \
                  (((uint32_t)RTC_DateStruct->RTC_Month) << 8) | \
                  ((uint32_t)RTC_DateStruct->RTC_Date));
    }
    else
    {
        tmpreg = (((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Year) << 16) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Century) << 15) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Month) << 8) | \
                  ((uint32_t)RTC_ByteToBcd2(RTC_DateStruct->RTC_Date)));
    }

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Set Initialization mode */
    if (RTC_EnterInitMode(RTC) == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Set the RTC_DR register */
        RTCx->DATE  = (uint32_t)(tmpreg & RTC_DATE_RESERVED_MASK);
        /* Exit Initialization mode */
        RTC_ExitInitMode(RTC);

        /* If  RTC_CR_BYPSHAD bit = 0, wait for synchro else this check is not needed */
        if ((RTCx->CR & RTC_CR_BYPSHAD) == RESET)
        {
            if(RTC_WaitForSynchro(RTC) == ERROR)
            {
                status = ERROR;
            }
            else
            {
                status = SUCCESS;
            }
        }
        else
        {
            status = SUCCESS;
        }
    }
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);

    return status;
}

/**
  * @brief  Fills each RTC_DateStruct member with its default value
  *         (Monday, January 01 xx00).
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_DateStruct: pointer to a RTC_DateTypeDef structure which will be
  *         initialized.
  * @retval None
  */
void RTC_DateStructInit(RTC_TypeDef *RTCx, RTC_DateTypeDef* RTC_DateStruct)
{
    /* Monday, January 01 xx00 */
    RTC_DateStruct->RTC_Date = 1;
    RTC_DateStruct->RTC_Month = RTC_Month_January;
    RTC_DateStruct->RTC_Year = 0;
    RTC_DateStruct->RTC_Century = 0;
}

/**
  * @brief  Get the RTC current date.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param RTC_DateStruct: pointer to a RTC_DateTypeDef structure that will
  *                        contain the returned current date configuration.
  * @retval None
  */
ErrorStatus RTC_GetDate(RTC_TypeDef *RTCx, \
                        uint32_t RTC_Format, \
                        RTC_DateTypeDef* RTC_DateStruct)
{
    uint32_t tmpreg = 0;
    uint32_t time1_reg = 0, date1_reg = 0, time2_reg = 0, date2_reg = 0;
    uint32_t counter_times = 0;
    ErrorStatus  read_ok = ERROR;


    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    if(1 == (RTCx->CR & RTC_CR_BYPSHAD)) //BYPSHAD = 1
    {
        counter_times = RTC_READ_TIMEOUT;
        do
        {
            time1_reg = RTCx->TIME;
            date1_reg = RTCx->DATE;
            time2_reg = RTCx->TIME;
            date2_reg = RTCx->DATE;

            if((time1_reg == time2_reg) && (date1_reg == date2_reg))
                read_ok = SUCCESS;

        } while((read_ok != SUCCESS) && (counter_times-- > 0));

        if(read_ok != SUCCESS)
        {
            return ERROR;
        }
    }
    else        //BYPSHAD = 0
    {
        while( (RTC->ISR & RTC_ISR_RSF) != RTC_ISR_RSF);

        time1_reg = RTCx->TIME;
        date1_reg = RTCx->DATE;

        /* Disable the write protection for RTC registers */
        RTC_WriteProtectionCmd(RTC, DISABLE);
        RTCx->ISR &= ~(RTC_ISR_RSF);
        RTC_WriteProtectionCmd(RTCx, ENABLE);
    }

    /* Get the RTC_TR register */
    tmpreg = (uint32_t)(date1_reg & RTC_DATE_RESERVED_MASK);

    /* Fill the structure fields with the read parameters */
    RTC_DateStruct->RTC_Year = (uint8_t)((tmpreg &  RTC_DR_YU) >> 16);
    RTC_DateStruct->RTC_Century = (uint8_t)((tmpreg &  RTC_DR_CEN) >> 15);
    RTC_DateStruct->RTC_Month = (uint8_t)((tmpreg & RTC_DR_MU) >> 8);
    RTC_DateStruct->RTC_Date = (uint8_t)(tmpreg &   RTC_DR_DU);

    /* Check the input parameters format */
    if (RTC_Format == RTC_Format_BIN)
    {
        /* Convert the structure parameters to Binary format */
        RTC_DateStruct->RTC_Year = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Year);
        RTC_DateStruct->RTC_Month = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Month);
        RTC_DateStruct->RTC_Date = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Date);
        RTC_DateStruct->RTC_Century = (uint8_t)RTC_Bcd2ToByte(RTC_DateStruct->RTC_Century);
    }

    return SUCCESS;
}

/**
  * @brief  Set the specified RTC Alarm.
  * @param  RTCx: selects the RTC peripheral
  * @note   The Alarm register can only be written when the corresponding Alarm
  *         is disabled (Use the RTC_AlarmCmd(DISABLE)).
  * @param  RTC_Format: specifies the format of the returned parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_AlarmEableStruct: pointer to a RTC_AlarmTypeDef structure that
  *         contains the alarm configuration parameters.
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that
  *                          contains the alarm configuration parameters.
  * @retval None
  */
void RTC_SetAlarm1(RTC_TypeDef *RTCx, \
                   uint32_t RTC_Format, \
                   RTC_AlarmTypeEnableDef*RTC_AlarmEableStruct, \
                   RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    uint32_t tmpreg = 0;
    uint32_t tmpreg1 = 0;

    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);


    /*alarm hour set*/
    if(RTC_AlarmEableStruct->RTC_HourAlarmEable == ENABLE)
    {
        if ((RTCx->CR & RTC_HourFormat_24) == (uint32_t)RESET)
        {
            assert_param(IS_RTC_HOUR12(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
            assert_param(IS_RTC_H12(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12));
        }
        else
        {
            assert_param(IS_RTC_HOUR24(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours));
        }

        tmpreg1 |= RTC_AlarmHour_ENABLE;
        if (RTC_Format == RTC_Format_BIN) //bin data
        {
            tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours) << 16;
            tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12) << 21;
        } else {        //bcd data
            tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours << 16;
            tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 << 21;
        }

    } else {

        tmpreg1 &= ~RTC_AlarmHour_ENABLE;
    }

    /*alarm minuter set*/
    if(RTC_AlarmEableStruct->RTC_MinAlarmEable == ENABLE)
    {
        assert_param(IS_RTC_MINUTES(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes));

        tmpreg1 |= RTC_AlarmMin_ENABLE;

        if (RTC_Format == RTC_Format_BIN) //bin data
            tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes) << 8;
        else  //bcd data
            tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes << 8;

    } else {

        tmpreg1 &= ~RTC_AlarmMin_ENABLE;
    }

    /*alarm sec set*/
    if(RTC_AlarmEableStruct->RTC_SecAlarmEable == ENABLE)
    {
        assert_param(IS_RTC_SECONDS(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds));

        tmpreg1 |= RTC_AlarmSec_ENABLE;

        if (RTC_Format == RTC_Format_BIN)
            tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds);
        else
            tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds;

    } else {

        tmpreg1 &= ~RTC_AlarmSec_ENABLE;
    }

    /*alarm weekday set*/
    if(RTC_AlarmEableStruct->RTC_WeekAlarmEable == ENABLE)
    {
        assert_param(IS_RTC_ALARM_DATE_WEEKDAY_DATE(RTC_AlarmStruct->RTC_AlarmDateWeekDay));

        tmpreg1 |= RTC_AlarmWeek_ENABLE;

        if (RTC_Format == RTC_Format_BIN)
            tmpreg |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay) << 24;
        else
            tmpreg |= (uint32_t)RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay << 24;

    } else {

        tmpreg1 &= ~RTC_AlarmWeek_ENABLE;
    }

    /*alarm year set*/
    if(RTC_AlarmEableStruct->RTC_YearAlarmEable == ENABLE)
    {
        assert_param(IS_RTC_YEAR(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year));

        tmpreg1 |= RTC_AlarmYear_ENABLE;

        if (RTC_Format == RTC_Format_BIN)
        {
            tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year) << 16;
            tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Century) << 15;
        } else {
            tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Year << 16;
            tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Century << 15;
        }
    } else {

        tmpreg1 &= ~RTC_AlarmYear_ENABLE;
    }

    /*alarm month set*/
    if(RTC_AlarmEableStruct->RTC_MonthAlarmEable == ENABLE)
    {
        assert_param(IS_RTC_MONTH(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month));

        tmpreg1 |= RTC_AlarmMon_ENABLE;

        if (RTC_Format == RTC_Format_BIN)
        {
            tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month) << 8;
        }
        else
        {
            tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Month << 8;
        }

    } else {

        tmpreg1 &= ~RTC_AlarmMon_ENABLE;
    }

    /*alarm date set*/
    if(RTC_AlarmEableStruct->RTC_DateAlarmEable == ENABLE)
    {
        assert_param(IS_RTC_DATE(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date));

        tmpreg1 |= RTC_AlarmDay_ENABLE;

        if (RTC_Format == RTC_Format_BIN)
        {
            tmpreg1 |= (uint32_t)RTC_ByteToBcd2(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date);
        }
        else
            tmpreg1 |= (uint32_t)RTC_AlarmStruct->RTC_AlarmDate.RTC_Date;

    } else {

        tmpreg1 &= ~RTC_AlarmDay_ENABLE;
    }


    /*write register*/
    RTCx->ALM1TIME = tmpreg;
    RTCx->ALM1DATE = tmpreg1;
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}


/**
  * @brief  Set the specified RTC Alarm.
  * @param  RTCx: selects the RTC peripheral
  * @param  value: set the value of ALPR
  * @retval None
  */
void RTC_SetAlarm2(RTC_TypeDef *RTCx, uint32_t value)
{
    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);
    /*set the value to the ALPR*/
    RTCx->ALM2PRD = value;
    RTC_WriteProtectionCmd(RTC, ENABLE);
}

/**
  * @brief  Fills each RTC_AlarmStruct member with its default value
  *         (Time = 00h:00mn:00sec / Date = 1st day of the month/Mask =
  *         all fields are masked).
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_AlarmStruct: pointer to a @ref RTC_AlarmTypeDef structure which
  *         will be initialized.
  * @retval None
  */
void RTC_AlarmStructInit(RTC_TypeDef *RTCx, RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    /* Alarm Time Settings : Time = 00h:00mn:00sec */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_H12_AM;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = 0;
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = 0;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = 0;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = 0;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = 0;
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = 0;
}

/**
  * @brief  Get the RTC Alarm value and masks.
  * @param  RTC_Format: specifies the format of the output parameters.
  *          This parameter can be one of the following values:
  *            @arg RTC_Format_BIN: Binary data format
  *            @arg RTC_Format_BCD: BCD data format
  * @param  RTC_AlarmStruct: pointer to a RTC_AlarmTypeDef structure that will
  *                          contains the output alarm configuration values.
  * @retval None
  */
void RTC_GetAlarm1(RTC_TypeDef *RTCx, \
                   uint32_t RTC_Format, \
                   RTC_AlarmTypeDef* RTC_AlarmStruct)
{
    uint32_t tmpregtime = 0;
    uint32_t tmpregdate = 0;


    /* Check the parameters */
    assert_param(IS_RTC_FORMAT(RTC_Format));
    assert_param(IS_RTC_ALARM(RTC_Alarm));

    /* Get the RTC_ALRMxR register */

    tmpregtime = (uint32_t)(RTCx->ALM1TIME)&RTC_AlarmMask_time;
    tmpregdate = (uint32_t)(RTCx->ALM1DATE)&RTC_AlarmMask_date;

    /* Fill the structure with the read parameters */
    RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = (uint32_t)((tmpregtime & RTC_AlarmMask_PA) >> 21);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = (uint32_t)((tmpregtime & RTC_AlarmMask_Hours) >> 16);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = (uint32_t)((tmpregtime & RTC_AlarmMask_Minutes) >> 8);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = (uint32_t)(tmpregtime & RTC_AlarmMask_Seconds);
    RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay = (uint32_t)((tmpregtime & RTC_AlarmMask_Week) >> 24);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = (uint32_t)((tmpregdate & RTC_AlarmMask_Year) >> 16);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = (uint32_t)((tmpregdate & RTC_AlarmMask_ALCEN) >> 15);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = (uint32_t)((tmpregdate & RTC_AlarmMask_Mouth) >> 8);
    RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = (uint32_t)(tmpregdate & RTC_AlarmMask_Day);

    /*BIN TO BCD */
    if (RTC_Format == RTC_Format_BIN)
    {
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Hours);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_H12 = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_H12);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Minutes);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_Seconds);
        RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmTime.RTC_WeekDay);
        RTC_AlarmStruct->RTC_AlarmDate.RTC_Year = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Year);
        RTC_AlarmStruct->RTC_AlarmDate.RTC_Century = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Century);
        RTC_AlarmStruct->RTC_AlarmDate.RTC_Month = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Month);
        RTC_AlarmStruct->RTC_AlarmDate.RTC_Date = RTC_Bcd2ToByte(RTC_AlarmStruct->RTC_AlarmDate.RTC_Date);
    }
}

/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  RTCx: selects the RTC peripheral
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Alarm is enabled/disabled
  *          - ERROR: RTC Alarm is not enabled/disabled
  */
uint8_t RTC_GetAlarm2(RTC_TypeDef *RTCx)
{
    return  (uint8_t)(RTCx->ALM2PRD);
}
/**
  * @brief  Enables or disables the specified RTC Alarm.
  * @param  RTC_Alarm: specifies the alarm to be configured.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_Alarm_A: to select Alarm A
  *            @arg RTC_Alarm_B: to select Alarm B
  * @param  NewState: new state of the specified alarm.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlarmCmd(RTC_TypeDef *RTCx, \
                  uint32_t RTC_Alarm, \
                  FunctionalState NewState)
{
    __IO uint32_t alarmcounter = 0x00;
    /* Check the parameters */
    assert_param(IS_RTC_GET_IT(RTC_Alarm));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Configure the Alarm state */
    if (NewState != DISABLE)
    {
        RTCx->CR |= (uint32_t)RTC_Alarm;

    } else {
        RTCx->CR &= (uint32_t)~RTC_Alarm;



    }
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);


}

/**
  * @brief  Configures the Coarse calibration parameters.
  * @param  RTC_CalibSign: specifies the sign of the coarse calibration value.
  *          This parameter can be  one of the following values:
  *            @arg RTC_CalibSign_Positive: The value sign is positive
  *            @arg RTC_CalibSign_Negative: The value sign is negative
  * @param  Value: value of coarse calibration expressed in ppm (coded on 5 bits).
  *
  * @note   This Calibration value should be between 0 and 63 when using negative
  *         sign with a 2-ppm step.
  *
  * @note   This Calibration value should be between 0 and 126 when using positive
  *         sign with a 4-ppm step.
  *
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: RTC Coarse calibration are initialized
  *          - ERROR: RTC Coarse calibration are not initialized
  */
ErrorStatus RTC_CoarseCalibConfig(RTC_TypeDef *RTCx, \
                                  uint32_t RTC_CalibSign, \
                                  uint32_t Value)
{
    ErrorStatus status = ERROR;

    /* Check the parameters */
    assert_param(IS_RTC_CALIB_SIGN(RTC_CalibSign));
    assert_param(IS_RTC_CALIB_VALUE(Value));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Set Initialization mode */
    if (RTC_EnterInitMode(RTC) == ERROR)
    {
        status = ERROR;
    }
    else
    {
        /* Set the coarse calibration value */
        RTCx->CLK_TRIM = (uint32_t)(RTC_CalibSign | Value);
        /* Exit Initialization mode */
        RTC_ExitInitMode(RTCx);

        status = SUCCESS;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);

    return status;
}



/**
  * @brief  Enables or disables the RTC clock to be output through the relative pin.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CalibOutputCmd(RTC_TypeDef *RTCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    if (NewState != DISABLE)
    {
        /* Enable the RTC clock output */
        RTCx->CR |= (uint32_t)RTC_CalibOutput_1Hz;
    }
    else
    {
        /* Disable the RTC clock output */
        RTCx->CR &= (uint32_t)~RTC_CalibOutput_1Hz;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}


/**
  * @brief  Enables or disables the RTC Count.
  * @param  RTCx: selects the RTC peripheral
  * @param  NewState: new state of the digital calibration Output.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_CountCmd(RTC_TypeDef *RTCx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    if (NewState != DISABLE)
    {
        /* Enable the RTC clock output */
        RTCx->CR |= (uint32_t)RTC_Count_Enable;
    }
    else
    {
        /* Disable the RTC clock output */
        RTCx->CR &= (uint32_t)~RTC_Count_Enable;
    }

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}




/**
  * @brief  Configures the Smooth Calibration Settings.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_SmoothCalibPeriod : Select the Smooth Calibration Period.
  *   This parameter can be can be one of the following values:
  *     @arg RTC_SmoothCalibPeriod_32sec : The smooth calibration period is 32s.
  *     @arg RTC_SmoothCalibPeriod_16sec : The smooth calibration period is 16s.
  *     @arg RTC_SmoothCalibPeriod_8sec  : The smooth calibartion period is 8s.
  * @param  RTC_SmoothCalibTrmingValue: Set the value to TRIM
  * @retval None
  */
void RTC_SmoothCalibConfig(RTC_TypeDef *RTCx, \
                           uint32_t RTC_SmoothCalibPeriod, \
                           uint32_t RTC_SmoothCalibTrmingValue)
{
    /* Check the parameters */
    assert_param(IS_RTC_SMOOTH_CALIB_PERIOD(RTC_SmoothCalibPeriod));
    assert_param(IS_RTC_SMOOTH_CALIB_TRMINGVALUE(RTC_SmoothCalibTrmingValue));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Configure the Smooth calibration settings */
    RTCx->CLK_TRIM = (uint32_t)((uint32_t)RTC_SmoothCalibPeriod | (uint32_t)RTC_SmoothCalibTrmingValue);

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}

/**@brief   Interrupts and flags management functions
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_IT: specifies the rtc interrupt parameter to config.
  * @param  NewState: new state of the digital calibration Output.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlprITConfig(RTC_TypeDef *RTCx, \
                      uint32_t RTC_IT, \
                      FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_CONFIG_IT(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    if (NewState != DISABLE)
    {
        /* Configure the Interrupts in the RTC_CR register */
        RTCx->CR |= (uint32_t)RTC_IT;

    }
    else
    {
        /* Configure the Interrupts in the RTC_CR register */
        RTCx->CR &= ~(uint32_t)RTC_IT;
    }
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}

/**
  * @brief  Alm and flags management functions
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_IT: specifies the RTC interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_TS:  Time Stamp interrupt mask
  *            @arg RTC_IT_WUT:  WakeUp Timer interrupt mask
  *            @arg RTC_IT_ALRB:  Alarm B interrupt mask
  *            @arg RTC_IT_ALRA:  Alarm A interrupt mask
  *            @arg RTC_IT_TAMP: Tamper event interrupt mask
  * @param  NewState: new state of the specified RTC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RTC_AlmITConfig(RTC_TypeDef *RTCx, \
                     uint32_t RTC_IT, \
                     FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_RTC_CONFIG_IT(RTC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    if (NewState != DISABLE)
    {
        /* Configure the Interrupts in the RTC_CR register */
        RTCx->CR |= (uint32_t)RTC_IT;

    }
    else
    {
        /* Configure the Interrupts in the RTC_CR register */
        RTCx->CR &= ~(uint32_t)RTC_IT;
    }
    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}


/**
  * @brief  Checks whether the specified RTC flag is set or not.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_FLAG: specifies the flag to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_IT_ALM1: ALM1 event flag.
  *            @arg RTC_IT_ALM2: ALM2 event flag.
  * @retval The new state of RTC_FLAG (SET or RESET).
  */
FlagStatus RTC_GetFlagStatus(RTC_TypeDef *RTCx, uint32_t RTC_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RTC_GET_FLAG(RTC_FLAG));

    /* Return the status of the flag */
    if ((RTCx->ISR & RTC_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Clears the RTC's pending flags.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_FLAG: specifies the RTC flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_ALM1: ALM1 event flag.
  *            @arg RTC_IT_ALM2: ALM2 event flag.
  * @retval None
  */
void RTC_ClearFlag(RTC_TypeDef *RTCx, uint32_t RTC_FLAG)
{
    /* Check the parameters */
    assert_param(IS_RTC_CLEAR_FLAG(RTC_FLAG));

    /* Disable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, DISABLE);

    /* Clear the Flags in the RTC_ISR register */
    RTCx->INTCLR  =  RTC_FLAG ;

    /* Enable the write protection for RTC registers */
    RTC_WriteProtectionCmd(RTC, ENABLE);
}

/**
  * @brief  Checks whether the specified RTC interrupt has occurred or not.
  * @param  RTCx: selects the RTC peripheral
  * @param  RTC_IT: specifies the RTC interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg RTC_IT_ALM1: ALM1 event flag.
  *            @arg RTC_IT_ALM2: ALM2 event flag.
  * @retval The new state of RTC_IT (SET or RESET).
  */
ITStatus RTC_GetITStatus(RTC_TypeDef *RTCx, uint32_t RTC_IT)
{
    ITStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_RTC_GET_IT(RTC_IT));

    /* Get the status of the Interrupt */
    if (RTCx->ISR & RTC_IT)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}



/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT AC1003 *****END OF FILE****/
