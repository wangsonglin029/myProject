#include "config.h"
#include "mdefine.h"
#include "menum.h"

uint16_t calculate_u16[CAL_U16_ALL_ID] = {0};

/* 获取 SOC --- % */
uint8_t GetNowSOC(void)
{
  return calculate_u16[CAL_U16_SOC_ID] * GetNowSOH() / 100;
}

/* 电量 1% 记录 */
uint8_t OnePercentCap(void)
{
  static float t_mAh = 0.0;
  static float t_current = 0.0;
  static float t_old_current = 0.0;
  static uint64_t s_timer = 0;
  
  uint64_t t_timer = 0;
  
  uint16_t t_ms = 0;
  
  /* 百分之一的电量 --- mAh */
  uint16_t t_CapPercentOne = GetNowSOH() * CONFIG_U8_E_CAP_ID / 10;
  
  /* 积分时基 --- ms */
  t_timer = GetTick();
  
  if(s_timer == 0)s_timer = t_timer;
    
  if(t_timer >= s_timer)
  {
    t_ms = t_timer - s_timer;
  }
  else
  {
    t_ms = 0xffffffffffffffff + t_timer - s_timer;
  }
  
  s_timer = t_timer;
  
  /* 当前电流 mA */
  if(IsChargeStatus() != STANDBY_STATUS_ID)t_current = (int16_t)curr0_.general;
  else t_current = 0.0;
  
  /* 添加电流 kalman 滤波 */
  
  /* 计算均值 */
  t_mAh += 1.0 * (t_current + t_old_current) * t_ms / (2 * 3600 * 1000);
  
  /* 更新电流 */
  t_old_current = t_current;
  
  // --------------------------------------------------------------------
  // 外部均衡时，有电流消耗，目前，均衡电阻是 100Ω，均衡电流是 33mA，但是
  // 均衡与采样周期各占 1 / 2，且奇偶节又各占这 1 / 2 中的 1 / 2，因此，只要开
  // 启一节电芯的均衡，必然是要除以 4，目前同时开启的电芯的均衡数量是 #define BAL_NUMBER 0x06
  // 因此，耗电量需要乘以 6
  if(GetEnBalStatus() == true)
  {
    t_mAh += - 1.0 * 33 * t_ms * 6 / (3600 * 1000 * 4);
  }
  // --------------------------------------------------------------------
  /* 待机耗电 --- 实测 10mA */
  t_mAh += - 1.0 * 10 * t_ms / (3600 * 1000);
  
  if(t_mAh >= 1.0 * t_CapPercentOne)
  {
    t_mAh = 0;
    calculate_u16[CAL_U16_CHG_CYCLE_PERCENT_ID] ++;
    return CHARGE_ONE_PERCENT_CAP;
  }
  else if(t_mAh <= - 1.0 * t_CapPercentOne)
  {
    t_mAh = 0;
    calculate_u16[CAL_U16_DSG_CYCLE_PERCENT_ID] ++;
    return DISCHARGE_ONE_PERCENT_CAP;
  }
  else return NOT_ARRIVED_ONE_PERCENT;
}

/* 记录循环次数 */
void RecordCycleTimes(void)
{
  if((calculate_u16[CAL_U16_CHG_CYCLE_PERCENT_ID] >= 100)&&
     (calculate_u16[CAL_U16_DSG_CYCLE_PERCENT_ID] >= 100))
  {
    calculate_u16[CAL_U16_CHG_CYCLE_PERCENT_ID] -= 100;
    calculate_u16[CAL_U16_DSG_CYCLE_PERCENT_ID] -= 100;
    calculate_u16[CAL_U16_CYCLE_TIMES_ID] ++;
  }
}

/* 获取电量 */
void mAhIntegral(void)
{
  uint8_t res = OnePercentCap();
  
  if(res == CHARGE_ONE_PERCENT_CAP)
  {
    // soc 测量值
    if(calculate_u16[CAL_U16_SOC_MEASURE_ID] >= 100)calculate_u16[CAL_U16_SOC_MEASURE_ID] = 100;
    else calculate_u16[CAL_U16_SOC_MEASURE_ID] ++;
    
    // soc 估计值
    SocKalmanManage();
  }
  
  else if(res == DISCHARGE_ONE_PERCENT_CAP)
  {
    // soc 测量值
    if(calculate_u16[CAL_U16_SOC_MEASURE_ID] > 0)calculate_u16[CAL_U16_SOC_MEASURE_ID] --;
    else calculate_u16[CAL_U16_SOC_MEASURE_ID] = 0;
    
    // soc 估计值
    SocKalmanManage();
  }
  
  /// 总压超过 3500 表示充满电，低于 2800 为 0 电压
  SocAdjustByVoltage();
}

