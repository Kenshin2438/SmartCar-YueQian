#include "car.h"
#include "delay.h"
#include "serial.h"
#include "stm32f10x.h"

int main() {
  Serial_Init();
  CarMovement_Init();

  uint8_t recv_data = 'Q';
  while (1) {
    if (Serial_GetRxFlag() == 1) {
      recv_data = Serial_GetRxData();
      // printf("%c\n", recv_data);
    }
    if (recv_data == 'W') {
      car_go();
    }
    if (recv_data == 'A') {
      car_left();
    }
    if (recv_data == 'S') {
      car_back();
    }
    if (recv_data == 'D') {
      car_right();
    }
    if (recv_data == 'Q') {
      car_stop();
    }
  }
}
