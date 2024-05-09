/**
  ******************************************************************************
  * @file    test_adc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    13-July-2018
  * @brief   This file contains all the functions prototypes for the adc 
  ******************************************************************************
  */
#ifndef __ADC_H
#define	__ADC_H

/* Includes -----------------------------------*/
#include "ac1003_adc.h"
#include "ac1003_rcc.h"
#include "ac1003_gpio.h"
#include "ac1003_spi.h"
#include "ac1003_lpuart.h"
#include "ac1003_uart.h"
#include "misc.h"


#define ADC_SOFTWARECONV_ENABLE      ENABLE
#define ADC_SOFTWARECONV_CYCLE       12

/*Uart0 trigs to enable adc function  */
//#define ADC_EXITTRIE_SEL             0x01

/*Uart1 trigs to enable adc function  */
#define ADC_EXITTRIE_SEL             0x02


/*******define function***************/
void ADC_Mode_Config(void);
void ADC_NVIC_Config(void);


#endif /* __ADC_H */


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/******************* (C) COPYRIGHT 2020 AC1003 *****END OF FILE****/

