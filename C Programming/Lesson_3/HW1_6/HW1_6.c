#include<stdio.h>

void main(){
    float a,b,temp;

    printf("Enter value of a: ");
    fflush(stdout);
    scanf("%f",&a);

    printf("\nEnter value of b: ");
    fflush(stdout);
    scanf("%f",&b);

    temp = a;
    a = b;
    b = temp;

    printf("\nAfter swapping, Value of a = %f",a);
    printf("\nAfter swapping, Value of b = %f",b);

}
