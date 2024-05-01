/*
 * STEM32_GPIO.c
 *
 *  Created on: Jan 2, 2024
 *      Author: Muhammad Atta
 */

#include "STM32_EXTI.h"
//#include "STM32_GPIO.h"
#include "stm32f103x6.h"

/*============================================================================================
 *                                  Generic Variables
 *============================================================================================
 */

void (* GP_Callback[15])(void);

/*============================================================================================
 *                                  Generic MACROS
 *============================================================================================
 */

#define AFIO_GPIO_EXTI_MAPPTING(x)                 ( (x==GPIOA)?0:\
		                                             (x==GPIOB)?1:\
		                                             (x==GPIOC)?2:\
		                                             (x==GPIOD)?3:0)


/*============================================================================================
 *                                  Generic functions
 *============================================================================================
 */


void NVIC_ENABLE(int IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_EXTI0_IRQ6_ENABLE;
		break;
	case 1:
		NVIC_EXTI1_IRQ7_ENABLE;
		break;
	case 2:
		NVIC_EXTI2_IRQ8_ENABLE;
			break;
	case 3:
		NVIC_EXTI3_IRQ9_ENABLE;
			break;
	case 4:
		NVIC_EXTI4_IRQ10_ENABLE ;
			break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_EXTI5_9_IRQ23_ENABLE;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_EXTI10_15_IRQ40_ENABLE;
		break;

	}
}

void NVIC_DISABLE(int IRQ)
{
	switch(IRQ)
		{
		case 0:
			NVIC_EXTI0_IRQ6_DISABLE;
			break;
		case 1:
			NVIC_EXTI1_IRQ7_DISABLE;
			break;
		case 2:
				NVIC_EXTI2_IRQ8_DISABLE;
				break;
		case 3:
				NVIC_EXTI3_IRQ9_DISABLE;
				break;
		case 4:
				NVIC_EXTI4_IRQ10_DISABLE;
				break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_EXTI5_9_IRQ23_DISABLE;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_EXTI10_15_IRQ40_DISABLE;
			break;

		}
}
void UPDATE(EXTI_PinConfig_t* EXTI_Config)
{
	//Configure GPIO to be floating input
	GPIO_Configure_t Pincfg;
	Pincfg.GPIO_PinNumber=EXTI_Config->EXTI_PIN.GPIO_PIN;
	Pincfg.GPIO_Mode     = GPIO_MODE_FLO;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_PORT, &Pincfg);

	//=========================================

	//Update AFIO to route between EXTI line and with port(A,B,C,D)
	uint8_t AFIO_EXTICR_INDEX = EXTI_Config->EXTI_PIN.EXTI_InputLineNum/4;
	uint8_t AFIO_EXTICR_POS   = (EXTI_Config->EXTI_PIN.EXTI_InputLineNum %4)*4;
	//Clear four bit
	AFIO->EXTICR[AFIO_EXTICR_INDEX] &= ~(0xF << AFIO_EXTICR_POS);
	AFIO->EXTICR[AFIO_EXTICR_INDEX] |= ((AFIO_GPIO_EXTI_MAPPTING(EXTI_Config->EXTI_PIN.GPIO_PORT)&0xF) << AFIO_EXTICR_POS);
    //Update Rising and Falling edge
	EXTI->RTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
	EXTI->FTSR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);

	if(EXTI_Config->Trigger_case == EXTI_Trigger_Rising)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
	}else if(EXTI_Config->Trigger_case == EXTI_Trigger_Falling)
	{
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
	}else if(EXTI_Config->Trigger_case == EXTI_Trigger_Both)
	{
		EXTI->RTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
		EXTI->FTSR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
	}

	//Update IRQ Handling Callback
	GP_Callback[EXTI_Config->EXTI_PIN.EXTI_InputLineNum] = EXTI_Config->P_Callback;
	//Enable/Disable IRQ
	if(EXTI_Config->IRQ_EN = EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
		NVIC_ENABLE(EXTI_Config->EXTI_PIN.EXTI_InputLineNum);

	}else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.EXTI_InputLineNum);
		NVIC_DISABLE(EXTI_Config->EXTI_PIN.EXTI_InputLineNum);

	}



}

/*============================================================================================
 *                                  APIs functions
 *============================================================================================
 */

/**================================================================
* @Fn-                      -MCAL_GPIO_INIT
* @brief -                  -Initializes GPIOx PINy according to te specified parameters in Pin configuration
* @retval -                 -None
* Note-                     -stm32f103c6 has GPIO(A,B,C,D) but the backage LFQP48 has only GPIO A,B, and part of C/D
*/

