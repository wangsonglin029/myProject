/**
  ******************************************************************************
  * @file    AC1003_tim.h
  * @author  MCD Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   This file contains all the functions prototypes for the TIM firmware
  *          library.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AC1003_ADVTIM_H
#define __AC1003_ADVTIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ac1003.h"
#include "ac1003_conf.h"

/**
  * @brief  TIM Time Base Init structure definition
  * @note   This structure is used with all TIMx except for TIM6 and TIM7.
  */

typedef struct
{
    uint16_t TIM_Prescaler;         /*!< Specifies the prescaler value used to divide the TIM clock.
                                       This parameter can be a number between 0x0000 and 0xFFFF */

    uint16_t TIM_CounterMode;       /*!< Specifies the counter mode.
                                       This parameter can be a value of @ref TIM_Counter_Mode */

    uint16_t TIM_Period;            /*!< Specifies the period value to be loaded into the active
                                       Auto-Reload Register at the next update event.
                                       This parameter must be a number between 0x0000 and 0xFFFF.  */

    uint16_t TIM_ClockDivision;     /*!< Specifies the clock division.
                                      This parameter can be a value of @ref TIM_Clock_Division_CKD */

    uint8_t TIM_RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
                                       reaches zero, an update event is generated and counting restarts
                                       from the RCR value (N).
                                       This means in PWM mode that (N+1) corresponds to:
                                          - the number of PWM periods in edge-aligned mode
                                          - the number of half PWM period in center-aligned mode
                                       This parameter must be a number between 0x00 and 0xFF.
                                       @note This parameter is valid only for TIM1 and TIM8. */
} ADVTIM_TimeBaseInitTypeDef;

/**
  * @brief  TIM Output Compare Init structure definition
  */

typedef struct
{
    uint16_t TIM_OCMode;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

    uint16_t TIM_OutputState;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */

    uint16_t TIM_OutputNState;  /*!< Specifies the TIM complementary Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_state
                                   @note This parameter is valid only for TIM1 and TIM8. */

    uint16_t TIM_Pulse;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register.
                                   This parameter can be a number between 0x0000 and 0xFFFF */

    uint16_t TIM_OCPolarity;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

    uint16_t TIM_OCNPolarity;   /*!< Specifies the complementary output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
                                   @note This parameter is valid only for TIM1 and TIM8. */

    uint16_t TIM_OCIdleState;   /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */

    uint16_t TIM_OCNIdleState;  /*!< Specifies the TIM Output Compare pin state during Idle state.
                                   This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
                                   @note This parameter is valid only for TIM1 and TIM8. */
} ADVTIM_OCInitTypeDef;

/**
  * @brief  TIM Input Capture Init structure definition
  */

typedef struct
{
    uint16_t TIM_Channel;      /*!< Specifies the TIM channel.
                                  This parameter can be a value of @ref TIM_Channel */

    uint16_t TIM_ICPolarity;   /*!< Specifies the active edge of the input signal.
                                  This parameter can be a value of @ref TIM_Input_Capture_Polarity */

    uint16_t TIM_ICSelection;  /*!< Specifies the input.
                                  This parameter can be a value of @ref TIM_Input_Capture_Selection */

    uint16_t TIM_ICPrescaler;  /*!< Specifies the Input Capture Prescaler.
                                  This parameter can be a value of @ref TIM_Input_Capture_Prescaler */

    uint16_t TIM_ICFilter;     /*!< Specifies the input capture filter.
                                  This parameter can be a number between 0x0 and 0xF */
} ADVTIM_ICInitTypeDef;

/**
  * @brief  BDTR structure definition
  * @note   This structure is used only with TIM1 and TIM8.
  */

typedef struct
{

    uint16_t TIM_OSSRState;        /*!< Specifies the Off-State selection used in Run mode.
                                      This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state */

    uint16_t TIM_OSSIState;        /*!< Specifies the Off-State used in Idle state.
                                      This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state */

    uint16_t TIM_LOCKLevel;        /*!< Specifies the LOCK level parameters.
                                      This parameter can be a value of @ref Lock_level */

    uint16_t TIM_DeadTime;         /*!< Specifies the delay time between the switching-off and the
                                      switching-on of the outputs.
                                      This parameter can be a number between 0x00 and 0xFF  */

    uint16_t TIM_Break;            /*!< Specifies whether the TIM Break input is enabled or not.
                                      This parameter can be a value of @ref Break_Input_enable_disable */

    uint16_t TIM_BreakPolarity;    /*!< Specifies the TIM Break Input pin polarity.
                                      This parameter can be a value of @ref Break_Polarity */

    uint16_t TIM_AutomaticOutput;  /*!< Specifies whether the TIM Automatic Output feature is enabled or not.
                                      This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset */
} ADVTIM_BDTRInitTypeDef;

