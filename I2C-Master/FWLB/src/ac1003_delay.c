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

static uint8_t  fac_us = 0;							//us延时倍乘数
static uint16_t fac_ms = 0;							//ms延时倍乘数,在os下,代表每个节拍的ms数


//初始化延迟函数
//当使用OS的时候,此函数会初始化OS的时钟节拍
//SYSTICK的时钟固定为AHB时钟的1/4
//SYSCLK:系统时钟频率
void delay_init(uint32_t SYSCLK)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div4);
    fac_us = SYSCLK / 4;						//不论是否使用OS,fac_us都需要使用
    fac_ms = (uint16_t)fac_us * 1000;				//非OS下,代表每个ms需要的systick时钟数

}


//延时nus
//nus为要延时的us数.
//注意:nus的值,不要大于16777216us(最大值即2^24/fac_us@fac_us=1)
void delay_us(uint32_t nus)
{
    uint32_t temp = 0;

    //传参检查
    if(nus == 0)
        return;

    SysTick->LOAD = nus * fac_us; 				//时间加载
    SysTick->VAL = 0x00;        				//清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;  //开始倒数
    do
    {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));	 //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk; //关闭计数器
    SysTick->VAL = 0X00;       				   //清空计数器
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*4*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对4M条件下,nms<=16777ms
void delay_xms(uint16_t nms)
{
    uint32_t temp = 0;

    if(nms == 0)
        return;

    SysTick->LOAD = (uint32_t)nms * fac_ms;			//时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;           			        //清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;      //开始倒数
    do
    {
        temp = SysTick->CTRL;
    } while((temp & 0x01) && !(temp & (1 << 16)));	 //等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;   //关闭计数器
    SysTick->VAL = 0X00;     		  		     //清空计数器
}
//延时nms
//nms:0~65535
void delay_ms(uint16_t nms)
{
    uint8_t repeat = nms / 1600;						//这里用1600,是考虑到某些客户可能超频使用,

    uint16_t remain = nms % 1600;
    while(repeat)
    {
        delay_xms(1600);
        repeat--;
    }
    if(remain)delay_xms(remain);
}





































