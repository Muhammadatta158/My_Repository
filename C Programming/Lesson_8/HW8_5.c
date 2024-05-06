#include<stdio.h>
#include<string.h>

struct SEmployee{
    char name[20];
    int ID;
}employee_information = {"Muhammad",10};

int main()
{
    struct SEmployee arr[10];
    struct SEmployee* ptr = arr;

    ptr->ID = employee_information.ID;
    strcpy(ptr->name, employee_information.name);

    printf("Employee Name: %s\n", ptr->name);
    printf("Employee ID: %d\n",ptr->ID);

    return 0;
}