/** @defgroup TIM_Exported_constants
  * @{
  */

#define IS_TIM_ALL_PERIPH(PERIPH) (((PERIPH) == TIM1) || \
                                   ((PERIPH) == TIM2))


/** @defgroup TIM_Output_Compare_and_PWM_modes
  * @{
  */

#define TIM_OCMode_Timing                  ((uint16_t)0x0000)
#define TIM_OCMode_Active                  ((uint16_t)0x0010)
#define TIM_OCMode_Inactive                ((uint16_t)0x0020)
#define TIM_OCMode_Toggle                  ((uint16_t)0x0030)
#define TIM_OCMode_PWM1                    ((uint16_t)0x0060)
#define TIM_OCMode_PWM2                    ((uint16_t)0x0070)
#define IS_TIM_OC_MODE(MODE) (((MODE) == TIM_OCMode_Timing) || \
                              ((MODE) == TIM_OCMode_Active) || \
                              ((MODE) == TIM_OCMode_Inactive) || \
                              ((MODE) == TIM_OCMode_Toggle)|| \
                              ((MODE) == TIM_OCMode_PWM1) || \
                              ((MODE) == TIM_OCMode_PWM2))
#define IS_TIM_OCM(MODE) (((MODE) == TIM_OCMode_Timing) || \
                          ((MODE) == TIM_OCMode_Active) || \
                          ((MODE) == TIM_OCMode_Inactive) || \
                          ((MODE) == TIM_OCMode_Toggle)|| \
                          ((MODE) == TIM_OCMode_PWM1) || \
                          ((MODE) == TIM_OCMode_PWM2) ||	\
                          ((MODE) == TIM_ForcedAction_Active) || \
                          ((MODE) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_One_Pulse_Mode
  * @{
  */

#define TIM_OPMode_Single                  ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive              ((uint16_t)0x0000)
#define IS_TIM_OPM_MODE(MODE) (((MODE) == TIM_OPMode_Single) || \
                               ((MODE) == TIM_OPMode_Repetitive))
/**
  * @}
  */

/** @defgroup TIM_Channel
  * @{
  */

#define TIM_Channel_1                      ((uint16_t)0x0000)
#define TIM_Channel_2                      ((uint16_t)0x0004)
#define TIM_Channel_3                      ((uint16_t)0x0008)
#define TIM_Channel_4                      ((uint16_t)0x000C)
#define IS_TIM_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                 ((CHANNEL) == TIM_Channel_2) || \
                                 ((CHANNEL) == TIM_Channel_3) || \
                                 ((CHANNEL) == TIM_Channel_4))
#define IS_TIM_PWMI_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                      ((CHANNEL) == TIM_Channel_2))
#define IS_TIM_COMPLEMENTARY_CHANNEL(CHANNEL) (((CHANNEL) == TIM_Channel_1) || \
                                               ((CHANNEL) == TIM_Channel_2) || \
                                               ((CHANNEL) == TIM_Channel_3))
/**
  * @}
  */

/** @defgroup TIM_Clock_Division_CKD
  * @{
  */

#define TIM_CKD_DIV1                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)
#define IS_TIM_CKD_DIV(DIV) (((DIV) == TIM_CKD_DIV1) || \
                             ((DIV) == TIM_CKD_DIV2) || \
                             ((DIV) == TIM_CKD_DIV4))
/**
  * @}
  */

/** @defgroup TIM_Counter_Mode
  * @{
  */

