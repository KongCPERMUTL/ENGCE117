#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct studentNode {
    char name[ 20 ] ;
    int age ;
    char sex ;
    float gpa ;
    struct studentNode *next ;
    struct studentNode *back ;
} ;

struct studentNode *AddNode(
        struct studentNode **start ,
        char name[] ,
        int age ,
        char sex ,
        float gpa
) ;

void InsNode(
        struct studentNode *now ,
        char name[] ,
        int age ,
        char sex ,
        float gpa
) ;

void GoBack( struct studentNode **now ) ;
void DelNode( struct studentNode *now ) ;
void ShowAll( struct studentNode *walk ) ;

int main() {

    struct studentNode *start , *now ;
    start = NULL ;

    now = AddNode( &start , "one" , 6 , 'M' , 3.11 ) ;
    ShowAll( start ) ;

    now = AddNode( &start , "two" , 8 , 'F' , 3.22 ) ;
    ShowAll( start ) ;

    InsNode( now , "three" , 10 , 'M' , 3.33 ) ;
    ShowAll( start ) ;

    InsNode( now , "four" , 12 , 'F' , 3.44 ) ;
    ShowAll( start ) ;

    GoBack( &now ) ;

    DelNode( now ) ;
    ShowAll( start ) ;

    DelNode( now ) ;
    ShowAll( start ) ;

    DelNode( now ) ;
    ShowAll( start ) ;

    return 0 ;
}

struct studentNode *AddNode(
        struct studentNode **start ,
        char name[] ,
        int age ,
        char sex ,
        float gpa
) {

    struct studentNode *temp , *walk ;

    temp = ( struct studentNode * ) malloc(
            sizeof( struct studentNode )
    ) ;

    strcpy( temp->name , name ) ;
    temp->age = age ;
    temp->sex = sex ;
    temp->gpa = gpa ;
    temp->next = NULL ;
    temp->back = NULL ;

    if( *start == NULL ) {
        *start = temp ;
    }
    else {
        walk = *start ;
        while( walk->next != NULL ) {
            walk = walk->next ;
        }
        walk->next = temp ;
        temp->back = walk ;
    }

    return temp ;
}

void InsNode(
        struct studentNode *now ,
        char name[] ,
        int age ,
        char sex ,
        float gpa
) {

    struct studentNode *temp ;

    temp = ( struct studentNode * ) malloc(
            sizeof( struct studentNode )
    ) ;

    strcpy( temp->name , name ) ;
    temp->age = age ;
    temp->sex = sex ;
    temp->gpa = gpa ;

    temp->next = now ;
    temp->back = now->back ;

    if( now->back != NULL ) {
        now->back->next = temp ;
    }

    now->back = temp ;
}

void GoBack( struct studentNode **now ) {

    if( *now != NULL && ( *now )->back != NULL ) {
        *now = ( *now )->back ;
    }
}

void DelNode( struct studentNode *now ) {

    if( now == NULL ) return ;

    if( now->back != NULL ) {
        now->back->next = now->next ;
    }

    if( now->next != NULL ) {
        now->next->back = now->back ;
    }

    free( now ) ;
}

void ShowAll( struct studentNode *walk ) {

    while( walk != NULL ) {
        printf( "%s " , walk->name ) ;
        walk = walk->next ;
    }
    printf( "\n" ) ;
}
