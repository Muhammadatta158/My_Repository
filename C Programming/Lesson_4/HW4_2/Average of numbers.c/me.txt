#include<stdio.h>
void main()
{
    float arr[10];
    float avg;
    float sum=0;
    int i;
    for(i=1;i<=10;i++)
    {
        printf("Enter Value[%d]: ",i);
        fflush(stdout); fflush(stdin);
        scanf("%f",&arr[i]);
    }
    for(i=1;i<=10;i++)
    {
        sum=sum+arr[i];
    }
    avg=sum/10;
    printf("Average=%f",avg);
}
