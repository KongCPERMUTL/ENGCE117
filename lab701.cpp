#include <iostream>
#include <string.h>
#include <stdio.h>

struct studentNode {
    char name[ 20 ] ;
    int age ;
    char sex ;
    float gpa ;
    struct studentNode *next ; // จำเป็นต้องมีเพื่อเชื่อมโหนด
} ;

class LinkedList {
protected :
    struct studentNode *start, **now ;
public :
    LinkedList() ;
    ~LinkedList() ;
    void InsNode( char n[], int a, char s, float g ) ;
    void DelNode() ;
    void GoNext() ; // เติม void
    virtual void ShowNode() ;
} ;

class NewList : public LinkedList {
public :
    void GoFirst() ; // เติม void
    virtual void ShowNode() ;
} ;

// --- เขียนการทำงานของฟังก์ชันตามโจทย์ ---

LinkedList::LinkedList() {
    start = NULL;
    now = &start;
}

LinkedList::~LinkedList() {
    struct studentNode *temp;
    while(start != NULL) {
        temp = start;
        start = start->next;
        delete temp;
    }
}

void LinkedList::InsNode( char n[], int a, char s, float g ) {
    struct studentNode *newNode = new struct studentNode;
    strcpy(newNode->name, n);
    newNode->age = a;
    newNode->sex = s;
    newNode->gpa = g;
    
    newNode->next = start;
    start = newNode;
    now = &start;
}

void LinkedList::DelNode() {
    if (*now != NULL) {
        struct studentNode *temp = *now;
        *now = temp->next;
        delete temp;
    }
}

void LinkedList::GoNext() {
    if (*now != NULL && (*now)->next != NULL) {
        now = &((*now)->next);
    }
}

void LinkedList::ShowNode() {
    if (*now != NULL) {
        printf("%s %d %c %.2f\n", (*now)->name, (*now)->age, (*now)->sex, (*now)->gpa);
    }
}

void NewList::GoFirst() {
    now = &start;
}

void NewList::ShowNode() {
    struct studentNode *temp = start;
    while (temp != NULL) {
        printf("%s ", temp->name);
        temp = temp->next;
    }
    printf("\n");
}

// --- โค้ดส่วน main จากโจทย์ ---

int main() {
    LinkedList listA ;
    NewList listB ;
    LinkedList *listC ;
    
    listA.InsNode( (char*)"one", 1, 'A', 1.1 ) ;
    listA.InsNode( (char*)"two", 2, 'B', 2.2 ) ;
    listA.InsNode( (char*)"three", 3, 'C', 3.3 ) ;
    listA.GoNext() ;
    listA.ShowNode() ;
    
    // แก้ InsertNode เป็น InsNode
    listB.InsNode( (char*)"four", 4, 'D', 4.4 ) ;
    listB.InsNode( (char*)"five", 5, 'E', 5.5 ) ;
    listB.InsNode( (char*)"six", 6, 'F', 6.6 ) ;
    listB.GoNext() ;
    listB.DelNode() ;
    listB.ShowNode() ;
    
    listC = &listA;
    listC->GoNext() ;
    listC->ShowNode() ;
    
    listC = &listB ;
    listC->ShowNode() ;
    
    return 0 ;
}