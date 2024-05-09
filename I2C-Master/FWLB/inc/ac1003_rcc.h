/**
  ******************************************************************************
  * @file    ac1003_rcc.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    16-JULY-2018
  * @brief   This file contains all the functions prototypes for the RCC firmware
  *          library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_RCC_H
#define __AC1003_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"

/** @defgroup RCC_ClocksTypeDef
  * @{
  */
typedef struct
{
    uint32_t SYSCLK_Frequency;  /*!< returns SYSCLK clock frequency expressed in Hz */
    uint32_t HCLK_Frequency;    /*!< returns HCLK clock frequency expressed in Hz */
    uint32_t PCLK_Frequency;   /*!< returns PCLK1 clock frequency expressed in Hz */
    uint32_t ADCCLK_Frequency;  /*!< returns ADCCLK clock frequency expressed in Hz */
} RCC_ClocksTypeDef;


/** @defgroup RCC_ClocksTypeDef
  * @{
  */
typedef struct
{
    uint32_t LXPORT;   /*!< returns SYSCLK clock frequency expressed in Hz */
    uint32_t LXAON;    /*!< returns HCLK clock frequency expressed in Hz */
    uint32_t LXTBYP;   /*!< returns PCLK1 clock frequency expressed in Hz */
    uint32_t LXTEN;    /*!< returns ADCCLK clock frequency expressed in Hz */
    uint32_t LXTSTARTUP;
    uint32_t LXTDIV;
} LXT_InitTypeDef;



/* Exported types ------------------------------------------------------------*/
#define IS_RCC_ALL_PERIPH(PERIPH) ((PERIPH) == RCC)


/** @defgroup RCC_CLK_KEY
  * @{
  */
#define  RCC_CLK_KEYMASK          (uint32_t)0xffff0000
#define  RCC_CLKCONKEY            (uint32_t)0x5A690000
#define  RCC_LXTCLK_KEY           (uint32_t)0x5A690000
#define  RCC_HIRCCLK_KEY          (uint32_t)0x5A690000
#define  RCC_HXTCLK_KEY           (uint32_t)0x5A690000
#define  RCC_LIRCCLK_KEY          (uint32_t)0x5A690000
#define  RCC_SYSCLKSEL_KEY        (uint32_t)0x5A690000
#define  RCC_REGLOCKKEY           (uint32_t)0x55aa6699
#define  RCC_RESGLOCKKEY          (uint32_t)0x55aa6698
#define  RCC_APBPeriph_RTCRSTKEY  (uint32_t)0x5A690000
#define  RCC_RSTKEY               (uint32_t)0x55AA6698




/** @defgroup AHBCLKEN_configuration
  * @{
  */
#define  RCC_AHB_CLKMASK          (uint32_t)0x0000001F
#define  RCC_APB_CLKMASK          (uint32_t)0x001FFFFF

#define  RCC_HICR_TRIMMASK        (uint32_t)0x0000E0000


/** @defgroup System_clock_source
  * @{
  */
#define  RCC_SYSCLKSource_HIRC     (uint32_t)0x00000001
#define  RCC_SYSCLKSource_HXT      (uint32_t)0x00000002
#define  RCC_SYSCLKSource_LIRC     (uint32_t)0x00000004
#define  RCC_SYSCLKSource_LXT      (uint32_t)0x00000008

#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HIRC)||\
                                      ((SOURCE) == RCC_SYSCLKSource_HXT) ||\
                                      ((SOURCE) == RCC_SYSCLKSource_LIRC)||\
																			((SOURCE) == RCC_SYSCLKSource_LXRC))


/** @defgroup System_clock_source
  * @{
  */
#define  RCC_SYSCLKSource_HIRC_EN      (uint32_t)0x00000001
#define  RCC_SYSCLKSource_HXT_EN       (uint32_t)0x00000002
#define  RCC_SYSCLKSource_LIRC_EN      (uint32_t)0x00000004
#define  RCC_SYSCLKSource_LXT_EN       (uint32_t)0x00000100
#define  RCC_SYSCLKSource_EN_MASK      (uint32_t)0x0000000f
#define  RCC_LXTCLKSource_EN_MASK      (uint32_t)0x00000100



/** @defgroup AHB_clock_source
  * @{
  */
#define IS_RCC_SYSCLK_DIV(SYSHCLK)  ((SYSHCLK>= (uint32_t)0x00000000) ||\
                                     (SYSHCLK<= (uint32_t)0x000000ff))

