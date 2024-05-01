/*
 * STM32_GPIO.h
 *
 *  Created on: Jan 2, 2024
 *      Author: PC
 */

#ifndef INC_STM32_GPIO_H_
#define INC_STM32_GPIO_H_

#include "stm32f103x6.h"

typedef struct{
	uint16_t GPIO_PinNumber;          //Specifies GPIO pins to be configured
	                                  //This parameter must based on @GPIO_PINS_DEFINATION
    uint8_t GPIO_Mode;               //Specifies GPIO pins to be configured
                                      //This parameter must based on @GPIO_MODE_DEFINATION
    uint8_t GPIO_Output_Speed;       //Specifies GPIO pins to be configured
                                      //This parameter must based on @GPIO_SPEED_DEFINATION


}GPIO_Configure_t;

//@GPIO_PINS_DEFINATION
#define GPIO_PIN_0          ((uint16_t)0x0001) //Set Pin0
#define GPIO_PIN_1          ((uint16_t)0x0002) //Set Pin1
#define GPIO_PIN_2          ((uint16_t)0x0004) //Set Pin2
#define GPIO_PIN_3          ((uint16_t)0x0008) //Set Pin3
#define GPIO_PIN_4          ((uint16_t)0x0010) //Set Pin4
#define GPIO_PIN_5          ((uint16_t)0x0020) //Set Pin5
#define GPIO_PIN_6          ((uint16_t)0x0040) //Set Pin6
#define GPIO_PIN_7          ((uint16_t)0x0080) //Set Pin7
#define GPIO_PIN_8          ((uint16_t)0x0100) //Set Pin8
#define GPIO_PIN_9          ((uint16_t)0x0200) //Set Pin9
#define GPIO_PIN_10         ((uint16_t)0x0400) //Set Pin10
#define GPIO_PIN_11         ((uint16_t)0x0800) //Set Pin11
#define GPIO_PIN_12         ((uint16_t)0x1000) //Set Pin12
#define GPIO_PIN_13         ((uint16_t)0x2000) //Set Pin13
#define GPIO_PIN_14         ((uint16_t)0x4000) //Set Pin14
#define GPIO_PIN_15         ((uint16_t)0x8000) //Set Pin15
#define GPIO_PIN_ALL        ((uint16_t)0xFFFF) //Set All Pin


//@GPIO_MODE_DEFINATION
#define GPIO_MODE_Analog          0x00000000u                //Analog mode
#define GPIO_MODE_FLO             0x00000001u                //Floating input (reset state)
#define GPIO_MODE_INPUT_PU        0x00000002u                //Input with pull-up
#define GPIO_MODE_INPUT_PD        0x00000003u                //Input with pull-down
#define GPIO_MODE_OUTPUT_PP       0x00000004u                //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD       0x00000005u                //General purpose output Open-drain
#define GPIO_MODE_OUTPUT_AF_PP    0x00000006u               //Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD    0x00000007u               //Alternate function output Open-drain
#define GPIO_MODE_AF_INPUT        0x00000008u               //Alternate function input



//@GPIO_SPEED_DEFINATION
#define GPIO_Speed_10M            0x00000001u                //Analog mode
#define GPIO_Speed_2M             0x00000002u                //Floating input (reset state)
#define GPIO_Speed_50M            0x00000003u                //Input with pull-up

//@GPIO_PINS_Status
#define GPIO_PIN_SET     1
#define GPIO_PIN_RESET   0

//@GPIO_Lock_retrn
#define GPIO_Locked      1
#define GPIO_NotLocked   0


//MCAL APIs
void MCAL_GPIO_INIT(GPIO_TypeDef* GPIOx, GPIO_Configure_t* PinConfig);
void MCAL_GPIO_RESET(GPIO_TypeDef* GPIOx);

uint8_t MCAL__GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx);

void MCAL__GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t Pinumber, uint8_t value);
void MCAL__GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t value);

void MCAL__GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);

uint8_t MCAL__GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber);

#endif /* INC_STM32_GPIO_H_ */
