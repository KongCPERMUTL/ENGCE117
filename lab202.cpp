#include <stdio.h>
#include <stdlib.h>

char* reverse(char str1[])
{
    int len = 0, i ;

    while (str1[len] != '\0') {
        len++ ;
    }

    char *str2 = (char*)malloc(len + 1) ; 

    for (i = 0; i < len; i++) {
        str2[i] = str1[len - 1 - i] ;
    }

    str2[len] = '\0' ;

    return str2 ;
}

int main()
{
    char text[50] ;
    char *out ;

    fgets(text, 50, stdin) ;

    int i = 0;
    while (text[i] != '\0') {
        if (text[i] == '\n') {
            text[i] = '\0' ;
            break;
        }
        i++ ;
    }

    out = reverse(text) ;
    printf("%s\n", out) ;
    free(out) ;
    return 0 ;
}
