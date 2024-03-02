#include<stdio.h>
void main()
{
    float X[2][2];
    float Y[2][2];
    float Sum[2][2];
    int i,j;
    for(i=1;i<=2;i++)
    {
       for(j=1;j<=2;j++)
        {
            printf("Please enter the element[%d][%d] of the first matrix: ",i,j);
            fflush(stdout); fflush(stdin);
            scanf("%f",&X[i][j]);
        }
    }
    printf("The matrix X= \n");
    for(i=1;i<=2;i++)
    {
       for(j=1;j<=2;j++)
        {
            printf("%0.2f\t",X[i][j]);
        }
        printf("\n");
    }
      for(i=1;i<=2;i++)
    {
       for(j=1;j<=2;j++)
        {
            printf("Please enter the element[%d][%d] of the second matrix: ",i,j);
            fflush(stdout); fflush(stdin);
            scanf("%f",&Y[i][j]);
        }
    }
    printf("The matrix Y= \n");
    for(i=1;i<=2;i++)
    {
       for(j=1;j<=2;j++)
        {
            printf("%0.2f\t ",Y[i][j]);
        }
        printf("\n");
    }
    printf("The sum of the matrices is= \n");
    for(i=1;i<=2;i++)
    {
       for(j=1;j<=2;j++)
        {
            printf("%0.2f\t ",((X[i][j])+(Y[i][j])));
        }
        printf("\n");
    }

}
