/**
  ******************************************************************************
  * @file    ac1003_syscon.h
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    24-July-2018
  * @brief   This file contains all the functions prototypes for the SYSCTRL firmware
  *          library.
  ******************************************************************************
  */

/*Define to prevent recursive inclusion ----------------------*/
#ifndef __ac1003_SYSCTRL_H
#define __ac1003_SYSCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"



/** @addtogroup SYSCFG KEY
  * @{
  */

#define SYSCTRL_UNLOCKKEY           (uint32_t)0x55aa6699
#define SYSCTRL_LOCKKEY             (uint32_t)0x55aa6698
#define SYSCTRL_CFGR0KEY            (uint32_t)0x5a690000
#define SYSCTRL_CFGR0KEY_MASK       (uint32_t)0x00000003
#define SYSCTRL_PORTINTCRKEY        (uint32_t)0x5a690000
#define SYSCTRL_PORTINTCRKEY_MASK   (uint32_t)0x00000003

/* Exported types ------------------------------------------------------------*/
#define IS_SYSCTRL_ALL_PERIPH(PERIPH)    (PERIPH) == SYSCTRL)


/** @defgroup SYSCFG_Exported_Constants
  * @{
  */
#define SYSCTRL_LOCKUP_EN              ((uint32_t)0x00000001);
#define SYSCTRL_DEEPSLEEPDebug_EN      ((uint32_t)0x00000002);
#define SYSCTRL_DEEPSLEEPPORTINT_EN    ((uint32_t)0x00000002);
#define SYSCTRL_ACTIVESLEEPPORTINT_EN  ((uint32_t)0x00000001);


/** @defgroup SYSCTRL MASK
  * @{
  */
#define SPINSS_SEL_MASK     ((uint32_t)0x0000000f)
#define TIM10_GATE_MASK     ((uint32_t)0x00000003<<4)
#define TIM11_GATE_MASK     ((uint32_t)0x00000003<<6)
#define IPTIM_GATE_MASK     ((uint32_t)0x00000003<<8)


#define PCA_CH_MASK         ((uint32_t)0x00000003)
#define TIM_ETR_MASK        ((uint32_t)0x0000000f<<16)
#define TIM_CH_MASK         ((uint32_t)0x00000007)

#define TIM1_BREAK_STM      ((uint32_t)0x00100000)
#define TIM1_BREAK_ZERO     ((uint32_t)0xFFEFFFFF)

#define LPUARTCLK_MASK      ((uint32_t)0x00000003)
#define LPUARTCLK_EN        ((uint32_t)0x00000010)



/** @defgroup SPINSS_SEL
  * @{
  */
#define SPINSS_HighLevel          ((uint32_t)0x00000000)
#define SPINSS_Pin1GPIOA          ((uint32_t)0x00000001)
#define SPINSS_Pin2GPIOA          ((uint32_t)0x00000002)
#define SPINSS_Pin3GPIOA          ((uint32_t)0x00000003)
#define SPINSS_Pin4GPIOB          ((uint32_t)0x00000004)
#define SPINSS_Pin5GPIOB          ((uint32_t)0x00000005)
#define SPINSS_Pin3GPIOC          ((uint32_t)0x00000006)
#define SPINSS_Pin4GPIOC          ((uint32_t)0x00000007)
#define SPINSS_Pin5GPIOC          ((uint32_t)0x00000008)
#define SPINSS_Pin6GPIOC          ((uint32_t)0x00000009)
#define SPINSS_Pin7GPIOC          ((uint32_t)0x0000000A)
#define SPINSS_Pin1GPIOD          ((uint32_t)0x0000000B)
#define SPINSS_Pin2GPIOD          ((uint32_t)0x0000000C)
#define SPINSS_Pin3GPIOD          ((uint32_t)0x0000000D)
#define SPINSS_Pin4GPIOD          ((uint32_t)0x0000000E)
#define SPINSS_Pin6GPIOD          ((uint32_t)0x0000000F)
#define IS_SPINSS_PORT_PIN(PIN)   ((PIN >= 0x00000000)&&(PIN <= 0x0000000f))

/**
  * @}TIM0_GATE_SEL
  */
#define TIM0_GATE_TIM0GATE      ((uint32_t)0x00000000<<4)
#define TIM0_UART0_RXD          ((uint32_t)0x00000001<<4)
#define TIM0_UART1_RXD          ((uint32_t)0x00000002<<4)
#define TIM0_LPUART_RXD         ((uint32_t)0x00000003<<4)
#define IS_TIM0_GATE_SEL(PIN)   ((PIN & 0xffffffcf == 0x00000000)&&(PIN >= 0x00000000))

/**
  * @}TIM1_GATE_SEL
  */
#define TIM1_GATE_TIM0GATE      ((uint32_t)0x00000000<<6)
#define TIM1_UART0_RXD          ((uint32_t)0x00000001<<6)
#define TIM1_UART1_RXD          ((uint32_t)0x00000002<<6)
#define TIM1_LPUART_RXD         ((uint32_t)0x00000003<<6)
#define IS_TIM1_GATE_SEL(PIN)   ((PIN & 0xffffff3f == 0x00000000)&&(PIN >= 0x00000000))

/**
  * @}IPTIM_GATE_SEL
  */
#define IPTIM_GATE_TIM1GATE      ((uint32_t)0x00000000<<8)
#define IPTIM_UART0_RXD          ((uint32_t)0x00000001<<8)
#define IPTIM_UART1_RXD          ((uint32_t)0x00000002<<8)
#define IPTIM_LPUART_RXD         ((uint32_t)0x00000003<<8)
#define IS_IPTIM_GATE_SEL(PIN)   ((PIN & 0xfffffcff == 0x00000000)&&(PIN >= 0x00000000))



