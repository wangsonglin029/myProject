/**
  ***************************************************************
  * @file    test_uart.c
  * @author  MCU Application Team
  * @version V0.0.0
  * @date    28-5-2019
  * @brief
  ***************************************************************
  */

/*Includes ----------------------------*/
#include "test_uart.h"
#include "misc.h"
#include "stdio.h"
#include "stdarg.h"

/*define parameters -------------------*/
uint8_t UART_RX_BUF[1];    /*<interrupt recive data buffer*/
uint8_t RxCounter = 0;
volatile uint8_t gRXFlagState = 0;    /*<interrupt recive data flag*/
volatile uint8_t gTXFlagState = 0;    /*<interrupt recive data flag*/

/**
 * @brief  Config UART1 NVIC of UART interrupt parameters.
 * @param  None
* @param  None
 * @retval None
 */
static void  UART1_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**
 * @brief  Config UART0 NVIC of UART interrupt parameters.
 * @param  None
* @param  None
 * @retval None
 */
static void  UART0_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = UART0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  Config UART1 Parameters.
 * @param  None
* @param  None
 * @retval None
 */
void UART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    UART_InitTypeDef UART_InitStructure;

    //将USART Rx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = DEBUG_UART1_RX_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(DEBUG_UART1_RX_GPIO_PORT, &GPIO_InitStruct);


    //将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = DEBUG_UART1_TX_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(DEBUG_UART1_TX_GPIO_PORT, &GPIO_InitStruct);


    //uart GPIO管脚配置
    GPIO_PinAFConfig(DEBUG_UART1_RX_GPIO_PORT, \
                     DEBUG_UART1_RX_PIN_SOURCE, \
                     DEBUG_UART1_RX_AF_VALUE); //RX

    GPIO_PinAFConfig(DEBUG_UART1_TX_GPIO_PORT, \
                     DEBUG_UART1_TX_PIN_SOURCE, \
                     DEBUG_UART1_TX_AF_VALUE); //TX


    // 配置串口的工作参数
    // 配置波特率
    UART_InitStructure.UART_BaudRate = DEBUG_UART1_BAUDRATE;
    // 配置 针数据字长
    UART_InitStructure.UART_BaudRateDbaud_Enable = ENABLE;
    // 配置停止位
    UART_InitStructure.UART_BaudRateTimer_Selected = DISABLE;
    // 配置校验位
    UART_InitStructure.UART_Mode = DEBUG_UART1_MODE ;

    // 完成串口的初始化配置
    UART_Init(UART1, DEBUG_TIM11, &UART_InitStructure);

    // 串口中断优先级配置
    UART1_NVIC_Configuration();

    // 使能串口接收中断*/
    UART_ITConfig(UART1, UART_RIEN_EABLE, ENABLE);

    // 使能串口发送中断*/
    UART_ITConfig(UART1, UART_TIEN_EABLE, ENABLE);


    // 使能串口接收/发送中断
    UART_Cmd(UART1, UART_RXEN_EABLE, ENABLE);
}

/**
 * @brief  Config UART0 Parameters.
 * @param  None
* @param  None
 * @retval None
 */
void UART0_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    UART_InitTypeDef UART_InitStructure;

    //将USART Rx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = DEBUG_UART0_RX_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(DEBUG_UART0_RX_GPIO_PORT, &GPIO_InitStruct);


    //将USART Tx的GPIO配置为推挽复用模式
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = DEBUG_UART0_TX_GPIO_PIN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;
    GPIO_Init(DEBUG_UART0_TX_GPIO_PORT, &GPIO_InitStruct);


    //uart GPIO管脚配置
    GPIO_PinAFConfig(DEBUG_UART0_RX_GPIO_PORT, \
                     DEBUG_UART0_RX_PIN_SOURCE, \
                     DEBUG_UART0_RX_AF_VALUE); //RX

    GPIO_PinAFConfig(DEBUG_UART0_TX_GPIO_PORT, \
                     DEBUG_UART0_TX_PIN_SOURCE, \
                     DEBUG_UART0_TX_AF_VALUE); //TX


    // 配置串口的工作参数
    // 配置波特率
    UART_InitStructure.UART_BaudRate = DEBUG_UART0_BAUDRATE;
    // 配置 针数据字长
    UART_InitStructure.UART_BaudRateDbaud_Enable = ENABLE;
    // 配置停止位
    UART_InitStructure.UART_BaudRateTimer_Selected = DISABLE;
    // 配置校验位
    UART_InitStructure.UART_Mode = DEBUG_UART0_MODE ;

    // 完成串口的初始化配置
    UART_Init(UART0, DEBUG_TIM10, &UART_InitStructure);

    // 串口中断优先级配置
    UART0_NVIC_Configuration();


    /*Enable UART0 Receive interrupt*/
    UART_ITConfig(UART0, UART_RIEN_EABLE, ENABLE);

    /*Enable UART0 Send interrupt*/
    UART_ITConfig(UART0, UART_TIEN_EABLE, ENABLE);


    //使能串口
    UART_Cmd(UART0, UART_RXEN_EABLE, ENABLE);
}

/*****************  发送一个字节 **********************/
void Uart_SendByte( UART_TypeDef * pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USART */
    UART_SendData(pUSARTx, ch);
    while(gTXFlagState != 0x01);
    gTXFlagState = 0x00;
}


/*****************  发送字符串 **********************/
void Uart_SendString( UART_TypeDef * pUSARTx, unsigned char *str, uint32_t size)
{
    unsigned int k = 0;
    
    for(k=0; k<size; k++)
    {
        Uart_SendByte( pUSARTx, *(str + k));
    }
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    UART_SendData(PRINTFUART, (uint8_t) ch);
    while(gTXFlagState != 0x01);
    gTXFlagState = 0x00;
    return (ch);
}

//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
    /* 等待串口输入数据 */
    while(gRXFlagState != 0x01);
    gRXFlagState = 0x00;
    return (int)UART_ReceiveData(PRINTFUART);
}

/*
void PRINTF(const char *format, ...)
{
  uint8_t buf[0x64]; //定义临时数组，根据实际发送大小微调
  va_list args;
  va_start(args, format);
  uint16_t len = vsnprintf((char *)buf, sizeof(buf), (char *)format, args);
  va_end(args);
  Uart_SendString(PRINTFUART, buf, len);
}
*/

/**
 * @brief  Config UART1 interrupt Parameters.
 * @param  None
* @param  None
 * @retval None
 */
void UART1_IRQHandler(void)
{
    if((UART1->INTSR & UART_ISR_TI) == UART_ISR_TI)
    {
        UART1->INTCLR |= UART_ICR_TI;
        gTXFlagState =  0x01;
    }
    else if((UART1->INTSR & UART_ISR_RI) == UART_ISR_RI)
    {
        UART1->INTCLR |= UART_ICR_RI;
        UART_RX_BUF[0] = UART_ReceiveData( UART1);
        gRXFlagState =  0x01;
    }
    else
    {;}
}


/**
 * @brief  Config UART0 interrupt Parameters.
 * @param  None
* @param  None
 * @retval None
 */
void UART0_IRQHandler(void)
{
    if((UART0->INTSR & UART_ISR_TI) == UART_ISR_TI)
    {
        UART0->INTCLR |= UART_ICR_TI;
        gTXFlagState =  0x01;
    }
    else if((UART0->INTSR & UART_ISR_RI) == UART_ISR_RI)
    {
        UART0->INTCLR |= UART_ICR_RI;
        UART_RX_BUF[0] = UART_ReceiveData( UART0);
        gRXFlagState =  0x01;
    }
    else
    {;}
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





