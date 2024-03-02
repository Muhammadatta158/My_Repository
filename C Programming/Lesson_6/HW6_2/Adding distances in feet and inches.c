#include<stdio.h>
struct SDistance
{
    float feet;
    float inch;
};
void main()
{
    struct SDistance d1,d2,sum;
    printf("Enter information of 1st distance: \n");
    printf("Enter Feet: ");
    scanf("%f",&d1.feet);
    printf("Enter Inch: ");
    scanf("%f",&d1.inch);
    printf("\nEnter information of 2nd distance: \n");
    printf("Enter Feet: ");
    scanf("%f",&d2.feet);
    printf("Enter Inch: ");
    scanf("%f",&d2.inch);
    sum.feet=d1.feet+d2.feet;
    sum.inch=d1.inch+d2.inch;
    if(sum.inch>12)
    {
        sum.inch=sum.inch-12;
        sum.feet++;
    }
    printf("\nSum of distances= %0.1f\'-%0.1f\"",sum.feet,sum.inch);
}