#define TIM_CounterMode_Up                 ((uint16_t)0x0000)
#define TIM_CounterMode_Down               ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)
#define IS_TIM_COUNTER_MODE(MODE) (((MODE) == TIM_CounterMode_Up) ||  \
                                   ((MODE) == TIM_CounterMode_Down) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned1) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned2) || \
                                   ((MODE) == TIM_CounterMode_CenterAligned3))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Polarity
  * @{
  */

 #define TIM_OCPolarity_High                ((uint16_t)0x0000)
#define TIM_OCPolarity_Low                 ((uint16_t)0x0002)
#define IS_TIM_OC_POLARITY(POLARITY) (((POLARITY) == TIM_OCPolarity_High) || \
                                      ((POLARITY) == TIM_OCPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Polarity
  * @{
  */

#define TIM_OCNPolarity_High               ((uint16_t)0x0000)
#define TIM_OCNPolarity_Low                ((uint16_t)0x0008)
#define IS_TIM_OCN_POLARITY(POLARITY) (((POLARITY) == TIM_OCNPolarity_High) || \
                                       ((POLARITY) == TIM_OCNPolarity_Low))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_state
  * @{
  */

#define TIM_OutputState_Disable            ((uint16_t)0x0000)
#define TIM_OutputState_Enable             ((uint16_t)0x0001)
#define IS_TIM_OUTPUT_STATE(STATE) (((STATE) == TIM_OutputState_Disable) || \
                                    ((STATE) == TIM_OutputState_Enable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_state
  * @{
  */

#define TIM_OutputNState_Disable           ((uint16_t)0x0000)
#define TIM_OutputNState_Enable            ((uint16_t)0x0004)
#define IS_TIM_OUTPUTN_STATE(STATE) (((STATE) == TIM_OutputNState_Disable) || \
                                     ((STATE) == TIM_OutputNState_Enable))
/**
  * @}
  */

/** @defgroup TIM_Capture_Compare_state
  * @{
  */

#define TIM_CCx_Enable                      ((uint16_t)0x0001)
#define TIM_CCx_Disable                     ((uint16_t)0x0000)
#define IS_TIM_CCX(CCX) (((CCX) == TIM_CCx_Enable) || \
                         ((CCX) == TIM_CCx_Disable))
/**
  * @}
  */

/** @defgroup TIM_Capture_Compare_N_state
  * @{
  */

#define TIM_CCxN_Enable                     ((uint16_t)0x0004)
#define TIM_CCxN_Disable                    ((uint16_t)0x0000)
#define IS_TIM_CCXN(CCXN) (((CCXN) == TIM_CCxN_Enable) || \
                           ((CCXN) == TIM_CCxN_Disable))
/**
  * @}
  */

/** @defgroup Break_Input_enable_disable
  * @{
  */

#define TIM_Break_Enable                   ((uint16_t)0x1000)
#define TIM_Break_Disable                  ((uint16_t)0x0000)
#define IS_TIM_BREAK_STATE(STATE) (((STATE) == TIM_Break_Enable) || \
                                   ((STATE) == TIM_Break_Disable))
/**
  * @}
  */

/** @defgroup Break_Polarity
  * @{
  */

#define TIM_BreakPolarity_Low              ((uint16_t)0x0000)
#define TIM_BreakPolarity_High             ((uint16_t)0x2000)
#define IS_TIM_BREAK_POLARITY(POLARITY) (((POLARITY) == TIM_BreakPolarity_Low) || \
                                         ((POLARITY) == TIM_BreakPolarity_High))
/**
  * @}
  */

/** @defgroup TIM_AOE_Bit_Set_Reset
  * @{
  */

#define TIM_AutomaticOutput_Enable         ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable        ((uint16_t)0x0000)
#define IS_TIM_AUTOMATIC_OUTPUT_STATE(STATE) (((STATE) == TIM_AutomaticOutput_Enable) || \
                                              ((STATE) == TIM_AutomaticOutput_Disable))
/**
  * @}
  */

/** @defgroup Lock_level
  * @{
  */

#define TIM_LOCKLevel_OFF                  ((uint16_t)0x0000)
#define TIM_LOCKLevel_1                    ((uint16_t)0x0100)
#define TIM_LOCKLevel_2                    ((uint16_t)0x0200)
#define TIM_LOCKLevel_3                    ((uint16_t)0x0300)
#define IS_TIM_LOCK_LEVEL(LEVEL) (((LEVEL) == TIM_LOCKLevel_OFF) || \
                                  ((LEVEL) == TIM_LOCKLevel_1) || \
                                  ((LEVEL) == TIM_LOCKLevel_2) || \
                                  ((LEVEL) == TIM_LOCKLevel_3))
/**
  * @}
  */

/** @defgroup OSSI_Off_State_Selection_for_Idle_mode_state
  * @{
  */

#define TIM_OSSIState_Enable               ((uint16_t)0x0400)
#define TIM_OSSIState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSI_STATE(STATE) (((STATE) == TIM_OSSIState_Enable) || \
                                  ((STATE) == TIM_OSSIState_Disable))
