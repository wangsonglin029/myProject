/**
  ********************************************************
  * @file    main.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   
  ********************************************************
  */
/*Includes ----------------------------*/
#include "test_i2c_master.h"
#include "test_uart.h"
#include "test_iwdt.h"
#include "stdbool.h"
#include "mdefine.h"
#include "time.h"
#include "stddef.h"
#include "menum.h"

/* 
  存储小数和整数的数组，各7个 
*/
/* 
  对于三级管的设计，要注重查看特性曲线，根据特性曲线
  上的 Vcv 找到管子的 Ib 以及 Ic
*/

/**
*** 写 309 ROM 需要延时 35ms，写 309 RAM 需要延时 1ms
***/
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

extern bool TimeOut(uint32_t ms, uint8_t timer_id);
extern void GPIO_Config(void);
extern void Sh367309ConfigInit(float rref, uint32_t *pComAddr);
extern float GetTemperatureRref(uint32_t *pComAddr);
extern void GetCellStatus(uint32_t *pComAddr);
extern void delay_init(uint32_t SYSCLK);
extern void BASIC_TIM_Mode_Config(void);
extern void GetAllSingleVoltage(uint32_t *pComAddr);
extern void GetCurrentParameters(uint32_t *pComAddr);
extern void GetTemperatureParameters(uint32_t *pComAddr);
extern void ADC_Mode_Config(void);
extern void GetMcuTemperature(void);
extern float Rt2Temperature(float Rt);
extern bool IsEcuEnter(void);
extern bool IsSendAllowed(void);
extern void SetSendAllowedStatus(bool res);
extern void mAhIntegral(void);
extern void GetLimitedSingleVoltage(void);
extern void UpdatePackStatus(void);
extern bool Send(void);
extern void CalNowSOH(void);
extern void SystemDataInitByReadFlash(void);
extern void WriteEEPROMCheck(void);
extern void AdjSocByStaticVoltage(void);
extern void EXTI_Key_Config(void);
extern void Enter_DeepSleep(void);
extern void GetConfStatus(uint32_t *pComAddr);
extern void Mos(bool res, uint32_t *pComAddr);
extern bool MosTempProtectedCheck(void);
extern void BalanceManage(uint32_t *prComAddr, uint32_t *pwComAddr);
extern void GetMcuUid(void);
extern void GetPackProtectedStatus(uint32_t *pComAddr);
extern void SocAdjustByVoltage(void);
extern void ClrStatusRegister(uint32_t *pComAddr);
extern uint64_t GetTick(void);
extern uint8_t IsChargeStatus(void);

extern void CurrentKalmanFliterInit(void);
extern float CurrentKalmanFliter(float Measurement_Value);
extern void SocKalmanFliterInit(float R);

extern void RecordProtectedStatus(void);
extern void PRINT(void);
extern TestStatus WriteToFlash(uint32_t Addr, uint32_t Data[], uint16_t Datalen);
extern void Kalman_Test(void);
extern void AnalysisAndPrintErrCode(void);

  /* 
    1、使用 SH367309 烧录器时，MCU 不能与芯片通讯；
    2、跑循环时要接上电池之后单片机不掉电，数据自动保存在 RAM 无需写入 FLASH；
  */

 /**
  * @brief  main.c.
  * @param  None
	* @param  None
  * @retval None
  */
int main(void)
{
  /*Enable the HIRC clock*/
  RCC_SysclkCmd(RCC,RCC_SYSCLKSource_HIRC,ENABLE);
	
  /*Enable the LIRC clock*/
  RCC_SysclkCmd(RCC,RCC_SYSCLKSource_LIRC,ENABLE);
	
  /*open IWDG Clock*/
  RCC_APBPeriphClockCmd(RCC,RCC_APBPeriph_IWDGCKEN, ENABLE);
        
  /*open I2C Clock*/
  RCC_APBPeriphClockCmd(RCC,RCC_APBPeriph_I2CCKEN, ENABLE);
	
  /*open ADC Clock*/
  RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_ADCCKEN, ENABLE);
    
  /*open UART1 Clock*/
  RCC_APBPeriphClockCmd(RCC,RCC_APBPeriph_UART1CKEN, ENABLE);
	
  /*open UART0 Clock*/
  RCC_APBPeriphClockCmd(RCC,RCC_APBPeriph_UART0CKEN, ENABLE);
        
  /*open Basetime Clock*/
  RCC_APBPeriphClockCmd(RCC, RCC_APBPeriph_BASETIMCKEN, ENABLE);
    
  /*open GPIOA Clock*/
  RCC_AHBPeriphClockCmd(RCC,RCC_AHBPeriph_GPIOAEN,ENABLE);
	
  /*open GPIOB Clock*/
  RCC_AHBPeriphClockCmd(RCC,RCC_AHBPeriph_GPIOBEN,ENABLE);
        
  /*open GPIOC Clock*/
  RCC_AHBPeriphClockCmd(RCC,RCC_AHBPeriph_GPIOCEN,ENABLE);
	
  /*open GPIOD Clock*/
  RCC_AHBPeriphClockCmd(RCC,RCC_AHBPeriph_GPIODEN,ENABLE);
	
  /*write HIRC Triming Value to the register*/
  RCC_HIRCTrim(RCC,HIRC24M_TIMVALUE);
        
  /*Wait HIRC Stable*/
  while(RCC_WaitForHIRCStable(RCC) != SUCCESS);
  
  /*Update SystemCoreClock*/
  SystemCoreClockUpdate();
  
  Delay(1000);
  delay_init(24);
  UART1_Config();
  I2C_Master_Init();
  ADC_Mode_Config();
  BASIC_TIM_Mode_Config();
  SystemDataInitByReadFlash();
  EXTI_Key_Config();
  GPIO_Config();
  
  // 卡尔曼滤波初始化
  CurrentKalmanFliterInit();
  SocKalmanFliterInit(0);
  
  // 看门狗
  // IWDG_Config();
  
