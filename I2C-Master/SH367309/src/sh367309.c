#include "sh367309.h"
#include "math.h"
#include "menum.h"


// 基本参数
RO_DEF_CELLVOL vol_      = {0};
RO_DEF_TEMPERATURE temp_ = {0};
RO_DEF_CURRENT0 curr0_   = {0};
RO_DEF_CURRENT1 curr1_   = {0};
RO_DEF_BSTATUS1 status1  = {0};
RO_DEF_BSTATUS2 status2  = {0};
RO_DEF_BSTATUS3 status3  = {0};
RO_DEF_CELLVOL_D cell_v  = {0};
RW_DEF_CONF ctrl_conf    = {0};
RW_DEF_BFLAG1 m_bflag1   = {0};
RO_DEF_BFLAG2 m_bflag2   = {0};

// 总共 50 条记录
#define RECORD_SIZE 0x32
#define MEM_OFFSET 0x04


RO_DEF_RECORD m_record[RECORD_SIZE] = {0};
static uint8_t record_counter = 0;

void Assert(bool res)
{
  if(res == false)while(1);
}

// MOS 管状态
void Mos(bool res, uint32_t *pComAddr)
{
  if(res == true)
  {
    /// 打开 MOS 管
    if((status3.details.chg_fet == 0)||(status3.details.dsg_fet == 0))
    {
      ctrl_conf.details.chgmos = 1;
      ctrl_conf.details.dsgmos = 1;
      SetRegister(pComAddr, CONF_ADDR, &ctrl_conf.general, 0x01);
    }
  }
  else
  {
    /// 关闭 MOS 管
    if((status3.details.chg_fet == 1)||(status3.details.dsg_fet == 1))
    {
      ctrl_conf.details.chgmos = 0;
      ctrl_conf.details.dsgmos = 0;
      SetRegister(pComAddr, CONF_ADDR, &ctrl_conf.general, 0x01);
    }
  }
}

// 1.8s 左右时间得到一次温度值
void GetMcuTemperature(void)
{
  // 读 MCU 获得温度 1/(10 + Rt) = adcvalue/(4095 * Rt)
  uint16_t adcvalue = 0;
  if(AdcForTemperature(&adcvalue) == true)
  {
    float T = 0;
    float Rt = 10 * adcvalue /(4095 - adcvalue);
    T = Rt2Temperature(Rt);
    temp_.details.t4.all = (int16_t)T;
  }
}

