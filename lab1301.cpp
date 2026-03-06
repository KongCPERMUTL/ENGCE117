#include <stdio.h>
#include <stdlib.h>

#define START_INDEX 0
#define OFFSET_ONE 1

int *KnapsackDP(int *weightArray, int *valueArray, int totalItems, int maxCapacity);

int main() {
    int totalElements;
    int weightLimit;
    
    totalElements = 5;
    weightLimit = 11;
    
    int weightData[5] = { 1, 2, 5, 6, 7 };
    int valueData[5] = { 1, 6, 18, 22, 28 };
    int *resultItems;
    
    resultItems = KnapsackDP(weightData, valueData, totalElements, weightLimit);
    
    int loopIndex;
    loopIndex = START_INDEX;
    
    while (loopIndex < totalElements) {
        printf("%d ", resultItems[loopIndex]);
        loopIndex = loopIndex + OFFSET_ONE;
    }
    
    return 0;
}

int *KnapsackDP(int *weightArray, int *valueArray, int totalItems, int maxCapacity) {
    int *selectedItems;
    selectedItems = new int[totalItems];
    
    if (selectedItems == NULL) {
        return NULL;
    }

    int tableRows;
    int tableCols;
    
    tableRows = totalItems + OFFSET_ONE;
    tableCols = maxCapacity + OFFSET_ONE;

    int *dpTable;
    dpTable = new int[tableRows * tableCols];
    
    if (dpTable == NULL) {
        return NULL;
    }

    int rowIndex;
    int colIndex;
    
    rowIndex = START_INDEX;

    while (rowIndex < tableRows) {
        colIndex = START_INDEX;
        while (colIndex < tableCols) {
            if (rowIndex == START_INDEX) {
                dpTable[rowIndex * tableCols + colIndex] = START_INDEX;
            } else if (colIndex == START_INDEX) {
                dpTable[rowIndex * tableCols + colIndex] = START_INDEX;
            }
            colIndex = colIndex + OFFSET_ONE;
        }
        rowIndex = rowIndex + OFFSET_ONE;
    }

    rowIndex = OFFSET_ONE;
    
    while (rowIndex <= totalItems) {
        colIndex = OFFSET_ONE;
        while (colIndex <= maxCapacity) {
            int currentItemWeight;
            int currentItemValue;
            
            currentItemWeight = weightArray[rowIndex - OFFSET_ONE];
            currentItemValue = valueArray[rowIndex - OFFSET_ONE];

            if (currentItemWeight <= colIndex) {
                int valueWithItem;
                int valueWithoutItem;
                
                valueWithoutItem = dpTable[(rowIndex - OFFSET_ONE) * tableCols + colIndex];
                valueWithItem = currentItemValue + dpTable[(rowIndex - OFFSET_ONE) * tableCols + (colIndex - currentItemWeight)];

                if (valueWithItem > valueWithoutItem) {
                    dpTable[rowIndex * tableCols + colIndex] = valueWithItem;
                } else {
                    dpTable[rowIndex * tableCols + colIndex] = valueWithoutItem;
                }
            } else {
                dpTable[rowIndex * tableCols + colIndex] = dpTable[(rowIndex - OFFSET_ONE) * tableCols + colIndex];
            }
            
            colIndex = colIndex + OFFSET_ONE;
        }
        rowIndex = rowIndex + OFFSET_ONE;
    }

    int remainingCapacity;
    int itemCursor;
    
    remainingCapacity = maxCapacity;
    itemCursor = totalItems;

    int initIndex;
    initIndex = START_INDEX;
    
    while (initIndex < totalItems) {
        selectedItems[initIndex] = START_INDEX;
        initIndex = initIndex + OFFSET_ONE;
    }

    while (itemCursor > START_INDEX) {
        int currentDpValue;
        int previousDpValue;
        
        currentDpValue = dpTable[itemCursor * tableCols + remainingCapacity];
        previousDpValue = dpTable[(itemCursor - OFFSET_ONE) * tableCols + remainingCapacity];

        if (currentDpValue != previousDpValue) {
            selectedItems[itemCursor - OFFSET_ONE] = OFFSET_ONE;
            remainingCapacity = remainingCapacity - weightArray[itemCursor - OFFSET_ONE];
        }
        
        itemCursor = itemCursor - OFFSET_ONE;
    }

    delete[] dpTable;

    return selectedItems;
}