#if 0
  uint32_t svoltage[] = 
  {
    27744, 28338, 29438, 30201, 30770, 31199, 31459, 31605, 31702, 31778, 
    31838, 31895, 31940, 31982, 32021, 32063, 32111, 32164, 32214, 32259, 
    32299, 32340, 32373, 32407, 32440, 32472, 32499, 32524, 32551, 32575, 
    32596, 32617, 32636, 32652, 32673, 32690, 32705, 32722, 32740, 32753, 
    32764, 32779, 32792, 32807, 32818, 32832, 32843, 32855, 32865, 32878, 
    32887, 32900, 32911, 32920, 32933, 32941, 32952, 32967, 32976, 32986, 
    32996, 33006, 33017, 33027, 33040, 33051, 33061, 33071, 33082, 33094, 
    33104, 33114, 33123, 33135, 33144, 33153, 33162, 33171, 33180, 33189,
    33199, 33206, 33214, 33222, 33230, 33240, 33247, 33253, 33262, 33271, 
    33279, 33288, 33295, 33302, 33310, 33320, 33332, 33344, 33361, 33413, 
    33722, 
  };
  
  WriteToFlash(WRITE_START_ADDR0, svoltage, 0x65);
#endif
  
#if 0
  float Rp[] = 
  {
    /// 测量噪声协方差
     0.0000,0.0001,0.0019,0.0040,0.0061,0.0082,0.0103,0.0125,0.0147,0.0170,
     0.0193,0.0216,0.0240,0.0265,0.0290,0.0315,0.0341,0.0368,0.0395,0.0423,
     0.0451,0.0480,0.0510,0.0541,0.0572,0.0604,0.0637,0.0671,0.0705,0.0741,
     0.0777,0.0814,0.0852,0.0892,0.0932,0.0973,0.1015,0.1059,0.1103,0.1148,
     0.1195,0.1243,0.1292,0.1342,0.1393,0.1446,0.1500,0.1555,0.1612,0.1670,
     
    -0.0021,-0.0043,-0.0062,-0.0081,-0.0100,-0.0118,-0.0136,-0.0153,-0.0171,-0.0187,
    -0.0204,-0.0220,-0.0236,-0.0251,-0.0266,-0.0281,-0.0295,-0.0309,-0.0323,-0.0336,
    -0.0349,-0.0362,-0.0375,-0.0387,-0.0399,-0.0411,-0.0422,-0.0433,-0.0444,-0.0454,
    -0.0465,-0.0475,-0.0484,-0.0494,-0.0503,-0.0512,-0.0521,-0.0530,-0.0538,-0.0546,
    -0.0554,-0.0562,-0.0569,-0.0577,-0.0584,-0.0591,-0.0598,-0.0604,-0.0611,-0.0617,
  };
  
  WriteToFlash(WRITE_KALMAN_ADDR, (uint32_t*)Rp, 0x65);
