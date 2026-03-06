#include <stdio.h>

#define NOT_FOUND -1

int BinSearch(int dataArray[], int totalElements, int targetValue);

int main() {
    int dataArray[6] = {1, 2, 3, 4, 5, 7};
    int arraySize;
    int targetValue;
    int foundPosition;

    arraySize = 6;
    targetValue = 5;

    foundPosition = BinSearch(dataArray, arraySize, targetValue);

    if (foundPosition != NOT_FOUND) {
        printf("Found %d at %d\n", targetValue, foundPosition);
    }

    return 0;
}

int BinSearch(int dataArray[], int totalElements, int targetValue) {
    int leftIndex;
    int rightIndex;
    int middleIndex;

    leftIndex = 0;
    rightIndex = totalElements - 1;

    while (leftIndex <= rightIndex) {
        middleIndex = (leftIndex + rightIndex) / 2;

        if (dataArray[middleIndex] == targetValue) {
            return middleIndex;
        }

        if (dataArray[middleIndex] < targetValue) {
            leftIndex = middleIndex + 1;
        } else {
            rightIndex = middleIndex - 1;
        }
    }

    return NOT_FOUND;
}