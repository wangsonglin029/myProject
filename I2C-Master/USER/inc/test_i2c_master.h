/**
  ************************************************************************
  * @file    test_i2c_ee.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file contains all the functions prototypes for the I2C 
  ************************************************************************
  */
#ifndef __AC1003_TEST_I2C_H
#define __AC1003_TEST_I2C_H

/* Includes -------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"
#include "ac1003_gpio.h"
#include "ac1003_i2c.h"
#include "misc.h"

#define CHIP_SIZE           2048    //2k bytes
#define PAGE_SIZE              8    //8  bytes
#define PAGE_NUMS            256    //256 pages
#define WRITE_CYCLE       100000    //Write cycle time 5ms (byte orpage)


//目标从机的设备地址，传送的时候 (0x1A << 1)
#define TARGET_ADDR       0x1A     //7bits:1010000


/*****************************/
#define      MASTER_IICx                            I2C
                                                   
//CS(NSS)     
#define      MASTER_IIC_SCK_PORT                    GPIOB
#define      MASTER_IIC_SCK_PIN                     GPIO_Pin_4
#define      MASTER_IIC_SCK_PIN_SOURCE              GPIO_PinSource4
                                                   
                                                   
//SDA                                       
#define      MASTER_IIC_SDA_PORT                    GPIOB
#define      MASTER_IIC_SDA_PIN                     GPIO_Pin_5
#define      MASTER_IIC_SDA_PIN_SOURCE              GPIO_PinSource5
                                                   
                                                   
                                                   
#define      MASTER_IIC_IRQ                         I2C_IRQn
#define      MASTER_IIC_IRQHandler                  I2C_IRQHandler
                                                   
                                                   
#define      MASTER_IIC_SCK_AF_VALUE                GPIO_AF_I2C_SCL_PB4
#define      MASTER_IIC_SDA_AF_VALUE                GPIO_AF_I2C_SDA_PB5
                                                   
                                                   
#define      MASTER_IIC_ACK                         I2C_Ack_Disable
#define      MASTER_IIC_CLOSKSPEED                  20000//í¨D??ù?è￡?<=1000000
#define      MASTER_IIC_MODE                        I2C_Mode_Master
#define      MASTER_IIC_BROADCASTADDRESS_RESPONE    0x00
#define      MASTER_IIC_OWNADDRESS                  0x50//I2C×÷?aslave?￡ê?μ??·



/**define functions**************************************/
void I2C_Master_Init(void);
void I2C_IRQHandler_MasterSend(void);
void I2C_IRQHandler_MasterRecive(void);
void I2C_Master_Receive(uint8_t regAddr , uint8_t *rData, uint8_t rSize);
void I2C_Master_Transmit(uint8_t regAddr ,uint8_t *wData, uint8_t size);
void I2C_Master_SendByte(uint8_t regAddr ,const uint8_t wData);

#endif

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


