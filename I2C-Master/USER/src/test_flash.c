/**
  *******************************************************************
  * @file   test_Flash.c
  * @author  fire
  * @version V0.0.0
  * @date    2019-8
  * @brief
  ********************************************************************
  */

/*Includes -------------------------*/
#include "test_flash.h"
#include "test_uart.h"

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(uint32_t uiAddress)
{
}

/**
 * @brief  Test  inner flash function.
 * @param  None
* @param  None
 * @retval None
 */
TestStatus WriteToFlash(uint32_t Addr, uint32_t Data[], uint16_t Datalen)
{
    /***define parameters***********/
    FLASH_Status FLASHStatus = FLASH_COMPLETE;
    TestStatus MemoryProgramStatus = PASSED;
    uint32_t EraseAddr;
    uint32_t *temp = Data;
    uint32_t uiAddress = 0;
    uint32_t Address = 0;

    /*clear warning*/
    FLASHStatus = FLASH_COMPLETE;

    /*Clear all flags of flash*/
    FLASH_ClearFlag(FLASH_FLAG_ALL);

    /*ERASE*///擦除操作
    for(EraseAddr = Addr; EraseAddr < Addr + 0x400; EraseAddr = EraseAddr + FLASH_PAGE_SIZE)
    {
        FLASHStatus = FLASH_EraseSector(EraseAddr);
        if(FLASHStatus != FLASH_COMPLETE);
    }

    uiAddress = Addr;
    //查空操作
    while (uiAddress < Addr + 0x400)
    {
        if (*(uint8_t*)(uiAddress) != 0xFF)
        {
            /* Error occurred while writing data in Flash memory.
               User can add here some code to deal with this error */
            Error_Handler(uiAddress);
            uiAddress = uiAddress + 1;
        }
        else
        {
            uiAddress = uiAddress + 1;
        }
    }

    /*PROGRAM*///写操作
    Address = Addr;
    while(Address < Addr + 4 * Datalen)
    {
        FLASHStatus = FLASH_ProgramWord(Address, *temp ++);
        if(FLASHStatus != FLASH_COMPLETE)
            printf("FLASH_ProgramWord FAILED\r\n");
        Address = Address + 4;
    }

    /*READ&&CHECK*///读操作和校验
    temp = Data;
    Address = Addr;
    while(Address < Addr + 4 * Datalen)
    {
        if((*(__IO uint32_t*) Address) != *temp ++)
        {
            MemoryProgramStatus = FAILED;
        }
        Address += 4;
    }
    return MemoryProgramStatus;
}

TestStatus ReadFromFlash(uint32_t Addr, uint32_t Data[], uint16_t Datalen)
{
    /***define parameters***********/
    TestStatus MemoryProgramStatus = PASSED;
    uint32_t *temp = Data;
    uint32_t Address = 0;

    /*READ&&CHECK*///读操作和校验
    temp = Data;
    Address = Addr;
    while(Address < Addr + 4 * Datalen)
    {
        *temp ++ = (*(__IO uint32_t*) Address);
        Address += 4;
    }
    return MemoryProgramStatus;
}

/// 总共 16 字节的 UID
void GetMcuUid(void)
{
  // UID 地址 ：0x180000F0 - 0x180000FF
  uint8_t  uid[0x12] = {0x00};
  uint32_t *temp = (uint32_t*)uid;
  uint32_t Address = 0x180000F0;
  
  while(Address < 0x180000F0 + 4 * 4)
  {
    *temp ++ = (*(__IO uint32_t*) Address);
    Address += 4;
  }
}

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





