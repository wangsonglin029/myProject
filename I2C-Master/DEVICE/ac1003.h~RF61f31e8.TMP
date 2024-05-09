/**
  ******************************************************************************
  * @file    ac1003.h
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    2019-8
  * @brief   CMSIS Cortex-M0 Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for ac1003 devices.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e.
  *                code will be based on direct access to peripheral’s registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral’s registers hardware
  *
  ******************************************************************************
  */

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup ac1003
  * @{
  */

#ifndef __AC1003_H
#define __AC1003_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned      int vu32;
typedef unsigned      short int vu16;
typedef unsigned      char vu8;

/**
 * @brief In the following line adjust the value of External High Speed oscillator (HXT)
   used in your application

   Tip: To avoid modifying this file each time you need to use different HSE, you
        can define the HSE value in your toolchain compiler preprocessor.
  */

#if !defined  (HICR_STABLE_TIMEOUT)
#define HICR_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /*HICR_STABLE_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup
   Timeout value
   */
#if !defined  (HXT_STABLE_TIMEOUT)
#define HXT_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI_STARTUP_TIMEOUT */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup
   Timeout value
   */
#if !defined  (LICR_STABLE_TIMEOUT)
#define LICR_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI_VALUE */

/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup
   Timeout value
   */
#if !defined  (LXT_STABLE_TIMEOUT)
#define LXT_STABLE_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI14_VALUE */


/**
 * @brief In the following line adjust the Internal High Speed oscillator (HSI) Startup
   Timeout value
   */
#if !defined  (SYSTEMTICKTIMER_SKEW_TIMEOUT)
#define SYSTEMTICKTIMER_SKEW_TIMEOUT   ((uint16_t)0x5000) /*!< Time out for HICR STABLE */
#endif /* HSI14_VALUE */


//PACKAGE is defined by default. for KDG customer, PACKAGE should be undefined.
#define PACKAGE

/** @defgroup RCC_HIRC_Calibration_Config HIRC Calibration Config
  * @{
  */
#define HIRC_FLASHADDR_A_BASEADDR					0x180000A0
#define HIRC_FLASHADDR_C_BASEADDR					0x180000C0
#define HIRC24M_FLASHADDR_OFFSET					0x00000000
#define HIRC22M_FLASHADDR_OFFSET					0x00000002
#define HIRC16M_FLASHADDR_OFFSET					0x00000004
#define HIRC8M_FLASHADDR_OFFSET						0x00000006
#define HIRC4M_FLASHADDR_OFFSET						0x00000008

#define LIRC_FLASHADDR_B_BASEADDR					0x180000B0
#define LIRC_FLASHADDR_D_BASEADDR					0x180000D0
#define LIRC32K_FLASHADDR_OFFSET					0x00000000
#define LIRC38K_FLASHADDR_OFFSET					0x00000004

#define HIRC24M_TRIMVALUE_A   ((*(__IO uint16_t*)(HIRC_FLASHADDR_A_BASEADDR + HIRC24M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR24M Value */
#define HIRC24M_TRIMVALUE_C   ((*(__IO uint16_t*)(HIRC_FLASHADDR_C_BASEADDR + HIRC24M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR24M Value */
#define HIRC22M_TRIMVALUE_A   ((*(__IO uint16_t*)(HIRC_FLASHADDR_A_BASEADDR + HIRC22M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR22M Value */
#define HIRC22M_TRIMVALUE_C   ((*(__IO uint16_t*)(HIRC_FLASHADDR_C_BASEADDR + HIRC22M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR22M Value */
#define HIRC16M_TRIMVALUE_A   ((*(__IO uint16_t*)(HIRC_FLASHADDR_A_BASEADDR + HIRC16M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR16M Value */
#define HIRC16M_TRIMVALUE_C   ((*(__IO uint16_t*)(HIRC_FLASHADDR_C_BASEADDR + HIRC16M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR16M Value */
#define HIRC8M_TRIMVALUE_A    ((*(__IO uint16_t*)(HIRC_FLASHADDR_A_BASEADDR + HIRC8M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR8M Value */
#define HIRC8M_TRIMVALUE_C    ((*(__IO uint16_t*)(HIRC_FLASHADDR_C_BASEADDR + HIRC8M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR8M Value */
#define HIRC4M_TRIMVALUE_A    ((*(__IO uint16_t*)(HIRC_FLASHADDR_A_BASEADDR + HIRC4M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR4M Value */
#define HIRC4M_TRIMVALUE_C    ((*(__IO uint16_t*)(HIRC_FLASHADDR_C_BASEADDR + HIRC4M_FLASHADDR_OFFSET))&0x00000fff) /*!< Timing HICR4M Value */

#define LIRC32K_TRIMVALUE_B    ((*(__IO uint16_t*)(LIRC_FLASHADDR_B_BASEADDR + LIRC32K_FLASHADDR_OFFSET))&0x000001ff) /*!< Timing LICR32K Value */
#define LIRC32K_TRIMVALUE_D    ((*(__IO uint16_t*)(LIRC_FLASHADDR_D_BASEADDR + LIRC32K_FLASHADDR_OFFSET))&0x000001ff) /*!< Timing LICR32K Value */
#define LIRC38K_TRIMVALUE_B    ((*(__IO uint16_t*)(LIRC_FLASHADDR_B_BASEADDR + LIRC38K_FLASHADDR_OFFSET))&0x000001ff) /*!< Timing LICR38K Value */
#define LIRC38K_TRIMVALUE_D    ((*(__IO uint16_t*)(LIRC_FLASHADDR_D_BASEADDR + LIRC38K_FLASHADDR_OFFSET))&0x000001ff) /*!< Timing LICR38K Value */



/**
 * @brief In the following line adjust the oscillator value.
   Timeout value
   */
#if !defined  (HIRC24M_TIMVALUE)
#define HIRC24M_TIMVALUE   	 ((uint32_t)24000000)/*!< Timing HICR24M Value */
#endif /*HIRC_TIM_VALUE*/


#if !defined  (HIRC22M_TIMVALUE)
#define HIRC22M_TIMVALUE   ((uint32_t)22120000) /*!< Timing HICR22M Value */
#endif /*HIRC_TIM_VALUE*/


#if !defined  (HIRC16M_TIMVALUE)
#define HIRC16M_TIMVALUE   ((uint32_t)16000000) /*!< Timing HICR16M Value */
#endif /*HIRC_TIM_VALUE*/


#if !defined  (HIRC8M_TIMVALUE)
#define HIRC8M_TIMVALUE    ((uint32_t)8000000) /*!< Timing HICR8M Value */
#endif /*HIRC_TIM_VALUE*/

#if !defined  (HIRC4M_TIMVALUE)
#define HIRC4M_TIMVALUE    ((uint32_t)4000000) /*!< Timing HICR4M Value */
#endif /*HIRC_TIM_VALUE*/


#if !defined  (LIRC32K_TIMVALUE)
#define LIRC32K_TIMVALUE    ((uint32_t)32768) /*!< Timing LICR32K Value */
#endif /*LIRC_TIM_VALUE*/

#if !defined  (LIRC38K_TIMVALUE)
#define LIRC38K_TIMVALUE    ((uint32_t)38400) /*!< Timing LICR38K Value */
#endif /*LIRC_TIM_VALUE*/


/* ########################## Oscillator Values adaptation ####################*/

#if !defined  (HIRC_VALUE_24M)
#define HIRC_VALUE_24M    		((uint32_t)24000000) 	/*!< Value of the Internal oscillator select 24MHz */
#endif /* HIRC_VALUE_24M */

#if !defined  (HIRC_VALUE_22M)
#define HIRC_VALUE_22M    		((uint32_t)22120000) 	/*!< Value of the Internal oscillator select 22.12MHz */
#endif /* HIRC_VALUE_22M */

#if !defined  (HIRC_VALUE_16M)
#define HIRC_VALUE_16M    		((uint32_t)16000000) 	/*!< Value of the Internal oscillator select 16MHz */
#endif /* HIRC_VALUE_16M */

#if !defined  (HIRC_VALUE_8M)
#define HIRC_VALUE_8M    			((uint32_t)8000000) 	/*!< Value of the Internal oscillator select 8MHz */
#endif /* HIRC_VALUE_8M */

#if !defined  (HIRC_VALUE_4M)
#define HIRC_VALUE_4M    			((uint32_t)4000000) 	/*!< Value of the Internal oscillator select 4MHz */
#endif /* HIRC_VALUE_4M */

#if !defined  (LIRC_VALUE_38K)
#define LIRC_VALUE_38K               38400U    /*!< LIRC Typical Value in Hz */
#endif /* LIRC_VALUE_38K */

#if !defined  (LIRC_VALUE_32K)
#define LIRC_VALUE_32K               32768U    /*!< LIRC Typical Value in Hz */
#endif /* LIRC_VALUE_32K */



/** @addtogroup Configuration_of_CMSIS
  * @{
  */

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum {
    /* =======================================  ARM Cortex-M0+ Specific Interrupt Numbers  ======================================= */
    Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
    NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
    HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
    SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
    PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
    SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */
    GPIOA_IRQn                =   0,              /*!< 0  GPIOA                                                                  */
    GPIOB_IRQn                =   1,              /*!< 1  GPIOB global interrupt                                                 */
    GPIOC_IRQn                =   2,              /*!< 2  GPIOC global interrupt                                                 */
    GPIOD_IRQn                =   3,              /*!< 3  GPIOD global interrupt                                                 */
    FLASH_IRQn                =   4,              /*!< 4  FLASH                                                                  */
    UART0_IRQn                =   6,              /*!< 6  UART0                                                                  */
    UART1_IRQn                =   7,              /*!< 7  UART1 global interrupt                                                 */
    LPUART_IRQn               =   8,              /*!< 8  LPUART                                                                 */
    SPI_IRQn                  =  10,              /*!< 10 SPI                                                                    */
    I2C_IRQn                  =  12,              /*!< 12 I2C                                                                    */
    TIM10_IRQn                =  14,              /*!< 14 TIM10                                                                  */
    TIM11_IRQn                =  15,              /*!< 15 TIM11 global interrupt                                                 */
    LPTIM_IRQn                =  16,              /*!< 16 LPTIM                                                                  */
    TIM1_IRQn                 =  18,              /*!< 18 TIM1                                                                   */
    TIM2_IRQn                 =  19,              /*!< 19 TIM2 global interrupt                                                  */
    PCA_IRQn                  =  21,              /*!< 21 PCA                                                                    */
    WWDG_IRQn                 =  22,              /*!< 22 WWDG                                                                   */
    IWDG_IRQn                 =  23,              /*!< 23 IWDG                                                                   */
    ADC_IRQn                  =  24,              /*!< 24 ADC                                                                    */
    LVD_IRQn                  =  25,              /*!< 25 LVD                                                                    */
    VC_IRQn                   =  26,              /*!< 26 VC                                                                     */
    AWK_IRQn                  =  28,              /*!< 28 AWK                                                                    */
    ONEWIRE_IRQn              =  29,              /*!< 29 OWIRE                                                                  */
    RTC_IRQn                  =  30,              /*!< 30 RTC                                                                    */
    CLKTRIM_IRQn              =  31               /*!< 31 CLKTRIM                                                                */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ==========================  Configuration of the ARM Cortex-M0+ Processor and Core Peripherals  =========================== */
#define __CM0PLUS_REV                  0x0201U  /*!< CM0PLUS Core Revision                                                     */
#define __NVIC_PRIO_BITS               2        /*!< Number of Bits used for Priority Levels                                   */
#define __Vendor_SysTickConfig         0        /*!< Set to 1 if different SysTick Config is used                              */
#define __VTOR_PRESENT                 1        /*!< Set to 1 if CPU supports Vector Table Offset Register                     */
#define __MPU_PRESENT                  0        /*!< MPU present or not                                                        */
#define __FPU_PRESENT                  0        /*!< FPU present or not                                                        */


#include "core_cm0plus.h"
#include "system_ac1003.h"


/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           Copyright (C) 2016 Brite Semiconductor Co., Ltd. All rights reserved.                */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;


/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @}addtogroup SYSCON_TypeDef
  */
typedef struct
{
    __IO uint32_t   CFGR0;
    __IO uint32_t   PORTINTCR;
    __IO uint32_t   PORTCR;
    __IO uint32_t   PCACR;
    __IO uint32_t   TIM1CR;
    __IO uint32_t   TIM2CR;
    __IO uint32_t   RESERVED[14];       /*!< Reserved, */
    __IO uint32_t   UNLOCK;
} SYSCON_TypeDef;



/**
  * @}addtogroup LPTIMER_TypeDef
  */
typedef struct
{
    __IO uint32_t CNTVAL;
    __IO uint32_t CR;
    __IO uint32_t LOAD;
    __IO uint32_t INTSR;
    __IO uint32_t INTCLR;
    __IO uint32_t BGLOAD;
} LPTIMER_TypeDef;


/**
  * @}addtogroup LVD_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SR;

} LVD_TypeDef;


/**
  * @}addtogroup VC_TypeDef
  */
typedef struct
{
    __IO uint32_t CR0;
    __IO uint32_t CR1;
    __IO uint32_t OUTCFG;
    __IO uint32_t SR;
} VC_TypeDef;

/**
  * @brief UART_TypeDef
  */

typedef struct
{
    __IO uint32_t SCON; /*!<UART¿ØÖÆ¼Ä´æÆ÷*/
    __IO uint32_t SBUF; /*!<UARTÊý¾Ý¼Ä´æÆ÷*/
    __IO uint32_t SADDR; /*!<UARTµØÖ·¼Ä´æÆ÷*/
    __IO uint32_t SADEN; /*!<UARTµØÖ·ÑÚÂë¼Ä´æÆ÷*/
    __IO uint32_t INTSR; /*!<UART±êÖ¾¼Ä´æÆ÷*/
    __IO uint32_t INTCLR; /*!<UART±êÖ¾Çå³ý¼Ä´æÆ÷*/
    __IO uint32_t BAUDCR;/*!<UART²¨ÌØÂÊ¿ØÖÆ¼Ä´æÆ÷*/
    __IO uint32_t IRDACR;/*!<IrDA¿ØÖÆ¼Ä´æÆ÷*/
} UART_TypeDef;


/**
  * @brief LPUART_TypeDef
  */

typedef struct
{
    __IO uint32_t SBUF;   /*!<LPUARTÊý¾Ý¼Ä´æÆ÷*/
    __IO uint32_t SCON;   /*!<LPUART¿ØÖÆ¼Ä´æÆ÷*/
    __IO uint32_t SADDR;  /*!<LPUARTµØÖ·¼Ä´æÆ÷*/
    __IO uint32_t SADEN;  /*!<LPUARTµØÖ·ÑÚÂë¼Ä´æÆ÷*/
    __IO uint32_t INTSR;  /*!<LPUART±êÖ¾¼Ä´æÆ÷*/
    __IO uint32_t INTCLR; /*!<LPUART±êÖ¾Çå³ý¼Ä´æÆ÷*/
    __IO uint32_t BAUDCR; /*!<LPUART²¨ÌØÂÊ¿ØÖÆ¼Ä´æÆ÷*/
} LPUART_TypeDef;


/**
  * @brief I2C_TypeDef
  */
typedef struct
{
    __IO uint16_t CR;    /*!< I2C Control register , Address offset: 0x00 */
    uint16_t  RESERVED0;
    __IO uint16_t DATA;  /*!< I2C Data register , Address offset: 0x04 */
    uint16_t  RESERVED2;
    __IO uint16_t ADDR;  /*!< I2C Address register , Address offset: 0x08 */
    uint16_t  RESERVED3;
    __IO uint16_t SR; /*!< I2C Status register , Address offset: 0x0C */
    uint16_t  RESERVED4;
    __IO uint16_t TIMRUN; /*!< I2C Baud rate counter enabled register , Address offset: 0x10 */
    uint16_t  RESERVED5;
    __IO uint16_t BAUDCR;    /*!< I2C Baud rate counter configuration register , Address offset: 0x14 */
    uint16_t  RESERVED6;
} I2C_TypeDef;
/**
  * @brief  WWDG_TypeDef
  */
typedef struct
{
    __IO uint32_t RLOAD;   /*!< WWDG Control register,       Address offset: 0x00 */
    __IO uint32_t CR;  /*!< WWDG Configuration register, Address offset: 0x04 */
    __IO uint32_t INTEN;   /*!< WWDG Status register,        Address offset: 0x08 */
    __IO uint32_t SR;
    __IO uint32_t INTCLR;
    __IO uint32_t CNTVAL;
} WWDG_TypeDef;

/**
  * @brief IWDG_TypeDef
  */
typedef struct
{
    __IO uint32_t CMDCR;   /*!< IWDG Control register,       Address offset: 0x00 */
    __IO uint32_t CFGR;  /*!< IWDG Configuration register, Address offset: 0x04 */
    __IO uint32_t RLOAD;   /*!< IWDG Rload counter register,        Address offset: 0x08 */
    __IO uint32_t CNTVAL;   /*!< IWDG count value register,        Address offset: 0x0c*/
    __IO uint32_t SR;   /*!< IWDG TI Status register,        Address offset: 0x10 */
    __IO uint32_t INTCLR;   /*!< IWDG TI CLear Status register,        Address offset: 0x14 */
    __IO uint32_t UNLOCK;   /*!< IWDG resigter protect  register,        Address offset: 0x18 */
} IWDG_TypeDef;

/**
  * @} GPIO_TypeDef
  */
typedef struct
{
    __IO uint32_t DIRCR;
    __IO uint32_t OTYPER;
    __IO uint32_t ODR;
    __IO uint32_t IDR;
    __IO uint32_t INTEN;
    __IO uint32_t RAWINTSR;
    __IO uint32_t MSKINTSR;
    __IO uint32_t INTCLR;
    __IO uint32_t INTTYPCR;
    __IO uint32_t INTPOLCR;
    __IO uint32_t INTANY;
    __IO uint32_t ODSET;
    __IO uint32_t ODCLR;
    __IO uint32_t INDBEN;
    __IO uint32_t DBCLKCR;
    __IO uint32_t PUPDR;
    __IO uint32_t SLEWCR;
    __IO uint32_t DRVCR;
    __IO uint32_t AFR;
} GPIO_TypeDef;
/**
  * @}  TIM_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t LOAD;
    __IO uint32_t CNT;
    __IO uint32_t RAWINTSR;
    __IO uint32_t MSKINTSR;
    __IO uint32_t INTCLR;
    __IO uint32_t BGLOAD;
} TIM_TypeDef;


/**
* @brief ADVTIM_TypeDef
  */

typedef struct
{
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SMCR;
    __IO uint32_t DIER;
    __IO uint32_t SR;
    __IO uint32_t EGR;
    __IO uint32_t CCMR1;
    __IO uint32_t CCMR2;
    __IO uint32_t CCER;
    __IO uint32_t CNT;
    __IO uint32_t PSC;
    __IO uint32_t ARR;
    __IO uint32_t RCR;
    __IO uint32_t CCR1;
    __IO uint32_t CCR2;
    __IO uint32_t CCR3;
    __IO uint32_t CCR4;
    __IO uint32_t BDTR;
} ADVTIM_TypeDef;

/**
  * @} SPI_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SSN;
    __IO uint32_t SR;
    __IO uint32_t DATA;
} SPI_TypeDef;


/**
  * @} PCA_TypeDef
  */
typedef struct
{
    __IO uint32_t  CR  ;
    __IO uint32_t  MOD  ;
    __IO uint32_t  CNT   ;
    __IO uint32_t  INTCLR  ;
    __IO uint32_t  CCAPM0 ;
    __IO uint32_t  CCAPM1 ;
    __IO uint32_t  CCAPM2 ;
    __IO uint32_t  CCAPM3 ;
    __IO uint32_t  CCAPM4 ;
    __IO uint32_t  RESERVED0 ;
    __IO uint32_t  RESERVED1 ;
    __IO uint32_t  RESERVED2	;
    __IO uint32_t  CCAP0L ;
    __IO uint32_t  CCAP0H ;
    __IO uint32_t  CCAP1L ;
    __IO uint32_t  CCAP1H ;
    __IO uint32_t  CCAP2L ;
    __IO uint32_t  CCAP2H ;
    __IO uint32_t  CCAP3L ;
    __IO uint32_t  CCAP3H ;
    __IO uint32_t  CCAP4L ;
    __IO uint32_t  CCAP4H ;
    __IO uint32_t  CCAPO  ;
    __IO uint32_t  POCR  ;
    __IO uint32_t  CCAP0  ;
    __IO uint32_t  CCAP1  ;
    __IO uint32_t  CCAP2  ;
    __IO uint32_t  CCAP3  ;
    __IO uint32_t  CCAP4  ;
} PCA_TypeDef;

/**
  * @} AWK_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t RLOAD;
    __IO uint32_t SR;
    __IO uint32_t INTCLR;
} AWK_TypeDef;


/**
  * @} CRC_TypeDef
  */
typedef struct
{
    __IO uint32_t RESERVED;
    __IO uint32_t RESULT;

} CRC_TypeDef;


/**
  * @} CLKTRIM_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t REFCON;
    __IO uint32_t REFCNT;
    __IO uint32_t CALCNT;
    __IO uint32_t IFR;
    __IO uint32_t ICLR;
    __IO uint32_t CALCON;
} CLKTRIM_TypeDef;
/**
  * @} OWIRE_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t NFCR;
    __IO uint32_t RSTCNT;
    __IO uint32_t PRESCNT;
    __IO uint32_t BITRATECNT;
    __IO uint32_t DRVCNT;
    __IO uint32_t RDSMPCNT;
    __IO uint32_t RECCNT;
    __IO uint32_t DATA;
    __IO uint32_t CMD;
    __IO uint32_t INTEN;
    __IO uint32_t SR;
    __IO uint32_t INTCLR;
} OWIRE_TypeDef;


/**
  * @} RTC_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t CLKCR;
    __IO uint32_t TIME;
    __IO uint32_t DATE;
    __IO uint32_t ALM1TIME;
    __IO uint32_t ALM1DATE;
    __IO uint32_t ALM2PRD;
    __IO uint32_t CLK_TRIM;
    __IO uint32_t ISR;
    __IO uint32_t INTCLR;
    __IO uint32_t WPR;
} RTC_TypeDef;


/**
  * @} RCC_TypeDef
  */
typedef struct
{
    __IO uint32_t HCLKDIV;
    __IO uint32_t PCLKDIV;
    __IO uint32_t HCLKEN;
    __IO uint32_t PCLKEN;
    __IO uint32_t MCOCR;
    __IO uint32_t RESERVED0;
    __IO uint32_t RSTCR;
    __IO uint32_t RSTSR;
    __IO uint32_t SYSCLKCR;
    __IO uint32_t SYSCLKSEL;
    __IO uint32_t HIRCCR;
    __IO uint32_t HXTCR;
    __IO uint32_t LIRCCR;
    __IO uint32_t LXTCR;
    __IO uint32_t IRQLATENCY;
    __IO uint32_t STICKCR;
    __IO uint32_t SWDIOCR;
    __IO uint32_t PERIRST;
    __IO uint32_t RTCRST;
    __IO uint32_t RESERVED1;
    __IO uint32_t RESERVED2;
    __IO uint32_t RESERVED3;
    __IO uint32_t RESERVED4;
    __IO uint32_t RESERVED5;
    __IO uint32_t UNLOCK;
} RCC_TypeDef;


/**
  * @} DEBUG_TypeDef
  */
typedef struct
{
    __IO uint32_t APBFZ;
} DEBUG_TypeDef;


/**
  * @} BEEPER_TypeDef
  */
typedef struct
{
    __IO uint32_t CSR;

} BEEPER_TypeDef;




/**
  * @} ADC_TypeDef
  */
typedef struct
{
    __IO uint32_t CR0;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t RESULT0;
    __IO uint32_t RESULT1;
    __IO uint32_t RESULT2;
    __IO uint32_t RESULT3;
    __IO uint32_t RESULT4;
    __IO uint32_t RESULT5;
    __IO uint32_t RESULT6;
    __IO uint32_t RESULT7;
    __IO uint32_t RESULT;
    __IO uint32_t RESULTACC;
    __IO uint32_t HT;
    __IO uint32_t LT;
    __IO uint32_t RESERVED0;
    __IO uint32_t RESERVED1;
    __IO uint32_t INTEN;
    __IO uint32_t INTCLR;
    __IO uint32_t RAWINTSR;
    __IO uint32_t MSKINTSR;
} ADC_TypeDef;


/**
  * @} FLASH_TypeDef
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t IFR;
    __IO uint32_t ICLR;
    __IO uint32_t BYPASS;
    __IO uint32_t SLOCK0;
    __IO uint32_t SLOCK1;
    __IO uint32_t ISPCON;
} FLASH_TypeDef;

/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           BASE ADDRESS DEFINE, DEFINE ALL MODE.....                                               */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#define PERIPH_BASE     ((uint32_t)0x40000000) /*!< Peripheral base address in the alias region */
#define	RTC_BASE		    (PERIPH_BASE + 0x00003000)
#define SYSCON_BASE     (PERIPH_BASE + 0x00001C00)
#define	WWDG_BASE		    (PERIPH_BASE + 0x00002000)
#define	IWDG_BASE		    (PERIPH_BASE + 0x00002400)
#define	UART0_BASE		  (PERIPH_BASE + 0x00000000)
#define	UART1_BASE		  (PERIPH_BASE + 0x00000400)
#define SPI_BASE        (PERIPH_BASE + 0x00000800)
#define	I2C_BASE		    (PERIPH_BASE + 0x00000C00)
#define PCA_BASE        (PERIPH_BASE + 0x00001400)
#define TIM10_BASE	    (PERIPH_BASE + 0x00001800)
#define TIM11_BASE	    (PERIPH_BASE + 0x00001900)
#define TIM1_BASE		    (PERIPH_BASE + 0x00001000)	//Advanced timer (pwm function)	
#define TIM2_BASE		    (PERIPH_BASE + 0x00003C00)	//Advanced timer	
#define AWK_BASE	      (PERIPH_BASE + 0x00002800)
#define CLKTRIM_BASE    (PERIPH_BASE + 0x00003400)
#define	GPIOA_BASE		  (PERIPH_BASE + 0x00021000)
#define	GPIOB_BASE		  (PERIPH_BASE + 0x00021400)
#define	GPIOC_BASE		  (PERIPH_BASE + 0x00021800)
#define	GPIOD_BASE		  (PERIPH_BASE + 0x00021C00)
#define OWIRE_BASE		  (PERIPH_BASE + 0x00003800)
#define CRC_BASE        (PERIPH_BASE + 0x00020800)
#define RCC_BASE        (PERIPH_BASE + 0x00020000)
#define BEEPER_BASE     (PERIPH_BASE + 0x00004800)
#define LPTIM_BASE      (PERIPH_BASE + 0x00004400)
#define LPUART_BASE     (PERIPH_BASE + 0x00005000)
#define LVD_BASE        (PERIPH_BASE + 0x00004000)
#define VC_BASE         (PERIPH_BASE + 0x00004080)
#define DEBUG_BASE      (PERIPH_BASE + 0x00004C00)
#define ADC_BASE        (PERIPH_BASE + 0x00002C00)
#define FLASH_BASE      (PERIPH_BASE + 0x00020400)

#define FLASH_MEMORY_BASE           0x00000000UL 		/*!< FLASH(up to 64 KB) base address in the alias region  */
#define SRAM_MEMORY_BASE            0x20000000UL 		/*!< SRAM1(4 KB) base address in the alias region         */
#define UID_BASE                    0x180000F0UL    /*!< Unique device ID register base address 							*/
/*------------------------------------------------------------------------------------------------*/
/*                                                                                                */
/*           BASE ADDRESS DEFINE, DEFINE ALL MODE......                                           */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
#define I2C                 ((I2C_TypeDef *)  I2C_BASE)
#define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *) GPIOD_BASE)
#define UART0               ((UART_TypeDef *) UART0_BASE)
#define UART1               ((UART_TypeDef *) UART1_BASE)
#define SPI                 ((SPI_TypeDef *)  SPI_BASE)
#define TIM1							  ((ADVTIM_TypeDef *) TIM1_BASE)
#define TIM2							  ((ADVTIM_TypeDef *) TIM2_BASE)
#define IWDG                ((IWDG_TypeDef *)IWDG_BASE)
#define WWDG                ((WWDG_TypeDef *)WWDG_BASE)
#define PCA                 ((PCA_TypeDef *)PCA_BASE)
#define AWK                 ((AWK_TypeDef *)AWK_BASE)
#define CRC                 ((CRC_TypeDef *)CRC_BASE)
#define CLKTRIM             ((CLKTRIM_TypeDef *)CLKTRIM_BASE)
#define OWIRE               ((OWIRE_TypeDef *)OWIRE_BASE)
#define RTC                 ((RTC_TypeDef *)RTC_BASE)
#define RCC                 ((RCC_TypeDef *)RCC_BASE)
#define TIM10               ((TIM_TypeDef *)TIM10_BASE)
#define TIM11               ((TIM_TypeDef *)TIM11_BASE)
#define BEEPER              ((BEEPER_TypeDef *)BEEPER_BASE)
#define SYSCTRL             ((SYSCON_TypeDef *)SYSCON_BASE)
#define LPTIM               ((LPTIMER_TypeDef *)LPTIM_BASE)
#define LVD                 ((LVD_TypeDef *)LVD_BASE)
#define VC                  ((VC_TypeDef *)VC_BASE)
#define LPUART              ((LPUART_TypeDef *)LPUART_BASE)
#define DEBUG               ((DEBUG_TypeDef *)DEBUG_BASE)
#define ADC                 ((ADC_TypeDef *)ADC_BASE)
#define FLASH               ((FLASH_TypeDef *)FLASH_BASE)


/******************************************************************************/
/*                                                                            */
/*                                    TIM                                     */
/*                                                                            */
/******************************************************************************/

///*******************  Bit definition for TIM_CR1 register  ********************/
#define  TIM_CR1_CEN                         ((uint16_t)0x0001)            /*!< Counter enable */
#define  TIM_CR1_UDIS                        ((uint16_t)0x0002)            /*!< Update disable */
#define  TIM_CR1_URS                         ((uint16_t)0x0004)            /*!< Update request source */
#define  TIM_CR1_OPM                         ((uint16_t)0x0008)            /*!< One pulse mode */
#define  TIM_CR1_DIR                         ((uint16_t)0x0010)            /*!< Direction */
#define  TIM_CR1_CMS                         ((uint16_t)0x0060)            /*!< CMS[1:0] bits (Center-aligned mode selection) */
#define  TIM_CR1_CMS_0                       ((uint16_t)0x0020)            /*!< Bit 0 */
#define  TIM_CR1_CMS_1                       ((uint16_t)0x0040)            /*!< Bit 1 */
#define  TIM_CR1_ARPE                        ((uint16_t)0x0080)            /*!< Auto-reload preload enable */
#define  TIM_CR1_CKD                         ((uint16_t)0x0300)            /*!< CKD[1:0] bits (clock division) */
#define  TIM_CR1_CKD_0                       ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_CR1_CKD_1                       ((uint16_t)0x0200)            /*!< Bit 1 */

/*******************  Bit definition for TIM_CR2 register  ********************/
#define  TIM_CR2_CCPC                        ((uint16_t)0x0001)            /*!< Capture/Compare Preloaded Control */
#define  TIM_CR2_CCUS                        ((uint16_t)0x0004)            /*!< Capture/Compare Control Update Selection */
#define  TIM_CR2_CCDS                        ((uint16_t)0x0008)            /*!< Capture/Compare DMA Selection */
#define  TIM_CR2_MMS                         ((uint16_t)0x0070)            /*!< MMS[2:0] bits (Master Mode Selection) */
#define  TIM_CR2_MMS_0                       ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CR2_MMS_1                       ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CR2_MMS_2                       ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CR2_TI1S                        ((uint16_t)0x0080)            /*!< TI1 Selection */
#define  TIM_CR2_OIS1                        ((uint16_t)0x0100)            /*!< Output Idle state 1 (OC1 output) */
#define  TIM_CR2_OIS1N                       ((uint16_t)0x0200)            /*!< Output Idle state 1 (OC1N output) */
#define  TIM_CR2_OIS2                        ((uint16_t)0x0400)            /*!< Output Idle state 2 (OC2 output) */
#define  TIM_CR2_OIS2N                       ((uint16_t)0x0800)            /*!< Output Idle state 2 (OC2N output) */
#define  TIM_CR2_OIS3                        ((uint16_t)0x1000)            /*!< Output Idle state 3 (OC3 output) */
#define  TIM_CR2_OIS3N                       ((uint16_t)0x2000)            /*!< Output Idle state 3 (OC3N output) */
#define  TIM_CR2_OIS4                        ((uint16_t)0x4000)            /*!< Output Idle state 4 (OC4 output) */

/*******************  Bit definition for TIM_SMCR register  *******************/
#define  TIM_SMCR_SMS                        ((uint16_t)0x0007)            /*!< SMS[2:0] bits (Slave mode selection) */
#define  TIM_SMCR_SMS_0                      ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_SMCR_SMS_1                      ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_SMCR_SMS_2                      ((uint16_t)0x0004)            /*!< Bit 2 */
#define  TIM_SMCR_TS                         ((uint16_t)0x0070)            /*!< TS[2:0] bits (Trigger selection) */
#define  TIM_SMCR_TS_0                       ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_SMCR_TS_1                       ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_SMCR_TS_2                       ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_SMCR_MSM                        ((uint16_t)0x0080)            /*!< Master/slave mode */
#define  TIM_SMCR_ETF                        ((uint16_t)0x0F00)            /*!< ETF[3:0] bits (External trigger filter) */
#define  TIM_SMCR_ETF_0                      ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_SMCR_ETF_1                      ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TIM_SMCR_ETF_2                      ((uint16_t)0x0400)            /*!< Bit 2 */
#define  TIM_SMCR_ETF_3                      ((uint16_t)0x0800)            /*!< Bit 3 */
#define  TIM_SMCR_ETPS                       ((uint16_t)0x3000)            /*!< ETPS[1:0] bits (External trigger prescaler) */
#define  TIM_SMCR_ETPS_0                     ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_SMCR_ETPS_1                     ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_SMCR_ECE                        ((uint16_t)0x4000)            /*!< External clock enable */
#define  TIM_SMCR_ETP                        ((uint16_t)0x8000)            /*!< External trigger polarity */

/*******************  Bit definition for TIM_DIER register  *******************/
#define  TIM_DIER_UIE                        ((uint16_t)0x0001)            /*!< Update interrupt enable */
#define  TIM_DIER_CC1IE                      ((uint16_t)0x0002)            /*!< Capture/Compare 1 interrupt enable */
#define  TIM_DIER_CC2IE                      ((uint16_t)0x0004)            /*!< Capture/Compare 2 interrupt enable */
#define  TIM_DIER_CC3IE                      ((uint16_t)0x0008)            /*!< Capture/Compare 3 interrupt enable */
#define  TIM_DIER_CC4IE                      ((uint16_t)0x0010)            /*!< Capture/Compare 4 interrupt enable */
#define  TIM_DIER_COMIE                      ((uint16_t)0x0020)            /*!< COM interrupt enable */
#define  TIM_DIER_TIE                        ((uint16_t)0x0040)            /*!< Trigger interrupt enable */
#define  TIM_DIER_BIE                        ((uint16_t)0x0080)            /*!< Break interrupt enable */
#define  TIM_DIER_UDE                        ((uint16_t)0x0100)            /*!< Update DMA request enable */
#define  TIM_DIER_CC1DE                      ((uint16_t)0x0200)            /*!< Capture/Compare 1 DMA request enable */
#define  TIM_DIER_CC2DE                      ((uint16_t)0x0400)            /*!< Capture/Compare 2 DMA request enable */
#define  TIM_DIER_CC3DE                      ((uint16_t)0x0800)            /*!< Capture/Compare 3 DMA request enable */
#define  TIM_DIER_CC4DE                      ((uint16_t)0x1000)            /*!< Capture/Compare 4 DMA request enable */
#define  TIM_DIER_COMDE                      ((uint16_t)0x2000)            /*!< COM DMA request enable */
#define  TIM_DIER_TDE                        ((uint16_t)0x4000)            /*!< Trigger DMA request enable */

/********************  Bit definition for TIM_SR register  ********************/
#define  TIM_SR_UIF                          ((uint16_t)0x0001)            /*!< Update interrupt Flag */
#define  TIM_SR_CC1IF                        ((uint16_t)0x0002)            /*!< Capture/Compare 1 interrupt Flag */
#define  TIM_SR_CC2IF                        ((uint16_t)0x0004)            /*!< Capture/Compare 2 interrupt Flag */
#define  TIM_SR_CC3IF                        ((uint16_t)0x0008)            /*!< Capture/Compare 3 interrupt Flag */
#define  TIM_SR_CC4IF                        ((uint16_t)0x0010)            /*!< Capture/Compare 4 interrupt Flag */
#define  TIM_SR_COMIF                        ((uint16_t)0x0020)            /*!< COM interrupt Flag */
#define  TIM_SR_TIF                          ((uint16_t)0x0040)            /*!< Trigger interrupt Flag */
#define  TIM_SR_BIF                          ((uint16_t)0x0080)            /*!< Break interrupt Flag */
#define  TIM_SR_CC1OF                        ((uint16_t)0x0200)            /*!< Capture/Compare 1 Overcapture Flag */
#define  TIM_SR_CC2OF                        ((uint16_t)0x0400)            /*!< Capture/Compare 2 Overcapture Flag */
#define  TIM_SR_CC3OF                        ((uint16_t)0x0800)            /*!< Capture/Compare 3 Overcapture Flag */
#define  TIM_SR_CC4OF                        ((uint16_t)0x1000)            /*!< Capture/Compare 4 Overcapture Flag */

/*******************  Bit definition for TIM_EGR register  ********************/
#define  TIM_EGR_UG                          ((uint8_t)0x01)               /*!< Update Generation */
#define  TIM_EGR_CC1G                        ((uint8_t)0x02)               /*!< Capture/Compare 1 Generation */
#define  TIM_EGR_CC2G                        ((uint8_t)0x04)               /*!< Capture/Compare 2 Generation */
#define  TIM_EGR_CC3G                        ((uint8_t)0x08)               /*!< Capture/Compare 3 Generation */
#define  TIM_EGR_CC4G                        ((uint8_t)0x10)               /*!< Capture/Compare 4 Generation */
#define  TIM_EGR_COMG                        ((uint8_t)0x20)               /*!< Capture/Compare Control Update Generation */
#define  TIM_EGR_TG                          ((uint8_t)0x40)               /*!< Trigger Generation */
#define  TIM_EGR_BG                          ((uint8_t)0x80)               /*!< Break Generation */

/******************  Bit definition for TIM_CCMR1 register  *******************/
#define  TIM_CCMR1_CC1S                      ((uint16_t)0x0003)            /*!< CC1S[1:0] bits (Capture/Compare 1 Selection) */
#define  TIM_CCMR1_CC1S_0                    ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_CCMR1_CC1S_1                    ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_CCMR1_OC1FE                     ((uint16_t)0x0004)            /*!< Output Compare 1 Fast enable */
#define  TIM_CCMR1_OC1PE                     ((uint16_t)0x0008)            /*!< Output Compare 1 Preload enable */
#define  TIM_CCMR1_OC1M                      ((uint16_t)0x0070)            /*!< OC1M[2:0] bits (Output Compare 1 Mode) */
#define  TIM_CCMR1_OC1M_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR1_OC1M_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR1_OC1M_2                    ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CCMR1_OC1CE                     ((uint16_t)0x0080)            /*!< Output Compare 1Clear Enable */
#define  TIM_CCMR1_CC2S                      ((uint16_t)0x0300)            /*!< CC2S[1:0] bits (Capture/Compare 2 Selection) */
#define  TIM_CCMR1_CC2S_0                    ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_CCMR1_CC2S_1                    ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TIM_CCMR1_OC2FE                     ((uint16_t)0x0400)            /*!< Output Compare 2 Fast enable */
#define  TIM_CCMR1_OC2PE                     ((uint16_t)0x0800)            /*!< Output Compare 2 Preload enable */
#define  TIM_CCMR1_OC2M                      ((uint16_t)0x7000)            /*!< OC2M[2:0] bits (Output Compare 2 Mode) */
#define  TIM_CCMR1_OC2M_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR1_OC2M_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR1_OC2M_2                    ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TIM_CCMR1_OC2CE                     ((uint16_t)0x8000)            /*!< Output Compare 2 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR1_IC1PSC                    ((uint16_t)0x000C)            /*!< IC1PSC[1:0] bits (Input Capture 1 Prescaler) */
#define  TIM_CCMR1_IC1PSC_0                  ((uint16_t)0x0004)            /*!< Bit 0 */
#define  TIM_CCMR1_IC1PSC_1                  ((uint16_t)0x0008)            /*!< Bit 1 */
#define  TIM_CCMR1_IC1F                      ((uint16_t)0x00F0)            /*!< IC1F[3:0] bits (Input Capture 1 Filter) */
#define  TIM_CCMR1_IC1F_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR1_IC1F_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR1_IC1F_2                    ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CCMR1_IC1F_3                    ((uint16_t)0x0080)            /*!< Bit 3 */
#define  TIM_CCMR1_IC2PSC                    ((uint16_t)0x0C00)            /*!< IC2PSC[1:0] bits (Input Capture 2 Prescaler) */
#define  TIM_CCMR1_IC2PSC_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  TIM_CCMR1_IC2PSC_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  TIM_CCMR1_IC2F                      ((uint16_t)0xF000)            /*!< IC2F[3:0] bits (Input Capture 2 Filter) */
#define  TIM_CCMR1_IC2F_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR1_IC2F_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR1_IC2F_2                    ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TIM_CCMR1_IC2F_3                    ((uint16_t)0x8000)            /*!< Bit 3 */

/******************  Bit definition for TIM_CCMR2 register  *******************/
#define  TIM_CCMR2_CC3S                      ((uint16_t)0x0003)            /*!< CC3S[1:0] bits (Capture/Compare 3 Selection) */
#define  TIM_CCMR2_CC3S_0                    ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_CCMR2_CC3S_1                    ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_CCMR2_OC3FE                     ((uint16_t)0x0004)            /*!< Output Compare 3 Fast enable */
#define  TIM_CCMR2_OC3PE                     ((uint16_t)0x0008)            /*!< Output Compare 3 Preload enable */
#define  TIM_CCMR2_OC3M                      ((uint16_t)0x0070)            /*!< OC3M[2:0] bits (Output Compare 3 Mode) */
#define  TIM_CCMR2_OC3M_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR2_OC3M_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR2_OC3M_2                    ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CCMR2_OC3CE                     ((uint16_t)0x0080)            /*!< Output Compare 3 Clear Enable */
#define  TIM_CCMR2_CC4S                      ((uint16_t)0x0300)            /*!< CC4S[1:0] bits (Capture/Compare 4 Selection) */
#define  TIM_CCMR2_CC4S_0                    ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_CCMR2_CC4S_1                    ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TIM_CCMR2_OC4FE                     ((uint16_t)0x0400)            /*!< Output Compare 4 Fast enable */
#define  TIM_CCMR2_OC4PE                     ((uint16_t)0x0800)            /*!< Output Compare 4 Preload enable */
#define  TIM_CCMR2_OC4M                      ((uint16_t)0x7000)            /*!< OC4M[2:0] bits (Output Compare 4 Mode) */
#define  TIM_CCMR2_OC4M_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR2_OC4M_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR2_OC4M_2                    ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TIM_CCMR2_OC4CE                     ((uint16_t)0x8000)            /*!< Output Compare 4 Clear Enable */

/*----------------------------------------------------------------------------*/

#define  TIM_CCMR2_IC3PSC                    ((uint16_t)0x000C)            /*!< IC3PSC[1:0] bits (Input Capture 3 Prescaler) */
#define  TIM_CCMR2_IC3PSC_0                  ((uint16_t)0x0004)            /*!< Bit 0 */
#define  TIM_CCMR2_IC3PSC_1                  ((uint16_t)0x0008)            /*!< Bit 1 */
#define  TIM_CCMR2_IC3F                      ((uint16_t)0x00F0)            /*!< IC3F[3:0] bits (Input Capture 3 Filter) */
#define  TIM_CCMR2_IC3F_0                    ((uint16_t)0x0010)            /*!< Bit 0 */
#define  TIM_CCMR2_IC3F_1                    ((uint16_t)0x0020)            /*!< Bit 1 */
#define  TIM_CCMR2_IC3F_2                    ((uint16_t)0x0040)            /*!< Bit 2 */
#define  TIM_CCMR2_IC3F_3                    ((uint16_t)0x0080)            /*!< Bit 3 */
#define  TIM_CCMR2_IC4PSC                    ((uint16_t)0x0C00)            /*!< IC4PSC[1:0] bits (Input Capture 4 Prescaler) */
#define  TIM_CCMR2_IC4PSC_0                  ((uint16_t)0x0400)            /*!< Bit 0 */
#define  TIM_CCMR2_IC4PSC_1                  ((uint16_t)0x0800)            /*!< Bit 1 */
#define  TIM_CCMR2_IC4F                      ((uint16_t)0xF000)            /*!< IC4F[3:0] bits (Input Capture 4 Filter) */
#define  TIM_CCMR2_IC4F_0                    ((uint16_t)0x1000)            /*!< Bit 0 */
#define  TIM_CCMR2_IC4F_1                    ((uint16_t)0x2000)            /*!< Bit 1 */
#define  TIM_CCMR2_IC4F_2                    ((uint16_t)0x4000)            /*!< Bit 2 */
#define  TIM_CCMR2_IC4F_3                    ((uint16_t)0x8000)            /*!< Bit 3 */

/*******************  Bit definition for TIM_CCER register  *******************/
#define  TIM_CCER_CC1E                       ((uint16_t)0x0001)            /*!< Capture/Compare 1 output enable */
#define  TIM_CCER_CC1P                       ((uint16_t)0x0002)            /*!< Capture/Compare 1 output Polarity */
#define  TIM_CCER_CC1NE                      ((uint16_t)0x0004)            /*!< Capture/Compare 1 Complementary output enable */
#define  TIM_CCER_CC1NP                      ((uint16_t)0x0008)            /*!< Capture/Compare 1 Complementary output Polarity */
#define  TIM_CCER_CC2E                       ((uint16_t)0x0010)            /*!< Capture/Compare 2 output enable */
#define  TIM_CCER_CC2P                       ((uint16_t)0x0020)            /*!< Capture/Compare 2 output Polarity */
#define  TIM_CCER_CC2NE                      ((uint16_t)0x0040)            /*!< Capture/Compare 2 Complementary output enable */
#define  TIM_CCER_CC2NP                      ((uint16_t)0x0080)            /*!< Capture/Compare 2 Complementary output Polarity */
#define  TIM_CCER_CC3E                       ((uint16_t)0x0100)            /*!< Capture/Compare 3 output enable */
#define  TIM_CCER_CC3P                       ((uint16_t)0x0200)            /*!< Capture/Compare 3 output Polarity */
#define  TIM_CCER_CC3NE                      ((uint16_t)0x0400)            /*!< Capture/Compare 3 Complementary output enable */
#define  TIM_CCER_CC3NP                      ((uint16_t)0x0800)            /*!< Capture/Compare 3 Complementary output Polarity */
#define  TIM_CCER_CC4E                       ((uint16_t)0x1000)            /*!< Capture/Compare 4 output enable */
#define  TIM_CCER_CC4P                       ((uint16_t)0x2000)            /*!< Capture/Compare 4 output Polarity */
#define  TIM_CCER_CC4NP                      ((uint16_t)0x8000)            /*!< Capture/Compare 4 Complementary output Polarity */


/*******************  Bit definition for TIM_BDTR register  *******************/
#define  TIM_BDTR_DTG                        ((uint16_t)0x00FF)            /*!< DTG[0:7] bits (Dead-Time Generator set-up) */
#define  TIM_BDTR_DTG_0                      ((uint16_t)0x0001)            /*!< Bit 0 */
#define  TIM_BDTR_DTG_1                      ((uint16_t)0x0002)            /*!< Bit 1 */
#define  TIM_BDTR_DTG_2                      ((uint16_t)0x0004)            /*!< Bit 2 */
#define  TIM_BDTR_DTG_3                      ((uint16_t)0x0008)            /*!< Bit 3 */
#define  TIM_BDTR_DTG_4                      ((uint16_t)0x0010)            /*!< Bit 4 */
#define  TIM_BDTR_DTG_5                      ((uint16_t)0x0020)            /*!< Bit 5 */
#define  TIM_BDTR_DTG_6                      ((uint16_t)0x0040)            /*!< Bit 6 */
#define  TIM_BDTR_DTG_7                      ((uint16_t)0x0080)            /*!< Bit 7 */
#define  TIM_BDTR_LOCK                       ((uint16_t)0x0300)            /*!< LOCK[1:0] bits (Lock Configuration) */
#define  TIM_BDTR_LOCK_0                     ((uint16_t)0x0100)            /*!< Bit 0 */
#define  TIM_BDTR_LOCK_1                     ((uint16_t)0x0200)            /*!< Bit 1 */
#define  TIM_BDTR_OSSI                       ((uint16_t)0x0400)            /*!< Off-State Selection for Idle mode */
#define  TIM_BDTR_OSSR                       ((uint16_t)0x0800)            /*!< Off-State Selection for Run mode */
#define  TIM_BDTR_BKE                        ((uint16_t)0x1000)            /*!< Break enable */
#define  TIM_BDTR_BKP                        ((uint16_t)0x2000)            /*!< Break Polarity */
#define  TIM_BDTR_AOE                        ((uint16_t)0x4000)            /*!< Automatic Output enable */
#define  TIM_BDTR_MOE                        ((uint16_t)0x8000)            /*!< Main Output enable */

/**
  * @}
  */
extern void (*SysTick_Callback)(void);

#ifdef __cplusplus
}
#endif

#endif /* __AC1003_H */

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
