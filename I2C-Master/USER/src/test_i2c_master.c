/**
  ***************************************************************
  * @file    test_i2c_ee.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    2019-8
  * @brief   
  ***************************************************************
  */

/*Includes ----------------------------*/
#include "test_i2c_master.h"
#include "test_uart.h"


uint8_t I2C_buffer[16];
uint8_t I2C_SEND_START ;
uint8_t I2C_REVCIVE_START ;
uint8_t I2C_SEND_END;
uint8_t I2C_REVCIVE_END;

uint8_t *g_rdata = NULL;

uint8_t I2C_SEND_NUM;
uint8_t I2C_REVICE_NUM;

 
I2C_EveTypeDef  I2C_EveStruct;



void delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


 /**
  * @brief  配置嵌套向量中断控制器NVIC
  * @param  无
  * @retval 无
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_InitStructure.NVIC_IRQChannel = MASTER_IIC_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
*********************************************************************************************************
*	函 数 名: i2c_CfgGpio
*	功能说明: 配置I2C总线的GPIO，采用模拟IO的方式实现
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void I2C_Master_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	I2C_InitTypeDef I2C_InitStruct;
	
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = MASTER_IIC_SCK_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(MASTER_IIC_SCK_PORT,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_Pin = MASTER_IIC_SDA_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
	GPIO_Init(MASTER_IIC_SDA_PORT,&GPIO_InitStruct);

    GPIO_PinAFConfig(MASTER_IIC_SCK_PORT,MASTER_IIC_SCK_PIN_SOURCE,MASTER_IIC_SCK_AF_VALUE);
    GPIO_PinAFConfig(MASTER_IIC_SDA_PORT,MASTER_IIC_SDA_PIN_SOURCE,MASTER_IIC_SDA_AF_VALUE);
	
	/*I2C模块初始化*/
	I2C_InitStruct.I2C_Ack = MASTER_IIC_ACK;
	I2C_InitStruct.I2C_BroadcastAddress_Response = MASTER_IIC_BROADCASTADDRESS_RESPONE;
	I2C_InitStruct.I2C_ClockSpeed = MASTER_IIC_CLOSKSPEED;
	I2C_InitStruct.I2C_Mode = MASTER_IIC_MODE;
	I2C_InitStruct.I2C_OwnAddress = MASTER_IIC_OWNADDRESS;
	
	I2C_Cmd(MASTER_IICx,DISABLE);
	/*i2c 初始化配置*/
	I2C_Init(MASTER_IICx, &I2C_InitStruct);
	
	/*i2c 中断配置*/
	NVIC_Configuration();
	
	/*I2C发送使能*/
	I2C_Cmd(MASTER_IICx,ENABLE);
}

/*
*********************************************************************************************************
*	函 数 名: ee_ReadBytes
*********************************************************************************************************
*/
void I2C_Master_Receive(uint8_t regAddr , uint8_t *rData, uint8_t rSize)
{

	I2C_EveStruct.I2C_Master_Recive = 0x01;
	I2C_EveStruct.I2C_Master_Send =0x00;
	
	I2C_buffer[0] = regAddr;
        I2C_buffer[1] = rSize;
	I2C_SEND_NUM   = 2;
	
	g_rdata = rData;
	I2C_REVCIVE_START = 0;
	I2C_REVCIVE_END =  rSize + 1;
	
	I2C_MasterSendCmd(I2C,ENABLE);//I2C发送使能
	while(I2C_EveStruct.I2C_Master_Recive == 0x01);
	*(rData+I2C_REVCIVE_END+1) = 0x00;
	
}



void I2C_Master_SendByte(uint8_t regAddr ,const uint8_t wData)
{
	
	I2C_EveStruct.I2C_Master_Recive = 0x00;
	I2C_EveStruct.I2C_Master_Send =   0x01;
	
	I2C_buffer[0] = regAddr;
	I2C_buffer[1] = wData;

    I2C_SEND_NUM = 2;
    I2C_MasterSendCmd(I2C,ENABLE);//I2C发送使能
    while(I2C_EveStruct.I2C_Master_Send == 0x01);//等待发送结束
}



void I2C_Master_Transmit(uint8_t regAddr ,uint8_t *wData, uint8_t size)
{
	uint8_t i = 0;
	
	I2C_EveStruct.I2C_Master_Recive = 0x00;
	I2C_EveStruct.I2C_Master_Send =   0x01;
	
	I2C_buffer[0] = regAddr;
        
	for(i=0;i<size;i++)
	{
		I2C_buffer[i+1] = wData[i];
	}

    I2C_SEND_NUM = size+1;
    I2C_MasterSendCmd(I2C,ENABLE);//I2C发送使能
    while(I2C_EveStruct.I2C_Master_Send == 0x01);//等待发送结束
}



/**
  * @brief  This function handles I2C IRQHandler Master send data  with ack
  * @param  None
  * @retval None
  */
