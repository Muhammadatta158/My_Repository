#include<stdio.h>
void main()
{
    int x,i,f=1;
    printf("please enter integer number: ");
    scanf("%d",&x);
    for(i=1;i<=x;i++)
    {
        f=f*i;
    }
    printf("Factorial = %d",f);
}
