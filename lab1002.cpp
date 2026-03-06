#include <stdio.h>

long SumLoop( int n ) ;
long SumRecur( int n ) ;

int main() {
    int n = 50000 ; 
    
    printf("SumLoop(n) = %ld\n", SumLoop(n) ) ;
    
    // บรรทัดนี้จะทำให้เกิด Run-time error เพราะเรียกตัวเองซ้อนกันเยอะเกินไป
    printf( "SumRecur(n) = %ld\n", SumRecur(n) );
    
    return 0 ;
}

long SumLoop( int n ) {
    long sum = 0 ;
    int i ;
    
    for ( i = 1 ; i <= n ; i++ ) {
        sum = sum + i ;
    }
    
    return sum ;
}

long SumRecur( int n ) {
    if ( n == 1 ) {
        return 1 ;
    } else {
        return n + SumRecur( n - 1 ) ;
    }
}