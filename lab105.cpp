#include <stdio.h>

void GetMatrix (int value[], int *row, int *col);

int main() {
    int *data;
    int m, n;

    // read matrix size and values
    GetMatrix((int*)&data, &m, &n);

    // print matrix
    for (int rowIndex = 0; rowIndex < m; rowIndex++) {
        for (int colIndex = 0; colIndex < n; colIndex++) {
            printf("%d ", data[rowIndex * n + colIndex]);
        }
        printf("\n");
    }

    delete[] data;
    return 0;
}

void GetMatrix (int value[], int *row, int *col) {
    int **ptr = (int**)value; 

    scanf("%d %d", row, col);     // read number of rows and columns

    *ptr = new int[*row * *col];  // allocate array

    // read each element
    for (int rowIndex = 0; rowIndex < *row; rowIndex++) {
        for (int colIndex = 0; colIndex < *col; colIndex++) {
            scanf("%d", &((*ptr)[rowIndex * *col + colIndex]));
        }
    }
}
