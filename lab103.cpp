#include <stdio.h>

int *GetSet(int *num);

int main () {
    int *data;
    int num;

    data = GetSet(&num);

    // Print elements
    for(int i = 0; i < num; i++) {
        printf("[%d]: %d\n", i, data[i]);
    }

    // Free memory
    delete[] data;
    return 0;
}

int *GetSet(int *num) {
    // Read number of elements
    scanf("%d", num);

    // Allocate array dynamically
    int *data = new int[*num];

    // Read each element
    for(int i = 0; i < *num; i++) {
        scanf("%d", &data[i]);
    }

    return data;
}
