#ifndef __CAR_H
#define __CAR_H

#include "stm32f10x.h"

/*****  电机驱动模块  *****/
void CarMovement_Init(void);

void CarMovement_STOP(void);
void CarMovement_UP(int);
void CarMovement_DOWN(int);
void CarMovement_RIGHT(int);
void CarMovement_LEFT(int);

/*****  红外模块  *****/
void CarRed_Init(void);

int CarRed_Check_LEFT(void);
int CarRed_Check_RIGHT(void);

#endif