#define IS_RCC_HCLK_DIV(SYSPCLK)    ((SYSPCLK>= (uint32_t)0x00000000) ||\
                                     (SYSPCLK<= (uint32_t)0x000000ff))

#define IS_RCC_FCLK_DIV(SYSPCLK)    ((SYSPCLK>= (uint32_t)0x00000000) ||\
                                     (SYSPCLK<= (uint32_t)0x000000ff))

#define RCC_FCLK_DIV_MASK            (uint32_t)0x000000ff

/** @defgroup AHB_clock_source
  * @{
  */
#define RCC_SYSCLKOSEL_HIRC            (uint32_t)0x00000000
#define RCC_SYSCLKOSEL_EXT             (uint32_t)0x00000100
#define RCC_SYSCLKOSEL_LIRC            (uint32_t)0x00000200
#define RCC_SYSCLKOSEL_LXT             (uint32_t)0x00000300
#define RCC_SYSCLKOSEL_SYS             (uint32_t)0x00000400
#define RCC_SYSCLKOSEL_FCLK            (uint32_t)0x00000500
#define RCC_SYSCLKOSEL_MASK            (uint32_t)0x00000700

#define IS_RCC_SYSCLKOSEL_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKOSEL_HIRC)||\
																					((SOURCE) == RCC_SYSCLKOSEL_EXT) ||\
																					((SOURCE) == RCC_SYSCLKOSEL_LIRC)||\
																					((SOURCE) == RCC_SYSCLKOSEL_LXT) ||\
																					((SOURCE) == RCC_SYSCLKOSEL_SYS) ||\
																					((SOURCE) == RCC_SYSCLKOSEL_FCLK))


#define  RCC_SYSCLKOUTPUT_ENABLE   (uint32_t)0x00001000

/** @defgroup AHB_peripheral_CLK
  * @{
  */
#define RCC_AHBPeriph_GPIOAEN                (uint32_t)0x00000001
#define RCC_AHBPeriph_GPIOBEN                (uint32_t)0x00000002
#define RCC_AHBPeriph_GPIOCEN                (uint32_t)0x00000004
#define RCC_AHBPeriph_GPIODEN                (uint32_t)0x00000008
#define RCC_AHBPeriph_CRCEN                  (uint32_t)0x00000010
#define RCC_AHBPeriph_FLASHEN                (uint32_t)0x00000100
#define IS_RCC_AHB_PERIPH(PERIPH) ((PERIPH == RCC_AHBPeriph_GPIOAEN)||\
																	 (PERIPH == RCC_AHBPeriph_GPIOBEN)||\
																	 (PERIPH == RCC_AHBPeriph_GPIOCEN)||\
																	 (PERIPH == RCC_AHBPeriph_GPIODEN)||\
																	 (PERIPH == RCC_AHBPeriph_CRCEN) ||\
																	 (PERIPH == RCC_AHBPeriph_FLASHEN) )










/** @defgroup APB_peripheral_CLKEN
  * @{
  */
#define RCC_APBPeriph_UART0CKEN              ((uint32_t)0x00000001)
#define RCC_APBPeriph_UART1CKEN              ((uint32_t)0x00000002)
#define RCC_APBPeriph_I2CCKEN                ((uint32_t)0x00000004)
#define RCC_APBPeriph_LPUARTCKEN             ((uint32_t)0x00000008)
#define RCC_APBPeriph_SPICKEN                ((uint32_t)0x00000010)
#define RCC_APBPeriph_LPTIMCKEN              ((uint32_t)0x00000020)
#define RCC_APBPeriph_BASETIMCKEN            ((uint32_t)0x00000040)
#define RCC_APBPeriph_SYSCONCKEN             ((uint32_t)0x00000080)
#define RCC_APBPeriph_PCACKEN                ((uint32_t)0x00000100)
#define RCC_APBPeriph_ONEWIRECKEN            ((uint32_t)0x00000200)
#define RCC_APBPeriph_TIM1CKEN               ((uint32_t)0x00000400)
#define RCC_APBPeriph_TIM2CKEN               ((uint32_t)0x00000800)
#define RCC_APBPeriph_WWDTCKEN               ((uint32_t)0x00001000)
#define RCC_APBPeriph_ADCCKEN                ((uint32_t)0x00002000)
#define RCC_APBPeriph_AWKCKEN                ((uint32_t)0x00004000)
#define RCC_APBPeriph_RTCCKEN                ((uint32_t)0x00008000)
#define RCC_APBPeriph_CLKTRIMCKEN            ((uint32_t)0x00010000)
#define RCC_APBPeriph_IWDGCKEN               ((uint32_t)0x00020000)
#define RCC_APBPeriph_LVDVCCKEN              ((uint32_t)0x00040000)
#define RCC_APBPeriph_BEEPCKEN               ((uint32_t)0x00080000)
#define RCC_APBPeriph_DBGCKEN                ((uint32_t)0x00100000)
#define IS_RCC_APB_PERIPH(PERIPH) ((((PERIPH) & 0xFFE00000) == 0x00000000) &&\
                                                  ((PERIPH) != 0x00000000))


