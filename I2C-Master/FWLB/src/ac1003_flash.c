/**
  ******************************************************************************
  * @file    ac1003_flash.c
  * @author  MCU_BU Application Team
  * @version V0.0.0
  * @date    28-5-2019
  * @brief   This file provides firmware functions to manage the following
  *          functionalities of the FLASH peripheral:
  *            + FLASH Interface configuration
  *            + FLASH Memory Programming
  *            + Option Bytes Programming
  *            + Interrupts and flags management
  ******************************************************************************
  */

/* Includes -------------------------------*/
#include "ac1003_flash.h"

/* Private define ------------------------------------------------------------*/
#define DUMMY_ADDERSS								(0x00002000)
#define DUMMY_DATA									(0x5555AAAA)


/**
  * @brief  Full erase of FLASH memory Bank
  * @param  None
  * @retval None
  */
static void FLASH_MassErase(void)
{
    uint32_t temp;

    __disable_irq();
    /* Whole chip will be erased*/
    __FLASH_REGISTER_UNLOCK;
    temp = FLASH->CR;
    FLASH->CR = ((temp & FLASH_OPERATION_MASK) | FLASH_CHIPEARSE);
    /* Write data in the address */
    *(__IO uint32_t*)DUMMY_ADDERSS = DUMMY_DATA;
    __FLASH_REGISTER_LOCK;

    __enable_irq();
}

/**
  * @brief  Erase the specified FLASH memory page
  * @param  PageAddress FLASH page to erase
  *         The value of this parameter depend on device used within the same series
  *
  * @retval None
  */
static void FLASH_PageErase(uint32_t PageAddress)
{
    uint32_t temp;

    __disable_irq();
    /* one page will be erased*/
    __FLASH_REGISTER_UNLOCK;
    temp = FLASH->CR;
    FLASH->CR = ((temp & FLASH_OPERATION_MASK) | FLASH_SECTOREARSE);
    /* Proceed to erase the page */
    *(__IO uint32_t*)PageAddress = DUMMY_DATA;

    __FLASH_REGISTER_LOCK;
    __enable_irq();
}

/**
  * @brief  Program a byte (8-bit) at a specified address.
  * @param  Address specify the address to be programmed.
  * @param  Data    specify the data to be programmed.
  * @retval None
  */
static void FLASH_Program_Byte(uint32_t Address, uint8_t Data)
{
    uint32_t temp;

    __disable_irq();
    /* Proceed to program the new data */
    __FLASH_REGISTER_UNLOCK;
    temp = FLASH->CR;
    FLASH->CR = ((temp & FLASH_OPERATION_MASK) | FLASH_PROGRAM);
    /* Write data in the address */
    *(__IO uint8_t*)Address = Data;

    __FLASH_REGISTER_LOCK;

    __enable_irq();
}

/**
  * @brief  Program a half-word (16-bit) at a specified address.
  * @param  Address specify the address to be programmed.
  * @param  Data    specify the data to be programmed.
  * @retval None
  */
static void FLASH_Program_HalfWord(uint32_t Address, uint16_t Data)
{
    uint32_t temp;

    __disable_irq();
    /* Proceed to program the new data */
    __FLASH_REGISTER_UNLOCK;
    temp = FLASH->CR;
    FLASH->CR = ((temp & FLASH_OPERATION_MASK) | FLASH_PROGRAM);
    /* Write data in the address */
    *(__IO uint16_t*)Address = Data;

    __FLASH_REGISTER_LOCK;
    __enable_irq();
}

/**
  * @brief  Program a word (32-bit) at a specified address.
  * @param  Address specify the address to be programmed.
  * @param  Data    specify the data to be programmed.
  * @retval None
  */
static void FLASH_Program_Word(uint32_t Address, uint32_t Data)
{
    uint32_t temp;

    __disable_irq();
    /* Proceed to program the new data */
    __FLASH_REGISTER_UNLOCK;
    temp = FLASH->CR;
    FLASH->CR = ((temp & FLASH_OPERATION_MASK) | FLASH_PROGRAM);
    /* Write data in the address */
    *(__IO uint32_t*)Address = Data;

    __FLASH_REGISTER_LOCK;
    __enable_irq();
}

/**
  * @brief  Unlock the FLASH Page Erase/write access.
  * @param  PageAddress:  Set the page address to lock erase/write protect.
  *                       This parameter can be set 0xFFFFFFFF which means lock all pages.
  * @retval FLASH Status
  */
FLASH_Status FLASH_OPERATION_Unlock(uint32_t PageAddress)
{
    FLASH_Status status = FLASH_OK;

    __disable_irq();
    /* One bit of SLOCKx controls 2 pages, page size is 1K bytes */
    if(PageAddress < FLASH_SIZE_32K)
    {
        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK0 |= (1 << (PageAddress >> 10));
        __FLASH_REGISTER_LOCK;
    }
    else if(PageAddress < FLASH_SIZE_64K)
    {
        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK1 |= (1 << ((PageAddress - 32 * 1024) >> 10));
        __FLASH_REGISTER_LOCK;
    }
    else if(PageAddress == FLASH_ALLPAGE_SELECTED)
    {
        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK0 |= 0xFFFFFFFF;
        __FLASH_REGISTER_LOCK;

        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK1 |= 0xFFFFFFFF;
        __FLASH_REGISTER_LOCK;
    }
    else
        return FLASH_ERROR;

    __enable_irq();
    return status;
}

