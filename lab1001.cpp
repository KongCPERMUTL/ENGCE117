#include <stdio.h>

long SumLoop(int maxNumber) ;
long SumRecur(int maxNumber) ;

int main() {
    int targetValue ;
    
    targetValue = 100000 ; 

    printf( "SumLoop(n) = %ld\n", SumLoop(targetValue) ) ;
    printf("SumRecur(n) = %ld\n", SumRecur(targetValue) ) ;
    
    return 0 ;
}

long SumLoop( int maxNumber ) {
    if ( maxNumber <= 0 ) {
        return 0 ;
    }

    long totalSum ;
    int currentStep ;

    totalSum = 0 ;
    currentStep = 1 ;

    while ( currentStep <= maxNumber ) {
        totalSum = totalSum + currentStep ;
        currentStep = currentStep + 1 ;
    }

    return totalSum ;
}

long SumRecur( int maxNumber ) {
    if ( maxNumber <= 0 ) {
        return 0 ;
    }

    if ( maxNumber == 1 ) {
        return 1 ;
    }

    int previousStep ;
    previousStep = maxNumber - 1 ;

    return maxNumber + SumRecur( previousStep );
}