#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdint.h"
#include "ac1003_delay.h"
#include "mdefine.h"
#include "time.h"


#ifndef __SH367309__
#define __SH367309__


#define WRITE_SLAVE 0x34|0x00
#define READ_SLAVE  0x34|0x01

#define SCONF1_ADDR 0x00
typedef union __SCONF1__
{
  struct
  {
    uint8_t cn0_cn3   : 0x04;
    uint8_t bal_ctrl  : 0x01;
    uint8_t ocpm      : 0x01;
    uint8_t en_mos    : 0x01;
    uint8_t en_pch    : 0x01;
  }details;
  uint8_t general;
}RW_DEF_SCONF1;

/// 定义寄存器地址
#define CONF_ADDR 0x40
typedef union __CONF__
{
  struct
  {
    uint8_t idle   : 0x01;
    uint8_t sleep  : 0x01;
    uint8_t enwdt  : 0x01;
    uint8_t cadcon : 0x01;
    uint8_t chgmos : 0x01;
    uint8_t dsgmos : 0x01;
    uint8_t pchmos : 0x01;
    uint8_t ocrc   : 0x01;
  }details;
  uint8_t general;
}RW_DEF_CONF;

#define BSTATUS1_ADDR 0x43
typedef union __BSTATUS1__
{
  struct
  {
    uint8_t ov  : 0x01;
    uint8_t uv  : 0x01;
    uint8_t ocd1: 0x01;
    uint8_t ocd2: 0x01;
    uint8_t occ : 0x01;
    uint8_t sc  : 0x01;
    uint8_t pf  : 0x01;
    uint8_t wdt : 0x01;
  }details;
  uint8_t general;
}RO_DEF_BSTATUS1;

#define BFLAG1_ADDR 0x70
typedef union __BFLAG1__
{
  struct
  {
    uint8_t ov_flag  : 0x01;
    uint8_t uv_flag  : 0x01;
    uint8_t ocd_flag : 0x01;
    uint8_t load_flag: 0x01;
    uint8_t occ_flag : 0x01;
    uint8_t sc_flag  : 0x01;
    uint8_t pf_flag  : 0x01;
    uint8_t wdt_flag : 0x01;
  }details;
  uint8_t general;
}RW_DEF_BFLAG1;

#define BSTATUS2_ADDR 0x44
typedef union __BSTATUS2__
{
  struct
  {
    uint8_t utc  : 0x01;
    uint8_t otc  : 0x01;
    uint8_t utd  : 0x01;
    uint8_t otd  : 0x01;
    uint8_t res  : 0x04;
  }details;
  uint8_t general;
}RO_DEF_BSTATUS2;

#define BFLAG2_ADDR 0x71
typedef union __BFLAG2__
{
  struct
  {
    uint8_t utc_flag  : 0x01;
    uint8_t otc_flag  : 0x01;
    uint8_t utd_flag : 0x01;
    uint8_t otd_flag: 0x01;
    uint8_t vadc_flag : 0x01;
    uint8_t cadc_flag : 0x01;
    uint8_t wake_flag  : 0x01;
    uint8_t rst_flag  : 0x01;
  }details;
  uint8_t general;
}RO_DEF_BFLAG2;

#define BSTATUS3_ADDR 0x45
typedef union __BSTATUS3__
{
  struct
  {
    uint8_t dsg_fet   : 0x01;
    uint8_t chg_fet   : 0x01;
    uint8_t pchg_fet  : 0x01;
    uint8_t l0v       : 0x01;
    uint8_t eepr_wr   : 0x01;
    uint8_t res       : 0x01;
    uint8_t dsging    : 0x01;
    uint8_t chging    : 0x01;
  }details;
  uint8_t general;
}RO_DEF_BSTATUS3;