/** @defgroup SYSCFG_EXTI_Pin_Sources
  * @{
  */
#define PCA_CH                        ((uint32_t)0x00000000)
#define PCA_UART0RXD                  ((uint32_t)0x00000001)
#define PCA_UART1RXD                  ((uint32_t)0x00000002)
#define PCA_LIRC                      ((uint32_t)0x00000003)
#define IS_CAP_CHANNEL_SEL(CHANNEL)   ((CHANNEL & 0xfffffffc == 0x00000000)&&(CHANNEL >= 0x00000000))


#define PCA_CHANNEL0                 ((uint32_t)0x00000000)
#define PCA_CHANNEL1                 ((uint32_t)0x00000001)
#define PCA_CHANNEL2                 ((uint32_t)0x00000002)
#define PCA_CHANNEL3                 ((uint32_t)0x00000003)
#define PCA_CHANNEL4                 ((uint32_t)0x00000004)
#define IS_PCA_CHANNEL_SET(CHANNEL)  ((CHANNEL >= 0x00000000)&&(CHANNEL <= 0x00000004))


#define TIMETR_LowLevel                  ((uint32_t)0x00000000<<16)
#define TIMETR_Pin1GPIOA                 ((uint32_t)0x00000001<<16)
#define TIMETR_Pin2GPIOA                 ((uint32_t)0x00000002<<16)
#define TIMETR_Pin3GPIOA                 ((uint32_t)0x00000003<<16)
#define TIMETR_Pin4GPIOB                 ((uint32_t)0x00000004<<16)
#define TIMETR_Pin5GPIOB                 ((uint32_t)0x00000005<<16)
#define TIMETR_Pin3GPIOC                 ((uint32_t)0x00000006<<16)
#define TIMETR_Pin4GPIOC                 ((uint32_t)0x00000007<<16)
#define TIMETR_Pin5GPIOC                 ((uint32_t)0x00000008<<16)
#define TIMETR_Pin6GPIOC                 ((uint32_t)0x00000009<<16)
#define TIMETR_Pin7GPIOC                 ((uint32_t)0x0000000A<<16)
#define TIMETR_Pin1GPIOD                 ((uint32_t)0x0000000B<<16)
#define TIMETR_Pin2GPIOD                 ((uint32_t)0x0000000C<<16)
#define TIMETR_Pin3GPIOD                 ((uint32_t)0x0000000D<<16)
#define TIMETR_Pin4GPIOD                 ((uint32_t)0x0000000E<<16)
#define TIMETR_Pin6GPIOD                 ((uint32_t)0x0000000F<<16)
#define IS_TIMETR_ETR_SET(CHANNEL)       ((CHANNEL >= 0x00000000)&&\
                                          ((CHANNEL && 0xfff0ffff) == (uint32_t)0x00000000))


#define TIM_CH           (uint32_t)0x00000000
#define TIM_UART0RXD     (uint32_t)0x00000001
#define TIM_UART1RXD     (uint32_t)0x00000002
#define TIM_LPUARTRXD    (uint32_t)0x00000003
#define TIM_LIRC         (uint32_t)0x00000004
#define IS_TIM_INPUTSIGNAL_SEL(CHANNEL)   ((CHANNEL >= 0x00000000)&&(CHANNEL<=0x00000004))


#define TIM_CHANNEL1     (uint32_t)0x00000000
#define TIM_CHANNEL2     (uint32_t)0x00000001
#define TIM_CHANNEL3     (uint32_t)0x00000002
#define TIM_CHANNEL4     (uint32_t)0x00000003
#define IS_TIM_CHANNEL_SET(CHANNEL)   ((CHANNEL >= 0x00000000)&&(CHANNEL<=0x00000003))


#define LPUARTCLK_PCLK           ((uint32_t)0x00000000)
#define LPUARTCLK_LXT            ((uint32_t)0x00000001)
#define LPUARTCLK_LIRC           ((uint32_t)0x00000002)
#define LPUARTCLK_BREAKUPPCLK    ((uint32_t)0x00000003)
#define IS_LPUART_CLK_SEL(CLK)   ((CLK >= 0x00000000)&&(CLK<=0x00000003))

/** @defgroup LPUART_Exported_Functions
  * @{
  */
void SYSCTRL_DeInit(void);
void SYSCTRL_CortexM0LockUpCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState);
void SYSCTRL_DebugModeDeepsleepCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState);
void SYSCTRL_DeepsleepPortITCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState);
void SYSCTRL_ActiveSleepPortITCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState);
void SYSCTRL_SPICSConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t SPINssPin);
void SYSCTRL_TIM10_GateConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t TIM10Gate);
void SYSCTRL_TIM11_GateConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t TIM11Gate) ;
void SYSCTRL_IPTIM_GateConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t LptimeGate);
void SYSCTRL_PCACapMuxConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t CapChannel, uint32_t CapSignal);
void SYSCTRL_TIM1_InputSignalConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t InputChannel, uint32_t InputSignal);
void SYSCTRL_TIM1_ETRSignalConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t InputSignal);
void SYSCTRL_TIM1_SetBreakSTM(SYSCON_TypeDef *SYSCTRLx);
void SYSCTRL_TIM1_SetBreakZERO(SYSCON_TypeDef *SYSCTRLx);
void SYSCTRL_TIM2_InputSignalConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t InputChannel, uint32_t InputSignal);
void SYSCTRL_TIM2_ETRSignalConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t InputSignal);
void SYSCTRL_LPUART_CLKConfig(SYSCON_TypeDef *SYSCTRLx, uint32_t LpuartClk);
void SYSCTRL_LPUART_CLKCmd(SYSCON_TypeDef *SYSCTRLx, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /*__ac1003_SYSCTRL_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Ascendchip *****END OF FILE****/
