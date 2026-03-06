#include <stdio.h>
#include <stdlib.h>

int *KnapsackGreedy(int *weightArray, int *valueArray, int totalItems, int maxCapacity);

int main() {
    int n = 5;
    int wx = 11;
    int w[5] = { 1, 2, 5, 6, 7 };
    int v[5] = { 1, 6, 18, 22, 28 };
    
    int *x = KnapsackGreedy(w, v, n, wx);
    
    for (int i = 0; i < n; i++) {
        printf("%d ", x[i]);
    }
    
    return 0;
}

int *KnapsackGreedy(int *weightArray, int *valueArray, int totalItems, int maxCapacity) {
    int *selectedItems;
    float *ratioArray;

    selectedItems = new int[totalItems];
    ratioArray = new float[totalItems];

    if (selectedItems == NULL) {
        return NULL;
    }
    if (ratioArray == NULL) {
        return NULL;
    }

    int loopIndex;
    loopIndex = 0;

    while (loopIndex < totalItems) {
        selectedItems[loopIndex] = 0;
        ratioArray[loopIndex] = (float)valueArray[loopIndex] / (float)weightArray[loopIndex];
        loopIndex = loopIndex + 1;
    }

    int currentCapacity;
    currentCapacity = maxCapacity;

    int stepCount;
    stepCount = 0;

    while (stepCount < totalItems) {
        float highestRatio;
        int bestItemIndex;
        int searchIndex;

        highestRatio = -1.0f;
        bestItemIndex = -1;
        searchIndex = 0;

        while (searchIndex < totalItems) {
            if (ratioArray[searchIndex] > highestRatio) {
                highestRatio = ratioArray[searchIndex];
                bestItemIndex = searchIndex;
            }
            searchIndex = searchIndex + 1;
        }

        if (bestItemIndex == -1) {
            break;
        }

        ratioArray[bestItemIndex] = -1.0f;

        if (weightArray[bestItemIndex] <= currentCapacity) {
            selectedItems[bestItemIndex] = 1;
            currentCapacity = currentCapacity - weightArray[bestItemIndex];
        }

        stepCount = stepCount + 1;
    }

    delete[] ratioArray;

    return selectedItems;
}