/**
  * @}
  */

/** @defgroup OSSR_Off_State_Selection_for_Run_mode_state
  * @{
  */

#define TIM_OSSRState_Enable               ((uint16_t)0x0800)
#define TIM_OSSRState_Disable              ((uint16_t)0x0000)
#define IS_TIM_OSSR_STATE(STATE) (((STATE) == TIM_OSSRState_Enable) || \
                                  ((STATE) == TIM_OSSRState_Disable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Idle_State
  * @{
  */

#define TIM_OCIdleState_Set                ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset              ((uint16_t)0x0000)
#define IS_TIM_OCIDLE_STATE(STATE) (((STATE) == TIM_OCIdleState_Set) || \
                                    ((STATE) == TIM_OCIdleState_Reset))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_N_Idle_State
  * @{
  */

#define TIM_OCNIdleState_Set               ((uint16_t)0x0200)
#define TIM_OCNIdleState_Reset             ((uint16_t)0x0000)
#define IS_TIM_OCNIDLE_STATE(STATE) (((STATE) == TIM_OCNIdleState_Set) || \
                                     ((STATE) == TIM_OCNIdleState_Reset))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Polarity
  * @{
  */

#define  TIM_ICPolarity_Rising             ((uint16_t)0x0000)
#define  TIM_ICPolarity_Falling            ((uint16_t)0x0002)
#define IS_TIM_IC_POLARITY(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                      ((POLARITY) == TIM_ICPolarity_Falling))
#define IS_TIM_IC_POLARITY_LITE(POLARITY) (((POLARITY) == TIM_ICPolarity_Rising) || \
                                           ((POLARITY) == TIM_ICPolarity_Falling))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Selection
  * @{
  */

#define TIM_ICSelection_DirectTI           ((uint16_t)0x0001) /*!< TIM Input 1, 2, 3 or 4 is selected to be 
                                                                   connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI         ((uint16_t)0x0002) /*!< TIM Input 1, 2, 3 or 4 is selected to be
                                                                   connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC                ((uint16_t)0x0003) /*!< TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */
#define IS_TIM_IC_SELECTION(SELECTION) (((SELECTION) == TIM_ICSelection_DirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_IndirectTI) || \
                                        ((SELECTION) == TIM_ICSelection_TRC))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Prescaler
  * @{
  */

#define TIM_ICPSC_DIV1                     ((uint16_t)0x0000) /*!< Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2                     ((uint16_t)0x0004) /*!< Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4                     ((uint16_t)0x0008) /*!< Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8                     ((uint16_t)0x000C) /*!< Capture performed once every 8 events. */
#define IS_TIM_IC_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ICPSC_DIV1) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV2) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV4) || \
                                        ((PRESCALER) == TIM_ICPSC_DIV8))
/**
  * @}
  */

/** @defgroup TIM_interrupt_sources
  * @{
  */

#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)
#define IS_TIM_IT(IT) ((((IT) & (uint16_t)0xFF00) == 0x0000) && ((IT) != 0x0000))

#define IS_TIM_GET_IT(IT) (((IT) == TIM_IT_Update) || \
                           ((IT) == TIM_IT_CC1) || \
                           ((IT) == TIM_IT_CC2) || \
                           ((IT) == TIM_IT_CC3) || \
                           ((IT) == TIM_IT_CC4) || \
                           ((IT) == TIM_IT_COM) || \
                           ((IT) == TIM_IT_Trigger) || \
                           ((IT) == TIM_IT_Break))

/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Prescaler
  * @{
  */

#define TIM_ExtTRGPSC_OFF                  ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)
#define IS_TIM_EXT_PRESCALER(PRESCALER) (((PRESCALER) == TIM_ExtTRGPSC_OFF) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV2) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV4) || \
                                         ((PRESCALER) == TIM_ExtTRGPSC_DIV8))
/**
  * @}
  */

/** @defgroup TIM_Internal_Trigger_Selection
  * @{
  */

