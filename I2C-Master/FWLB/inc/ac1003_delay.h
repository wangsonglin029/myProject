#ifndef __AC1003_DELAY_H
#define __AC1003_DELAY_H			   
	  
/**
  ******************************************************************************
  * @file    ac1003_delay.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    09-17-2019
  * @brief   This file contains all the functions prototypes for the delay firmware 
  *          library.
  ******************************************************************************
  */
  
#include "ac1003.h"
#include "ac1003_conf.h"
////////////////////////////////////////////////////////////////////////////////// 	 
void delay_init(uint32_t SYSCLK);
void delay_ms(uint16_t nms);
void delay_us(uint32_t nus);

#endif





























