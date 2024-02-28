#include<stdio.h>
void main()
{
    float Matrix[3][3];
    float Transpose [3][3];
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
           printf("Please enter element[%d][%d]: ",i,j);
           fflush(stdout); fflush(stdin);
           scanf("%f",&Matrix[i][j]);
        }

    }
    printf("The Matrix is \n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
             printf("%f\t",Matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n The Transpose is \n");
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
             Transpose[i][j]=Matrix[j][i];
        }

    }
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
             printf("%f\t",Transpose[i][j]);
        }
        printf("\n");
    }


}