/** @defgroup APB_peripheral
  * @{
  */
#define RCC_APBPeriph_UART0RST               ((uint32_t)0x00000001)
#define RCC_APBPeriph_UART1RST               ((uint32_t)0x00000002)
#define RCC_APBPeriph_I2CRST                 ((uint32_t)0x00000004)
#define RCC_APBPeriph_LPUARTRST              ((uint32_t)0x00000008)
#define RCC_APBPeriph_SPIRST                 ((uint32_t)0x00000010)
#define RCC_APBPeriph_LPTIMRST               ((uint32_t)0x00000020)
#define RCC_APBPeriph_BASETIMRST             ((uint32_t)0x00000040)
#define RCC_APBPeriph_SYSCONRST              ((uint32_t)0x00000080)
#define RCC_APBPeriph_PCARST                 ((uint32_t)0x00000100)
#define RCC_APBPeriph_ONEWIRERST             ((uint32_t)0x00000200)
#define RCC_APBPeriph_TIM1RST                ((uint32_t)0x00000400)
#define RCC_APBPeriph_TIM2RST                ((uint32_t)0x00000800)
#define RCC_APBPeriph_WWDTRST                ((uint32_t)0x00001000)
#define RCC_APBPeriph_ADCRST                 ((uint32_t)0x00002000)
#define RCC_APBPeriph_AWKRST                 ((uint32_t)0x00004000)
#define RCC_APBPeriph_TRIMRST                ((uint32_t)0x00010000)
#define RCC_APBPeriph_LVDVCRST               ((uint32_t)0x00040000)
#define RCC_APBPeriph_BEEPRST                ((uint32_t)0x00080000)
#define RCC_APBPeriph_MCUDBGRST              ((uint32_t)0x00100000)

/** @defgroup AHB_peripheral
  * @{
  */
#define RCC_AHBPeriph_GPIOARST               ((uint32_t)0x01000000)
#define RCC_AHBPeriph_GPIOBRST               ((uint32_t)0x02000000)
#define RCC_AHBPeriph_GPIOCRST               ((uint32_t)0x04000000)
#define RCC_AHBPeriph_GPIODRST               ((uint32_t)0x08000000)
#define RCC_AHBPeriph_CRCRST                 ((uint32_t)0x10000000)
#define IS_RCC_PERIPHRST(PERIPH)  ((((PERIPH) & 0x1f1d7fff) == PERIPH) && \
                                                   ((PERIPH) != 0x00))


#define RCC_RTCPeriph_RSTEABLE       ((uint32_t)0x00000001)
#define RCC_RTCPeriph_RSTDISABLE     ((uint32_t)0x00000000)



/** @defgroup RST MODEL
  * @{
  */
#define RCC_MCURST       (uint32_t)0x00000001
#define RCC_CPURST       (uint32_t)0x00000002
#define IS_RCC_RST(RST)  ((RST== RCC_MCURST)||(RST == RCC_CPURST))



/** @defgroup GET RCC RESET FLAG
  * @{
  */
#define RCC_FLAG_MCURST       ((uint32_t)0x00000001)
#define RCC_FLAG_CPURST       ((uint32_t)0x00000002)
#define RCC_FLAG_WWDTRST      ((uint32_t)0x00000004)
#define RCC_FLAG_IWDTRST      ((uint32_t)0x00000008)
#define RCC_FLAG_LVDRST       ((uint32_t)0x00000010)
#define RCC_FLAG_PORRST       ((uint32_t)0x00000020)
#define RCC_FLAG_LOCKUPRST    ((uint32_t)0x00000040)
#define RCC_FLAG_PADRST       ((uint32_t)0x00000080)
#define RCC_FLAG_SFTRST       ((uint32_t)0x00000100)

#define IS_RCC_FLAG_RST(FLAG) ((FLAG == RCC_FLAG_MCURST)  ||\
                               (FLAG == RCC_FLAG_CPURST)  ||\
															 (FLAG == RCC_FLAG_WWDTRST) ||\
															 (FLAG == RCC_FLAG_IWDTRST) ||\
															 (FLAG == RCC_FLAG_LVDRST)  ||\
															 (FLAG == RCC_FLAG_PORRST)  ||\
															 (FLAG == RCC_FLAG_LOCKUPRST)||\
															 (FLAG == RCC_FLAG_PADRST)   ||\
															 (FLAG == RCC_FLAG_SFTRST))


