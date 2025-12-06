#include <stdio.h>

void GetSet(int data[], int *num) ;

int main() {
    int data[100] ;
    int num ;

    // Fill array and get the number of elements
    GetSet(data, &num) ;

    // Print all elements
    for (int i = 0; i < num; i++) {
        printf("[%d]: %d\n", i , data[i]) ;
    }
    
    return 0 ;
}

void GetSet(int data[], int *num) { // Read number of elements
    scanf("%d", num) ;

    // Read each element
    for (int i = 0 ; i < *num ; i++) {
        scanf("%d", &data[i]) ;
    }
}