/* 电流校准 --- 充电末期 */
void SocAdjustByVoltage(void)
{
#if __MAKE_CHECK02__
  #error Three stage charging check 
#endif
  
  if((cell_v.total_v.general == 0)||(cell_v.total_v.general == 0xffff))return;
  
  /* 
    充电到充满电压 3650 * Series
  */
  if(cell_v.real_v.general >= (CONFIG_U16_CUT_UP_VOLTAGE_SIZE_ID - 150) * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID)
  {
    /* 充电完成 */
    calculate_u16[CAL_U16_SOC_ID] = 100;
    RecordCycleTimes();
  }
  
  /*
    放电到 2800 * Series
  */
  else if(cell_v.real_v.general <= CONFIG_U16_CUT_DO_VOLTAGE_SIZE_ID * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID)
  {
    calculate_u16[CAL_U16_SOC_ID] = 0;
    RecordCycleTimes();
  }
}

/* 
  系数量级  ：-4      -8     -12
  0.4 - DOD ：-0.581  0.169  0.201 
  0.6 - DOD ：-0.897  1.36   -1.11 
  0.8 - DOD ：-1.34   3.11   -3.04 
  1.0 - DOD ：-1.69   4.48   -4.54 
*/

#if __MAKE_CHECK03__
  #error We check capacity and suppose the DOD is 0.8
#endif

void CalNowSOH(void)
{
  /* 循环次数检查 */
	uint16_t cycles = 0;
	float rate = 0.0;
	float soh = 0, B = -1.34 * 10000, C = 3.11, D = - 0.000304;
	
  RecordCycleTimes();
  cycles = calculate_u16[CAL_U16_CYCLE_TIMES_ID];
  rate = SocDecayDueToTemperature();

  soh  = 100000000 + B * cycles + C * cycles * cycles + D * cycles * cycles * cycles;
  soh /= 1000000;
  calculate_u16[CAL_U16_SOH_ID] = (uint8_t)(soh * rate);
}

/* 
  Decay = -5.06974 * exp( -t / 55.90333 ) + 14.03729;
  R^2 = 0.99784;
  测试电池的总容量设置为 11Ah，系数有问题时需要进行重新设置。
*/
float SocDecayDueToTemperature(void)
{
  /* 不同温度与容量衰减关系 */
  float A = - 0.0003488;
  float B = 0.07495;
  float C = 9.092;
  float T = temp_.general[0];
  float soh = (A * T * T + B * T + C) / 11;
  
  /* 大于 1 按照等于 1 来处理 */
  if(soh > 1)soh = 1.0;
  return soh;
}

/* 获取当前的 SOC 值 */
uint8_t GetNowSOH(void)
{
  return calculate_u16[CAL_U16_SOH_ID];
}

/// BMS 状态检查
uint8_t IsChargeStatus(void)
{
  if(status3.details.chging == 1)return CHARGE_STATUS_ID;
  else if(status3.details.dsging == 1)return DISCHARGE_STATUS_ID;
  else return STANDBY_STATUS_ID;
}

/// 写内存检查，需要注意的地方是当检测到小于 1A 的电流时，\
    都认为处于待机模式，由于系统一直待机不断电的模式，所以，暂 \
    不需要将信息写到内存中
void WriteEEPROMCheck(void)
{
  static bool res = false;
  uint8_t status = IsChargeStatus();
 
  if(res == false)
  {
    if(status != STANDBY_STATUS_ID)
    {
      res = true;
    }
  }
  else
  {
    if(status == STANDBY_STATUS_ID)
    {
      WriteToFlash(WRITE_START_ADDR,(uint32_t*)calculate_u16 + \
        CAL_U16_CHG_CYCLE_PERCENT_ID, CAL_U16_ALL_ID);
      res = false;
    }
  }
}

/// 系统参数初始化，通过读取内存的值
void SystemDataInitByReadFlash(void)
{
#if 0
  for(uint8_t i = 0; i < CAL_U16_ALL_ID; i ++)
  {
    calculate_u16[i] = 0xffff;
  }
  WriteToFlash(WRITE_START_ADDR, (uint32_t*)calculate_u16 + \
    CAL_U16_CHG_CYCLE_PERCENT_ID, CAL_U16_ALL_ID);
#endif
  
  ReadFromFlash(WRITE_START_ADDR, (uint32_t*)calculate_u16 + \
    CAL_U16_CHG_CYCLE_PERCENT_ID, CAL_U16_ALL_ID);

  if(calculate_u16[CAL_U16_SOC_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_SOC_ID] = 50;
  }
  
  if(calculate_u16[CAL_U16_SOC_MEASURE_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_SOC_MEASURE_ID] = 50;
  }
  
    if(calculate_u16[CAL_U16_SOC_ESTIMATE_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_SOC_ESTIMATE_ID] = 50;
  }

  if(calculate_u16[CAL_U16_SOH_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_SOH_ID] = 100;
  }

  if(calculate_u16[CAL_U16_CHG_CYCLE_PERCENT_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_CHG_CYCLE_PERCENT_ID] = 0;
  }

  if(calculate_u16[CAL_U16_DSG_CYCLE_PERCENT_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_DSG_CYCLE_PERCENT_ID] = 0;
  }

  if(calculate_u16[CAL_U16_CYCLE_TIMES_ID] == 0xffff)
  {
    calculate_u16[CAL_U16_CYCLE_TIMES_ID] = 0;
  }
}

