#include "ac1003_gpio.h"
#include "ac1003_rcc.h"
#include "ac1003.h"
#include "ac1003_conf.h"
#include "stdio.h"
#include "stdbool.h"



// �������˲����ṹ��
typedef struct 
{
  float X;    // ״̬����
  float P;    // ״̬���Ƶķ���
  float A;    // ״̬ת�ƾ���
  float H;    // �۲����
  float Q;    // ϵͳ����Э����
  float R;    // ��������Э����
} KalmanFilter;


