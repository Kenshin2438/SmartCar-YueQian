#include "stm32f10x.h"

/** Include **/
#include "buzzer.h"
#include "delay.h"
#include "key.h"
// #include "led.h"
#include "car.h"

/**
 *
 * + [x] 1.遇横线(开始和结束)，遇到横线小车应该停止。
 * + [x] 2.按键启动小车。当长按KEY1的时候，启动小车，**蜂鸣器鸣叫三声**
 * + [x] 3.按键KEY2切换速度。可以低速、中速、高速模式。
 * 评分按照小车的速度与完成度来评分。
 *
 */

int main() {
  CarMovement_Init();
  CarRed_Init();
  Key_Init();
  Buzzer_Init();

  /** 低速，中速，高速 Mode */
  static const int speedControl[] = {8, 7, 6};
  /** 速度切换控制 */
  volatile int idx = 0, start = 0;

CONTROL:
  while (start == 0) {
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == Bit_RESET) {
      while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == Bit_RESET)
        ;
      delay_ms(20);
      idx = (idx + 1) % 3;
      Buzzer_Control(Bit_RESET);
      delay_ms(500);
      Buzzer_Control(Bit_SET);
      delay_ms(500);
    }
    if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == Bit_RESET) {
      while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == Bit_RESET)
        ;
      delay_ms(20);
      start ^= 1;
    }
  }
  for (int _ = 0; _ < 3; _++) {
    Buzzer_Control(Bit_RESET);
    delay_ms(500);
    Buzzer_Control(Bit_SET);
    delay_ms(500);
  }
  while (1) {
    CarMovement_UP(speedControl[idx]);
    if (CarRed_Check_LEFT() && CarRed_Check_RIGHT()) {
      CarMovement_STOP();
      start = 0;
      goto CONTROL;
    } else if (CarRed_Check_LEFT() && !CarRed_Check_RIGHT()) {
      while (CarRed_Check_LEFT() && !CarRed_Check_RIGHT()) {
        CarMovement_LEFT(speedControl[idx]);
      }
    } else if (!CarRed_Check_LEFT() && CarRed_Check_RIGHT()) {
      while (!CarRed_Check_LEFT() && CarRed_Check_RIGHT()) {
        CarMovement_RIGHT(speedControl[idx]);
      }
    }
  }
}
