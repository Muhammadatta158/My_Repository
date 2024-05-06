#include<stdio.h>
void main()
{
   char c[26];
   char *p;
   int i;
   p=&c;
   for(i='A';i<='Z';i++)
   {
       *p=i;
        p++;
   }
   p=&c;
   for(i=0;i<=25;i++)
   {
       printf("%c\t",*p);
        p++;
   }
}
