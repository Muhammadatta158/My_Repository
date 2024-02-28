#include<stdio.h>
void main()
{
    int sum=0;
    int num;
    int i;
    printf("Please enter number: ");
    scanf("%d",&num);
      for(i=0;i<=num;i++)
        {
            sum=sum+i;
        }
        printf("%d",sum);
}
