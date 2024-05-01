/*
 * stm32f103x6.h
 *
 *  Created on: Jan 2, 2024
 *      Author: PC
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//Includes
#include "stdlib.h"
#include <stdint.h>

#define Flash_Memory_BASE                              0x08000000UL
#define System_Memory_BASE                             0x1FFFF000UL
#define SRAM_Memory_BASE                               0x20000000UL
#define Peripherals_BASE                               0x40000000UL
#define Cortex_Internal_Peripherals_BASE               0x40000000UL

//AHB Peripherals
#define RCC_BASE                                       (Peripherals_BASE + 0x00021000UL)

//APB2 Peripherals
#define GPIOA_BASE                                     (Peripherals_BASE + 0x00010800UL)
#define GPIOB_BASE                                     (Peripherals_BASE + 0x00010C00UL)
#define GPIOC_BASE                                     (Peripherals_BASE + 0x00011000UL)
#define GPIOD_BASE                                     (Peripherals_BASE + 0x00011400UL)
#define GPIOE_BASE                                     (Peripherals_BASE + 0x00011800UL)

#define AFIO_BASE                                      (Peripherals_BASE + 0x00010000UL)
#define EXTI_BASE                                      (Peripherals_BASE + 0x00010400UL)

//APB1 Peripherals

//GPIO Registers
typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_TypeDef;

//AFIO Registers
typedef struct{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	 uint32_t Reserved;
	volatile uint32_t MAPR2;
}AFIO_TypeDef;

//EXTI Registers
typedef struct{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_TypeDef;

//RCC Registers
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_TypeDef;

//Peripherals instants
#define GPIOA                               ((GPIO_TypeDef*)(GPIOA_BASE))
#define GPIOB                               ((GPIO_TypeDef*)(GPIOB_BASE))
#define GPIOC                               ((GPIO_TypeDef*)(GPIOC_BASE))
#define GPIOD                               ((GPIO_TypeDef*)(GPIOD_BASE))
#define GPIOE                               ((GPIO_TypeDef*)(GPIOE_BASE))

#define RCC                                 ((RCC_TypeDef*)(RCC_BASE))

#define EXTI                                ((EXTI_TypeDef*)(EXTI_BASE))

#define AFIO                                ((AFIO_TypeDef*)(AFIO_BASE))

//Clock Enable
#define RCC_GPIOA_CLK_EN()                   (RCC->APB2ENR |=(1<<2))
#define RCC_GPIOB_CLK_EN()                   (RCC->APB2ENR |=(1<<3))
#define RCC_GPIOC_CLK_EN()                   (RCC->APB2ENR |=(1<<4))
#define RCC_GPIOD_CLK_EN()                   (RCC->APB2ENR |=(1<<5))
#define RCC_GPIOE_CLK_EN()                   (RCC->APB2ENR |=(1<<6))

#define RCC_AFIO_CLK_EN()                   (RCC->APB2ENR |=(1<<0))


#endif /* INC_STM32F103X6_H_ */