#define TIM_TS_ITR0                        ((uint16_t)0x0000)
#define TIM_TS_ITR1                        ((uint16_t)0x0010)
#define TIM_TS_ITR2                        ((uint16_t)0x0020)
#define TIM_TS_ITR3                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED                     ((uint16_t)0x0040)
#define TIM_TS_TI1FP1                      ((uint16_t)0x0050)
#define TIM_TS_TI2FP2                      ((uint16_t)0x0060)
#define TIM_TS_ETRF                        ((uint16_t)0x0070)
#define IS_TIM_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                             ((SELECTION) == TIM_TS_ITR1) || \
                                             ((SELECTION) == TIM_TS_ITR2) || \
                                             ((SELECTION) == TIM_TS_ITR3) || \
                                             ((SELECTION) == TIM_TS_TI1F_ED) || \
                                             ((SELECTION) == TIM_TS_TI1FP1) || \
                                             ((SELECTION) == TIM_TS_TI2FP2) || \
                                             ((SELECTION) == TIM_TS_ETRF))
#define IS_TIM_INTERNAL_TRIGGER_SELECTION(SELECTION) (((SELECTION) == TIM_TS_ITR0) || \
                                                      ((SELECTION) == TIM_TS_ITR1) || \
                                                      ((SELECTION) == TIM_TS_ITR2) || \
                                                      ((SELECTION) == TIM_TS_ITR3))
/**
  * @}
  */

/** @defgroup TIM_TIx_External_Clock_Source
  * @{
  */

#define TIM_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)
#define IS_TIM_TIXCLK_SOURCE(SOURCE) (((SOURCE) == TIM_TIxExternalCLK1Source_TI1) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI2) || \
                                      ((SOURCE) == TIM_TIxExternalCLK1Source_TI1ED))
/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Polarity 
  * @{
  */
#define TIM_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)
#define IS_TIM_EXT_POLARITY(POLARITY) (((POLARITY) == TIM_ExtTRGPolarity_Inverted) || \
                                       ((POLARITY) == TIM_ExtTRGPolarity_NonInverted))
/**
  * @}
  */

/** @defgroup TIM_Prescaler_Reload_Mode
  * @{
  */

#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)
#define IS_TIM_PRESCALER_RELOAD(RELOAD) (((RELOAD) == TIM_PSCReloadMode_Update) || \
                                         ((RELOAD) == TIM_PSCReloadMode_Immediate))
/**
  * @}
  */

/** @defgroup TIM_Forced_Action
  * @{
  */

#define TIM_ForcedAction_Active            ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive          ((uint16_t)0x0040)
#define IS_TIM_FORCED_ACTION(ACTION) (((ACTION) == TIM_ForcedAction_Active) || \
                                      ((ACTION) == TIM_ForcedAction_InActive))
/**
  * @}
  */

/** @defgroup TIM_Encoder_Mode
  * @{
  */

#define TIM_EncoderMode_TI1                ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2                ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12               ((uint16_t)0x0003)
#define IS_TIM_ENCODER_MODE(MODE) (((MODE) == TIM_EncoderMode_TI1) || \
                                   ((MODE) == TIM_EncoderMode_TI2) || \
                                   ((MODE) == TIM_EncoderMode_TI12))
/**
  * @}
  */


/** @defgroup TIM_Event_Source
  * @{
  */

#define TIM_EventSource_Update             ((uint16_t)0x0001)
#define TIM_EventSource_CC1                ((uint16_t)0x0002)
#define TIM_EventSource_CC2                ((uint16_t)0x0004)
#define TIM_EventSource_CC3                ((uint16_t)0x0008)
#define TIM_EventSource_CC4                ((uint16_t)0x0010)
#define TIM_EventSource_COM                ((uint16_t)0x0020)
#define TIM_EventSource_Trigger            ((uint16_t)0x0040)
#define TIM_EventSource_Break              ((uint16_t)0x0080)
#define IS_TIM_EVENT_SOURCE(SOURCE) ((((SOURCE) & (uint16_t)0xFF00) == 0x0000) && ((SOURCE) != 0x0000))

/**
  * @}
  */

/** @defgroup TIM_Update_Source
  * @{
  */

#define TIM_UpdateSource_Global            ((uint16_t)0x0000) /*!< Source of update is the counter overflow/underflow
                                                                   or the setting of UG bit, or an update generation
                                                                   through the slave mode controller. */
