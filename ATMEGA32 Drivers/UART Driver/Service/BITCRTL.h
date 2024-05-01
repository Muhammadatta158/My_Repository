/*
 * BITCRTL.h
 *
 * Created: 1/15/2024 8:28:24 PM
 *  Author: Muhammad Atta
 */ 


#ifndef BITCRTL_H_
#define BITCRTL_H_

#define SET_BIT(PORT,Bit)       PORT |=  (1<<Bit)		
#define RESET_BIT(PORT,Bit)     PORT &= ~(1<<Bit)		
#define TOGGLE_BIT(PORT,Bit)    PORT ^=  (1<<Bit)		
#define READ_BIT(PORT,Bit)     ((PORT >> Bit) & 1)		


#endif /* BITCRTL_H_ */