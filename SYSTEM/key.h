#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

/** SW1->2 SW2->13 SW3->6 SW4->7 */
#define KEY_PinAll (GPIO_Pin_2 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_13)

void Key_Init(void);

#endif
