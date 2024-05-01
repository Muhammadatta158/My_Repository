/*
 * ATMEGA32.h
 *
 * Created: 1/15/2024 8:27:10 PM
 *  Author: Muhammad Atta
 */ 


#ifndef ATMEGA32_H_
#define ATMEGA32_H_

// USART Registers

#define UDR							(*(uint8_t *)0x2C)
#define UCSRA						(*(uint8_t *)0x2B)
#define UCSRB						(*(uint8_t *)0x2A)
#define UCSRC						(*(uint8_t *)0x40)
#define UBRRH						(*(uint8_t *)0x40)
#define UBRRL						(*(uint8_t *)0x29)

// UCSRA
#define MPCM		0
#define U2X			1
#define PE			2
#define DOR			3
#define FE			4
#define UDRE		5
#define TXC			6
#define RXC			7

// UCSRB
#define TXB8		0
#define RXB8		1
#define UCSZ2		2
#define TXEN		3
#define RXEN		4
#define UDRIE		5
#define TXCIE		6
#define RXCIE		7

// UCSRC
#define UCPOL		0
#define UCSZ0		1
#define UCSZ1		2
#define USBS		3
#define UPM0		4
#define UPM1		5
#define UMSEL		6
#define URSEL		7
#endif /* ATMEGA32_H_ */