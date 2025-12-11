#include <stdio.h>

void reverse(char str1[], char str2[])
{
    int i, len = 0 ;

    while (str1[len] != '\0') {
        len++ ;
    }

    for (i = 0; i < len; i++) {
        str2[i] = str1[len - 1 - i] ;
    }

    str2[len] = '\0' ;
}

int main()
{
    char text[50] ;
    char out[50] ;

    fgets(text, 50, stdin) ;

    int i = 0;
    while (text[i] != '\0') {
        if (text[i] == '\n') {
            text[i] = '\0' ;
            break;
        }
        i++ ;
    }

    reverse(text, out) ;

    printf("%s\n", out) ;

    return 0 ;
}
