#include "lcd1602.h"

void GPIO_Configuration(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_CMD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_DAT;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void LCD1602_DB_IO_outputMode(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_DAT;      // PG�˿�����
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;  // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);  // �����趨������ʼ��GPIOG.0
  GPIO_SetBits(GPIOB, GPIO_Pin_DAT);
}

void LCD1602_DB_IO_inputMode(void) {
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_DAT;   // PG�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // ��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);  // �����趨������ʼ��GPIOG.0
  GPIO_SetBits(GPIOB, GPIO_Pin_DAT);
}

void LCD1602_Wait_Ready(void) {
  u8 sta;
  LCD_RS_Clr();
  LCD_RW_Set();
  do {
    LCD_EN_Set();
    delay_ms(5);
    LCD1602_DB_IO_inputMode();
    sta = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15);
    LCD1602_DB_IO_outputMode();
    LCD_EN_Clr();
  } while (sta & 0x8000);
}

void LCD1602_Write_Cmd(u8 cmd) {
  // u8 j;
  LCD1602_Wait_Ready();
  LCD_RS_Clr();
  LCD_RW_Clr();
  LCD_EN_Clr();
  GPIOB->ODR = (GPIOB->ODR & 0x00ff) | cmd << 8;
  LCD_EN_Set();
  delay_ms(5);
  LCD_EN_Clr();
}

void LCD1602_Write_Dat(u8 dat) {
  // u8 j;
  LCD1602_Wait_Ready();
  LCD_RS_Set();
  LCD_RW_Clr();
  LCD_EN_Clr();
  GPIOB->ODR = (GPIOB->ODR & 0x00ff) | dat << 8;
  LCD_EN_Set();
  delay_ms(5);
  LCD_EN_Clr();
}

void LCD1602_ClearScreen(void) { LCD1602_Write_Cmd(0x01); }

void LCD1602_Set_Cursor(u8 x, u8 y) {
  u8 addr;

  if (y == 0)
    addr = 0x00 + x;
  else
    addr = 0x40 + x;
  LCD1602_Write_Cmd(addr | 0x80);
}

void LCD1602_Show_Str(u8 x, u8 y, u8 *str) {
  LCD1602_Set_Cursor(x, y);
  while (*str != '\0') {
    LCD1602_Write_Dat(*str++);
  }
}

void LCD1602_Init(void) {
  GPIO_Configuration();
  delay_ms(15);
  LCD1602_Write_Cmd(0x38);  // 4λ��������ģʽ����ʾ2�����ݣ�5*10����ÿ�ַ�
                            // 0X38Ϊ8λ����ģʽ�� ��ʾ2�����ݣ�5*10����ÿ�ַ�
  delay_ms(5);
  // LCD_EN_Set();
  // LCD_EN_Clr();
  LCD1602_Write_Cmd(0x38);  // 4λ��������ģʽ����ʾ2�����ݣ�5*10����ÿ�ַ�
                            // 0X38Ϊ8λ����ģʽ�� ��ʾ2�����ݣ�5*10����ÿ�ַ�
  delay_ms(5);
  LCD1602_Write_Cmd(0x38);  // 4λ��������ģʽ����ʾ2�����ݣ�5*10����ÿ�ַ�
                            // 0X38Ϊ8λ����ģʽ�� ��ʾ2�����ݣ�5*10����ÿ�ַ�
  delay_ms(5);
  LCD1602_Write_Cmd(0x0c);  // ��ʾ�����ع��
  delay_ms(5);
  LCD1602_Write_Cmd(0x06);  // �ƶ����
  delay_ms(5);
  LCD1602_Write_Cmd(0x01);  // ���LCD����ʾ����
  delay_ms(5);
}
