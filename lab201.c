#include <stdio.h>

void reverse(char str1[], char str2[])
{
    int i, len = 0 ;

    // หาความยาว string
    while (str1[len] != '\0') {
        len++ ;
    }

    // คัดลอกจากท้ายไปหน้า
    for (i = 0; i < len; i++) {
        str2[i] = str1[len - 1 - i] ;
    }

    // ปิดท้ายด้วย null
    str2[len] = '\0' ;
}

int main()
{
    char text[50] ;
    char out[50] ;

    fgets(text, 50, stdin) ;

    // ตัด newline ออก (ถ้ามี)
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
