/*
 * UART.h
 *
 * Created: 1/15/2024 4:50:03 PM
 *  Author: Muhammad Atta
 */ 


#ifndef UART_H_
#define UART_H_

#include "BITCRTL.h"
#include "ATMEGA32.h"
#include "stdint.h"

#define stop '\r'

void UART_INIT(void);
void UART_SEND(uint8_t data);
uint8_t UART_RECIEVE(void);
void SEND_NUM(uint32_t num);
uint32_t RECIEVE_NUM(void);
void SEND_STRING(uint8_t* str);
void RECIEVE_STRING(uint8_t* buff);





#endif /* UART_H_ */