#include <stdio.h>

void explode(char str1[], char splitter, char str2[][10], int *count)
{
    int i = 0 ;
    int c = 0 ;
    int r = 0 ;

    while (str1[i] != '\0')
    {
        if (str1[i] == splitter) {
            str2[r][c] = '\0' ;
            r++;
            c = 0 ;
        } else {
            str2[r][c] = str1[i] ;
            c++;
        }
        i++;
    }

    str2[r][c] = '\0' ;
    *count = r + 1 ;
}

int main()
{
    char out[20][10] ;
    int num;

    explode("I/Love/You", '/', out, &num) ;

    // ตัวอย่างแสดงผลให้ดู 
    for (int i = 0; i < num; i++) {
        printf("%s\n", out[i]) ;
    }

    return 0 ;
}
