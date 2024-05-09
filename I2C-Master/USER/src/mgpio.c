#include "mgpio.h"
#include "stdbool.h"

void GPIO_Config(void)
{
  // PC4 PRO 控制脚 --- 输出
  // PC5 OW 一线通通讯脚 --- 输出
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_ResetBits(GPIOC, GPIO_Pin_4);
  GPIO_ResetBits(GPIOC, GPIO_Pin_5);
    
  // PC3 ALARM 报警 --- 输入
  // PC6 反接检测 --- 输入
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
    
  // PA3 热敏电阻采样控制脚 --- 输出
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_ResetBits(GPIOA, GPIO_Pin_3);
  
  // PD2 ECU 接入检测 --- 输入
  // PD4 3.3V 电压监测口 --- 输入
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
}

// 是否接入了 ECU 
bool IsEcuEnter(void)
{
  return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
}

// 设置 PRO 的状态，对于 EEPROM 中的参数需要设置为高电平，否则无法写进去
// 比如 MCU 控制平衡寄存器
void SetVProStatus(bool res)
{
  if(res == true)GPIO_SetBits(GPIOC, GPIO_Pin_4);
  else GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}





