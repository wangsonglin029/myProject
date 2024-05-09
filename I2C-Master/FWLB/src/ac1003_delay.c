#include "ac1003_delay.h"
#include "misc.h"
//////////////////////////////////////////////////////////////////////////////////

/**
  ******************************************************************************
  * @file    ac1003_delay.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    09-17-2019
  * @brief   This file provides all the dealy firmware functions (add-on
  *          to CMSIS functions).
  ******************************************************************************
  */

//////////////////////////////////////////////////////////////////////////////////

static uint8_t  fac_us = 0;							//us��ʱ������
static uint16_t fac_ms = 0;							//ms��ʱ������,��os��,����ÿ�����ĵ�ms��


//��ʼ���ӳٺ���
//��ʹ��OS��ʱ��,�˺������ʼ��OS��ʱ�ӽ���
//SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӵ�1/4
//SYSCLK:ϵͳʱ��Ƶ��
void delay_init(uint32_t SYSCLK)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div4);
    fac_us = SYSCLK / 4;						//�����Ƿ�ʹ��OS,fac_us����Ҫʹ��
    fac_ms = (uint16_t)fac_us * 1000;				//��OS��,����ÿ��ms��Ҫ��systickʱ����

}


//��ʱnus
//nusΪҪ��ʱ��us��.
//ע��:nus��ֵ,��Ҫ����16777216us(���ֵ��2^24/fac_us@fac_us=1)
void delay_us(uint32_t nus)
{
    uint32_t temp = 0;

    //���μ��
    if(nus == 0)
        return;

    SysTick->LOAD = nus * fac_us; 				//ʱ�����
    SysTick->VAL = 0x00;        				//��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;  //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));	 //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //�رռ�����
    SysTick->VAL = 0X00;       				   //��ռ�����
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*4*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��4M������,nms<=16777ms
void delay_xms(uint16_t nms)
{
    uint32_t temp = 0;

    if(nms == 0)
        return;

    SysTick->LOAD = (uint32_t)nms * fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL = 0x00;           			        //��ռ�����
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;      //��ʼ����
    do
    {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));	 //�ȴ�ʱ�䵽��
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;   //�رռ�����
    SysTick->VAL = 0X00;     		  		     //��ռ�����
}
//��ʱnms
//nms:0~65535
void delay_ms(uint16_t nms)
{
    uint8_t repeat = nms / 1600;						//������1600,�ǿ��ǵ�ĳЩ�ͻ����ܳ�Ƶʹ��,

    uint16_t remain = nms % 1600;
    while(repeat)
    {
        delay_xms(1600);
        repeat--;
    }
    if(remain)delay_xms(remain);
}





































