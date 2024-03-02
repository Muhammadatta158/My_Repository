#include<stdio.h>
void main()
{
    int x,n;
    printf("Enter base: ");
    fflush(stdout); fflush(stdin);
    scanf("%d",&x);
    printf("Enter power: ");
    fflush(stdout); fflush(stdin);
    scanf("%d",&n);
    printf("%d^%d=%d",x,n,power(x,n));
}
int power(int a, int b)
{
    if(b!=0)
    {
        return (a*power(a,b-1));
    }
    else
    {
        return(1);
    }
}
