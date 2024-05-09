/**
  ************************************************************************
  * @file    test_wwdt.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file contains all the functions prototypes for the wwdt 
  ************************************************************************
  */
#ifndef __TEST_WWDG_H
#define	__TEST_WWDG_H

/*Includes --------------------------*/
#include "ac1003_wwdt.h"
#include "misc.h"


/***define parameters*************/
#define DEBUG_WWDGx                  WWDG
// 窗口计数器值，范围为：0x40~0x7f，一般设置成最大0X7F ,使用的时间为系统PCLK
//PCLK=24M，预分频0xFFFF之后，为2.73ms，窗口大小设置的是0xF = 43.7ms。CNT为0x7F = 346.7ms。
#define WWDG_CNT	                   (uint32_t)0x7f		//窗口看门狗计数值
#define WWDG_PRESCALER               (uint32_t)0xffff //WWDG预分频
#define WWDG_WINDOWVALUE             (uint32_t)0x0f		//窗口区间
                                     
/*Disable/Enable WWDG Interrupt*/
#define WWDG_CMD_TI                  ENABLE
#define WWDG_CMD_ENABLE              ENABLE


/*Define WWDG IRQ*/
#define  DEBUG_WWDG_IRQ              WWDG_IRQn
#define  DEBUG_WWDG_IRQHandler       WWDG_IRQHandler


/*Define function----------------------------*/
void WWDG_Config(void);
void WWDG_Feed(void);

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