void I2C_IRQHandler_MasterSend(void)
{
	static uint8_t transmit_num = 0;
	/*obtain STAT Value*/
	/*已发送起始条件 or 已发送重复起始条件*/ 
	if (I2C->SR == 0x08 || I2C->SR == 0x10 )
	{
		/*发送7bit的地址数据*/
		I2C_SendData(I2C, ((TARGET_ADDR << 1) & 0xFE)); //slave address
		/*no Generate start*/
		I2C_GenerateSTART(I2C,DISABLE);
		/*no Generate ack*/
		I2C_AcknowledgeConfig(I2C,DISABLE);
		/*no Generate stop*/
		I2C_GenerateSTOP(I2C,DISABLE);  
	} 				 
	/*已发送SLA+W and 已接收ACK or 已发送SLA+W and 已接收非ACK */
	else if (I2C->SR == 0x18 || I2C->SR == 0x20)
	{
		/*master send data */
		if(transmit_num < I2C_SEND_NUM)
		{
			I2C_SendData(I2C,I2C_buffer[transmit_num]); //reg address
			transmit_num++;
		  /*no Generate start*/
			I2C_GenerateSTART(I2C,DISABLE);
			/*no Generate ack*/
			I2C_AcknowledgeConfig(I2C,DISABLE);
			/*no Generate stop*/
			I2C_GenerateSTOP(I2C,DISABLE); 
		} 
		else 
		{
			/*no Generate start*/
			I2C_GenerateSTART(I2C,DISABLE);
			/*no Generate ack*/
			I2C_AcknowledgeConfig(I2C,DISABLE);
			/*Generate stop*/
			I2C_GenerateSTOP(I2C,ENABLE); 
			I2C_EveStruct.I2C_Master_Send = 0;
			transmit_num = 0;
		}
	}
	/*已发送I2C_DATA中的数据 and 已接收ACK or 已发送I2C_DATA中的数据 */
	else if (I2C->SR == 0x28 ||I2C->SR == 0x30) /*same to 0x28 can send data */
	{
		if(transmit_num <  I2C_SEND_NUM)
		 {
				/*master send data */
				I2C_SendData(I2C, I2C_buffer[transmit_num]); //data
			  transmit_num++; 
				/*no Generate start*/
				I2C_GenerateSTART(I2C,DISABLE);
				/*no Generate ack*/
				I2C_AcknowledgeConfig(I2C,DISABLE);
			  /*Generate stop*/
				I2C_GenerateSTOP(I2C,DISABLE); 
		 } 
		 else 
		 {
			   /*no Generate start*/
				I2C_GenerateSTART(I2C,DISABLE);
				/*no Generate ack*/
				I2C_AcknowledgeConfig(I2C,DISABLE);
		   	/*Generate stop*/
				I2C_GenerateSTOP(I2C,ENABLE); 
			  I2C_EveStruct.I2C_Master_Send = 0;
			  transmit_num = 0;
		}
									
	}  
	else if (I2C->SR == 0xF8)//Own SLA +W has been received ACK has been return
	{
				;/*无任何动作，等待传输*/
	}
	else
	{
			/*no Generate start*/
			I2C_GenerateSTART(I2C,DISABLE);
			/*no Generate ack*/
			I2C_AcknowledgeConfig(I2C,DISABLE);
		  /*no Generate stop*/
			I2C_GenerateSTOP(I2C,ENABLE); 
		  I2C_EveStruct.I2C_Master_Send = 0;
		  transmit_num = 0;
	}			
}

/**
  * @brief  This function handles I2C IRQHandler Master recive data
  * @param  None
  * @retval None
  */
