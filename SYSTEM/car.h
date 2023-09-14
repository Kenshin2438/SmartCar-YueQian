#ifndef __CAR_H
#define __CAR_H

#include "stm32f10x.h"

void CarCheck_Init(void);
void CarMovement_Init(void);

void CarMovement_STOP(void);
void CarMovement_UP(int);
void CarMovement_DOWN(int);
void CarMovement_RIGHT(int);
void CarMovement_LEFT(int);

#endif
