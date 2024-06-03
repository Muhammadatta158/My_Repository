/*
 * Student_info.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Muhammad Atta
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

/**********Student infrmation store***********************/
typedef struct {
	char Fname[50];
	char Lname[50];
	int roll;
	float GPA;
	int CID[10];
}Sinfo_t;


#define DPRINTF(...)      {fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}
#define width 50
Sinfo_t buffer[width];

//FIFO data
typedef struct{
	unsigned int length;
	unsigned int count;
	Sinfo_t* base;
	Sinfo_t* head;
	Sinfo_t* tail;
}FIFO_Buff_t;

typedef enum {
	FIFO_NO_ERROR,
	FIFO_FULL,
	FIFO_EMPTY,
	FIFO_NULL
}FIFO_Status_t;

/*************** API Integration************************/
FIFO_Status_t FIFO_init(FIFO_Buff_t* fifo, Sinfo_t* buf, uint32_t length);
FIFO_Status_t FIFO_IsEmpty(FIFO_Buff_t* fifo);
FIFO_Status_t FIFO_IsFull(FIFO_Buff_t* fifo);
int check_roll(FIFO_Buff_t* fifo, int num);
void add_student_file(FIFO_Buff_t* fifo);
void add_student_manual(FIFO_Buff_t* fifo);
void find_roll(FIFO_Buff_t* fifo);
void find_Fn(FIFO_Buff_t* fifo);
void find_c(FIFO_Buff_t* fifo);
void total_s(FIFO_Buff_t* fifo);
void delete_s(FIFO_Buff_t* fifo);
void update_s(FIFO_Buff_t* fifo);
void show_s(FIFO_Buff_t* fifo);

#endif /* FIFO_H_ */