#define TIM_UpdateSource_Regular           ((uint16_t)0x0001) /*!< Source of update is counter overflow/underflow. */
#define IS_TIM_UPDATE_SOURCE(SOURCE) (((SOURCE) == TIM_UpdateSource_Global) || \
                                      ((SOURCE) == TIM_UpdateSource_Regular))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Preload_State
  * @{
  */

#define TIM_OCPreload_Enable               ((uint16_t)0x0008)
#define TIM_OCPreload_Disable              ((uint16_t)0x0000)
#define IS_TIM_OCPRELOAD_STATE(STATE) (((STATE) == TIM_OCPreload_Enable) || \
                                       ((STATE) == TIM_OCPreload_Disable))
/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Fast_State
  * @{
  */

#define TIM_OCFast_Enable                  ((uint16_t)0x0004)
#define TIM_OCFast_Disable                 ((uint16_t)0x0000)
#define IS_TIM_OCFAST_STATE(STATE) (((STATE) == TIM_OCFast_Enable) || \
                                    ((STATE) == TIM_OCFast_Disable))

/**
  * @}
  */

/** @defgroup TIM_Output_Compare_Clear_State
  * @{
  */

#define TIM_OCClear_Enable                 ((uint16_t)0x0080)
#define TIM_OCClear_Disable                ((uint16_t)0x0000)
#define IS_TIM_OCCLEAR_STATE(STATE) (((STATE) == TIM_OCClear_Enable) || \
                                     ((STATE) == TIM_OCClear_Disable))
/**
  * @}
  */

/** @defgroup TIM_Trigger_Output_Source
  * @{
  */

#define TIM_TRGOSource_Reset               ((uint16_t)0x0000)
#define TIM_TRGOSource_Enable              ((uint16_t)0x0010)
#define TIM_TRGOSource_Update              ((uint16_t)0x0020)
#define TIM_TRGOSource_OC1                 ((uint16_t)0x0030)
#define TIM_TRGOSource_OC1Ref              ((uint16_t)0x0040)
#define TIM_TRGOSource_OC2Ref              ((uint16_t)0x0050)
#define TIM_TRGOSource_OC3Ref              ((uint16_t)0x0060)
#define TIM_TRGOSource_OC4Ref              ((uint16_t)0x0070)
#define IS_TIM_TRGO_SOURCE(SOURCE) (((SOURCE) == TIM_TRGOSource_Reset) || \
                                    ((SOURCE) == TIM_TRGOSource_Enable) || \
                                    ((SOURCE) == TIM_TRGOSource_Update) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1) || \
                                    ((SOURCE) == TIM_TRGOSource_OC1Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC2Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC3Ref) || \
                                    ((SOURCE) == TIM_TRGOSource_OC4Ref))
/**
  * @}
  */

/** @defgroup TIM_Slave_Mode
  * @{
  */

#define TIM_SlaveMode_Reset                ((uint16_t)0x0004)
#define TIM_SlaveMode_Gated                ((uint16_t)0x0005)
#define TIM_SlaveMode_Trigger              ((uint16_t)0x0006)
#define TIM_SlaveMode_External1            ((uint16_t)0x0007)
#define IS_TIM_SLAVE_MODE(MODE) (((MODE) == TIM_SlaveMode_Reset) || \
                                 ((MODE) == TIM_SlaveMode_Gated) || \
                                 ((MODE) == TIM_SlaveMode_Trigger) || \
                                 ((MODE) == TIM_SlaveMode_External1))
/**
  * @}
  */

/** @defgroup TIM_Master_Slave_Mode
  * @{
  */

#define TIM_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable        ((uint16_t)0x0000)
#define IS_TIM_MSM_STATE(STATE) (((STATE) == TIM_MasterSlaveMode_Enable) || \
                                 ((STATE) == TIM_MasterSlaveMode_Disable))
/**
  * @}
  */

/** @defgroup TIM_Flags
  * @{
  */

#define TIM_FLAG_Update                    ((uint16_t)0x0001)
#define TIM_FLAG_CC1                       ((uint16_t)0x0002)
#define TIM_FLAG_CC2                       ((uint16_t)0x0004)
#define TIM_FLAG_CC3                       ((uint16_t)0x0008)
#define TIM_FLAG_CC4                       ((uint16_t)0x0010)
#define TIM_FLAG_COM                       ((uint16_t)0x0020)
#define TIM_FLAG_Trigger                   ((uint16_t)0x0040)
#define TIM_FLAG_Break                     ((uint16_t)0x0080)
 #define TIM_FLAG_CC1OF                     ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF                     ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF                     ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF                     ((uint16_t)0x1000)
