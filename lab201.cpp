#include <stdio.h>

void reverse(char str1[], char str2[])
{
    int i, j;
    for(i = 0; str1[i] != '\0'; i++);

    j = 0;
    i--;
    while(i >= 0){
        str2[j] = str1[i];
        j++;
        i--;
    }
    str2[j] = '\0';
}

int main()
{
    char text[50];
    char out[50];

    gets(text);  

    reverse(text, out);

    printf("%s\n", out);

    return 0;
}
