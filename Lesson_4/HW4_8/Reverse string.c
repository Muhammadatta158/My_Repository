void main()
{

char str[100];

int size;

printf("Please insert the string you want to reverse: ");

gets(str);

size = strlen(str);

for(int i = size - 1; i >= 0; i--) {

     printf("%c", str[i]);

}

}
