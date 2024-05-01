#include "LCD.h"

void LCD_EN()
{
	LCDCRTL_PORT &= ~(1<<EN);
	_delay_ms(30);
	LCDCRTL_PORT |= (1<<EN);
}
void LCD_GOTO_XY(int line, int pos)
{
	if(line==1)
	{
		if(pos<16 && pos>=0)

	   {
		LCD_W_COMM(BEGIN_FIRST_ROW+pos);
	   }
    }
	else if(line == 2)
	{
		if(pos<16 && pos>=0)
	    {
		LCD_W_COMM(BEGIN_SECOND_ROW+pos);
	    }
   }
}

void LCD_CLEAR_SCREEN();
{
	 LCD_W_COMM(CLEAR_DISPLAY);
}
void LCD_BUSY(void)
{
	DDR_LCD_PORT  = 0x00;
	LCDCRTL_PORT |= (1<<RW);
	LCDCRTL_PORT &= ~(1<<RS);
	LCD_EN();
	DDR_LCD_PORT = 0xFF;
	LCDCRTL_PORT &= ~(1<<RW);
}
void LCD_INIT(void)
{
	_delay_ms(20);
	#ifdef Eight_bit_mode
	     LCD_BUSY();
	     DDR_LCDCRTL_PORT |= (1<<EN) | (1<<RW) | (1<<RS);
	     LCDCRTL_PORT &= ~((1<<EN) | (1<<RW) | (1<<RS));
	     DDR_LCD_PORT = 0xFF;
	     LCD_CLEAR_SCREEN();
	     LCD_W_COMM(FUNC_8BIT_L2);
	#endif
	     LCD_W_COMM(ENTRY_MODE);
	     LCD_W_COMM(BEGIN_FIRST_ROW);
	     LCD_W_COMM(DISPLAY_ON_CRUSOR_BLK);
}
void LCD_W_COMM(unsigned char comm)
{
	#ifdef Eight_bit_mode
	LCD_BUSY();
	LCD_PORT = comm;
	LCDCRTL_PORT &= ~((1<<RW) | (1<<RS));
	LCD_EN();
	#endif
}
void LCD_W_CHAR(unsigned char data)
{
	#ifdef Eight_bit_mode
	LCD_BUSY();
	LCD_PORT = data;
	LCDCRTL_PORT &= ~((1<<RW));
	LCDCRTL_PORT |= (1<<RS);
	LCD_EN();
	#endif
}
void LCD_W_STRING(char* data)
{
	int i=0;
	while(*data > 0)
	{
		i++;
	
	LCD_W_CHAR(*data++);
	if(i==16)
	{
		LCD_GOTO_XY(2,0);
	}
	else if(1==32)
	{
		LCD_CLEAR_SCREEN();
		LCD_GOTO_XY(1,0);
		i=0;
	}
    }
}