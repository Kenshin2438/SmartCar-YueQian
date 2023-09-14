#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_PinAll ((uint16_t)0x00FF)

void LED_Init(void);
void LED_Control(uint16_t LED_Pin, BitAction state);

#define SEG_PinAll ((uint16_t)0xFF30)

void SEG_Init(void);
void SEG_Display(int num);

#endif
