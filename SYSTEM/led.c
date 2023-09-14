#include "led.h"

#include "delay.h"

void LED_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = LED_PinAll;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * 
 *
 * Bit_RESET 点亮，Bit_SET   熄灭
 **/
void LED_Control(uint16_t LED_Pin, BitAction state) {
  GPIO_WriteBit(GPIOB, LED_Pin, state);
}

/**
 * 流水灯 从D0->D7依次亮起，之后从D7->D0依次熄灭
 */
void light_water() {
  for (int i = 0; i < 8; i++) {
    LED_Control((uint16_t)1 << i, Bit_RESET);
    delay_ms(500);
  }
  for (int i = 0; i < 8; i++) {
    LED_Control((uint16_t)1 << (7 - i), Bit_SET);
    delay_ms(500);
  }
}

void SEG_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = SEG_PinAll;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static const uint8_t SEG_CODE[43] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
  0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00, 0x40, 0x76, 0x1E,
  0x70, 0x38, 0x37, 0x5C, 0x73, 0x3E, 0x78, 0x3D, 0x67, 0x50,
  0x37, 0x6E, 0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87,
  0xFF, 0xEF, 0x46
};
static void SEG_Display_Single(uint8_t w, uint8_t code) {
  assert_param(0 <= w && w < 4);
  GPIO_WriteBit(GPIOB, GPIO_Pin_4, (BitAction)(w >> 0 & 1));
  GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)(w >> 1 & 1));
  for (int i = 0; i < 8; i++) {
    if (code >> i & 1) {
      GPIO_SetBits(GPIOB, GPIO_Pin_8 << i);
    } else {
      GPIO_ResetBits(GPIOB, GPIO_Pin_8 << i);
    }
  }
}
void SEG_Display(int num) {
  uint8_t dig[] = {
    num % 10,
    num / 10 % 10,
    num / 100 % 10,
    num / 1000 % 10,
  };
  while (1) {
    for (uint8_t w = 0; w < 4; w++) {
      SEG_Display_Single(w, SEG_CODE[ dig[w] ]);
      delay_ms(2);
    }
  }
}
