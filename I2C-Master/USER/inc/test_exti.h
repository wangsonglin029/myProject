/*
  *************************************************************
  * @file    test_exit.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file provides gpio exit functions.             
  **************************************************************
  */
#ifndef __EXTI_H
#define	__EXTI_H

/* Includes ------------------------*/
#include "ac1003_gpio.h"
#include "ac1003.h"
#include "ac1003_conf.h"
#include "ac1003_exti.h"



/*define exit GPIO pin k1*/
#define KEY1_IRQ_Pin_Enable     ENABLE
#define KEY1_IRQ_Pin_Type       ENABLE
#define KEY1_IRQ_Pin_Polarity   ENABLE
#define KEY1_IRQ_Pin_Edge       ENABLE
#define KEY1_IRQ_Pin_Clear      ENABLE
	
#define KEY1_INT_GPIO_PORT         GPIOC
#define KEY1_INT_GPIO_PIN          GPIO_Pin_3
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource3
#define KEY1_INT_EXTI_IRQ          GPIOC_IRQn
#define KEY1_IRQHandler            GPIOC_IRQHandler

/*define exit GPIO pin k2*/
#define KEY2_IRQ_Pin_Enable     ENABLE;
#define KEY2_IRQ_Pin_Type       DISABLE;
#define KEY2_IRQ_Pin_Polarity   DISABLE;
#define KEY2_IRQ_Pin_Edge       DISABLE;
#define KEY2_IRQ_Pin_Clear      ENABLE;

#define KEY2_INT_GPIO_PORT         GPIOC
#define KEY2_INT_GPIO_PIN          GPIO_Pin_6
#define KEY2_INT_EXTI_PINSOURCE    GPIO_PinSource6
#define KEY2_INT_EXTI_IRQ          GPIOC_IRQn
#define KEY2_IRQHandler            GPIOC_IRQHandler

/*define exit GPIO pin k3*/
#define KEY3_IRQ_Pin_Enable     ENABLE;
#define KEY3_IRQ_Pin_Type       DISABLE; //1:��ƽ����            0:���ش���
#define KEY3_IRQ_Pin_Polarity   DISABLE;  //1:�ߵ�ƽ�������ش���  0:�͵�ƽ���½��ش���
#define KEY3_IRQ_Pin_Edge       DISABLE; //1:����/�½��ض�����   0:�жϴ�����PxVALn����
#define KEY3_IRQ_Pin_Clear      ENABLE;

#define KEY3_INT_GPIO_PORT         GPIOC
#define KEY3_INT_GPIO_PIN          GPIO_Pin_7
#define KEY3_INT_EXTI_PINSOURCE    GPIO_PinSource7
#define KEY3_INT_EXTI_IRQ          GPIOC_IRQn
#define KEY3_IRQHandler            GPIOC_IRQHandler

/*define exit GPIO pin k4*/
#define KEY4_IRQ_Pin_Enable     ENABLE;
#define KEY4_IRQ_Pin_Type       DISABLE;
#define KEY4_IRQ_Pin_Polarity   DISABLE;
#define KEY4_IRQ_Pin_Edge       DISABLE;
#define KEY4_IRQ_Pin_Clear      ENABLE;

#define KEY4_INT_GPIO_PORT         GPIOD
#define KEY4_INT_GPIO_PIN          GPIO_Pin_2
#define KEY4_INT_EXTI_PINSOURCE    GPIO_PinSource1
#define KEY4_INT_EXTI_IRQ          GPIOD_IRQn
#define KEY4_IRQHandler            GPIOD_IRQHandler


/* define------------------------*/
void EXTI_Key_Config(void);

#endif /* __EXTI_H */

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