// 静态电压检查
void AdjSocByStaticVoltage(void)
{
  uint8_t msoc = 0;
  
  uint8_t status = IsChargeStatus();
	
	uint32_t *pointer = NULL;
  uint32_t s_max_volt = 0, s_min_volt = 0;
	uint32_t real_volt = 0, tmax_voltage = 0, tmin_voltage = 0;
	uint8_t i = 0;
	
  /* 只是在待机的时候测 */
  if(status != STANDBY_STATUS_ID)return;
  
  pointer = (uint32_t*)WRITE_START_ADDR0;
  
  s_max_volt = pointer[99];
  s_min_volt = pointer[0];
   
  /* 实际电压估计，内存中单体电压乘以 10 所以，此处一样扩大 */
  real_volt = 10 * cell_v.real_v.general;
  
  tmax_voltage = s_max_volt * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID;
  tmin_voltage = s_min_volt * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID;
  
  // 没有读到电压值
  if(real_volt == 0)return;
  
  for(i = 0; i <= 100; i ++)
  {
    uint32_t t_voltage = pointer[i] * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID;
    
    if(real_volt >= tmax_voltage)
    {
      msoc = 100;
      break;
    }
    else if(real_volt <= tmin_voltage)
    {
      msoc = 0;
    }
    else
    {
      if(t_voltage > real_volt)
      {
        msoc = i;
        break;
      }
    }
  }

  // 根据相差的数值的大小，去调整 R 值的大小，显示值要大，让其变小
  if(calculate_u16[CAL_U16_SOC_ID] > msoc)
  {
    // R 设置为正值
    float R = GetPositiveRvalue(calculate_u16[CAL_U16_SOC_ID] - msoc);
    SocKalmanFliterInit(R);
  }
  
  // 根据相差的数值的大小，去调整 R 值的大小，显示值要小，让其变大
  else if(calculate_u16[CAL_U16_SOC_ID] < msoc)
  {
    // R 设置为负值
    float R = GetNegativeRvalue(msoc - calculate_u16[CAL_U16_SOC_ID]);
    SocKalmanFliterInit(R);
  }
}

void SocKalmanManage(void)
{
  calculate_u16[CAL_U16_SOC_ESTIMATE_ID] = \
    (uint8_t)SocKalmanFliter(calculate_u16[CAL_U16_SOC_MEASURE_ID]);
  
  // 更新显示值：
#if 0
  // 使用估计值
  calculate_u16[CAL_U16_SOC_ID] = calculate_u16[CAL_U16_SOC_ESTIMATE_ID];
#else
  // 使用测量值
  calculate_u16[CAL_U16_SOC_ID] = calculate_u16[CAL_U16_SOC_MEASURE_ID];
#endif
}

/// 系统状态读取
void UpdatePackStatus(void)
{
#if 0
  sif_para.details.bms_current_status.details.chgmos = status3.details.chg_fet;
  sif_para.details.bms_current_status.details.dsgmos = status3.details.dsg_fet;
  sif_para.details.bms_current_status.details.prechgmos = status3.details.pchg_fet;
  sif_para.details.bms_current_status.details.chger_status = 0;
  if(cell_v.sort_volt.volt[0x00] < CONFIG_U16_CUT_UP_VOLTAGE_SIZE_ID)
  sif_para.details.bms_current_status.details.enable_chg = 1;
  else sif_para.details.bms_current_status.details.enable_chg = 0;
  
  sif_para.details.soc = GetNowSOC();
  sif_para.details.cycle.all = calculate_u16[CAL_U16_CYCLE_TIMES_ID];
  
  sif_para.details.temperature = temp_.details.t4.all;
  sif_para.details.highest_single_volt.all = cell_v.sort_volt.volt[0x00];
  sif_para.details.lowest_single_volt.all = cell_v.sort_volt.volt[0x0E];
  sif_para.details.max_allowed_re_current = (uint16_t)(0.05 * CONFIG_U8_E_CAP_ID);
  sif_para.details.max_allowed_chg_current = CONFIG_U8_E_CAP_ID;
  sif_para.details.max_allowed_chg_volt.all = cell_v.max_chg.general / 100;
  
#else
  sif_para.details.byte0 = 0;
  sif_para.details.soc = calculate_u16[CAL_U16_SOC_ID];
  sif_para.details.byte2 = 0;
  sif_para.details.byte3 = 0;
  sif_para.details.byte4 = 0;
  sif_para.details.check_sum = sif_para.details.soc;
  
#endif
}

/// 发送用户协议
bool Send(void)
{
  return SendHandle(sif_para.single, 0x06);
}

/// 打印函数
void PRINT(void)
{
  printf("\r\ntotal_v:%.1f, real_v:%.1f, Max_v:%d, Min_v:%d,soc: %d,curr: %d\r\n", \
        1.0 * cell_v.total_v.general,1.0 * cell_v.real_v.general,\
        cell_v.sort_volt.volt[0], cell_v.sort_volt.volt[0x0E],\
        calculate_u16[CAL_U16_SOC_ID],(int16_t)curr0_.general);
}




