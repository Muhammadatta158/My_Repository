#include<stdio.h>
int Prime(int x, int y)
{
    int i,j,p=0;
    for(i=x;i<=y;++i)
    {
        for(j=2;j<=(i/2);++j)
           {
               if(i%j==0)
               {
                 p=1;
                 break;
               }
               else if(i%j!=0)
               {
                   p=0;
               }

           }
            if(p!=1)
               {
                     printf("%d\t",i);
               }
    }
return i;
}
void main()
{
    Prime(1,20);
}
