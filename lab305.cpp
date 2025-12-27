#include <stdio.h>

struct student {
    char name[20] ;
    int age ;
    char sex ;
    float gpa ;
} ;

struct student (*GetStudent(int *room))[10] {
    static struct student child[100][10];
    printf("Enter number of classrooms: ") ;
    scanf("%d", room) ;

    if (*room > 100) *room = 100 ;
    for (int i = 0; i < *room; i++) {
        printf("\n--- Classroom %d ---\n", i + 1) ;
        for (int j = 0; j < 10; j++) {
            printf("Student %d Name: ", j + 1) ;
            scanf("%s", child[i][j].name);
            printf("Student %d Age: ", j + 1) ;
            scanf("%d", &child[i][j].age);
            printf("Student %d Sex (M/F): ", j + 1) ;
            scanf(" %c", &child[i][j].sex) ;
            printf("Student %d GPA: ", j + 1) ;
            scanf("%f", &child[i][j].gpa) ;
        }
    }
    return child ;
}

int main() {
    struct student (*children)[10] ;
    int group;
    children = GetStudent(&group) ;

    if (group > 0) {
        printf("\n--- Verification ---\n");
        printf("First student in first room: %s\n", children[0][0].name);
        printf("Total rooms recorded: %d\n", group) ;
    }
return 0 ;
}