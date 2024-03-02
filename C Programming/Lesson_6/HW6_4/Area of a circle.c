#include <stdio.h>

#define PI 3.14159
#define area(radius) (PI * (radius) * (radius))

int main() {
    float radius,area;

    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    area = area(radius);

    printf("The area of the circle with radius %0.2f is %0.2f\n", radius, area);

    return 0;
}
