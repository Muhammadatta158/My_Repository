#include<stdio.h>
void main()
{
    int arr[10]={1,2,3,4,5};
    int x;
    int n,i;
    int loc;
    printf("Please enter the number you need to insert: ");
    fflush(stdout); fflush(stdin);
    scanf("%d",&x);
    printf("Please enter the location you need to insert the number in: ");
    fflush(stdout); fflush(stdin);
    scanf("%d",&loc);
    for(i=5;i>=loc;i--)
    {
        arr[i+1]=arr[i];
    }
    arr[loc]=x;
    n=6;
    for(i=0;i<n;i++)
    {
        printf("%d\t",arr[i]);
    }

}
