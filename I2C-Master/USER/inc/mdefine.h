#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdint.h"
#include "ac1003_delay.h"

#ifndef __MDEF__
#define __MDEF__

#define enable                                  (0x01)
#define disable                                 (0x00)

#define CONFIG_U8_E_CAP_ID                      (0x0C)
#define CONFIG_U8_SERIES_V_NUMBER_SIZE_ID       (0x0F)
#define CONFIG_U8_SERIES_T_NUMBER_SIZE_ID       (0x03)
#define CONFIG_U16_CUT_UP_VOLTAGE_SIZE_ID       (0x0E42)
#define CONFIG_U16_CUT_DO_VOLTAGE_SIZE_ID       (0x0BB8)

// SOC 循环次数等
#define WRITE_START_ADDR     0x7800 //flash:30K

// 电压与 SOC 的对应值
#define WRITE_START_ADDR0    0x7C00 //flash:31K

// 卡尔曼参数
#define WRITE_KALMAN_ADDR    0x8000 //flash:32K

#endif







































