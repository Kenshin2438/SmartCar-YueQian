#ifndef __LCD1602_H
#define __LCD1602_H

#include "delay.h"
#include "stm32f10x.h"

#define GPIO_Pin_DAT                                                  \
  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | \
      GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15

#define GPIO_Pin_CMD GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2

#define LCD_RS_Set() GPIOB->ODR |= (0x1 << 0)   // RS=1
#define LCD_RS_Clr() GPIOB->ODR &= ~(0x1 << 0)  // RS=0,PB0
#define LCD_RW_Set() GPIOB->ODR |= (0x1 << 1)   // RW=1
#define LCD_RW_Clr() GPIOB->ODR &= ~(0x1 << 1)  // RW=0,PB1
#define LCD_EN_Set() GPIOB->ODR |= (0x1 << 2)   // E=1
#define LCD_EN_Clr() GPIOB->ODR &= ~(0x1 << 2)  // E=0,PB2
#define DATAOUT(x)   GPIOB->ODR |= x;

void GPIO_Configuration(void);
void LCD1602_Wait_Ready(void);
void LCD1602_Write_Cmd(u8 cmd);
void LCD1602_Write_Dat(u8 dat);
void LCD1602_ClearScreen(void);
void LCD1602_Set_Cursor(u8 x, u8 y);
void LCD1602_Show_Str(u8 x, u8 y, u8 *str);
void LCD1602_Init(void);

void LCD1602_DB_IO_outputMode(void);
void LCD1602_DB_IO_inputMode(void);

#endif