/** @defgroup GET RCC CLOCK RDY FLAG
  * @{
  */
#define RCC_FLAG_HIRCRDY       ((uint32_t)0x00001000)
#define RCC_FLAG_HXTRDY        ((uint32_t)0x00000040)
#define RCC_FLAG_LIRCRDY       ((uint32_t)0x00001000)
#define RCC_FLAG_LXTRDY        ((uint32_t)0x00000040)


/** @defgroup RCC HXT Driver Level Param
  * @{
  */
#define IS_RCC_HXT_DRIVER(LEVEL) ((LEVEL >= 0x00000000)&&(LEVEL <=  0x00000007))
#define IS_RCC_LXT_DRIVER(LEVEL) ((LEVEL >= 0x00000000)&&(LEVEL <=  0x0000000f))




/** @defgroup RCC HXT Driver Level Param
  * @{
  */
#define RCC_HIRC_TRIM_MASK       ((uint32_t)0x000007FF)
#define RCC_LIRC_TRIM_MASK       ((uint32_t)0x000001FF)

#define RCC_HXT_DRIVER_MASK      ((uint32_t)0x0000000F)
#define RCC_HXT_STARTUP_MASK     ((uint32_t)0x00000030)
#define RCC_LIRC_STARTUP_MASK    ((uint32_t)0x00000C00)
#define RCC_LXT_STARTUP_MASK     ((uint32_t)0x00000030)
#define RCC_LXT_DRIVER_MASK      ((uint32_t)0x0000000F)

#define RCC_LXT_AON_MASK         ((uint32_t)0x00000400)
#define RCC_LXT_AON_EN           ((uint32_t)0x00000100)
#define RCC_LXT_BYP_EN           ((uint32_t)0x00000200)
#define RCC_X32K_PORT_EN         ((uint32_t)0x00000800)

#define RCC_SYSTEMTICKTIMER_STCALIB_MASK  ((uint32_t)0x01FFFFFF)
#define RCC_SYSTEMTICKTIMER_REFCORE_CLOCK ((uint32_t)0x02000000)




/** @defgroup GET RCC CLOCK PERIOD
  * @{
  */
#define RCC_LIRC_STARTUP_PERIOD4     ((uint32_t) 0x00000000)
#define RCC_LIRC_STARTUP_PERIOD16    ((uint32_t) 0x00000400)
#define RCC_LIRC_STARTUP_PERIOD64    ((uint32_t) 0x00000800)
#define RCC_LIRC_STARTUP_PERIOD256   ((uint32_t) 0x00000C00)
#define IS_RCC_LIRC_STARTUP_PERIOD(StartUpPeriod) ((StartUpPeriod == RCC_LIRC_STARTUP_PERIOD4)||\
                                                  (StartUpPeriod == RCC_LIRC_STARTUP_PERIOD16)||\
																									(StartUpPeriod == RCC_LIRC_STARTUP_PERIOD64)||\
																									(StartUpPeriod == RCC_LIRC_STARTUP_PERIOD256))


/** @defgroup GET RCC CLOCK PERIOD
  * @{
  */
#define RCC_HXT_STARTUP_PERIOD1024     ((uint32_t)0x00000000)
#define RCC_HXT_STARTUP_PERIOD2048     ((uint32_t)0x00000010)
#define RCC_HXT_STARTUP_PERIOD4096     ((uint32_t)0x00000020)
#define RCC_HXT_STARTUP_PERIOD16384    ((uint32_t)0x00000030)
#define IS_RCC_HXT_STARTUP_PERIOD(StartUpPeriod) ((StartUpPeriod == RCC_HXT_STARTUP_PERIOD1024)||\
                                                  (StartUpPeriod == RCC_HXT_STARTUP_PERIOD2048)||\
																									(StartUpPeriod == RCC_HXT_STARTUP_PERIOD4096)||\
																									(StartUpPeriod == RCC_HXT_STARTUP_PERIOD16384))


/** @defgroup GET RCC CLOCK PERIOD
  * @{
  */
