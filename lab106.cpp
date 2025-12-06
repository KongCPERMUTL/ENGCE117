#include <stdio.h>

int *GetMatrix (int *row, int *col);

int main () {
    int *data, m, n;

    // get dimensions
    data = GetMatrix(&m, &n);

    // print the matrix
    for(int rowIndex = 0 ; rowIndex < m ; rowIndex++) {
        for(int colIndex = 0 ; colIndex < n ; colIndex++) {
            printf("%d  ",data[rowIndex * n + colIndex]);
        }
        printf("\n");
    }

    // free memory
    delete[] data;
    return 0;
}

int *GetMatrix (int *row, int *col) {
    int *matrix;

    // read number of rows and columns
    scanf("%d %d", row, col);

    // allocate dynamic array for matrix
    matrix = new int[*row * *col];

    // read each element of the matrix
    for(int rowIndex = 0 ; rowIndex < *row ; rowIndex++) {
        for(int colIndex = 0 ; colIndex < *col ; colIndex++) {
            scanf("%d",&(matrix[rowIndex * *col + colIndex]));
        }
    }

    // return pointer to the matrix
    return matrix;
}
