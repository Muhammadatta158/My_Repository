#include <stdio.h>
int factorial(int n);

void main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);

    // Checking if the number is negative
    if (num < 0) {
        printf("Factorial of a negative number is not defined.\n");
    } else {
        printf("Factorial of %d is %d\n", num, factorial(num));
    }
}

int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

