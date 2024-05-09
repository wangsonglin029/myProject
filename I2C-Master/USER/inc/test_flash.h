/**
  ************************************************************************
  * @file    test_flash.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file contains all the functions prototypes for the uart
  ************************************************************************
  */
#ifndef  _TEST_FLASH
#define  _TEST_FLASH


/* Includes --------------------------*/
#include "ac1003_flash.h"
#include "mdefine.h"


/*******parameters define**************/


/*******flash test status**************/
typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;


/*****define functions**************/
TestStatus Test_Flash(uint32_t Data);



#endif /* __INTERNAL_FLASH_H */


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











