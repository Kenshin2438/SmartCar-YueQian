#include "buzzer.h"

void Buzzer_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  Buzzer_Control(Bit_SET);
}

/**
 * \brief 蜂鸣器控制
 * \param state: Bit_RESET 开始蜂鸣；Bit_SET 停止蜂鸣
 */
void Buzzer_Control(BitAction state) {
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, state);
}
