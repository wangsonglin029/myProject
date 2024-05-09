#include "ac1003_gpio.h"
#include "ac1003_rcc.h"
#include "ac1003.h"
#include "ac1003_conf.h"
#include "stdio.h"
#include "stdbool.h"



// 卡尔曼滤波器结构体
typedef struct 
{
  float X;    // 状态估计
  float P;    // 状态估计的方差
  float A;    // 状态转移矩阵
  float H;    // 观测矩阵
  float Q;    // 系统噪声协方差
  float R;    // 测量噪声协方差
} KalmanFilter;


