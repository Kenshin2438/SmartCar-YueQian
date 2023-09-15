#include "car.h"

#include "delay.h"

#define IR_Left_Pin  GPIO_Pin_3
#define IR_Right_Pin GPIO_Pin_4

void CarCheck_Init(void) {  // Infrared Ray Mode
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
  GPIO_InitStruct.GPIO_Pin   = IR_Left_Pin | IR_Right_Pin;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}

#define Motor_L_VCC_Pin GPIO_Pin_1
#define Motor_L_GND_Pin GPIO_Pin_0
#define Motor_R_VCC_Pin GPIO_Pin_7
#define Motor_R_GND_Pin GPIO_Pin_6

void CarMovement_Init(void) {  // Motor Driver Mode
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

#define PWM_LOOP 200

void CarMovement_UP(int PWM) {
  for (int _ = 0; _ < PWM_LOOP; _++) {
    Motor_Set_High(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_High(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    if (PWM > 0) delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    if (10 > PWM) delay_us(10 - PWM);
  }
}

void CarMovement_DOWN(int PWM) {
  for (int _ = 0; _ < PWM_LOOP; _++) {
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_High(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_High(Motor_R_GND_Pin);
    if (PWM > 0) delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    if (10 > PWM) delay_us(10 - PWM);
  }
}

void CarMovement_RIGHT(int PWM) {
  for (int _ = 0; _ < PWM_LOOP; _++) {
    Motor_Set_High(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_High(Motor_R_GND_Pin);
    if (PWM > 0) delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    if (10 > PWM) delay_us(10 - PWM);
  }
}

void CarMovement_LEFT(int PWM) {
  for (int _ = 0; _ < PWM_LOOP; _++) {
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_High(Motor_L_GND_Pin);
    Motor_Set_High(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    if (PWM > 0) delay_us(PWM);
    Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
    Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
    if (10 > PWM) delay_us(10 - PWM);
  }
}

// TODO: Merge
void car_go() {
  Motor_Set_High(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
  Motor_Set_High(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
}
void car_back() {
  Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_High(Motor_L_GND_Pin);
  Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_High(Motor_R_GND_Pin);
}
void car_stop() {
  Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
  Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
}
void car_right() {
  Motor_Set_High(Motor_L_VCC_Pin), Motor_Set_Low(Motor_L_GND_Pin);
  Motor_Set_Low(Motor_R_VCC_Pin), Motor_Set_High(Motor_R_GND_Pin);
}
void car_left() {
  Motor_Set_Low(Motor_L_VCC_Pin), Motor_Set_High(Motor_L_GND_Pin);
  Motor_Set_High(Motor_R_VCC_Pin), Motor_Set_Low(Motor_R_GND_Pin);
}
