#include "ac1003_uart.h"
#include "ac1003_gpio.h"
#include "ac1003_rcc.h"
#include "stdbool.h"
#include "sh367309.h"
#include "test_flash.h"

uint16_t GetRemainingRealTimeAh(void);
uint16_t GetRemainingAllAh(void);
uint8_t GetNowSOC(void);
uint8_t OnePercentCap(void);
void RecordCycleTimes(void);
void mAhIntegral(void);
void SocAdjustByVoltage(void);
void CalNowSOH(void);
float SocDecayDueToTemperature(void);
uint8_t GetNowSOH(void);
void WriteEEPROMCheck(void);
void SystemDataInitByReadFlash(void);
void AdjSocByStaticVoltage(void);
uint8_t IsChargeStatus(void);
void PrintfOcv(bool res);

extern RO_DEF_CELLVOL vol_ ;
extern RO_DEF_TEMPERATURE temp_;
extern RO_DEF_CURRENT0 curr0_;
extern RO_DEF_CURRENT1 curr1_;
extern RO_DEF_BSTATUS1 status1;
extern RO_DEF_BSTATUS2 status2;
extern RO_DEF_BSTATUS3 status3;
extern RO_DEF_CELLVOL_D cell_v;
extern float CurrentKalmanFliter(float Measurement_Value);
extern float SocKalmanFliter(float Measurement_Value);

extern float GetPositiveRvalue(uint8_t x);
extern float GetNegativeRvalue(uint8_t x);

extern bool GetEnBalStatus(void);
extern TestStatus WriteToFlash(uint32_t Addr, uint32_t Data[], uint16_t Datalen);
extern TestStatus ReadFromFlash(uint32_t Addr, uint32_t Data[], uint16_t Datalen);
extern bool SendHandle(uint8_t *data, uint8_t datalen);
extern void SocKalmanFliterInit(float R);
void SocKalmanManage(void);


#if 0

#pragma pack(1)
union
{
  struct
  {
    union
    {
      struct
      {
        uint8_t enable_chg : 0x01;
        uint8_t resversed0:0x02;
        uint8_t chger_status:0x01;
        uint8_t resversed1:0x01;
        uint8_t prechgmos:0x01;
        uint8_t dsgmos:0x01;
        uint8_t chgmos:0x01;
      }details;
      uint8_t general;
    }bms_current_status;

    uint8_t soc;
    
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }cycle;
    
    int8_t temperature;
    
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }highest_single_volt;
    
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }lowest_single_volt;
    
    uint8_t max_allowed_re_current;
    uint8_t max_allowed_chg_current;
    
    union
    {
      uint8_t single[0x02];
      uint16_t all;
    }max_allowed_chg_volt;
    
  }details;
  
  uint8_t single[13];
}sif_para;

#pragma pack()

#else
#pragma pack(1)
union
{
  struct
  {
    uint8_t byte0;
    uint8_t soc;
    uint8_t byte2;
    uint8_t byte3;
    uint8_t byte4;
    uint8_t check_sum;
  }details;
  
  uint8_t single[0x06];
}sif_para;

#pragma pack()
#endif






