/*
 * LCD.h
 *
 * Created: 1/15/2024 9:14:04 PM
 *  Author: Muhammad Atta
 */ 


#ifndef LCD_H_
#define LCD_H_

#include<avr/io.h>
#include<avr/delay.h>
#define F_CPU 1000000UL

#define LCD_PORT PORTA
#define DDR_LCD_PORT DDRA
#define LCDCRTL_PORT PORTB
#define DDR_LCDCRTL_PORT DDRB
#define RS_SW 1
#define RW_SW 2
#define EN_SW 3
#define Eight_bit_mode

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





#endif /* LCD_H_ */