#define RREF_ADDR 0x19
typedef union __RREF__
{
  struct
  {
    uint8_t tr0:1;
    uint8_t tr1:1;
    uint8_t tr2:1;
    uint8_t tr3:1;
    uint8_t tr4:1;
    uint8_t tr5:1;
    uint8_t tr6:1;
    uint8_t res:1; 
  }details;
  uint8_t general;
}RO_DEF_RREF;

#define CELLVOL_ADDR 0x4E
typedef union __CELLVOL__
{
  struct
  {
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_00;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_01;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_02;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_03;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_04;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_05;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_06;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_07;
    
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_08;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_09;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_10;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_11;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_12;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_13;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_14;
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cell_15;
  }details;
  
  uint16_t general[0x10];
}RO_DEF_CELLVOL;

#define TEMPERATURE_ADDR 0x46
typedef union __TEMPERATURE__
{
  struct
  {
    union
    {
      uint8_t single[0x02];
      int16_t all;
    }t1;
    union
    {
      uint8_t single[0x02];
      int16_t all;
    }t2;
    union
    {
      uint8_t single[0x02];
      int16_t all;
    }t3;
    
    union
    {
      uint8_t single[0x02];
      int16_t all;
    }t4;
    
  }details;
  
  uint16_t general[0x04];
  
}RO_DEF_TEMPERATURE;

#define CURRENT0_ADDR 0x4C
typedef union __CURRENT0__
{
  uint8_t single[0x04];
  int32_t general;
  
}RO_DEF_CURRENT0;

#define CURRENT1_ADDR 0x6E
typedef union __CURRENT1__
{
  uint8_t single[0x04];
  int32_t general;
  
}RO_DEF_CURRENT1;


typedef struct CELL_VOLT
{
  union
  {
    uint8_t single[0x02];
    uint16_t general;
  }max_chg;
  
  union
  {
    uint8_t single[0x02];
    uint16_t general;
  }total_v;
  
  union
  {
    uint8_t single[0x02];
    uint16_t general;
  }real_v;
  
  struct
  {
    uint16_t volt[0x10];
    uint8_t pos[0x10];  
  }sort_volt;
  
}RO_DEF_CELLVOL_D;

typedef struct __RECORD__
{
  uint8_t  err_code;
    
  struct
  {
    uint64_t year : 24;
    uint64_t mon  : 8;
    uint64_t day  : 8;
    uint64_t hour : 8;
    uint64_t min  : 8;
    uint64_t sec  : 8;
  }details;

}RO_DEF_RECORD;

void Endian2Bytes(uint16_t*dataIn, uint16_t*dataOut, uint8_t datalen);

// 读到的电压值转化为相应的电压值
void v_switch(uint16_t *dataIn, uint16_t *dataOut, uint8_t datalen);
void c0_switch(int16_t *dataIn, int16_t *dataOut);
void c1_switch(int16_t *dataIn, int16_t *dataOut, uint8_t Rsense);
void t_switch(int16_t *dataIn, int16_t *dataOut, uint8_t datalen, float Ref);
void GetConfStatus(uint32_t *pComAddr);
bool MosTempProtectedCheck(void);
void BalanceManage(uint32_t *prComAddr, uint32_t *pwComAddr);
void SetRegister(uint32_t *pComAddr, uint8_t reg_addr, uint8_t *temp, uint8_t t_size);
uint8_t crc8(uint8_t* pBuffer, uint8_t bufSize);
void EnableExternalBalance(uint32_t *prComAddr, uint32_t *pwComAddr, bool res);
float Rt2Temperature(float Rt);
bool IsDataAllRight(uint8_t* pBuffer, uint8_t bufSize);
void DescendingOrderSort(uint16_t *value, uint16_t *a, uint8_t *index, uint8_t size) ;

extern uint64_t GetTick(void);
extern bool AdcForTemperature(uint16_t *adcvalue);
extern void GetStandardTime(struct tm * str_tt);
extern void SetVProStatus(bool res);
extern float CurrentKalmanFliter(float Measurement_Value);

#endif


