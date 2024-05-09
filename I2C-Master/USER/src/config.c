#include "config.h"
#include "mdefine.h"
#include "menum.h"

uint16_t calculate_u16[CAL_U16_ALL_ID] = {0};

/* ��ȡ SOC --- % */
uint8_t GetNowSOC(void)
{
  return calculate_u16[CAL_U16_SOC_ID] * GetNowSOH() / 100;
}

/* ���� 1% ��¼ */
uint8_t OnePercentCap(void)
{
  static float t_mAh = 0.0;
  static float t_current = 0.0;
  static float t_old_current = 0.0;
  static uint64_t s_timer = 0;
  
  uint64_t t_timer = 0;
  
  uint16_t t_ms = 0;
  
  /* �ٷ�֮һ�ĵ��� --- mAh */
  uint16_t t_CapPercentOne = GetNowSOH() * CONFIG_U8_E_CAP_ID / 10;
  
  /* ����ʱ�� --- ms */
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
  
  /* ��ǰ���� mA */
  if(IsChargeStatus() != STANDBY_STATUS_ID)t_current = (int16_t)curr0_.general;
  else t_current = 0.0;
  
  /* ��ӵ��� kalman �˲� */
  
  /* �����ֵ */
  t_mAh += 1.0 * (t_current + t_old_current) * t_ms / (2 * 3600 * 1000);
  
  /* ���µ��� */
  t_old_current = t_current;
  
  // --------------------------------------------------------------------
  // �ⲿ����ʱ���е������ģ�Ŀǰ����������� 100������������� 33mA������
  // ������������ڸ�ռ 1 / 2������ż���ָ�ռ�� 1 / 2 �е� 1 / 2����ˣ�ֻҪ��
  // ��һ�ڵ�о�ľ��⣬��Ȼ��Ҫ���� 4��Ŀǰͬʱ�����ĵ�о�ľ��������� #define BAL_NUMBER 0x06
  // ��ˣ��ĵ�����Ҫ���� 6
  if(GetEnBalStatus() == true)
  {
    t_mAh += - 1.0 * 33 * t_ms * 6 / (3600 * 1000 * 4);
  }
  // --------------------------------------------------------------------
  /* �����ĵ� --- ʵ�� 10mA */
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

/* ��¼ѭ������ */
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

/* ��ȡ���� */
void mAhIntegral(void)
{
  uint8_t res = OnePercentCap();
  
  if(res == CHARGE_ONE_PERCENT_CAP)
  {
    // soc ����ֵ
    if(calculate_u16[CAL_U16_SOC_MEASURE_ID] >= 100)calculate_u16[CAL_U16_SOC_MEASURE_ID] = 100;
    else calculate_u16[CAL_U16_SOC_MEASURE_ID] ++;
    
    // soc ����ֵ
    SocKalmanManage();
  }
  
  else if(res == DISCHARGE_ONE_PERCENT_CAP)
  {
    // soc ����ֵ
    if(calculate_u16[CAL_U16_SOC_MEASURE_ID] > 0)calculate_u16[CAL_U16_SOC_MEASURE_ID] --;
    else calculate_u16[CAL_U16_SOC_MEASURE_ID] = 0;
    
    // soc ����ֵ
    SocKalmanManage();
  }
  
  /// ��ѹ���� 3500 ��ʾ�����磬���� 2800 Ϊ 0 ��ѹ
  SocAdjustByVoltage();
}

/* ����У׼ --- ���ĩ�� */
void SocAdjustByVoltage(void)
{
#if __MAKE_CHECK02__
  #error Three stage charging check 
#endif
  
  if((cell_v.total_v.general == 0)||(cell_v.total_v.general == 0xffff))return;
  
  /* 
    ��絽������ѹ 3650 * Series
  */
  if(cell_v.real_v.general >= (CONFIG_U16_CUT_UP_VOLTAGE_SIZE_ID - 150) * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID)
  {
    /* ������ */
    calculate_u16[CAL_U16_SOC_ID] = 100;
    RecordCycleTimes();
  }
  
  /*
    �ŵ絽 2800 * Series
  */
  else if(cell_v.real_v.general <= CONFIG_U16_CUT_DO_VOLTAGE_SIZE_ID * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID)
  {
    calculate_u16[CAL_U16_SOC_ID] = 0;
    RecordCycleTimes();
  }
}

/* 
  ϵ������  ��-4      -8     -12
  0.4 - DOD ��-0.581  0.169  0.201 
  0.6 - DOD ��-0.897  1.36   -1.11 
  0.8 - DOD ��-1.34   3.11   -3.04 
  1.0 - DOD ��-1.69   4.48   -4.54 
*/

#if __MAKE_CHECK03__
  #error We check capacity and suppose the DOD is 0.8
#endif

void CalNowSOH(void)
{
  /* ѭ��������� */
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
  ���Ե�ص�����������Ϊ 11Ah��ϵ��������ʱ��Ҫ�����������á�
*/
float SocDecayDueToTemperature(void)
{
  /* ��ͬ�¶�������˥����ϵ */
  float A = - 0.0003488;
  float B = 0.07495;
  float C = 9.092;
  float T = temp_.general[0];
  float soh = (A * T * T + B * T + C) / 11;
  
  /* ���� 1 ���յ��� 1 ������ */
  if(soh > 1)soh = 1.0;
  return soh;
}

/* ��ȡ��ǰ�� SOC ֵ */
uint8_t GetNowSOH(void)
{
  return calculate_u16[CAL_U16_SOH_ID];
}

/// BMS ״̬���
uint8_t IsChargeStatus(void)
{
  if(status3.details.chging == 1)return CHARGE_STATUS_ID;
  else if(status3.details.dsging == 1)return DISCHARGE_STATUS_ID;
  else return STANDBY_STATUS_ID;
}

/// д�ڴ��飬��Ҫע��ĵط��ǵ���⵽С�� 1A �ĵ���ʱ��\
    ����Ϊ���ڴ���ģʽ������ϵͳһֱ�������ϵ��ģʽ�����ԣ��� \
    ����Ҫ����Ϣд���ڴ���
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

/// ϵͳ������ʼ����ͨ����ȡ�ڴ��ֵ
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

// ��̬��ѹ���
void AdjSocByStaticVoltage(void)
{
  uint8_t msoc = 0;
  
  uint8_t status = IsChargeStatus();
	
	uint32_t *pointer = NULL;
  uint32_t s_max_volt = 0, s_min_volt = 0;
	uint32_t real_volt = 0, tmax_voltage = 0, tmin_voltage = 0;
	uint8_t i = 0;
	
  /* ֻ���ڴ�����ʱ��� */
  if(status != STANDBY_STATUS_ID)return;
  
  pointer = (uint32_t*)WRITE_START_ADDR0;
  
  s_max_volt = pointer[99];
  s_min_volt = pointer[0];
   
  /* ʵ�ʵ�ѹ���ƣ��ڴ��е����ѹ���� 10 ���ԣ��˴�һ������ */
  real_volt = 10 * cell_v.real_v.general;
  
  tmax_voltage = s_max_volt * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID;
  tmin_voltage = s_min_volt * CONFIG_U8_SERIES_V_NUMBER_SIZE_ID;
  
  // û�ж�����ѹֵ
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

  // ����������ֵ�Ĵ�С��ȥ���� R ֵ�Ĵ�С����ʾֵҪ�������С
  if(calculate_u16[CAL_U16_SOC_ID] > msoc)
  {
    // R ����Ϊ��ֵ
    float R = GetPositiveRvalue(calculate_u16[CAL_U16_SOC_ID] - msoc);
    SocKalmanFliterInit(R);
  }
  
  // ����������ֵ�Ĵ�С��ȥ���� R ֵ�Ĵ�С����ʾֵҪС��������
  else if(calculate_u16[CAL_U16_SOC_ID] < msoc)
  {
    // R ����Ϊ��ֵ
    float R = GetNegativeRvalue(msoc - calculate_u16[CAL_U16_SOC_ID]);
    SocKalmanFliterInit(R);
  }
}

void SocKalmanManage(void)
{
  calculate_u16[CAL_U16_SOC_ESTIMATE_ID] = \
    (uint8_t)SocKalmanFliter(calculate_u16[CAL_U16_SOC_MEASURE_ID]);
  
  // ������ʾֵ��
#if 0
  // ʹ�ù���ֵ
  calculate_u16[CAL_U16_SOC_ID] = calculate_u16[CAL_U16_SOC_ESTIMATE_ID];
#else
  // ʹ�ò���ֵ
  calculate_u16[CAL_U16_SOC_ID] = calculate_u16[CAL_U16_SOC_MEASURE_ID];
#endif
}

/// ϵͳ״̬��ȡ
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

/// �����û�Э��
bool Send(void)
{
  return SendHandle(sif_para.single, 0x06);
}

/// ��ӡ����
void PRINT(void)
{
  printf("\r\ntotal_v:%.1f, real_v:%.1f, Max_v:%d, Min_v:%d,soc: %d,curr: %d\r\n", \
        1.0 * cell_v.total_v.general,1.0 * cell_v.real_v.general,\
        cell_v.sort_volt.volt[0], cell_v.sort_volt.volt[0x0E],\
        calculate_u16[CAL_U16_SOC_ID],(int16_t)curr0_.general);
}




