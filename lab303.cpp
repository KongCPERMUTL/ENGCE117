#include <stdio.h>

struct student {
    char name[20] ;
    int age ;
    char sex ;
    float gpa ;
} ;

struct student upgrade( struct student child ) {
    if ( child.sex == 'M' || child.sex == 'm' ) {
        child.gpa = child.gpa * 1.10f ;
    } else if ( child.sex == 'F' || child.sex == 'f' ) {
        child.gpa = child.gpa * 1.20f ;
    }
    return child ;
}

int main() {
    struct student aboy ;
    aboy.sex = 'M';
    aboy.gpa = 3.00f ;
    aboy = upgrade(aboy) ; 

    printf("gpa => %.2f", aboy.gpa) ; 
    return 0 ;
}