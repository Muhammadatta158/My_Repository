#include<stdio.h>
struct SStudent
{
    char name[100];
    int R;
    int M;
};
void main()
{
   struct SStudent S;
   printf("Enter student name: ");
   gets(S.name);
   printf("Enter roll number: ");
   scanf("%d",&S.R);
   printf("Enter mark: ");
   scanf("%d",&S.M);
   printf("Student name is: %s\n Roll number is: %d\n Mark is: %d\n",S.name,S.R,S.M);


}