#define IS_TIM_GET_FLAG(FLAG) (((FLAG) == TIM_FLAG_Update) || \
                               ((FLAG) == TIM_FLAG_CC1) || \
                               ((FLAG) == TIM_FLAG_CC2) || \
                               ((FLAG) == TIM_FLAG_CC3) || \
                               ((FLAG) == TIM_FLAG_CC4) || \
                               ((FLAG) == TIM_FLAG_COM) || \
                               ((FLAG) == TIM_FLAG_Trigger) || \
                               ((FLAG) == TIM_FLAG_Break) || \
                               ((FLAG) == TIM_FLAG_CC1OF) || \
                               ((FLAG) == TIM_FLAG_CC2OF) || \
                               ((FLAG) == TIM_FLAG_CC3OF) || \
                               ((FLAG) == TIM_FLAG_CC4OF))


#define IS_TIM_CLEAR_FLAG(TIM_FLAG) ((((TIM_FLAG) & (uint16_t)0xE100) == 0x0000) && ((TIM_FLAG) != 0x0000))
/**
  * @}
  */

/** @defgroup TIM_Input_Capture_Filer_Value
  * @{
  */

#define IS_TIM_IC_FILTER(ICFILTER) ((ICFILTER) <= 0xF)
/**
  * @}
  */

/** @defgroup TIM_External_Trigger_Filter
  * @{
  */

#define IS_TIM_EXT_FILTER(EXTFILTER) ((EXTFILTER) <= 0xF)


/** @defgroup TIM_Exported_Functions
  * @{
  */

void ADVTIM_DeInit(ADVTIM_TypeDef* TIMx);
void ADVTIM_TimeBaseInit(ADVTIM_TypeDef* TIMx, ADVTIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void ADVTIM_OC1Init(ADVTIM_TypeDef* TIMx, ADVTIM_OCInitTypeDef* TIM_OCInitStruct);
void ADVTIM_OC2Init(ADVTIM_TypeDef* TIMx, ADVTIM_OCInitTypeDef* TIM_OCInitStruct);
void ADVTIM_OC3Init(ADVTIM_TypeDef* TIMx, ADVTIM_OCInitTypeDef* TIM_OCInitStruct);
void ADVTIM_OC4Init(ADVTIM_TypeDef* TIMx, ADVTIM_OCInitTypeDef* TIM_OCInitStruct);
void ADVTIM_ICInit(ADVTIM_TypeDef* TIMx, ADVTIM_ICInitTypeDef* TIM_ICInitStruct);
void ADVTIM_PWMIConfig(ADVTIM_TypeDef* TIMx, ADVTIM_ICInitTypeDef* TIM_ICInitStruct);
void ADVTIM_BDTRConfig(ADVTIM_TypeDef* TIMx, ADVTIM_BDTRInitTypeDef *TIM_BDTRInitStruct);
void ADVTIM_TimeBaseStructInit(ADVTIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void ADVTIM_OCStructInit(ADVTIM_OCInitTypeDef* TIM_OCInitStruct);
void ADVTIM_ICStructInit(ADVTIM_ICInitTypeDef* TIM_ICInitStruct);
void ADVTIM_BDTRStructInit(ADVTIM_BDTRInitTypeDef* TIM_BDTRInitStruct);
void ADVTIM_Cmd(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_CtrlPWMOutputs(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_ITConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);
void ADVTIM_GenerateEvent(ADVTIM_TypeDef* TIMx, uint16_t TIM_EventSource);
void ADVTIM_InternalClockConfig(ADVTIM_TypeDef* TIMx);
void ADVTIM_ITRxExternalClockConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void ADVTIM_TIxExternalClockConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,
                                   uint16_t TIM_ICPolarity, uint16_t ICFilter);
void ADVTIM_ETRClockMode1Config(ADVTIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                                uint16_t ExtTRGFilter);
void ADVTIM_ETRClockMode2Config(ADVTIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler,
                                uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);
void ADVTIM_ETRConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                      uint16_t ExtTRGFilter);
void ADVTIM_PrescalerConfig(ADVTIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void ADVTIM_CounterModeConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_CounterMode);
void ADVTIM_SelectInputTrigger(ADVTIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource);
void ADVTIM_EncoderInterfaceConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_EncoderMode,
                                   uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);
