#include "ac1003_uart.h"
#include "ac1003_gpio.h"
#include "ac1003_rcc.h"
#include "stdbool.h"

#define SYNC_HIGH_LEVEL_TIMER            (0x02 - 1)
#define SYNC_LOW_LEVEL_TIMER             (0x3E - 0)
#define LOGICAL_0x00_HIGH_LEVEL_TIMER    (0x02 - 1)
#define LOGICAL_0x00_LOW_LEVEL_TIMER     (0x04 - 1)
#define LOGICAL_0x01_HIGH_LEVEL_TIMER    (0x04 - 1)
#define LOGICAL_0x01_LOW_LEVEL_TIMER     (0x02 - 1)
#define STOP_LOW_LEVEL_TIMER             (0x14 - 1)

enum
{
  Send_Sync_00_Id,
  Send_Sync_01_Id,
  Send_Bit0x01_00_Id,
  Send_Bit0x01_01_Id,
  Send_Bit0x00_00_Id,
  Send_Bit0x00_01_Id,
  Send_Byte_Id,
  Send_Payload_Id,
  Send_Stop_Signal_00_Id,
  Send_Stop_Signal_01_Id,
};

enum
{
  timer_10ms_id,
  timer_100ms_id,
  timer_500ms_id,
  timer_1000ms_id,
  timer_3000ms_id,
  timer_10000ms_id,
  timer_bal_id,
  timer_calibrate_id,
  timer_sms_id,
  timer_all_id,
};

void SendHighBit(bool res);
bool SendHandle(uint8_t *data, uint8_t datalen);
extern bool TimeOut(uint32_t ms, uint8_t timer_id);




