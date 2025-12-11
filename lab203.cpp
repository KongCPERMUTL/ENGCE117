#include <stdio.h>
#include <string.h>

void explode(char str1[], char splitter, char str2[][10], int *count);

int main() {
    char str_in[] = "/I/Love/You";
    char split_char = '/';
    char out[20][10];
    int num;
    int i;
    
    explode(str_in, split_char, out, &num);
    
    for (i = 0; i < num; i++) {
        printf("str2[%d] = \"%s\"\n", i, out[i]);
    }
    
    printf("count = %d\n", num);
    
    return 0;
}

void explode(char str1[], char splitter, char str2[][10], int *count) {
    int str1_len = strlen(str1);
    int current_part = 0;
    int current_char = 0;
    int i;

    *count = 0; 
    
    for (i = 0; i < str1_len; i++) {
        if (str1[i] == splitter) {
            str2[current_part][current_char] = '\0';
            current_part++;
            current_char = 0;
            (*count)++;
            
        } else {
            str2[current_part][current_char] = str1[i];
            current_char++;
        }
    }
    
    str2[current_part][current_char] = '\0';
    (*count)++;
}