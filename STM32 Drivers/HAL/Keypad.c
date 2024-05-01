#include "Keypad.h"

int KEYPAD_R[]={R0,R1,R2,R3};
int KEYPAD_C[]={C0,C1,C2,C3};

void KEYPAD_INIT()
{
	//DDR_KEYPAD &= ~((1<<RO) | (1<<R1) | (1<<R2) | (1<<R3));
	//DDR_KEYPAD |= ((1<<C0) | (1<<C1) | (1<<C3) | (1<<C3));
	PINcfg.GPIO_PinNumber = R0;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);


	PINcfg.GPIO_PinNumber = R1;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);

	PINcfg.GPIO_PinNumber = R2;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);

	PINcfg.GPIO_PinNumber = R3;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);

	PINcfg.GPIO_PinNumber = C0;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);

	PINcfg.GPIO_PinNumber = C1;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);

	PINcfg.GPIO_PinNumber = C2;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;


	PINcfg.GPIO_PinNumber = C3;
	PINcfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	PINcfg.GPIO_Output_Speed = GPIO_Speed_10M;
	MCAL_GPIO_INIT(KEYPAD_PORT, &PINcfg);

	//KEYPAD_PORT = 0xFF;
	MCAL__GPIO_WritePort(KEYPAD_PORT, 0xFF);
}
char GET_CHAR()
{
	int i,j;
	for(i=0;i<4;i++)
	{
		//KEYPAD_PORT |= ((1<<KEYPAD_C[0]) | (1<<KEYPAD_C[1]) | (1<<KEYPAD_C[2]) | (1<<KEYPAD_C[3]));
		//KEYPAD_PORT &= ~(1<<KEYPAD_C[i]);
		MCAL__GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[0], GPIO_PIN_SET);
		MCAL__GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[1], GPIO_PIN_SET);
		MCAL__GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[2], GPIO_PIN_SET);
		MCAL__GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[3], GPIO_PIN_SET);
		MCAL__GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[i], GPIO_PIN_SET);
		for(j=0;j<4;j++)
		{

			if(MCAL_GPIO_ReadPin((KEYPAD_PORT, KEYPAD_R[j])==0))
			{
				while(MCAL_GPIO_ReadPin((KEYPAD_PORT, KEYPAD_R[j])==0));
				switch(i)
				{
				case(0):
					{
						if(j==0) return '7';
						else if(j==1) return '4';
						else if(j==2) return '1';
						else if(j==3) return '?';
					}
				case(1):
					{
						if(j==0) return '8';
						else if(j==1) return '5';
						else if(j==2) return '2';
						else if(j==3) return '0';
					}
				case(2):
					{
						if(j==0) return '9';
						else if(j==1) return '6';
						else if(j==2) return '3';
						else if(j==3) return '=';
					}
				case(3):
					{
						if(j==0) return '/';
						else if(j==1) return '*';
						else if(j==2) return '-';
						else if(j==3) return '+';
					}
				}
			}
		}
	}
	return 'E';  //IF NO KEY PRESSED
}
