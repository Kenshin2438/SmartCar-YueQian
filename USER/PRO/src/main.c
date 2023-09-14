#include "stm32f10x.h"

/** Include **/
#include "buzzer.h"
#include "delay.h"
#include "key.h"
// #include "led.h"
#include "car.h"

/**

// int main() {
//   CarMovement_Init();
//   CarRed_Init();
//   Key_Init();
//   Buzzer_Init();

//   static const int speedControl[] = {8, 7, 6};
//   volatile uint8_t idx            = 0;

// CONTROL:  // 初始状态控制
//   while (1) {
//     if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == Bit_RESET) {
//       delay_ms(20);
//       while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6) == Bit_RESET)
//         ;
//       idx = (idx + 1) % 3;
//       Buzzer_Control(Bit_RESET);
//       delay_ms(500);
//       Buzzer_Control(Bit_SET);
//       delay_ms(500);
//     }
//     if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == Bit_RESET) {
//       delay_ms(20);
//       while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_13) == Bit_RESET)
//         ;
//       goto RUN;
//     }
//   }

// RUN:  // 自动循迹
//   for (int _ = 0; _ < 3; _++) {
//     Buzzer_Control(Bit_RESET);
//     delay_ms(500);
//     Buzzer_Control(Bit_SET);
//     delay_ms(500);
//   }
//   while (1) {
//     CarMovement_UP(speedControl[idx]);
//     if (CarRed_Check_LEFT() && CarRed_Check_RIGHT()) {
//       CarMovement_STOP();
//       goto CONTROL;
//     } else if (CarRed_Check_LEFT() && !CarRed_Check_RIGHT()) {
//       while (CarRed_Check_LEFT() && !CarRed_Check_RIGHT()) {
//         CarMovement_LEFT(speedControl[idx]);
//       }
//     } else if (!CarRed_Check_LEFT() && CarRed_Check_RIGHT()) {
//       while (!CarRed_Check_LEFT() && CarRed_Check_RIGHT()) {
//         CarMovement_RIGHT(speedControl[idx]);
//       }
//     }
//   }
// }

**/

#define CAR_STOP  0
#define CAR_UP    1
#define CAR_DOWN  2
#define CAR_RIGHT 3
#define CAR_LEFT  4

volatile int state = CAR_STOP;

void EXIT() {
  
}

int main(void) {
  while (1) {
    switch (state) {
      case CAR_STOP:
        CarMovement_STOP(8);
        break;
      case CAR_UP:
        CarMovement_UP(8);
        break;
      case CAR_DOWN:
        CarMovement_DOWN(8);
        break;
      case CAR_RIGHT:
        CarMovement_RIGHT(8);
        break;
      case CAR_LEFT:
        CarMovement_LEFT(8);
        break;
    }
  }
}