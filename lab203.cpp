#include <stdio.h>

void explode(char str1[], char splitter, char str2[][10], int *count)
{
    int i = 0, col = 0, row = 0 ;

    while (str1[i] != '\0')
    {
        if (str1[i] == splitter) {
            str2[row][col] = '\0' ;
            row++;
            col = 0 ;
        } else {
            str2[row][col] = str1[i] ;
            col++ ;
        }
        i++ ;
    }

    str2[row][col] = '\0' ;
    *count = row + 1 ;
}

int main()
{
    char out[20][10] ;
    int num ;

    explode("I/Love/You", '/', out, &num) ;

    // ทดสอบแสดงผล (ใส่ไว้ให้ดู)
    for (int i = 0; i < num; i++) {
        printf("%s\n", out[i]) ;
    }

    return 0 ;
}
