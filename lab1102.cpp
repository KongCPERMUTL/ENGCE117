#include <stdio.h>
#include <stdlib.h>

void mergesort(int targetArray[], int totalSize);
void merge(int *leftArray, int leftSize, int *rightArray, int rightSize, int *targetArray);

int main() {
    int dataArray[7] = {4, 6, 1, 2, 5, 1, 8};
    int arraySize;
    int loopIndex;

    arraySize = 7;

    mergesort(dataArray, arraySize);

    loopIndex = 0;
    while (loopIndex < arraySize) {
        printf("%d ", dataArray[loopIndex]);
        loopIndex = loopIndex + 1;
    }

    return 0;
}

void mergesort(int targetArray[], int totalSize) {
    if (totalSize <= 1) {
        return;
    }

    int leftSize;
    int rightSize;
    
    leftSize = totalSize / 2;
    rightSize = totalSize - leftSize;

    int *leftBuffer;
    int *rightBuffer;

    leftBuffer = (int *)malloc(leftSize * sizeof(int));
    rightBuffer = (int *)malloc(rightSize * sizeof(int));

    if (leftBuffer == NULL) {
        return;
    }
    if (rightBuffer == NULL) {
        return;
    }

    int copyIndex;
    
    copyIndex = 0;
    while (copyIndex < leftSize) {
        leftBuffer[copyIndex] = targetArray[copyIndex];
        copyIndex = copyIndex + 1;
    }

    copyIndex = 0;
    while (copyIndex < rightSize) {
        rightBuffer[copyIndex] = targetArray[leftSize + copyIndex];
        copyIndex = copyIndex + 1;
    }

    mergesort(leftBuffer, leftSize);
    mergesort(rightBuffer, rightSize);

    merge(leftBuffer, leftSize, rightBuffer, rightSize, targetArray);

    free(leftBuffer);
    free(rightBuffer);
}

void merge(int *leftArray, int leftSize, int *rightArray, int rightSize, int *targetArray) {
    int leftCursor;
    int rightCursor;
    int targetCursor;
    int totalMergedSize;

    leftCursor = 0;
    rightCursor = 0;
    targetCursor = 0;
    totalMergedSize = leftSize + rightSize;

    while (targetCursor < totalMergedSize) {
        if (leftCursor >= leftSize) {
            targetArray[targetCursor] = rightArray[rightCursor];
            rightCursor = rightCursor + 1;
        } else if (rightCursor >= rightSize) {
            targetArray[targetCursor] = leftArray[leftCursor];
            leftCursor = leftCursor + 1;
        } else if (leftArray[leftCursor] < rightArray[rightCursor]) {
            targetArray[targetCursor] = leftArray[leftCursor];
            leftCursor = leftCursor + 1;
        } else {
            targetArray[targetCursor] = rightArray[rightCursor];
            rightCursor = rightCursor + 1;
        }
        targetCursor = targetCursor + 1;
    }
}