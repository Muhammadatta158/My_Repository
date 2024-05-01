/*
 * UART.c
 *
 * Created: 1/15/2024 4:49:44 PM
 *  Author: Muhammad Atta
 */ 

#include "UART.h"

void UART_INIT(void)
{
	//Baudrate
	UBRRL = 51;
	
	//Normal mode
	RESET_BIT(UCSRA,U2X);
	
	//frame
	//No Parity
	//8-bit mode (default)
	
	//Enabe
	SET_BIT(UCSRB,TXEN);
	SET_BIT(UCSRB,RXEN);
	
}

void UART_SEND(uint8_t data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR = data;
	
}

uint8_t UART_RECIEVE(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

void SEND_NUM(uint32_t num)
{
	//UART_SEND((uint8_t)num); 
	//UART_SEND((uint8_t)(num>>8));
	//UART_SEND((uint8_t)(num>>16));
	//UART_SEND((uint8_t)(num>>24));
	uint8_t* p = &num;
	UART_SEND(p[0]);
    UART_SEND(p[1]);
	UART_SEND(p[2]);
	UART_SEND(p[3]);
}

uint32_t RECIEVE_NUM(void)
{
	//uint8_t b1=UART_RECIEVE();
	//uint8_t b2=UART_RECIEVE();
	//uint8_t b3=UART_RECIEVE();
	//uint8_t b4=UART_RECIEVE();
	//uint32_t num = 0;
	//num=b1|(uint32_t)b2<<8|(uint32_t)b3<<16|(uint32_t)b4<<24;
	uint32_t num;
	uint8_t* p = &num;
	p[0] = UART_RECIEVE();
	p[1] = UART_RECIEVE();
	p[2] = UART_RECIEVE();
	p[3] = UART_RECIEVE();
	return num;
}

void SEND_STRING(uint8_t* str)
{
	uint8_t i;
	for(i=0;i<str[i];i++)
	{
		UART_SEND(str[i]);
	}
	UART_SEND(stop);
}

void RECIEVE_STRING(uint8_t* buff)
{
	uint8_t i=0;
	buff[i]=UART_RECIEVE();
	while(buff[i]!=stop)
	{
		i++;
		buff[i]=UART_RECIEVE();
	}
	buff[i] = '\0'; 
}