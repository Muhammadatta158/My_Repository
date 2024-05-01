/*
 * STEM32_GPIO.c
 *
 *  Created on: Jan 2, 2024
 *      Author: Muhammad Atta
 */

#include "STM32_GPIO.h"


uint8_t GET_CRHL_POS(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
	  return 0 ;
	  break;
	case GPIO_PIN_1:
		  return 4 ;
		  break;
	case GPIO_PIN_2:
			  return 8 ;
			  break;
	case GPIO_PIN_3:
			  return 12 ;
			  break;
	case GPIO_PIN_4:
			  return 16 ;
			  break;
	case GPIO_PIN_5:
			  return 20 ;
			  break;
	case GPIO_PIN_6:
			  return 24 ;
			  break;
	case GPIO_PIN_7:
			  return 28 ;
			  break;
	case GPIO_PIN_8:
		      return 0 ;
		      break;
	case GPIO_PIN_9:
			  return 4 ;
			  break;
	case GPIO_PIN_10:
			  return 8 ;
			  break;
	case GPIO_PIN_11:
			  return 12 ;
			  break;
	case GPIO_PIN_12:
			  return 16 ;
		      break;
	case GPIO_PIN_13:
			  return 20 ;
			  break;
	case GPIO_PIN_14:
			  return 24 ;
			  break;
	case GPIO_PIN_15:
			  return 28 ;
			  break;
	}
}

/**================================================================
* @Fn-                      -MCAL_GPIO_INIT
* @brief -                  -Initializes GPIOx PINy according to te specified parameters in Pin configuration
* @param [in] -             -GPIOx (x may be (A...E))
* @param [in] -             -PinConfig pointer to GPIO_Configure_t that contain pin configuration
* @retval -                 -None
* Note-                     -stm32f103c6 has GPIO(A,B,C,D) but the backage LFQP48 has only GPIO A,B, and part of C/D
*/

void MCAL_GPIO_INIT(GPIO_TypeDef* GPIOx, GPIO_Configure_t* PinConfig)
{
    //Port configuration register low (GPIOx_CRL) configures pins from 0 to 7
	//Port configuration register High (GPIOx_CRH) configures pins from 8 to 15
	volatile uint32_t* ConfigRegister = NULL;
	uint8_t PIN_Config = 0;
	ConfigRegister = (PinConfig->GPIO_PinNumber <GPIO_PIN_8)? &GPIOx->CRL : &GPIOx->CRH;
	//clear CNF and MODE bits
    (*ConfigRegister) &= ~(0xf<< GET_CRHL_POS(PinConfig->GPIO_PinNumber));

    //If pin is output
    if((PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_PP) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_Mode == GPIO_MODE_OUTPUT_AF_OD))
    {
    	//Set CNF
    	PIN_Config = ((((PinConfig->GPIO_Mode -4)<<2) | (PinConfig->GPIO_Output_Speed))&0x0f);

    }
    //if pin is input
    else
    {
    	if ((PinConfig->GPIO_Mode == GPIO_MODE_FLO) || (PinConfig->GPIO_Mode == GPIO_MODE_Analog))
		{
    		PIN_Config = ( (((PinConfig->GPIO_Mode)<<2) | 0x0) & 0x0f );

		}else if (PinConfig->GPIO_Mode == GPIO_MODE_AF_INPUT  )
		{
			PIN_Config = ( (((GPIO_MODE_FLO)<<2) | 0x0) & 0x0f );
		}
		else//PU and PD inputs
		{
			if (PinConfig->GPIO_Mode == GPIO_MODE_INPUT_PU  )
			{
				//for pull-up input, ODR =1
				GPIOx->ODR |= PinConfig->GPIO_PinNumber;

			}else
			{
				//for pull-down input, ODR =0
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
			}
		}

    }
    (*ConfigRegister) |= ( (PIN_Config) << GET_CRHL_POS(PinConfig->GPIO_PinNumber) );
}