void MCAL_EXTI_GPIO_RESET(void)
{
	EXTI->IMR   = 0x00000000;
	EXTI->EMR   = 0x00000000;
	EXTI->RTSR  = 0x00000000;
	EXTI->FTSR  = 0x00000000;
	EXTI->SWIER = 0x00000000;
	//r1 to clear PR
	EXTI->PR    = 0xFFFFFFFF;

	//Disable EXTI IRQ from NVIC
     NVIC_EXTI0_IRQ6_DISABLE           ;
     NVIC_EXTI1_IRQ7_DISABLE           ;
     NVIC_EXTI2_IRQ8_DISABLE           ;
     NVIC_EXTI3_IRQ9_DISABLE           ;
     NVIC_EXTI4_IRQ10_DISABLE          ;
     NVIC_EXTI5_9_IRQ23_DISABLE        ;
     NVIC_EXTI10_15_IRQ40_DISABLE      ;


}

/**================================================================
* @Fn-                      -MCAL_EXTI_GPIO_INIT
* @brief -                  -Initializes EXTI from specific GPIO PIN and specifies mask configuration and IRQ Callback.
* @param [in] -             -EXTI_Config set according to @ref EXTI_define
* @retval -                 -None
* Note-                     -stm32f103c6 has GPIO(A,B,C,D) but the backage LFQP48 has only GPIO A,B, and part of C/D
*/

void MCAL_EXTI_GPIO_INIT(EXTI_PinConfig_t* EXTI_Config)
{
	UPDATE(EXTI_Config);

}
void MCAL_EXTI_GPIO_UPDATE(EXTI_PinConfig_t* EXTI_Config)
{
	UPDATE(EXTI_Config);
}


/*============================================================================================
 *                                  ISR Functions
 *============================================================================================
 */

void EXTI0_IRQHandler(void)
{
	//Clear PR by writing '1' into the pending register (EXTI_PR)
	EXTI->PR |= (1<<0);    //Shifting 0 (EXTI0)
	//Call the IRQ Callback
	GP_Callback[0]();


}

void EXTI1_IRQHandler(void)
{
	//Clear PR by writing '1' into the pending register (EXTI_PR)
	EXTI->PR |= (1<<1);    //Shifting 0 (EXTI0)
	//Call the IRQ Callback
	GP_Callback[1]();

}

void EXTI2_IRQHandler(void)
{
	//Clear PR by writing '1' into the pending register (EXTI_PR)
	EXTI->PR |= (1<<2);    //Shifting 0 (EXTI0)
	//Call the IRQ Callback
	GP_Callback[2]();

}

void EXTI3_IRQHandler(void)
{
	//Clear PR by writing '1' into the pending register (EXTI_PR)
	EXTI->PR |= (1<<3);    //Shifting 0 (EXTI0)
	//Call the IRQ Callback
	GP_Callback[3]();

}


void EXTI4_IRQHandler(void)
{
	//Clear PR by writing '1' into the pending register (EXTI_PR)
	EXTI->PR |= (1<<4);    //Shifting 0 (EXTI0)
	//Call the IRQ Callback
	GP_Callback[4]();

}

void EXTI5_9_IRQHandler(void)
{
	if(EXTI->PR & 1<<5){EXTI->PR |= (1<<5) ; GP_Callback[5]();}
	if(EXTI->PR & 1<<6){EXTI->PR |= (1<<6) ; GP_Callback[6]();}
	if(EXTI->PR & 1<<7){EXTI->PR |= (1<<7) ; GP_Callback[7]();}
	if(EXTI->PR & 1<<8){EXTI->PR |= (1<<8) ; GP_Callback[8]();}
	if(EXTI->PR & 1<<9){EXTI->PR |= (1<<9) ; GP_Callback[9]();}

}

void EXTI10_15_IRQHandler(void)
{
	if(EXTI->PR & 1<<10){EXTI->PR |= (1<<10) ; GP_Callback[10]();}
	if(EXTI->PR & 1<<11){EXTI->PR |= (1<<11) ; GP_Callback[11]();}
	if(EXTI->PR & 1<<12){EXTI->PR |= (1<<12) ; GP_Callback[12]();}
	if(EXTI->PR & 1<<13){EXTI->PR |= (1<<13) ; GP_Callback[13]();}
	if(EXTI->PR & 1<<14){EXTI->PR |= (1<<14) ; GP_Callback[14]();}
	if(EXTI->PR & 1<<15){EXTI->PR |= (1<<15) ; GP_Callback[15]();}


}


