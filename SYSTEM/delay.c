#include "delay.h"

void delay_ms(int N_ms) {
  uint32_t fpms = SystemCoreClock / 8000;
  int tmp;
  SysTick->LOAD = fpms * N_ms;

  SysTick->VAL   = 0x00;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

  do {
    tmp = SysTick->CTRL;
  } while ((tmp & 0x01) && !(tmp & (1 << 16)));

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL   = 0x00;
}

void delay_us(int N_us) {
  uint32_t fpus = SystemCoreClock / 8000000;
  int tmp;
  SysTick->LOAD = fpus * N_us;

  SysTick->VAL   = 0x00;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

  do {
    tmp = SysTick->CTRL;
  } while ((tmp & 0x01) && !(tmp & (1 << 16)));

  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
  SysTick->VAL   = 0x00;
}
