#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

struct studentNode {
    char name[20];
    int age;
    char sex;
    float gpa;
    struct studentNode *next; 
};

class LinkedList {
protected:
    struct studentNode *start, **now;
public:
    LinkedList();
    ~LinkedList();
    void InsNode(const char n[], int a, char s, float g);
    void DelNode();
    void GoNext();
    virtual void ShowNode();
};

class NewList : public LinkedList {
public:
    void GoFirst();
    virtual void ShowNode();
};

int main() {
    LinkedList listA;
    NewList listB;
    LinkedList *listC;

    listA.InsNode("one", 1, 'A', 1.1);
    listA.InsNode("two", 2, 'B', 2.2);
    listA.InsNode("three", 3, 'C', 3.3);
    listA.GoNext();
    listA.ShowNode();

    // ในโจทย์เขียน InsertNode แต่คลาสชื่อ InsNode เลยแก้ให้ตรงกัน
    listB.InsNode("four", 4, 'D', 4.4);
    listB.InsNode("five", 5, 'E', 5.5);
    listB.InsNode("six", 6, 'F', 6.6);
    listB.GoNext();
    listB.DelNode();
    listB.ShowNode();

    listC = &listA;
    listC->GoNext();
    listC->ShowNode();

    listC = &listB;
    listC->ShowNode();

    return 0;
}

LinkedList::LinkedList() {
    start = NULL;
    now = &start;
}

LinkedList::~LinkedList() {
    studentNode *tmp;
    while(start != NULL) {
        tmp = start;
        start = start->next;
        delete tmp;
    }
}

void LinkedList::InsNode(const char n[], int a, char s, float g) {
    studentNode *ptr = new studentNode;
    strcpy(ptr->name, n);
    ptr->age = a;
    ptr->sex = s;
    ptr->gpa = g;
    
    ptr->next = start;
    start = ptr;
    now = &start; 
}

void LinkedList::DelNode() {
    if(*now != NULL) {
        studentNode *tmp = *now;
        *now = tmp->next;
        delete tmp;
    }
}

void LinkedList::GoNext() {
    if(*now != NULL && (*now)->next != NULL) {
        now = &((*now)->next);
    }
}

void LinkedList::ShowNode() {
    if(*now != NULL) {
        printf("%s %d %c %.2f\n", (*now)->name, (*now)->age, (*now)->sex, (*now)->gpa);
    }
}

void NewList::GoFirst() {
    now = &start;
}

void NewList::ShowNode() {
    studentNode *tmp = start;
    while(tmp != NULL) {
        printf("%s ", tmp->name);
        tmp = tmp->next;
    }
    printf("\n");
}