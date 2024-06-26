#ifndef LCD_H_
#define LCD_H_

#include "stm32f103x6.h"
#include "STM32_GPIO.h"
#include "stdlib.h"
#include "stdio.h"

#define F_CPU 1000000UL

#define LCD_PORT        GPIOA
//#define DATA_SHIFT      4       //0:8-bit mode  - 4:4-bit mode
#define LCDCRTL_PORT    GPIOA
#define RS_SW           GPIO_PIN_8
#define RW_SW           GPIO_PIN_9
#define EN_SW           GPIO_PIN_10
//#define Eight_bit_mode
//#define Four_bit_mode

#define FUNC_8BIT_L1           (0x30)
#define FUNC_8BIT_L2           (0x38)
#define FUNC_4BIT_L1           (0x20)
#define FUNC_4BIT_L1           (0x28)
#define ENTRY_MODE             (0x06)
#define DISPLAY_OFF_CRUSOR_OFF (0x08)
#define DISPLAY_ON_CRUSOR_ON   (0x0E)
#define DISPLAY_ON_CRUSOR_OFF  (0x0C)
#define DISPLAY_ON_CRUSOR_BLK  (0x0F)
#define SHIFT_DIS_LEFT         (0x18)
#define SHIFT_DIS_RIGHT        (0x1C)
#define MOVE_CRUSOR_1LEFT      (0x10)
#define MOVE_CRUSOR_1RIGHT     (0x14)
#define CLEAR_DISPLAY          (0x01)
#define BEGIN_FIRST_ROW        (0x80)
#define BEGIN_SECOND_ROW       (0xC0)

void LCD_INIT(void);
void LCD_W_COMM(unsigned char comm);
void LCD_W_CHAR(unsigned char data);
void LCD_W_STRING(char* data);
void LCD_BUSY(void);
void LCD_CLEAR_SCREEN(void);
void wait(int x);







#endif
