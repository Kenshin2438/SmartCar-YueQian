#include "serial.h"

#define Serial_GPIO_CLK  RCC_APB2Periph_GPIOA
#define Serial_CLK       RCC_APB2Periph_USART1
#define Serial_GPIO_Port GPIOA
#define Serial_Tx_Pin    GPIO_Pin_9
#define Serial_Rx_Pin    GPIO_Pin_10

uint8_t Serial_RxData;
volatile uint8_t Serial_RxFlag;

void Serial_Init() {
  RCC_APB2PeriphClockCmd(Serial_GPIO_CLK | Serial_CLK | RCC_APB2Periph_AFIO,
                         ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin   = Serial_Tx_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(Serial_GPIO_Port, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Pin   = Serial_Rx_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(Serial_GPIO_Port, &GPIO_InitStructure);

  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode       = USART_Mode_Tx | USART_Mode_Rx;
  USART_InitStructure.USART_Parity     = USART_Parity_No;
  USART_InitStructure.USART_StopBits   = USART_StopBits_1;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART1, &USART_InitStructure);

  USART_Cmd(USART1, ENABLE);

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Serial_SendByte(uint8_t Byte) {
  USART_SendData(USART1, Byte);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
    ;
}

int fputc(int ch, FILE *f) {
  Serial_SendByte(ch);
  return ch;
}

uint8_t Serial_GetRxFlag(void) {
  if (Serial_RxFlag == 1) {
    Serial_RxFlag = 0;
    return 1;
  }
  return 0;
}

uint8_t Serial_GetRxData(void) { return Serial_RxData; }
void USART1_IRQHandler(void) {
  if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
    Serial_RxData = USART_ReceiveData(USART1);
    Serial_RxFlag = 1;
    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  }
}
