#include<stdio.h>
void main()
{
   int sum,x1,x2;
   char o;
   printf("Please enter the operator(+, -, *, /):  "); //Entering operators before numbers//
   fflush(stdout);
   scanf("%c",&o);
   printf("Please enter the two numbers: ");
   scanf("%d %d",&x1,&x2);
   switch(o){
         case'+':
         sum=x1+x2;
         printf("The sum of numbers you entered = %d",sum);
         break;
         case'-':
         sum=x1-x2;
         printf("The sum of numbers you entered = %d",sum);
         break;
         case'*':
         sum=x1*x2;
         printf("The sum of numbers you entered = %d",sum);
         break;
         case'/':
         sum=x1/x2;
         printf("The sum of numbers you entered = %d",sum);
         break;

   }
}
