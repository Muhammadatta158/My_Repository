#include<stdio.h>

void main(){
    float a,b;

    printf("Enter value of a: ");
    fflush(stdout);
    scanf("%f",&a);

    printf("\nEnter value of b: ");
    fflush(stdout);
    scanf("%f",&b);

    a = a + b;
    b = a - b;
    a = a - b;

    printf("\nAfter swapping, Value of a = %f",a);
    printf("\nAfter swapping, Value of b = %f",b);

}
