#include "LCD.h"

GPIO_Configure_t PINcfg;


void LCD_EN()
{
	//LCDCRTL_PORT &= ~(1<<EN);
	MCAL__GPIO_WritePin(LCD_PORT, EN_SW, GPIO_PIN_SET);
	wait(1);
	//LCDCRTL_PORT |= (1<<EN);
	MCAL__GPIO_WritePin(LCD_PORT, EN_SW, GPIO_PIN_RESET);
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

void LCD_CLEAR_SCREEN()
{
	 LCD_W_COMM(CLEAR_DISPLAY);
}
void LCD_BUSY(void)
{

	         PINcfg.GPIO_PinNumber = GPIO_PIN_0;
		     PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		     PINcfg.GPIO_PinNumber = GPIO_PIN_1;
		     PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    PINcfg.GPIO_PinNumber = GPIO_PIN_2;
		    PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    PINcfg.GPIO_PinNumber = GPIO_PIN_3;
		    PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    PINcfg.GPIO_PinNumber = GPIO_PIN_4;
		    PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    PINcfg.GPIO_PinNumber = GPIO_PIN_5;
		    PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    PINcfg.GPIO_PinNumber = GPIO_PIN_6;
		    PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    PINcfg.GPIO_PinNumber = GPIO_PIN_7;
		    PINcfg.GPIO_Mode = GPIO_MODE_FLO;
		    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

		    MCAL__GPIO_WritePin(LCDCRTL_PORT, RW_SW, GPIO_PIN_SET);
		    MCAL__GPIO_WritePin(LCDCRTL_PORT, RS_SW, GPIO_PIN_RESET);
	        //LCDCRTL_PORT |= (1<<RW);
	        //LCDCRTL_PORT &= ~(1<<RS);
	        LCD_EN();
	        //DDR_LCD_PORT = 0xFF;
	        MCAL__GPIO_WritePin(LCDCRTL_PORT, RW_SW, GPIO_PIN_RESET);
	        //LCDCRTL_PORT &= ~(1<<RW);
}
void LCD_INIT(void)
{
	wait(20);
	     LCD_BUSY();
	     //LCDCRTL_PORT &= ~((1<<EN) | (1<<RW) | (1<<RS));
	     //PA1 floating input
	     PINcfg.GPIO_PinNumber = EN_SW;
	     PINcfg.GPIO_Mode = GPIO_MODE_FLO;
	     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	     PINcfg.GPIO_PinNumber = RS_SW;
	     PINcfg.GPIO_Mode = GPIO_MODE_FLO;
	     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	     PINcfg.GPIO_PinNumber = RW_SW;
	     PINcfg.GPIO_Mode = GPIO_MODE_FLO;
	     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	     wait(15);
	     PINcfg.GPIO_PinNumber = GPIO_PIN_0;
	     PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	     PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	     PINcfg.GPIO_PinNumber = GPIO_PIN_1;
	     PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	     PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	     MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	    PINcfg.GPIO_PinNumber = GPIO_PIN_2;
	    PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	    PINcfg.GPIO_PinNumber = GPIO_PIN_3;
	    PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	    PINcfg.GPIO_PinNumber = GPIO_PIN_4;
	    PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	    PINcfg.GPIO_PinNumber = GPIO_PIN_5;
	    PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	    PINcfg.GPIO_PinNumber = GPIO_PIN_6;
	    PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	    PINcfg.GPIO_PinNumber = GPIO_PIN_7;
	    PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	    PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	    MCAL_GPIO_INIT(LCD_PORT, &PINcfg);

	     LCD_CLEAR_SCREEN();
	     LCD_W_COMM(FUNC_8BIT_L2);

	     LCD_W_COMM(ENTRY_MODE);
	     LCD_W_COMM(BEGIN_FIRST_ROW);
	     LCD_W_COMM(DISPLAY_ON_CRUSOR_BLK);
}
void LCD_W_COMM(unsigned char comm)
{
	//#ifdef Eight_bit_mode
	LCD_BUSY();
	//LCD_PORT = comm;
	MCAL__GPIO_WritePort(LCD_PORT, comm);
	MCAL__GPIO_WritePin(LCD_PORT, RS_SW, GPIO_PIN_RESET);
	MCAL__GPIO_WritePin(LCD_PORT, RW_SW, GPIO_PIN_RESET);
	wait(1);
	LCD_EN();
	//#endif
}
void LCD_W_CHAR(unsigned char data)
{
	//#ifdef Eight_bit_mode
	LCD_BUSY();
	//LCD_PORT = data;
	MCAL__GPIO_WritePort(LCD_PORT, data);
	//LCDCRTL_PORT &= ~((1<<RW));
	MCAL__GPIO_WritePin(LCD_PORT, RW_SW, GPIO_PIN_RESET);
	//LCDCRTL_PORT |= (1<<RS);
	MCAL__GPIO_WritePin(LCD_PORT, RS_SW, GPIO_PIN_SET);
	LCD_EN();
	//#endif
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