void ADVTIM_ForcedOC1Config(ADVTIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void ADVTIM_ForcedOC2Config(ADVTIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void ADVTIM_ForcedOC3Config(ADVTIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void ADVTIM_ForcedOC4Config(ADVTIM_TypeDef* TIMx, uint16_t TIM_ForcedAction);
void ADVTIM_ARRPreloadConfig(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_SelectCOM(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_SelectCCDMA(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_CCPreloadControl(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_OC1PreloadConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void ADVTIM_OC2PreloadConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void ADVTIM_OC3PreloadConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void ADVTIM_OC4PreloadConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void ADVTIM_OC1FastConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void ADVTIM_OC2FastConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void ADVTIM_OC3FastConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void ADVTIM_OC4FastConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void ADVTIM_ClearOC1Ref(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void ADVTIM_ClearOC2Ref(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void ADVTIM_ClearOC3Ref(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void ADVTIM_ClearOC4Ref(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void ADVTIM_OC1PolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void ADVTIM_OC1NPolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void ADVTIM_OC2PolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void ADVTIM_OC2NPolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void ADVTIM_OC3PolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void ADVTIM_OC3NPolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void ADVTIM_OC4PolarityConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void ADVTIM_CCxCmd(ADVTIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void ADVTIM_CCxNCmd(ADVTIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);
void ADVTIM_SelectOCxM(ADVTIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);
void ADVTIM_UpdateDisableConfig(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_UpdateRequestConfig(ADVTIM_TypeDef* TIMx, uint16_t TIM_UpdateSource);
void ADVTIM_SelectHallSensor(ADVTIM_TypeDef* TIMx, FunctionalState NewState);
void ADVTIM_SelectOnePulseMode(ADVTIM_TypeDef* TIMx, uint16_t TIM_OPMode);
void ADVTIM_SelectOutputTrigger(ADVTIM_TypeDef* TIMx, uint16_t TIM_TRGOSource);
void ADVTIM_SelectSlaveMode(ADVTIM_TypeDef* TIMx, uint16_t TIM_SlaveMode);
void ADVTIM_SelectMasterSlaveMode(ADVTIM_TypeDef* TIMx, uint16_t TIM_MasterSlaveMode);
void ADVTIM_SetCounter(ADVTIM_TypeDef* TIMx, uint16_t Counter);
void ADVTIM_SetAutoreload(ADVTIM_TypeDef* TIMx, uint16_t Autoreload);
void ADVTIM_SetCompare1(ADVTIM_TypeDef* TIMx, uint16_t Compare1);
void ADVTIM_SetCompare2(ADVTIM_TypeDef* TIMx, uint16_t Compare2);
void ADVTIM_SetCompare3(ADVTIM_TypeDef* TIMx, uint16_t Compare3);
void ADVTIM_SetCompare4(ADVTIM_TypeDef* TIMx, uint16_t Compare4);
void ADVTIM_SetIC1Prescaler(ADVTIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void ADVTIM_SetIC2Prescaler(ADVTIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void ADVTIM_SetIC3Prescaler(ADVTIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void ADVTIM_SetIC4Prescaler(ADVTIM_TypeDef* TIMx, uint16_t TIM_ICPSC);
void ADVTIM_SetClockDivision(ADVTIM_TypeDef* TIMx, uint16_t TIM_CKD);
uint16_t ADVTIM_GetCapture1(ADVTIM_TypeDef* TIMx);
uint16_t ADVTIM_GetCapture2(ADVTIM_TypeDef* TIMx);
uint16_t ADVTIM_GetCapture3(ADVTIM_TypeDef* TIMx);
uint16_t ADVTIM_GetCapture4(ADVTIM_TypeDef* TIMx);
uint16_t ADVTIM_GetCounter(ADVTIM_TypeDef* TIMx);
uint16_t ADVTIM_GetPrescaler(ADVTIM_TypeDef* TIMx);
FlagStatus ADVTIM_GetFlagStatus(ADVTIM_TypeDef* TIMx, uint16_t TIM_FLAG);
void ADVTIM_ClearFlag(ADVTIM_TypeDef* TIMx, uint16_t TIM_FLAG);
ITStatus ADVTIM_GetITStatus(ADVTIM_TypeDef* TIMx, uint16_t TIM_IT);
void ADVTIM_ClearITPendingBit(ADVTIM_TypeDef* TIMx, uint16_t TIM_IT);

#ifdef __cplusplus
}
#endif

#endif /*__AC1003_ADVTIM_H */



/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/************************ (C) COPYRIGHT ac1003 *****END OF FILE****/
