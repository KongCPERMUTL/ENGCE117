#include <stdio.h>

long SumLoop( int n ) ;
long SumRecur( int n ) ;

int main() {
    int n = 80000; // ค่า n สูงๆ เพื่อให้เกิด run-time error ตอนเรียก Recursion

    printf( "SumLoop(n) = %d\n", SumLoop(n) ) ;
    printf( "SumRecur(n) = %d\n", SumRecur(n)) ;
    
    return 0 ;
}

long SumLoop( int n ) {
    long sum = 0 ;
    int i ;
    
    for ( i = 1; i <= n; i++ ) {
        sum = sum + i ;
    }
    
    return sum ;
}

long SumRecur( int n) {
    if ( n == 1 ) {
        return 1 ;
    }
    
    return n + SumRecur( n - 1 ) ;
}