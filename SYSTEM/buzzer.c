#include "buzzer.h"

void Buzzer_Init(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  Buzzer_Control(Bit_SET);  // 初始关闭蜂鸣器
}

/**
 * \brief 蜂鸣器控制函数
 * \param state:
 *   \arg Bit_RESET  开始蜂鸣
 *   \arg Bit_SET    停止蜂鸣
 **/
void Buzzer_Control(BitAction state) {
  GPIO_WriteBit(GPIOA, GPIO_Pin_1, state);
}