/**
  * @brief  Lock the FLASH Page Erase/Write access.
  * @param  PageAddress:  Set the page address to lock erase/write protect.
  *                       This parameter can be set 0xFFFFFFFF which means lock all pages.
  * @retval FLASH Status
  */
FLASH_Status FLASH_OPERATION_Lock(uint32_t PageAddress)
{
    FLASH_Status status = FLASH_OK;

    __disable_irq();
    /* One bit of SLOCKx controls 2 pages, page size is 1K bytes */
    if(PageAddress < FLASH_SIZE_32K)
    {
        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK0 &= ~(1 << (PageAddress >> 10));
        __FLASH_REGISTER_LOCK;
    }
    else if(PageAddress < FLASH_SIZE_64K)
    {
        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK1 &= ~(1 << ((PageAddress - 32 * 1024) >> 10));
        __FLASH_REGISTER_LOCK;
    }
    else if(PageAddress == FLASH_ALLPAGE_SELECTED)
    {
        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK0 &= ~0xFFFFFFFF;
        __FLASH_REGISTER_LOCK;

        __FLASH_REGISTER_UNLOCK;
        FLASH->SLOCK1 &= ~0xFFFFFFFF;
        __FLASH_REGISTER_LOCK;
    }
    else
        return FLASH_ERROR;

    __enable_irq();
    return status;
}

/**
  * @brief  Erases a specified FLASH Sector.
  * @note   If an erase and a program operations are requested simustaneously,
  *         the erase operation is performed before the program one.
  * @param  FLASH_Addr: The Flash Address to be erased.
	* @param  None
  * @retval FLASH Status: The returned value can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseSector(uint32_t FLASH_Addr)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(FLASH_Addr));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Unlock(FLASH_Addr);
    FLASH_PageErase(FLASH_Addr);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Lock(FLASH_Addr);

    /* If the page erase operation is completed, change operation to Read */
    __disable_irq();
    __FLASH_REGISTER_UNLOCK;;
    FLASH->CR &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();

    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Erases all FLASH Sectors.
  * @note   If an erase and a program operations are requested simustaneously,
  *         the erase operation is performed before the program one.
  * @param  None
  * @param  None
  * @retval FLASH Status: The Vlaue can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_EraseAllSectors(void)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Unlock(FLASH_ALLPAGE_SELECTED);

    /*Mass erase to be done*/
    FLASH_MassErase();

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Lock(FLASH_ALLPAGE_SELECTED);

    /* If the page erase operation is completed, change operation to Read */
    __disable_irq();
    __FLASH_REGISTER_UNLOCK;;
    FLASH->CR &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();

    /* Return the Erase Status */
    return status;
}

/**
  * @brief  Programs a word (32-bit) at a specified address.
  * @note   This function must be used when the device voltage range is from 2.7V to 3.6V.
  * @note   If an erase and a program operations are requested simustaneously,
  *         the erase operation is performed before the program one.
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH Status: The returned value can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Unlock(Address);

    FLASH_Program_Word(Address, Data);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    /* If the program operation is completed, change operation to Read */
    __disable_irq();
    __FLASH_REGISTER_UNLOCK;;
    FLASH->CR &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();

    FLASH_OPERATION_Lock(Address);

    /* Return the Program Status */
    return status;
}

/**
  * @brief  Programs a half word (16-bit) at a specified address.
  * @note   This function must be used when the device voltage range is from 2.1V to 3.6V.
  * @note   If an erase and a program operations are requested simustaneously,
  *         the erase operation is performed before the program one.
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH_Status: The returned value can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Unlock(Address);

    FLASH_Program_HalfWord(Address, Data);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    /* If the program operation is completed, change operation to Read */
    __disable_irq();
    __FLASH_REGISTER_UNLOCK;;
    FLASH->CR &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();

    FLASH_OPERATION_Lock(Address);
    /* Return the Program Status */
    return status;
}

/**
  * @brief  Programs a byte (8-bit) at a specified address.
  * @note   This function can be used within all the device supply voltage ranges.
  * @note   If an erase and a program operations are requested simustaneously,
  *         the erase operation is performed before the program one.
  * @param  Address: specifies the address to be programmed.
  *         This parameter can be any address in Program memory zone or in OTP zone.
  * @param  Data: specifies the data to be programmed.
  * @retval FLASH_Status: The returned value can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_ProgramByte(uint32_t Address, uint8_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    /* Check the parameters */
    assert_param(IS_FLASH_ADDRESS(Address));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    FLASH_OPERATION_Unlock(Address);

    FLASH_Program_Byte(Address, Data);

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    /* If the program operation is completed, change operation to Read */
    __disable_irq();
    __FLASH_REGISTER_UNLOCK;;
    FLASH->CR &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();

    FLASH_OPERATION_Lock(Address);
    /* Return the Program Status */
    return status;
}