/**================================================================
* @Fn                        -MCAL_GPIO_DEINIT
* @brief                     -Reset all GPIO register
* @param [in]                -GPIOx (x may be (A...E))
* @retval                    -None
* Note                       -None
*/
void MCAL_GPIO_RESET(GPIO_TypeDef* GPIOx)
{
	//Without Reset register
	//GPIOx->BRR  = 0x00000000;
	//GPIOx->BSRR = 0x00000000;
	//GPIOx->CRH  = 0x44444444;
	//GPIOx->CRL  = 0x44444444;
	//GPIOx->IDR is read only register
	//GPIOx->LCKR = 0x00000000;
	//GPIOx->ODR  = 0x00000000;

	if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}else if(GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}else if(GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}else if(GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}else if(GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}



}

/**================================================================
* @Fn                        -MCAL_GPIO_ReadPin
* @brief                     -Read specific PIN
* @param [in]                -GPIOx (x may be (A...E))
* @param [in]                -Set Pin Number according to @GPIO_PINS_DEFINATION
* @retval                    -Input Pin value according to @GPIO_PINS_Status
* Note                       -None
*/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	uint8_t PinStatus;

	if (((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		PinStatus = GPIO_PIN_SET;
	}else
	{
		PinStatus = GPIO_PIN_RESET;
	}

}

/**================================================================
* @Fn                        -MCAL_GPIO_ReadPort
* @brief                     -Read specific PORT
* @param [in]                -GPIOx (x may be (A...E))
* @retval                    -Input Port value
* Note                       -None
*/

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef* GPIOx)
{
	uint16_t PortValue;
	PortValue = (uint16_t)(GPIOx->IDR);


}

/**================================================================
* @Fn                        -MCAL__GPIO_WritePin
* @brief                     -Write specific PIN
* @param [in]                -GPIOx (x may be (A...E))
* @param [in]                -Pin Number according to @GPIO_PINS_DEFINATION
* @param [in]                -Pin value
* @retval                    -None
* Note                       -None
*/

void MCAL__GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t PinNumber, uint8_t value)
{
	if (value != GPIO_PIN_RESET)
		{
			//GPIOx->ODR |= PinNumber;
			//OR
		GPIOx->BSRR = PinNumber;
		}
		else
		{
			GPIOx->BRR = PinNumber;
		}

}

/**================================================================
* @Fn                        -MCAL__GPIO_WritePort
* @brief                     -Write specific PORT
* @param [in]                -GPIOx (x may be (A...E))
* @param [in]                -Port value
* @retval                    -None
* Note                       -None
*/

void MCAL__GPIO_WritePort(GPIO_TypeDef* GPIOx, uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}

/**================================================================
* @Fn                        -MCAL__GPIO_TogglePin
* @brief                     -Toggle specific PIN
* @param [in]                -GPIOx (x may be (A...E))
* @param [in]                -Pin Number according to @GPIO_PINS_DEFINATION
* @retval                    -None
* Note                       -None
*/

void MCAL__GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t PinNmber)
{
	GPIOx->ODR ^= (PinNmber);

}

/**================================================================
* @Fn                        -MCAL__GPIO_LockPin
* @brief                     -Lock specific PIN
* @param [in]                -GPIOx (x may be (A...E))
* @param [in]                -Pin Number according to @GPIO_PINS_DEFINATION
* @retval                    -Ok if pin is locked / Error if pin is not locked according to @GPIO_Lock_retrn
* Note                       -None
*/

uint8_t MCAL__GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t PinNumber)
{
	//Set LCK[16]
	volatile uint32_t temp = 1<<16;
	//Set LCKy
	temp |= PinNumber;

	//write 1
	GPIOx->LCKR = temp;
	//write 0
	GPIOx->LCKR = PinNumber;
	//write 1
	GPIOx->LCKR = temp;

	//read 0
	temp = GPIOx->LCKR;
	//read 1
	if((GPIOx->LCKR) & (1<<16))
	{
		return GPIO_Locked;
	}else
	{
		return GPIO_NotLocked;
	}

}

