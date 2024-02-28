#include<stdio.h>
void main()
{
    int arr[10];
    int i,n,x;
    int pos;
    printf("Please enter the size of the array: ");
    fflush(stdout); fflush(stdin);
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("Enter the value[%d]: ",i);
        fflush(stdout); fflush(stdin);
        scanf("%d",&arr[i]);
    }
    printf("Please enter the number you want to search for: ");
    fflush(stdout); fflush(stdin);
    scanf("%d",&x);
    for(i=1;i<=n;i++)
    {
        if(arr[i]==x)
        {
           pos=i;
           printf("The position of this element is %d",pos);
           break;
        }

    }
}
