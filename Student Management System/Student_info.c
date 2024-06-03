/*
 * Student.info.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Muhammad Atta
 */

#include "FIFO.h"

FIFO_Status_t FIFO_init(FIFO_Buff_t* fifo, Sinfo_t* buf, uint32_t length)
{
	if(buf == NULL){
		return FIFO_NULL;
	}
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;
	return FIFO_NO_ERROR;
}

FIFO_Status_t FIFO_IsFull(FIFO_Buff_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail){
			return FIFO_NULL;
		}
	if(fifo->count == fifo->length){
		return FIFO_FULL;
	}
	return FIFO_NO_ERROR;

}

FIFO_Status_t FIFO_IsEmpty(FIFO_Buff_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail){
		return FIFO_NULL;
	}
	if(fifo->count == 0){
		return FIFO_EMPTY;
	}
	return FIFO_NO_ERROR;
}

int check_roll(FIFO_Buff_t* fifo, int num)
{
	Sinfo_t* ptr = fifo->base;
	int flag = 0;

	for(int i = 0; i<fifo->count;i++){
		if(num == ptr->roll){
			flag++;
		}
		ptr++;
	}
	return flag;
}
void add_student_file(FIFO_Buff_t* fifo)
{
	FILE* fptr = fopen("Add Student.txt","r");
	char line[50];
	char* token;
	Sinfo_t student;

	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("Buffer not found!");
	}else if(FIFO_IsFull(fifo) == FIFO_FULL){
		printf("Buffer is full, you cannot add another student \n");
	}

	if(fptr == NULL){
		printf("Error opening the file...\n");
		return;
	}
	while(fgets(line, sizeof(line),fptr)){
		token =  strtok(line, ",");
		if(check_roll(fifo, atoi(token))){
			printf("This roll number is already taken..\n");
		}else{
			student.roll = atoi(token);
		}
		token = strtok(NULL,",");
		strcpy(student.Fname, token);
		token = strtok(NULL,",");
		strcpy(student.Fname, token);
		token = strtok(NULL,",");
		student.GPA = atof(token);
		for(int i = 0; i<5; i++){
			token = strtok(NULL,",");
			student.CID[i] = atoi(token);
		}
		*fifo->head = student;
		fifo->count++;
		if(fifo->head == ((fifo->base)+((fifo->length)*sizeof(Sinfo_t)))){
			fifo->head = fifo->base;
		}else{
			fifo->head++;
		}
	}
	fclose(fptr);
	printf("Student/s added successfully....\n");

}
void add_student_manual(FIFO_Buff_t* fifo)
{
	int RollNumber = 0;
	float gpa = 0;
	int ID = 0;
	if(!fifo->base || !fifo->head || !fifo->tail){
		DPRINTF("Buffer not found!");
	}else if(FIFO_IsFull(fifo) == FIFO_FULL){
		printf("Buffer is full, you cannot add another student \n");
	}else{
		DPRINTF("Select Roll Number: \n");
		//fflush(stdout);
		scanf("%d",&RollNumber);
		getchar();
		if(check_roll(fifo,RollNumber)){
			printf("This Roll Number has already taken \n");
			return;
		}
		fifo->head->roll = RollNumber;

		getchar();  //To enable fgets() after scanf()

		DPRINTF("\nEnter first name of student: ");
		fgets(fifo->head->Fname,50,stdin);
		strtok(fifo->head->Fname, "\n"); // Remove trailing newline
		DPRINTF("\nEnter last name of the student: ");
		fgets(fifo->head->Lname,50,stdin);
		strtok(fifo->head->Lname, "\n"); // Remove trailing newline
		DPRINTF("\nEnter student's GPA: ");
		//fflush(stdout);
		scanf("%f",&gpa);
		fifo->head->GPA = gpa;
		printf("\nEnter each course ID: ");
		for(int i = 1;i<=5;i++){
			DPRINTF("Course %d ID: ",i);
			//fflush(stdout);
			scanf("%d",&ID);
			fifo->head->CID[i] = ID;
		}
		fifo->count++;
		//For circular buffer
		if(fifo->head == (Sinfo_t*)((fifo->base)+(fifo->length * sizeof(Sinfo_t)))){
			fifo->head = fifo->base;
		}else{
			fifo->head++;
		}

	}

}
void find_roll(FIFO_Buff_t* fifo)
{
	int rollNumber = 0;
	DPRINTF("Enter the the roll number you want to check..: \n");
	scanf("%d", &rollNumber);
	Sinfo_t* ptr = fifo->base;
	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("FIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else if(!check_roll(fifo, rollNumber)){
		printf("This number does not exist...\n");
	}else{
		for(int i; i<fifo->count;i++){
			if(rollNumber == ptr->roll){
				printf("Student's first name: %s\n", ptr->Fname);
				printf("Student's last name: %s\n", ptr->Lname);
				printf("Student's roll number: %d\n", ptr->roll);
				printf("Student's GPA: %f\n", ptr->GPA);
				printf("ID of registered courses:\n");
				for(int j = 0; j<5; j++){
					printf("%d\t",ptr->CID[j]);
				}
				break;
			}
			ptr++;
		}
	}
}
void find_Fn(FIFO_Buff_t* fifo)
{
	char neededName[50];
	Sinfo_t* ptr = fifo->base;
	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("FIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else{
		if(strcmp(ptr->Fname, neededName) == 0){
			printf("Student's first name: %s\n", ptr->Fname);
			printf("Student's last name: %s\n", ptr->Lname);
			printf("Student's roll number: %d\n", ptr->roll);
		    printf("Student's GPA: %f\n", ptr->GPA);
			printf("ID of registered courses:\n");
			for(int j = 0; j<5; j++){
				printf("%d\t",ptr->CID[j]);
			}
		}else{
			printf("This name does not exist....\n");
		}
		ptr++;
	}
}
void find_c(FIFO_Buff_t* fifo)
{
	unsigned int neededID = 0;
	int count = 0;
	Sinfo_t* ptr = fifo->base;
	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("FIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else{
		for(int i = 1; i<=fifo->count; i++){
			for(int j = 0; j<5; j++){
				if(neededID == ptr->CID[j]){
					printf("Student[%d] details:",i);
					printf("Student's first name: %s\n", ptr->Fname);
					printf("Student's last name: %s\n", ptr->Lname);
					printf("Student's roll number: %d\n", ptr->roll);
				    printf("Student's GPA: %f\n", ptr->GPA);
				    count++;
				}
			}
			ptr++;
		}
		printf("The total number of students enrolled in this course is: %d\n", count);
	}
}
void total_s(FIFO_Buff_t* fifo)
{
	if(!fifo->base || !fifo->head || fifo->tail){
		printf("FIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else{
		printf("The total number of students: %d\n", fifo->count);
	}
}
void delete_s(FIFO_Buff_t* fifo)
{
	int rollNumber;
	int flag = 0;
	Sinfo_t* ptr = fifo->base;
	DPRINTF("Enter the roll number of the student that you want to delete: \n");
	scanf("%d",&rollNumber);
	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("FIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else if(!(check_roll(fifo, rollNumber))){
		printf("Entered roll number does not exist...\n");
	}else{
		for(int i = 0; i<fifo->count; i++){
			if(rollNumber == ptr->roll){
			*ptr = *(fifo->tail);
			 fifo->count--;
			 flag++;
			if(fifo->tail == (Sinfo_t*)((fifo->base)+(fifo->length * sizeof(Sinfo_t)))){
				fifo->tail = fifo->base;
			}else{
				fifo->tail++;
			}
				break;
		  }
			ptr++;
	}
		if(flag != 0){
			printf("Student removed successfully..\n");
		}
  }
}
void update_s(FIFO_Buff_t* fifo)
{
	int rollNumber = 0;
	Sinfo_t* ptr = fifo->base;
	char newFirstName[50];
	char newLastName[50];
	float newGPA = 0;
	int newRollNumber = 0;
	int newCoureses[10];

	printf("Enter the roll number of the student you want to update: \t");
	fflush(stdout);
	scanf("%d", &rollNumber);

	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("\nFIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else if(!(check_roll(fifo, rollNumber))){
		printf("Entered roll number does not exist...\n");
	}else{
		for(int i = 0; i<fifo->count; i++){
			if(rollNumber == ptr->roll){
				DPRINTF("Enter updated first name: \n");
				//fflush(stdout);
				fgets(newFirstName, 50, stdin);
				DPRINTF("\nEnter updated last name: \n");
				//fflush(stdout);
				fgets(newLastName, 50, stdin);
				DPRINTF("\nEnter updated roll number: \n");
				//fflush(stdout);
				scanf("%d",&newRollNumber);
				DPRINTF("\nEnter updated GPA: \n");
				//fflush(stdout);
				scanf("%f",&newGPA);
				DPRINTF("\nEnter new registered courses(ID): \n");
				//fflush(stdout);
				for(int count = 0; count<5; count++){
					DPRINTF("Course[%d]", count);
					scanf("%d", &newCoureses[count]);
				}
				for(int j = 0; j<5; j++){
					ptr->CID[j] = newCoureses[j];
				}

			}
			ptr++;
		}
	}
}

void show_s(FIFO_Buff_t* fifo)
{
    Sinfo_t* ptr = fifo->base;
	if(!fifo->base || !fifo->head || !fifo->tail){
		printf("FIFO not found..\n");
	}else if(fifo->count == 0){
		printf("FIFO is empty...\n");
	}else{
		for(int i = 0; i<fifo->count; i++){
			printf("Student's first name: %s\n", ptr->Fname);
			printf("Student's last name: %s\n", ptr->Lname);
			printf("Student's roll number: %d\n", ptr->roll);
			printf("Student's GPA: %f\n", ptr->GPA);
			printf("ID of registered courses:\n");
			for(int j = 0; j<5; j++){
			   printf("%d\t",ptr->CID[j]);
		}
			ptr++;
	}
 }
}
