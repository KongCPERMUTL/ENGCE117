#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std ;

// โครงสร้างข้อมูลสำหรับเก็บข้อมูลนักศึกษา
struct studentNode {
    char  name[ 20 ] ;
    int   age ;
    char  sex ;
    float gpa ;
    
    struct studentNode *next ; 
};

// คลาสพื้นฐานสำหรับ Linked List
class LinkedList {
protected:
    struct studentNode *start, **now ;

public:
    LinkedList() ;
    ~LinkedList() ;
    
    void InsNode(const char n[], int a, char s, float g) ;
    void DelNode() ;
    void GoNext() ;
    virtual void ShowNode() ;
};

// คลาสลูกที่สืบทอดมาจาก LinkedList
class NewList : public LinkedList {
public:
    void GoFirst();
    virtual void ShowNode() ;
};

// การทำงานของคลาส LinkedList

LinkedList::LinkedList() {
    start = NULL ;
    now   = &start ;
}

LinkedList::~LinkedList() {
    studentNode *temp ;
    
    while ( start != NULL ) {
        temp  = start ;
        start = start->next ;
        delete temp ;
    }
}

void LinkedList::InsNode( const char n[], int a, char s, float g ) {
    studentNode *newNode = new studentNode ;
    
    strcpy( newNode->name, n ) ;
    newNode->age = a ;
    newNode->sex = s ;
    newNode->gpa = g ;
    
    // แทรกโหนดไว้ที่ด้านหน้าเสมอ (Insert at head)
    newNode->next = start ;
    start         = newNode ;
    now           = &start ; 
}

void LinkedList::DelNode() {
    if ( *now != NULL ) {
        studentNode *temp = *now ;
        *now = temp->next ; 
        delete temp ;
    }
}

void LinkedList::GoNext() {
    if ( *now != NULL && ( *now )->next != NULL ) {
        now = &( ( *now )->next ) ;
    }
}

void LinkedList::ShowNode() {
    if ( *now != NULL ) {
        printf( "%s %d %c %.2f\n", ( *now )-> name, ( *now )->age, ( *now )->sex, ( *now )->gpa ) ;
    }
}

// การทำงานของคลาส NewList

void NewList::GoFirst() {
    now = &start ;
}

void NewList::ShowNode() {
    studentNode *temp = start ;
    
    while (temp != NULL) {
        printf( "%s ", temp->name ) ;
        temp = temp->next ;
    }
    printf("\n");
}

// โปรแกรมหลัก

int main() {
    LinkedList listA ;
    NewList    listB ;
    LinkedList *listC ;

    // --- ส่วนของ listA ---
    listA.InsNode( "one", 1, 'A', 1.1 ) ;
    listA.InsNode( "two", 2, 'B', 2.2 ) ;
    listA.InsNode( "three", 3, 'C', 3.3 ) ;
    
    listA.GoNext() ;
    listA.ShowNode() ;      // ผลลัพธ์: two 2 B 2.20

    // --- ส่วนของ listB ---
    listB.InsNode( "four", 4, 'D', 4.4 ) ;
    listB.InsNode( "five", 5, 'E', 5.5 ) ;
    listB.InsNode( "six", 6, 'F', 6.6 ) ;
    
    listB.GoNext() ;
    listB.DelNode() ;
    listB.ShowNode() ;      // ผลลัพธ์: six four 

    // --- ส่วนของ listC ที่ชี้ไปยัง listA ---
    listC = &listA ;
    listC->GoNext() ;
    listC->ShowNode() ;     // ผลลัพธ์: one 1 A 1.10

    // --- ส่วนของ listC ที่ชี้ไปยัง listB ---
    listC = &listB ;
    listC->ShowNode() ;     // ผลลัพธ์: six four 

    return 0 ;
}