bool MosTempProtectedCheck(void)
{
  static bool t_protected_h = false;
    
  /// 充电高温保护温度 60，释放 55
  if(status3.details.chging == 1)
  {
    if(temp_.details.t4.all > 60)
    {
      t_protected_h = true;
    }
    else
    {
      if(t_protected_h == true)
      {
        if(temp_.details.t4.all < 55)
        {
          t_protected_h = false;
        }
      }
    }
  }
  else if(status3.details.dsging == 1)
  {
    /// 放电高温保护温度 70，释放 65
    if(temp_.details.t4.all > 70)
    {
      t_protected_h = true;
    }
    else
    {
      if(t_protected_h == true)
      {
        if(temp_.details.t4.all < 65)
        {
          t_protected_h = false;
        }
      }
    }
  }
  else
  {
    /// 待机时测得的 MOS 温度超过 90 度
    if(temp_.details.t4.all == 99)
    {
      t_protected_h = true;
      printf("\r\nThermistor Error!");
    }
    else
    {
      t_protected_h = false;
    }
  }
  
  /// 检测到发生保护
  if(t_protected_h == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

static bool en_bal = false;

void SetEnBalStatus(bool res)
{
  en_bal = res;
}

bool GetEnBalStatus(void)
{
  return en_bal;
}

/// 均衡控制 ,50mv 开启均衡控制，注意均衡开启时的电量变化
void BalanceManage(uint32_t *prComAddr, uint32_t *pwComAddr)
{
  #define BAL_NUMBER 0x06
  
  uint8_t bal_pos[BAL_NUMBER] = {0};
  
  memcpy(bal_pos,cell_v.sort_volt.pos,BAL_NUMBER);
  
  // 上位机设置的均衡条件，测试时是 3000
  if((status3.details.chging == 1)&& \
     (cell_v.sort_volt.volt[0x00] - cell_v.sort_volt.volt[0x0E] > 5))
  {
    /// VPRO 只要是高电平就会进入烧写模式，移除高压就会进入复位状态，进而根据 \
        MODE 管脚进入相应的状态，程序在正常的充放电过程中应该避免 VPRO 频繁拉高 \
        从而导致系统频繁复位断电
    if(GetEnBalStatus() == false)
    {
      // SetVProStatus(true);
      // EnableExternalBalance(prComAddr, pwComAddr, true);
      // SetVProStatus(false);
      
      printf("\r\nStart External Balance !\r\n");
      SetEnBalStatus(true);
    }
  }
  else
  {
    // 此前是开启了均衡的
    if(GetEnBalStatus() == true)
    {
      // SetVProStatus(true);
      // EnableExternalBalance(prComAddr, pwComAddr, false);
      // SetVProStatus(false);
      
      printf("\r\nStop External Balance !\r\n");
      SetEnBalStatus(false);
    }
  }
    
  if(GetEnBalStatus() == true)
  {
    // 开启平衡具体的电芯开关
    uint8_t *temp = bal_pos;
    uint8_t t_temp[0x04] = {0};
      
    for(uint8_t i = 0; i < BAL_NUMBER; i ++)
    {
      /// 0x41_H 0x42_L
      if(temp[i] > 0x07)
      {
        t_temp[0] |= (1 << (temp[i] - 0x08));
      }
      else
      {
        t_temp[1] |= (1 << temp[i]);
      }
    }
    
    SetRegister(pwComAddr, 0x41, &t_temp[0], 0x01);
    printf("\r\nBalance Cell Pos0 : %x !\r\n",t_temp[0]);
          
    // 需要延时 1ms
    SetRegister(pwComAddr, 0x42, &t_temp[1], 0x01);
    printf("\r\nBalance Cell Pos1 : %x !\r\n",t_temp[1]);
  }
}

// 使能 / 关闭外部均衡
void EnableExternalBalance(uint32_t *prComAddr, uint32_t *pwComAddr, bool res)
{
  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
        
  // 开启外部平衡
  uint8_t t_memory[0x02 + MEM_OFFSET] = {0x34,SCONF1_ADDR,0x01,0x35};
 
  FUNC func = {0};
  func.p = prComAddr;
  func.read(SCONF1_ADDR, t_memory + MEM_OFFSET, 0x01);
        
  RW_DEF_SCONF1 sconf1 = {0};
  sconf1.general = t_memory[MEM_OFFSET];
  
  if(res == true)sconf1.details.bal_ctrl = 0x01;
  else sconf1.details.bal_ctrl = 0x00;
  
  t_memory[MEM_OFFSET] = sconf1.general;
  SetRegister(pwComAddr, SCONF1_ADDR, &t_memory[MEM_OFFSET], 0x01);
}

/// 获取内部参考电阻值
float GetTemperatureRref(uint32_t *pComAddr)
{
  float rref = 0;

  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;
  
  uint8_t t_memory[0x02 + MEM_OFFSET] = {0x34,RREF_ADDR,0x01,0x35};
  
  func.read(RREF_ADDR, t_memory + MEM_OFFSET, 0x01);
  
  rref = 6.8 + 0.05 * (t_memory[MEM_OFFSET] & 0x7f);
  
  return rref;
}

// 读取电压 --- mv
void GetAllSingleVoltage(uint32_t *pComAddr)
{
  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;
  
  uint8_t t_memory[0x22 + MEM_OFFSET] = {0x34,CELLVOL_ADDR,0x20,0x35};
  
  // 读取电压值
  func.read(CELLVOL_ADDR, (uint8_t*)t_memory + MEM_OFFSET, 0x20);
  
  // 加上 CRC 校验
  if(IsDataAllRight(t_memory, 0x20 + MEM_OFFSET) == true)
  {
    // 字节序转化
    Endian2Bytes((uint16_t*)t_memory + MEM_OFFSET / 0x02, vol_.general, 16);
    
    // 转化为实际电压值
    v_switch(vol_.general, vol_.general, 16);
  }
}

//  读取电流 --- mA
void GetCurrentParameters(uint32_t *pComAddr)
{
  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;
  
  uint8_t t_memory[0x04 + MEM_OFFSET] = {0x34,CURRENT0_ADDR,0x02,0x35};

  // 读取电流 --- 周期要短
  func.read(CURRENT0_ADDR, (uint8_t*)t_memory + MEM_OFFSET, 0x02);
  
  if(IsDataAllRight(t_memory, 0x02 + MEM_OFFSET) == true)
  {
    // 电流 0 --- 单位 mA
    Endian2Bytes((uint16_t*)&t_memory + MEM_OFFSET / 0x02, (uint16_t*)&curr0_.general, 1);
    
    c0_switch((int16_t*)&curr0_.general, (int16_t*)&curr0_.general);
  }
}

// 读取温度 --- ℃
void GetTemperatureParameters(uint32_t *pComAddr)
{
  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;
  
  uint8_t t_memory[0x0A + MEM_OFFSET] = {0x34,TEMPERATURE_ADDR,0x06,0x35};
  
  float rref = GetTemperatureRref(pComAddr);
  
  // 读取温度
  func.read(TEMPERATURE_ADDR, (uint8_t*)t_memory + MEM_OFFSET, 0x06);
  
  // 温度
  Endian2Bytes((uint16_t*)t_memory + MEM_OFFSET / 2, temp_.general, 3);
  
  t_switch((int16_t*)temp_.general, (int16_t*)temp_.general, 3, rref);
}

// 读取电芯状态
void GetCellStatus(uint32_t *pComAddr)
{
  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;
  
  uint8_t t_memory[0x05 + MEM_OFFSET] = {0x34,BSTATUS1_ADDR,0x03,0x35};

  func.read(BSTATUS1_ADDR, t_memory + MEM_OFFSET, 0x03);
  
  status1.general = t_memory[0x00 + MEM_OFFSET];
  status2.general = t_memory[0x01 + MEM_OFFSET];
  status3.general = t_memory[0x02 + MEM_OFFSET];
}

// 读取 CONF 状态
void GetConfStatus(uint32_t *pComAddr)
{
  typedef union
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;
  
  uint8_t t_memory[0x03 + MEM_OFFSET] = {0x34,CONF_ADDR,0x01,0x35};

  func.read(CONF_ADDR, t_memory + MEM_OFFSET, 0x01);
  
  ctrl_conf.general = t_memory[0x00 + MEM_OFFSET];
}

// 写寄存器状态
void SetRegister(uint32_t *pComAddr, uint8_t reg_addr, uint8_t *temp, uint8_t t_size)
{
  typedef union
  {
    void (*write)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  uint8_t data[0x10] = {0};
  
  FUNC func = {0};
  func.p = pComAddr;
  
  // 设备地址 --- 写
  data[0] = WRITE_SLAVE;
  
  // 寄存器地址
  data[1] = reg_addr;
  
  // 计算 CRC8 准备
  for(uint8_t i = 2, j = 0; j < t_size; i ++, j ++)
  {
    Assert(i < 0x10);
    data[i] = temp[j];
  }
  
  uint8_t crc = crc8(data, t_size + 2);
  
  memcpy(data,temp,t_size);
  
  data[t_size] = crc;
  
  func.write(reg_addr, data, t_size + 1);
}

// 清除状态寄存器
void ClrStatusRegister(uint32_t *pComAddr)
{
  uint8_t temp[0x03] = {0};
  static uint8_t counter1 = 0;
  static uint8_t counter2 = 0;
  
  if(m_bflag1.general)
  {
    if(counter1 ++ >= 10)
    {
      counter1 = 0;
      SetRegister(pComAddr, 0x70, &temp[0], 0x01);
    }
  }
  
  if(m_bflag2.general)
  {
    if(counter2 ++ >= 10)
    {
      counter2 = 0;
      SetRegister(pComAddr, 0x71, &temp[1], 0x01);
    }
  }
}

// 双字节，字节序切换
void Endian2Bytes(uint16_t*dataIn, uint16_t*dataOut, uint8_t datalen)
{
  union
  {
    uint8_t single[0x02];
    uint16_t all;
  }t[0x02];
    
  for(uint8_t i = 0; i < datalen; i ++)
  {
    // 小端或者大端
    t[0].all = dataIn[i];
    
    // 大端或者小端
    t[1].single[0] = t[0].single[1];
    t[1].single[1] = t[0].single[0];
      
    dataOut[i] = t[1].all;
  }
}
#include "math.h"
#include "stdlib.h"
// 读到的电压值转化为相应的电压值
void v_switch(uint16_t *dataIn, uint16_t *dataOut, uint8_t datalen)
{
  for(uint8_t i = 0; i < datalen; i ++)
  {
    dataOut[i] = abs((int16_t)dataIn[i]) * 5 / 32;
  }
}

// 单位是 mA
void c0_switch(int16_t *dataIn, int16_t *dataOut)
{
  dataOut[0] = (65 * dataIn[0] - 269) / 10;
  
  // 获得电流，对读到的电流进行滤波
  dataOut[0] = (int16_t)CurrentKalmanFliter(dataOut[0]);
  dataOut[0] -= (0.0348 * dataOut[0] - 47.65);
}
  
void c1_switch(int16_t *dataIn, int16_t *dataOut, uint8_t Rsense)
{
  dataOut[0] = 200 * dataIn[0] /(21470 * Rsense);
}

void t_switch(int16_t *dataIn, int16_t *dataOut, uint8_t datalen, float Ref)
{
  float Rt = 0;
  
  for(uint8_t i = 0; i < datalen; i ++)
  {
    Rt = (dataIn[i] * Ref/(32768 - dataIn[i]));
    dataOut[i] = (uint16_t)round(Rt2Temperature(Rt));
  }
}

// 根据电阻的值查询温度函数
float Rt2Temperature(float Rt)
{
  float Rp = 10000.0;               // 10K
  float T2 = (273.15 + 25.0);       // T2
  float B  = 3435.0;                // B
  float Ka = 273.15;
  float temp;
  temp  = 1000 * Rt / Rp;
  temp  = log(temp);                // ln(Rt/Rp)
  temp /= B;                        // ln(Rt/Rp)/B
  temp += (1 / T2);
  temp  = (1 / temp);
  temp -= Ka;
  return temp;
}

void GetLimitedSingleVoltage(void)
{
  uint16_t total_v = 0;
  uint16_t real_v = 0;
  
  DescendingOrderSort(vol_.general, cell_v.sort_volt.volt, cell_v.sort_volt.pos, 0x10);
  
  cell_v.max_chg.general = CONFIG_U8_SERIES_V_NUMBER_SIZE_ID * \
    CONFIG_U16_CUT_UP_VOLTAGE_SIZE_ID;
  
  for(uint8_t i = 0; i < 0x10; i ++)
  {
    total_v += cell_v.sort_volt.volt[i];
    
    if((i > 0)&&(i < 0x0c))
    {
      /* 去除一个最大值以及三个最小值 */
      real_v += cell_v.sort_volt.volt[i];
    }
  }
  
  /* 15s 的电芯 */
  cell_v.real_v.general = real_v * 15 / 11;
  
  cell_v.total_v.general = total_v;
}

void DescendingOrderSort(uint16_t *value, uint16_t *a, uint8_t *index, uint8_t size) 
{        
  uint8_t i, j;
  uint16_t temp;
  
  for (i = 0; i < size; i ++) 
  {
    a[i] = value[i];
    index[i] = i;  
  }

  for (i = 0; i < size - 1; i ++) 
  {
    for (j = 0; j < size - 1 - i; j ++) 
    {
      if (a[j] < a[j + 1]) 
      {
        // 交换数组元素
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
              
        // 交换位置编号数组元素
        temp = index[j];
        index[j] = index[j + 1];
        index[j + 1] = temp;
      }
    }
  }
}

void GetPackProtectedStatus(uint32_t *pComAddr)
{
  typedef union                                                                                                                              
  {
    void (*read)(uint8_t regAddr, uint8_t *rData, uint8_t rSize);
    uint32_t *p;
  }FUNC;
  
  FUNC func = {0};
  func.p = pComAddr;

  uint8_t t_memory1[0x03 + MEM_OFFSET] = {0x34,BFLAG1_ADDR,0x01,0x35};
  uint8_t t_memory2[0x03 + MEM_OFFSET] = {0x34,BFLAG2_ADDR,0x01,0x35};
  
  func.read(BFLAG1_ADDR, t_memory1 + MEM_OFFSET, 0x01);
  m_bflag1.general = t_memory1[0x00 + MEM_OFFSET];  
  
  func.read(BFLAG2_ADDR, t_memory2 + MEM_OFFSET, 0x01);
  m_bflag2.general = t_memory2[0x00 + MEM_OFFSET];
  
  m_bflag2.details.cadc_flag = 0;
  m_bflag2.details.vadc_flag = 0;
}

// 采用 unix 时间，需要对时
void RecordProtectedStatus(void)
{
  if(m_bflag1.details.occ_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x01;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nover current in charge !\r\n");
  }
  else if(m_bflag1.details.ocd_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x02;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nover current in discharge !\r\n");
  }
  else if(m_bflag1.details.ov_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x03;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nover voltage !\r\n");
  }
  else if(m_bflag1.details.pf_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x04;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nsecond over voltage !\r\n");
  }
  else if(m_bflag1.details.sc_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x05;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nshort circuit !\r\n");
  }
  else if(m_bflag1.details.uv_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x06;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nunder voltage !\r\n");
  }
  else if(m_bflag1.details.load_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x07;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nover load!\r\n");
  }
  else if(m_bflag1.details.wdt_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x08;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nSh367309 watch dog flow!\r\n");
  }
  
  if(m_bflag2.details.cadc_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x09;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nCadc interrupted !\r\n");
  }
  else if(m_bflag2.details.otc_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x0A;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nhigh temperature in charge !\r\n");
  }
  else if(m_bflag2.details.otd_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x0B;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nhigh temperature in discharge !\r\n");
  }
  else if(m_bflag2.details.rst_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x0C;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nSh367309 reset !\r\n");
  }
  else if(m_bflag2.details.utc_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x0D;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nlow temperature in charge !\r\n");
  }
  else if(m_bflag2.details.utd_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x0E;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\nlow temperature in discharge !\r\n");
  }
  // else if(m_bflag2.details.vadc_flag)printf("\r\nVadc interrupted !\r\n");
  else if(m_bflag2.details.wake_flag)
  {
    struct tm str_tt = {0};
    GetStandardTime(&str_tt);
    m_record[record_counter].err_code = 0x0F;
    m_record[record_counter].details.year = str_tt.tm_year;
    m_record[record_counter].details.mon = str_tt.tm_mon;
    m_record[record_counter].details.day = str_tt.tm_mday;
    m_record[record_counter].details.hour = str_tt.tm_hour;
    m_record[record_counter].details.min = str_tt.tm_min;
    m_record[record_counter].details.sec = str_tt.tm_sec;
    if(record_counter ++ >= RECORD_SIZE)record_counter = 0;
    // printf("\r\naWake !\r\n");
  }
}

// basetime 定时器为 1ms
bool TimeOut(uint32_t ms, uint8_t timer_id)
{
  static uint64_t timer[timer_all_id] = {0};
  
  uint64_t t_timer = GetTick();
    
  if(ms == 0)timer[timer_id] = t_timer;

  if(t_timer > timer[timer_id])
  {
      if(t_timer - timer[timer_id] > ms)
      {
        timer[timer_id] = t_timer;
        return true;
      }
      else return false;
  }
  else if(t_timer < timer[timer_id])
  {
    if(t_timer + 0xffffffffffffffff - timer[timer_id] > ms)
    {
        timer[timer_id] = t_timer;
        return true;
    }
    else return false;
  }
  else return false;
}

uint8_t crc8(uint8_t* pBuffer, uint8_t bufSize)
{
  uint8_t crc = 0;
  
  if ( bufSize <= 0 )return crc;
  
  while(bufSize -- != 0)
  {
    for(uint8_t i = 0x80; i != 0; i /= 2)
    {
      if((crc & 0x80) != 0)
      {
        crc *= 2;
        crc ^= 0x07;
      }
      else crc *= 2;
      
      if ((*pBuffer & i) != 0)crc ^= 0x07;
    }
    pBuffer ++;
  }
  return crc;
}

bool IsDataAllRight(uint8_t* pBuffer, uint8_t bufSize)
{
  if(crc8(pBuffer, bufSize) == pBuffer[bufSize])return true;
  else return false;
}

/* 解析打印故障码 */
void AnalysisAndPrintErrCode(void)
{
  static uint8_t i = 0;
  
  switch(m_record[i].err_code)
  {
    case 0x00:
    break;
    case 0x01:
      printf("over current in charge happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x02:
      printf("over current in discharge happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x03:
      printf("over voltage happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x04:
      printf("second over voltage happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x05:
      printf("short circuit happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x06:
      printf("under voltage happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x07:
      printf("over load happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x08:
    break;
    case 0x09:
    break;
    case 0x0A:
      printf("high temperature in charge happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x0B:
      printf("high temperature in discharge happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x0C:
    break;
    case 0x0D:
      printf("low temperature in charge happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x0E:
      printf("low temperature in discharge happened, the time is:\r\n!");
      printf("%04u-%02u-%02u %02u:%02u:%02u\r\n",m_record[i].details.year + 1900, m_record[i].details.mon + 1,\
      m_record[i].details.day, m_record[i].details.hour, m_record[i].details.min, m_record[i].details.sec);
    break;
    case 0x0F:
    break;
  }
  
  if(i ++ >= RECORD_SIZE - 1)i = 0;
}



