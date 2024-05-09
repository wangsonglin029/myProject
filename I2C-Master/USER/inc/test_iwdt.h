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
* IWDG ���¼���
* IWDGʱ����㣺 1 / (LIRC) * (IWDG_LOAD)
*	���������ã�1 / (38.4K) * 0x5DC00 = 10s
*****************************************/


/* define parameters --------------------------*/ 
#define  DEBUG_IWDGx          IWDG

/*Config IWDG MODE*/
#define  DEBUG_IWDG_MODE      COMMAND_WDT_INT //�ж�ģʽ
//#define  DEBUG_IWDG_MODE      COMMAND_WDT_RESET //��λģʽ

/*Enable/Disable IWDG Mask function*/
#define  DEBUG_IWDG_MASK      DISABLE 		//INT: DISABLE  RESET: ENABLE

//iwdt ʹ��LIRC�����38.4K��(38400*10)0x5DC00Ϊ10s
//							 ���32.768K��(32768*10)=0x50000Ϊ10s
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
