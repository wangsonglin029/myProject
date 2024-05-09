/**
  ************************************************************************
  * @file    test_iwdt.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file contains all the functions prototypes for the iwdt 
  ************************************************************************
  */

#ifndef __TEST_WWDG_H
#define	__TEST_WWDG_H

/* Includes --------------------------*/ 
#include "ac1003_iwdt.h"
#include "misc.h"


/****************************************
* IWDG 向下计数
* IWDG时间计算： 1 / (LIRC) * (IWDG_LOAD)
*	如例程配置：1 / (38.4K) * 0x5DC00 = 10s
*****************************************/


/* define parameters --------------------------*/ 
#define  DEBUG_IWDGx          IWDG

/*Config IWDG MODE*/
#define  DEBUG_IWDG_MODE      COMMAND_WDT_INT //中断模式
//#define  DEBUG_IWDG_MODE      COMMAND_WDT_RESET //复位模式

/*Enable/Disable IWDG Mask function*/
#define  DEBUG_IWDG_MASK      DISABLE 		//INT: DISABLE  RESET: ENABLE

//iwdt 使用LIRC，如果38.4K，(38400*10)0x5DC00为10s
//							 如果32.768K，(32768*10)=0x50000为10s
// #define  DEBUG_IWDG_LOAD      0x50000			
#define  DEBUG_IWDG_LOAD         0x9600	

/**define debug iwdg IRQ*/
#define  DEBUG_IWDG_IRQ                IWDG_IRQn
#define  DEBUG_IWDG_IRQHandler         IWDG_IRQHandler
                                       



/*define function-------------------------*/
void IWDG_Config(void);
void IWDG_Feed(void);

#endif /* __BSP_WWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT To AC1003 *****END OF FILE****/