void I2C_IRQHandler_MasterRecive(void)
{
	static uint8_t transmit_num = 0;
	/* START has been transmitted and prepare SLA+R */
	if (I2C->SR == 0x08)   
	{
	  /*发送7bit的地址数据  sla+w*/
	  I2C_SendData(I2C, ((TARGET_ADDR << 1) & 0xFE)); //slave address & write
		/*no Generate start*/
		I2C_GenerateSTART(I2C,DISABLE);
		/*no Generate ack*/
		I2C_AcknowledgeConfig(I2C,DISABLE);
		/*no Generate stop*/
		I2C_GenerateSTOP(I2C,DISABLE);  
	} 
	/* SLA+W has been transmitted and ACK has been received */
	else if (I2C->SR == 0x18 || I2C->SR == 0x20)
	{
		/*master send data */
		if(transmit_num < I2C_SEND_NUM)
		{
			I2C_SendData(I2C,I2C_buffer[I2C_SEND_START + transmit_num]); //reg address
			transmit_num++;
			 /*no Generate start*/
			I2C_GenerateSTART(I2C,DISABLE);
			/*no Generate ack*/
			I2C_AcknowledgeConfig(I2C,DISABLE);
			/*no Generate stop*/
			I2C_GenerateSTOP(I2C,DISABLE); 
		}
	}
	/*same to 0x28 can send data */
	else if (I2C->SR == 0x28 ||I2C->SR == 0x30) 
	{
		 if(transmit_num < I2C_SEND_NUM)
		 {
				/*master send data */
				I2C_SendData(I2C,I2C_buffer[I2C_SEND_START + transmit_num]);
			  transmit_num++;
				/*no Generate start*/
				I2C_GenerateSTART(I2C,DISABLE);
				/*no Generate ack*/
				I2C_AcknowledgeConfig(I2C,DISABLE);
		 } else {
       /*no Generate start*/
			 I2C_GenerateSTART(I2C,ENABLE);
		 }			 							
	} 	
	else if(I2C->SR == 0x10)
	{
			/*master send data */
			I2C_SendData(I2C,((TARGET_ADDR << 1) | 0x01)); //slave address & read
		  I2C_GenerateSTOP(I2C,DISABLE); 
	}
	else if (I2C->SR == 0x38)                                            
	{
				/*Generate start*/
				I2C_GenerateSTART(I2C,ENABLE);
        I2C_GenerateSTOP(I2C,DISABLE); 		
	}  								
	else if (I2C->SR == 0x40) /* SLA+R has been transmitted and ACK has been received */
	{
				/*设置第一个字节recive ack*/
		   if(I2C_REVCIVE_START<I2C_REVCIVE_END)
			 {
					if(I2C_REVCIVE_START == (I2C_REVCIVE_END-1))
						I2C_AcknowledgeConfig(I2C,DISABLE);//goto the status(0x50)
					else
						I2C_AcknowledgeConfig(I2C,ENABLE);//goto the status(0x50)
						I2C_GenerateSTART(I2C,DISABLE); 
						I2C_GenerateSTOP(I2C,DISABLE); 
			}else {
				I2C_GenerateSTOP(I2C,ENABLE); 
		    /*Generate dummy start*/
				I2C_GenerateSTART(I2C,DISABLE);
      }				
	}
	else if (I2C->SR == 0x48) /* SLA+R has been transmitted and ACK has been received */
	{
				/*Generate start*/
				I2C_GenerateSTART(I2C,ENABLE); 
		    I2C_GenerateSTOP(I2C,ENABLE); 
	}
	else if (I2C->SR == 0x50)
	{
		  *(g_rdata+I2C_REVCIVE_START) = I2C_ReceiveData(I2C);	//  data recive 
		  I2C_REVCIVE_START++;
		  if(I2C_REVCIVE_START<I2C_REVCIVE_END)
			{
				if(I2C_REVCIVE_START == (I2C_REVCIVE_END-1)) //设置倒数第一个数据接收
				{
					 /*设置最后一个字节recive ack*/
					 I2C_AcknowledgeConfig(I2C,DISABLE);//data recive no over
					 I2C_GenerateSTART(I2C,DISABLE); 			
					 I2C_GenerateSTOP(I2C,DISABLE);
				}
				else
				{
						/*设置下一个字节recive ack*/
					 I2C_AcknowledgeConfig(I2C,ENABLE);//data recive no over
					 I2C_GenerateSTART(I2C,DISABLE); 
					 I2C_GenerateSTOP(I2C,DISABLE); 
				}
			}
	}                 
	else if (I2C->SR == 0x58) /* SLA+R has been transmitted and ACK has been received */
	{
				*(g_rdata+I2C_REVCIVE_START) = I2C_ReceiveData(I2C);
		    I2C_REVCIVE_START++;
		    I2C_GenerateSTOP(I2C,ENABLE); 
		    /*Generate dummy start*/
				I2C_GenerateSTART(I2C,DISABLE);
		    I2C_EveStruct.I2C_Master_Recive = 0x00; 
        		transmit_num = 0;
	}
	else if (I2C->SR == 0xF8)//Own SLA +W has been received ACK has been return
	{
			/*无任何动作，等待传输*/
	
	}
	else
	{
		I2C_EveStruct.I2C_Master_Recive = 0x00;
		/*Generate start*/
		I2C_GenerateSTART(I2C,DISABLE);
		/*no Generate ack*/
		I2C_AcknowledgeConfig(I2C,DISABLE);
		 /*接收结束，设置STOP*/
		I2C_GenerateSTOP(I2C,ENABLE); 
		
		transmit_num = 0;
	}		
}


/**
  * @brief  This function handles I2C0 IRQHandler
  * @param  None
  * @retval None
  */
void MASTER_IIC_IRQHandler(void)
{
	if(I2C_EveStruct.I2C_Master_Send == 0x01)  /*master send mode */
	{
		I2C_IRQHandler_MasterSend();		  		
	} //end  master send
	if(I2C_EveStruct.I2C_Master_Recive == 0x01) /*master recive mode*/
	{	
		I2C_IRQHandler_MasterRecive(); 			
	}  //end master recive


	if(I2C->CR&0x08)   //退出中断清中断标志位；
        I2C->CR &= 0xf7;
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
