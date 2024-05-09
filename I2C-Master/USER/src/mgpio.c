#include "mgpio.h"
#include "stdbool.h"

void GPIO_Config(void)
{
  // PC4 PRO ���ƽ� --- ���
  // PC5 OW һ��ͨͨѶ�� --- ���
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_ResetBits(GPIOC, GPIO_Pin_4);
  GPIO_ResetBits(GPIOC, GPIO_Pin_5);
    
  // PC3 ALARM ���� --- ����
  // PC6 ���Ӽ�� --- ����
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
    
  // PA3 ��������������ƽ� --- ���
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_ResetBits(GPIOA, GPIO_Pin_3);
  
  // PD2 ECU ������ --- ����
  // PD4 3.3V ��ѹ���� --- ����
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_4;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
}

// �Ƿ������ ECU 
bool IsEcuEnter(void)
{
  return GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
}

// ���� PRO ��״̬������ EEPROM �еĲ�����Ҫ����Ϊ�ߵ�ƽ�������޷�д��ȥ
// ���� MCU ����ƽ��Ĵ���
void SetVProStatus(bool res)
{
  if(res == true)GPIO_SetBits(GPIOC, GPIO_Pin_4);
  else GPIO_ResetBits(GPIOC, GPIO_Pin_4);
}





