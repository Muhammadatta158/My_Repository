/*
 * main.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Muhammad Atta
 */



#include "FIFO.h"

int main()
{
	FIFO_Buff_t student_buffer;
	int choice = 0;

	FIFO_init(&student_buffer, buffer, 50);

	printf("Welcome to the student management system...\n");
	while(1){
		printf("Select one of the choices: \n");
		printf("1. Add the student Details Manually\n");
		printf("2. Add the student Details From Text File\n");
		printf("3. Find the Student Details by Roll Number\n");
		printf("4. Find the Student Details by First Name\n");
		printf("5. Find the student Details by Course ID\n");
		printf("6. Find the Total number of Students\n");
		printf("7. Delete the Students Details by Roll Number\n");
		printf("8. Update the Students Details by Roll Number\n");
		printf("9. Show all information\n");
		printf("10. To Exit\n");
		fflush(stdout);
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				printf("/***********************/");
				printf("\nAdd student details: \n");
				add_student_manual(&student_buffer);
				break;
			case 2:
				printf("/***********************/");
				printf("\nAdd student details: \n");
				add_student_file(&student_buffer);
				break;
			case 3:
				printf("=========================\n");
				find_roll(&student_buffer);
				break;
			case 4:
				printf("==========================\n");
				find_Fn(&student_buffer);
				break;
			case 5:
				printf("==========================\n");
				find_c(&student_buffer);
				break;
			case 6:
				printf("==========================\n");
				total_s(&student_buffer);
				break;
			case 7:
				printf("==========================\n");
				delete_s(&student_buffer);
				break;
			case 8:
				printf("==========================\n");
				update_s(&student_buffer);
				break;
			case 9:
				printf("==========================\n");
				show_s(&student_buffer);
				break;
			case 10:
				printf("==========================\n");
				exit(1);
				break;
		}
	}
	return 0;

}
