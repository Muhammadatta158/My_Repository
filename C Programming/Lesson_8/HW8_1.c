#include<stdio.h>

int main()
{
    int m = 29;
    int* ab;

    printf("Address of m is: %d", &m);
    printf("\nValue of m: %d", m);

    ab = &m;
    printf("\nNow ab is assigned to the address of m");
    printf("\nAddress of pointer ab is: %d", ab);
    printf("\nContent of pointer ab: %d", *ab);

    m = 34;
    printf("\nAddress of pointer ab is: %d", ab);
    printf("\nContent of pointer ab: %d", *ab);

    *ab = 7;
    printf("\nAddress of m is: %d", &m);
    printf("\nValue of m: %d",m);

    return 0;
}
