#include<stdio.h>
void main()
{
    int a,b,c;
    printf("Plaese enter number[1]: \n");
    scanf("%d",&a);
    printf("Please enter number [2]: \n");
    fflush(stdout);
    scanf("%d",&b);
    printf("Please enter number [3]: \n");
    fflush(stdout);
    scanf("%d",&c);
    if (a>b)
    {
        if (a>c)
        printf("%d s the largest number",a);
        else
        printf("%d is the largest number",c);
    }
    else if (a>c)
    {
        printf("%d is the largest number",b);
    }
    else if (b>c)
    {
        printf("%d is the largest number",b);
    }
        else
        printf("%d is the largest number",c);
}