FLASH_Status FLASH_SWDP_Config(FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;

    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    __disable_irq();
    __FLASH_REGISTER_UNLOCK;
    FLASH->CR  &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    /* Disable the write protection for flash registers */
    __FLASH_REGISTER_UNLOCK;
    FLASH->CR |= FLASH_SECTOREARSE;
    *(__IO uint32_t *)0x08000004 = (uint32_t)DUMMY_DATA;
    __FLASH_REGISTER_LOCK;

    __enable_irq();

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    __disable_irq();
    /*if the erase operation is completed, disable the SER Bit */
    __FLASH_REGISTER_UNLOCK;
    FLASH->CR  &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();


    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    __disable_irq();
    /* if the previous operation is completed, proceed to program the new data */
    __FLASH_REGISTER_UNLOCK;
    FLASH->CR  &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    /* Disable the write protection for flash registers */
    __FLASH_REGISTER_UNLOCK;
    FLASH->CR |= FLASH_PROGRAM;

    if(NewState == ENABLE)
        *(__IO uint32_t*)0x08000004 = 0x7FFFFFFE;
    else
        *(__IO uint32_t*)0x08000004 = 0x7FFFFFFF;

    __FLASH_REGISTER_LOCK;
    __enable_irq();

    /* Wait for last operation to be completed */
    status = FLASH_WaitForLastOperation();

    __disable_irq();
    /* if the program operation is completed, disable the PG Bit */
    __FLASH_REGISTER_UNLOCK;
    FLASH->CR  &= FLASH_OPERATION_MASK;
    __FLASH_REGISTER_LOCK;
    __enable_irq();

    return status;
}

/**
  * @brief  Enables or disables the specified FLASH interrupts.
  * @param  FLASH_IT: specifies the FLASH interrupt sources to be enabled or disabled.
  *         This parameter can be any combination of the following values:
  * @param  Newstate: This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FLASH_IT(FLASH_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* Disable the write protection for flash registers */
    __FLASH_REGISTER_UNLOCK;

    if(NewState != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CR |= FLASH_IT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CR &= ~(uint32_t)FLASH_IT;
    }

    __FLASH_REGISTER_LOCK;
}

/**
  * @brief  Checks whether the specified FLASH flag is set or not.
  * @param  FLASH_FLAG: specifies the FLASH flag to check.
  *          This parameter can be one of the following values:
  *            @arg FLASH_FLAG_IT_PC: IT PC FLAG
  *            @arg FLASH_FLAG_IT_PROTECT: IT PROTECT FLAG
  * @param  None
  * @retval The new state of FLASH_FLAG (SET or RESET).
  */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;
    /* Check the parameters */
    assert_param(IS_FLASH_FLAG_IT(FLASH_FLAG));

    if((FLASH->IFR & FLASH_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}

/**
  * @brief  Clears the FLASH's pending flags.
  * @param  FLASH_FLAG: specifies the FLASH flags to clear.
  *          This parameter can be any combination of the following values:
  *            @arg FLASH_FLAG_IT_PC: IT PC FLAG
  *            @arg FLASH_FLAG_IT_PROTECT: IT PROTECT FLAG
  * @param  None
  * @retval None
  */
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Check the parameters */
    assert_param(IS_FLASH_FLAG_IT(FLASH_FLAG));

    /* Disable the write protection for flash registers */
    __FLASH_REGISTER_UNLOCK;

    /* Clear the flags */
    FLASH->ICLR &= (~FLASH_FLAG);

    __FLASH_REGISTER_LOCK;
}

/**
  * @brief  Returns the FLASH Status.
  * @param  None
  * @param  None
  * @retval FLASH Status: The returned value can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_GetStatus(void)
{
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if((FLASH->CR & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        flashstatus = FLASH_COMPLETE;
    }
    /* Return the FLASH Status */
    return flashstatus;
}

/**
  * @brief  Waits for a FLASH operation to complete.
  * @param  None
  * @param  None
  * @retval FLASH Status: The returned value can be FLASH_BUSY or FLASH_COMPLETE.
  */
FLASH_Status FLASH_WaitForLastOperation(void)
{
    __IO FLASH_Status status = FLASH_COMPLETE;

    /* Check for the FLASH Status */
    status = FLASH_GetStatus();

    /* Wait for the FLASH operation to complete by polling on BUSY flag to be reset.
       Even if the FLASH operation fails, the BUSY flag will be reset and an error
       flag will be set */
    while(status == FLASH_BUSY)
    {
        status = FLASH_GetStatus();
    }
    /* Return the operation status */
    return status;
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
/************************ (C) COPYRIGHT Ascendchip *****END OF FILE****/

