#include "car.h"

#include "delay.h"

#define Motor_L_VCC_Pin GPIO_Pin_1
#define Motor_L_GND_Pin GPIO_Pin_0
#define Motor_R_VCC_Pin GPIO_Pin_7
#define Motor_R_GND_Pin GPIO_Pin_6

void CarMovement_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Pin =
      Motor_L_VCC_Pin | Motor_L_GND_Pin | Motor_R_VCC_Pin | Motor_R_GND_Pin;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  CarMovement_STOP();
}

#define Motor_Set_High(pin) GPIO_SetBits(GPIOB, pin)
#define Motor_Set_Low(pin)  GPIO_ResetBits(GPIOB, pin)

void CarMovement_STOP(void) {
  Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
  Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
}

void CarMovement_UP(int PWM) {
  for (int _ = 0; _ < 150; _++) {
    Motor_Set_High(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_High(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    delay_us(10 - PWM);
  }
}

void CarMovement_DOWN(int PWM) {
  for (int _ = 0; _ < 150; _++) {
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_High(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_High(Motor_R_GND_Pin);
    delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    delay_us(10 - PWM);
  }
}

void CarMovement_RIGHT(int PWM) {
  for (int _ = 0; _ < 200; _++) {
    Motor_Set_High(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_High(Motor_R_GND_Pin);
    delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    delay_us(10 - PWM);
  }
}

void CarMovement_LEFT(int PWM) {
  for (int _ = 0; _ < 200; _++) {
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_High(Motor_L_GND_Pin);
    Motor_Set_High(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    delay_us(10 - PWM);
  }
}

#undef Motor_Set_High
#undef Motor_Set_Low

void CarRed_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
 * \brief 红外对管所面对的区域
 * \return 0: 白色，低电平，LED灯亮起
 *         1: 黑色，高电平，LED灯熄灭
 */
int CarRed_Check_LEFT(void) {
  return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3) != 0;
}
int CarRed_Check_RIGHT(void) {
  return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4) != 0;
}
