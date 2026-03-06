#include <stdio.h>
#include <stdlib.h>

#define START_INDEX 0
#define DEFAULT_VALUE 0

int KnapsackBT(int *weightArray, int *valueArray, int totalElements, int currentCapacity, int startIndex, int *resultItems);

int main() {
    int totalItems;
    int maxCapacity;
    
    totalItems = 5;
    maxCapacity = 11;
    
    int weightData[5] = { 1, 2, 5, 6, 7 };
    int valueData[5] = { 1, 6, 18, 22, 28 };
    
    int *finalItems;
    int finalValue;
    
    finalItems = new int[totalItems];
    
    finalValue = KnapsackBT(weightData, valueData, totalItems, maxCapacity, START_INDEX, finalItems);
    
    printf("Value = %d\n", finalValue);
    
    int loopIndex;
    loopIndex = START_INDEX;
    
    while (loopIndex < totalItems) {
        printf("%d ", finalItems[loopIndex]);
        loopIndex = loopIndex + 1;
    }
    
    return 0;
}

int KnapsackBT(int *weightArray, int *valueArray, int totalElements, int currentCapacity, int startIndex, int *resultItems) {
    int bestValue;
    int currentItemIndex;
    int *temporaryItems;
    
    bestValue = DEFAULT_VALUE;
    
    int clearIndex;
    clearIndex = START_INDEX;
    
    while (clearIndex < totalElements) {
        resultItems[clearIndex] = DEFAULT_VALUE;
        clearIndex = clearIndex + 1;
    }
    
    temporaryItems = new int[totalElements];
    
    if (temporaryItems == NULL) {
        return DEFAULT_VALUE;
    }
    
    currentItemIndex = startIndex;
    
    while (currentItemIndex < totalElements) {
        if (weightArray[currentItemIndex] <= currentCapacity) {
            int branchValue;
            int remainingCapacity;
            int nextIndex;
            
            remainingCapacity = currentCapacity - weightArray[currentItemIndex];
            nextIndex = currentItemIndex + 1;
            
            branchValue = valueArray[currentItemIndex] + KnapsackBT(weightArray, valueArray, totalElements, remainingCapacity, nextIndex, temporaryItems);
            
            if (branchValue > bestValue) {
                bestValue = branchValue;
                
                int copyIndex;
                copyIndex = START_INDEX;
                
                while (copyIndex < totalElements) {
                    resultItems[copyIndex] = temporaryItems[copyIndex];
                    copyIndex = copyIndex + 1;
                }
                
                resultItems[currentItemIndex] = 1;
            }
        }
        currentItemIndex = currentItemIndex + 1;
    }
    
    delete[] temporaryItems;
    
    return bestValue;
}