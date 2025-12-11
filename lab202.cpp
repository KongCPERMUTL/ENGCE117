#include <stdio.h>
#include <string.h>

char* reverse(char str1[]);

int main() {
    char text[50] = "I Love You";
    char *out;
    
    out = reverse(text);
    
    printf("\"%s\"\n", out);
    
    return 0;
}

char* reverse(char str1[]) {
    int length = strlen(str1);
    int i, j;
    char temp;
    
    for (i = 0, j = length - 1; i < j; i++, j--) {
        temp = str1[i];
        str1[i] = str1[j];
        str1[j] = temp;
    }
    
    return str1;
}