#include <stdio.h>

int GetSet(int data[]);

int main() {
    int *data;
    int num;

    num = GetSet((int*)&data); // fill data

    for (int i = 0; i < num; i++) {
        printf("[%d]: %d\n", i, data[i]);
    }

    delete[] data; // free memory

    return 0;
}

int GetSet(int data[]) {
    int **p = (int**)data; 
    int num;

    scanf("%d", &num);      // read size
    *p = new int[num];       // allocate array

    for (int i = 0; i < num; i++) {
        scanf("%d", &((*p)[i])); // read elements
    }

    return num;
}
