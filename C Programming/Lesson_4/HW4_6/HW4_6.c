#include<stdio.h>
#include<string.h>

void main()
{
    char str[100];
    int i,count=0;
    char c;

    printf("Enter string: ");
    gets(str);

    printf("Enter character you need to know the frequency of: ");
    scanf("%c",&c);

    for(i=0;str[i]!='\0';i++){
      if(c==str[i]){
        count++;
      }
    }
    printf("The frequency of %c is %d",c,count);

}
