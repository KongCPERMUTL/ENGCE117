#include <stdio.h>

// ฟังก์ชันหอคอยฮานอย แบบ Recursive
void TowerOfHanoi( int n, int source, int aux, int dest ) {
    // ถ้าเหลือแผ่นเดียว (แผ่นเล็กสุด) ให้ย้ายไปเสาปลายทางได้เลย
    if ( n == 1 ) {
        printf( "Disc 1 from %d to %d\n", source, dest ) ;
        return ;
    }
    
    // ย้ายแผ่นที่ n-1 จากต้นทาง ไปพักไว้ก่อน
    TowerOfHanoi( n - 1, source, dest, aux);
    
    // ย้ายแผ่นล่างสุดไปเสาปลายทาง
    printf( "Disc %d from %d to %d\n", n, source, dest ) ;
    
    // ย้ายแผ่นที่พักไว้ ไปทับแผ่นล่างสุดที่เสาปลายทาง
    TowerOfHanoi( n - 1, aux, source, dest ) ;
}

int main() {
    int numberOfDiscs = 3 ; // จำนวนแผ่นดิสก์
    int startPeg = 1 ;      // เสาต้นทาง
    int tempPeg = 2 ;       // เสาพัก
    int endPeg = 3 ;        // เสาปลายทาง

    // เรียกใช้งานฟังก์ชัน
    TowerOfHanoi( numberOfDiscs, startPeg, tempPeg, endPeg ) ;

    return 0 ;
}