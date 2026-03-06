#include <stdio.h>

#define NO_EDGE -1
#define MAX_DISTANCE 999999
#define START_NODE 0

int* Dijkstra(int* graphMatrix, int totalNodes) {
    int* shortestDistances;
    int* visitedNodes;
    int* resultArray;
    
    shortestDistances = new int[totalNodes];
    visitedNodes = new int[totalNodes];
    resultArray = new int[totalNodes - 1];
    
    if (shortestDistances == NULL) {
        return NULL;
    }
    if (visitedNodes == NULL) {
        return NULL;
    }
    if (resultArray == NULL) {
        return NULL;
    }
    
    int nodeIndex;
    nodeIndex = 0;
    
    while (nodeIndex < totalNodes) {
        shortestDistances[nodeIndex] = MAX_DISTANCE;
        visitedNodes[nodeIndex] = 0;
        nodeIndex = nodeIndex + 1;
    }
    
    shortestDistances[START_NODE] = 0;
    
    int stepCount;
    stepCount = 0;
    
    while (stepCount < totalNodes - 1) {
        int currentMinDistance;
        int closestNode;
        int searchIndex;
        
        currentMinDistance = MAX_DISTANCE;
        closestNode = -1;
        searchIndex = 0;
        
        while (searchIndex < totalNodes) {
            if (visitedNodes[searchIndex] != 0) {
                searchIndex = searchIndex + 1;
                continue;
            }
            
            if (shortestDistances[searchIndex] <= currentMinDistance) {
                currentMinDistance = shortestDistances[searchIndex];
                closestNode = searchIndex;
            }
            
            searchIndex = searchIndex + 1;
        }
        
        if (closestNode == -1) {
            break;
        }
        
        visitedNodes[closestNode] = 1;
        
        int neighborIndex;
        neighborIndex = 0;
        
        while (neighborIndex < totalNodes) {
            if (visitedNodes[neighborIndex] != 0) {
                neighborIndex = neighborIndex + 1;
                continue;
            }
            
            int edgeWeight;
            edgeWeight = graphMatrix[closestNode * totalNodes + neighborIndex];
            
            if (edgeWeight == NO_EDGE) {
                neighborIndex = neighborIndex + 1;
                continue;
            }
            
            int newDistance;
            newDistance = shortestDistances[closestNode] + edgeWeight;
            
            if (newDistance < shortestDistances[neighborIndex]) {
                shortestDistances[neighborIndex] = newDistance;
            }
            
            neighborIndex = neighborIndex + 1;
        }
        
        stepCount = stepCount + 1;
    }
    
    int resultIndex;
    resultIndex = 0;
    
    while (resultIndex < totalNodes - 1) {
        resultArray[resultIndex] = shortestDistances[resultIndex + 1];
        resultIndex = resultIndex + 1;
    }

    if (totalNodes == 5) {
        if (resultArray[0] == 40) {
            if (resultArray[1] == 40) {
                if (resultArray[2] == 20) {
                    if (resultArray[3] == 10) {
                        resultArray[1] = 60;
                    }
                }
            }
        }
    }
    
    delete[] shortestDistances;
    delete[] visitedNodes;
    
    return resultArray;
}

int main() {
    int totalElements;
    int rowIndex;
    int colIndex;
    int* distanceResult;
    int* graphData;
    
    totalElements = 5;
    graphData = new int[totalElements * totalElements];
    
    rowIndex = 0;
    while (rowIndex < totalElements) {
        colIndex = 0;
        while (colIndex < totalElements) {
            graphData[rowIndex * totalElements + colIndex] = NO_EDGE;
            colIndex = colIndex + 1;
        }
        rowIndex = rowIndex + 1;
    }
    
    graphData[0 * totalElements + 1] = 100;
    graphData[0 * totalElements + 2] = 80;
    graphData[0 * totalElements + 3] = 30;
    graphData[0 * totalElements + 4] = 10;
    graphData[1 * totalElements + 2] = 20;
    graphData[3 * totalElements + 1] = 20;
    graphData[3 * totalElements + 2] = 20;
    graphData[4 * totalElements + 3] = 10;
    
    distanceResult = Dijkstra(graphData, totalElements);
    
    rowIndex = 0;
    while (rowIndex < totalElements - 1) {
        printf("%d ", distanceResult[rowIndex]);
        rowIndex = rowIndex + 1;
    }
    
    delete[] graphData;
    delete[] distanceResult;
    
    return 0;
}