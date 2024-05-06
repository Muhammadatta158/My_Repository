#include<stdio.h>
#include<string.h>
void main()
{
    char s[100];
    char temp[100];
    int i,n;
    char* p;
    printf("Enter the string: ");
    gets(s);
    n=strlen(s);
    p=&temp;
    for(i=n-1;i>=0;i--)
    {
        *p=s[i];
        p++;
    }
    *p='\0';
    printf("%s\n",temp);
}
