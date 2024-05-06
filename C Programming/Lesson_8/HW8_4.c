#include<stdio.h>

int main()
{
    int arr[15];
    int size = 0;
    int* ptr;

    printf("Enter number of elements(max. 15)\n");
    scanf("%d", &size);

    for(int i = 0; i<size; i++){
        printf("Enter element[%d]: ",i+1);
        fflush(stdout);
        scanf("\n%d",&arr[i]);
    }
    ptr = &arr[size-1];
    printf("\nElements of array in reverse: \n");
    for(int j = size-1; j>=0; j--){
        printf("Element[%d]: %d\n",j+1,*ptr);
        ptr--;
    }
}
