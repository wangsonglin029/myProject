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
// ���ڼ�����ֵ����ΧΪ��0x40~0x7f��һ�����ó����0X7F ,ʹ�õ�ʱ��ΪϵͳPCLK
//PCLK=24M��Ԥ��Ƶ0xFFFF֮��Ϊ2.73ms�����ڴ�С���õ���0xF = 43.7ms��CNTΪ0x7F = 346.7ms��
#define WWDG_CNT	                   (uint32_t)0x7f		//���ڿ��Ź�����ֵ
#define WWDG_PRESCALER               (uint32_t)0xffff //WWDGԤ��Ƶ
#define WWDG_WINDOWVALUE             (uint32_t)0x0f		//��������
                                     
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