#endif
  
  Delay(1000);
  
  // 是否要实现看门狗 
  printf("MY AC1003 RESET!");
  
  
  
  Kalman_Test();
  
  while(1)
  {
    // 喂狗则不进入中断
    // IWDG_Feed();
    
    if(IsSendAllowed() == true)
    {
      // 协议栈发送成功
      if(Send() == true)
      {
        SetSendAllowedStatus(false);
        CalNowSOH();
      }
    }
    else
    {
      if(TimeOut(10, timer_10ms_id) == true)
      {
        // 读 SH367309 获取电流
        GetCurrentParameters((uint32_t*)I2C_Master_Receive);
        mAhIntegral();
      }
      
      if(TimeOut(100, timer_100ms_id) == true)
      {
        // 读 Mcu 获取 MOS 温度，读 SH367309 获取电芯温度
        GetMcuTemperature();
        GetTemperatureParameters((uint32_t*)I2C_Master_Receive);
        if(MosTempProtectedCheck() == true)Mos(false, (uint32_t*)I2C_Master_Transmit);
        else Mos(true, (uint32_t*)I2C_Master_Transmit);
      }
      
      if(TimeOut(505, timer_500ms_id) == true)
      {
        // 读 SH367309 获取保护状态处理，设置 505ms 为了写 RAM 延时 1ms
        GetCellStatus((uint32_t*)I2C_Master_Receive);
        GetPackProtectedStatus((uint32_t*)I2C_Master_Receive);
        RecordProtectedStatus();
        ClrStatusRegister((uint32_t*)I2C_Master_Transmit);
      }
      
      if(TimeOut(1000, timer_1000ms_id) == true)
      {
        // 读 SH367309 获取获取电芯电压
        GetConfStatus((uint32_t*)I2C_Master_Receive);
        GetAllSingleVoltage((uint32_t*)I2C_Master_Receive);
        GetLimitedSingleVoltage();
        UpdatePackStatus();
        PRINT();
      }
      
      if(TimeOut(65000, timer_bal_id) == true)
      {
        // 每隔 65s 检查一次均衡状态，每隔 60s 均衡关闭，需要重新开启均衡
        BalanceManage((uint32_t*)I2C_Master_Receive, (uint32_t*)I2C_Master_Transmit);
      }
      
      // 是否达到校准时间
      if(IsChargeStatus() != STANDBY_STATUS_ID)
      {
        TimeOut(0, timer_calibrate_id);
      }
      else
      {
        if(TimeOut(3600000, timer_calibrate_id) == true)
        {
          // 静置时间超过 1h
          AdjSocByStaticVoltage();
        }
      }
    }
    
    // 检测到 ECU 接入信号，输出数据
    if(IsEcuEnter() == false)
    {
      // TimeOut(0, timer_10000ms_id);
      
      if(TimeOut(2000, timer_3000ms_id) == true)
      {
        SetSendAllowedStatus(true);
      }
    }
    else
    {
      // 10S 中无信号可以进入深度睡眠状态
      // if(TimeOut(0, timer_10000ms_id) == true)Enter_DeepSleep();
      // GetMcuUid();
    }
  }

  AnalysisAndPrintErrCode();
}

// 系统复位
// RCC_MCURST   会重新装载选项字节区中的 ISP
// RCC_CPURST 不会重新装载选项字节区中的 ISP
void SystemReset(void)
{
  RCC_ResetCmd(RCC, RCC_MCURST, ENABLE);
}

// 获取标准时间
void GetStandardTime(struct tm * str_tt)
{
  // 要转化的时间戳
  time_t tnow;
  uint64_t t_time = GetTick();
	
	// 把整数的时间转换为 struct tm 结构体的时间
  uint8_t t[0x2D] = {0};
	
	/* 分配空间 */
  struct tm *str_tm = (struct tm *)t;
  // GetTick() 这个是需要对时的参数，unix 时间戳，首次启动程序时对时的参数
  // 时间戳转化网址： https://m.wannianli.tianqi.com/jisuanqi/shijianchuo/
  // 获取当前系统时间，从 1970 年开始计时的
  tnow = (t_time / 1000);


  

  
  str_tm = localtime(&tnow);
  str_tm -> tm_year += 1900;
  str_tm -> tm_mon  += 1;
  /*
  printf("%04u-%02u-%02u %02u:%02u:%02u\n",str_tm -> tm_year + 1900, str_tm -> tm_mon + 1,\
          str_tm -> tm_mday, str_tm -> tm_hour, str_tm -> tm_min, str_tm -> tm_sec);

  printf("%04u年%02u月%02u日%02u时%02u分%02u秒\n",str_tm->tm_year+1900,\
          str_tm -> tm_mon + 1,str_tm -> tm_mday, str_tm -> tm_hour, str_tm -> tm_min, str_tm -> tm_sec);

  // 只输出年月日
  printf("%04u-%02u-%02u\n",str_tm -> tm_year + 1900,str_tm -> tm_mon + 1,str_tm -> tm_mday);
  */
  memcpy(str_tt, str_tm, sizeof(str_tm));
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT to AC1003 *****END OF FILE****/