#define RCC_LXT_STARTUP_PERIO1024    ((uint32_t) 0x00000000)
#define RCC_LXT_STARTUP_PERIOD2048   ((uint32_t) 0x00000010)
#define RCC_LXT_STARTUP_PERIOD4096   ((uint32_t) 0x00000020)
#define RCC_LXT_STARTUP_PERIOD16384  ((uint32_t) 0x00000030)
#define IS_RCC_LXT_STARTUP_PERIOD(StartUpPeriod) ((StartUpPeriod == RCC_LXT_STARTUP_PERIO1024)||\
                                                  (StartUpPeriod == RCC_LXT_STARTUP_PERIOD2048)||\
																									(StartUpPeriod == RCC_LXT_STARTUP_PERIOD4096)||\
																									(StartUpPeriod == RCC_LXT_STARTUP_PERIOD16384))

#define PIN_SWD_FUNCTION    ((uint32_t)0x00000001)
#define PIN_GPIO_FUNCTION   ((uint32_t)0x00000000)
#define IS_PIN_FUNCTION(FUNCTION)  ((FUNCTION == PIN_SWD_FUNCTION)||\
                                    (FUNCTION == PIN_GPIO_FUNCTION))


/* Exported Variables --------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void RCC_DeInit(void);
void RCC_HIRCTrim(RCC_TypeDef *RCCx, uint32_t TrimValue);
void RCC_LIRCTrim(RCC_TypeDef *RCCx, uint32_t TrimValue);
void RCC_SetHXTDrive(RCC_TypeDef *RCCx, uint32_t HXTDrive);
void RCC_SetLXTDrive(RCC_TypeDef *RCCx, uint8_t LXTDrive);
ErrorStatus RCC_WaitForHIRCStable(RCC_TypeDef *RCCx);
ErrorStatus RCC_WaitForHXTStable(RCC_TypeDef *RCCx, uint32_t Period);
ErrorStatus RCC_WaitForLIRCStable(RCC_TypeDef *RCCx, uint32_t Period);
ErrorStatus RCC_WaitForLXTStable(RCC_TypeDef *RCCx);
void RCC_LXTCmd(RCC_TypeDef *RCCx, LXT_InitTypeDef *LXT_InitStruct);
void RCC_SetX32KPort(RCC_TypeDef *RCCx, FunctionalState NewState);
void RCC_SetM0IRQLatency(RCC_TypeDef *RCCx, uint32_t IRQLATENCY);
void RCC_SystemTickTimerConfig(RCC_TypeDef *RCCx, uint8_t SKEW, uint32_t TICKTIMERSTCALIB);
void RCC_SetSystemTickTimerCoreRefClockcmd(RCC_TypeDef *RCCx, FunctionalState NewState);
void RCC_SysclkCmd(RCC_TypeDef *RCCx, uint32_t  SYSCLKSource, FunctionalState NewState);
void RCC_SelSysClk(RCC_TypeDef *RCCx, uint32_t SYSCLKSource);
void RCC_SysclkOutputConfig(RCC_TypeDef *RCCx, uint32_t SYSCLKSource);
void RCC_SysclkOutputCmd(RCC_TypeDef *RCCx, FunctionalState NewState);
void RCC_SysclkFclkDiv(RCC_TypeDef *RCCx, uint8_t SYSCLKDiv);
uint8_t RCC_GetSysclkSource(RCC_TypeDef *RCCx);
void RCC_SetHclkDiv(RCC_TypeDef *RCCx, uint8_t SYSCLKDiv);
void RCC_SetPclkDiv(RCC_TypeDef *RCCx, uint8_t PCLKDiv);
void RCC_AHBPeriphClockCmd(RCC_TypeDef *RCCx, uint32_t RCC_AHBPeriph, FunctionalState NewState);
void RCC_APBPeriphClockCmd(RCC_TypeDef *RCCx, uint32_t RCC_APBPeriph, FunctionalState NewState);
void RCC_PeriphResetCmd(RCC_TypeDef *RCCx, uint32_t RCC_PeriphRst, FunctionalState NewState);
void RCC_RTCResetCmd(RCC_TypeDef *RCCx, FunctionalState NewState);
void RCC_ResetCmd(RCC_TypeDef *RCCx, uint32_t RCC_RSTModle, FunctionalState NewState);
FlagStatus RCC_GetFlagStatus(RCC_TypeDef *RCCx, uint32_t  FlagRst);
void RCC_SetIoMux(RCC_TypeDef *RCCx, uint32_t I0_MUX);
uint32_t RCC_GetHCLKFreq(void);
uint32_t RCC_GetPCLKFreq(RCC_TypeDef *RCCx);
#ifdef __cplusplus
}
#endif

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

/******************* (C) COPYRIGHT 2018 AC1003 *****END OF FILE****/

