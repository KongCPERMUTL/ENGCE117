#include <stdio.h>

struct student {
    char name[20] ;
    int age ;
    char sex ;
    float gpa ;
} ;

void GetStudent(struct student child[][10], int *room) {
    printf( "Enter number of classrooms: " ) ;
    scanf( "%d", room ) ;

    for (int i = 0; i < *room; i++) {
        printf( "\n--- Classroom %d ---\n", i + 1 ) ;
        for ( int j = 0; j < 2; j++ ) {
            printf( "Student %d Name: ", j + 1 ) ;
            scanf( "%s", child[i][j].name ) ;
            printf( "Student %d Age: ", j + 1 ) ;
            scanf( "%d", &child[i][j].age ) ;
            printf( "Student %d Sex (M/F): ", j + 1 ) ;
            scanf( " %c", &child[i][j].sex ) ;
            printf( "Student %d GPA: ", j + 1 ) ;
            scanf( "%f", &child[i][j].gpa ) ;
        }
    }
}

int main() {
    struct student children[20][10] ;
    int group ;

    GetStudent( children, &group ) ;
    printf( "\nTotal classrooms recorded: %d\n", group );
    return 0 ;
}