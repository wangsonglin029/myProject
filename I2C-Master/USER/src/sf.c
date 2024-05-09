#include "sf.h"

static bool allow_send = false;

// ????????
void SendHighBit(bool res)
{
#if 0
  if(res == true)GPIO_SetBits(GPIOC, GPIO_Pin_5);
  else GPIO_ResetBits(GPIOC, GPIO_Pin_5);
#else
  if(res == false)GPIO_SetBits(GPIOC, GPIO_Pin_5);
  else GPIO_ResetBits(GPIOC, GPIO_Pin_5);
#endif
}

bool SendHandle(uint8_t *data, uint8_t datalen)
{
  static bool timer_init = false;
  static uint8_t step = 0;
  static uint8_t bit_counter = 0;
  static uint8_t byte_counter = 0;
  bool res = false;
  static uint8_t byte = 0;
    
  if(timer_init == false)
  {
    timer_init = true;
    TimeOut(0, timer_sms_id);
  }

  switch(step)
  {
    case Send_Sync_00_Id:
      SendHighBit(false);
      if(TimeOut(SYNC_LOW_LEVEL_TIMER, timer_sms_id))
      {
        step = Send_Sync_01_Id;
        timer_init = false;
      }
    break;
    
    case Send_Sync_01_Id:
      SendHighBit(true);
      if(TimeOut(SYNC_HIGH_LEVEL_TIMER, timer_sms_id))step = Send_Payload_Id;
    break;
    
    case Send_Bit0x01_00_Id:
      SendHighBit(false);
      if(TimeOut(LOGICAL_0x01_LOW_LEVEL_TIMER, timer_sms_id))
      {
        step = Send_Bit0x01_01_Id;
        timer_init = false;
      }
    break;
    
    case Send_Bit0x01_01_Id:
      SendHighBit(true);
      if(TimeOut(LOGICAL_0x01_HIGH_LEVEL_TIMER, timer_sms_id))
      {
        step = Send_Byte_Id;
        timer_init = false;
      }
    break;
    
    case Send_Bit0x00_00_Id:
      SendHighBit(false);
      if(TimeOut(LOGICAL_0x00_LOW_LEVEL_TIMER, timer_sms_id))
      {
        step = Send_Bit0x00_01_Id;
        timer_init = false;
      }
    break;
    
    case Send_Bit0x00_01_Id:
      SendHighBit(true);
      if(TimeOut(LOGICAL_0x00_HIGH_LEVEL_TIMER, timer_sms_id))
      {
        step = Send_Byte_Id;
        timer_init = false;
      }
    break;
    
    case Send_Byte_Id:
      if(bit_counter ++ < 8)
      {
        if((byte << (bit_counter - 1))&0x80)
        step = Send_Bit0x01_00_Id;
        else step = Send_Bit0x00_00_Id;
        timer_init = false;
      }
      else
      {
        step = Send_Payload_Id;
        bit_counter = 0;
      }
    break;
    
    case Send_Payload_Id:
      if(byte_counter ++ < datalen)
      {
        byte = data[byte_counter - 1];
        step = Send_Byte_Id;
      }
      else
      {
        step = Send_Stop_Signal_00_Id;
        byte_counter = 0;
      }
    break;
    
    case Send_Stop_Signal_00_Id:
      SendHighBit(false);
      if(TimeOut(STOP_LOW_LEVEL_TIMER, timer_sms_id))step = Send_Stop_Signal_01_Id;
    break;
    
    case Send_Stop_Signal_01_Id:
      SendHighBit(true);
      res = true;
      timer_init = false;
      step = 0;
    break;
  }
  
  return res;
}

bool IsSendAllowed(void)
{
  return allow_send;
}

void SetSendAllowedStatus(bool res)
{
  allow_send = res;
}




