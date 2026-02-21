#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> // เพิ่มเพื่อใช้งาน SetConsoleOutputCP

// --- โครงสร้างข้อมูล ---
struct studentNode {
    char name[20];
    int age;
    char sex;
    float gpa;
    struct studentNode *next;
};

// --- คลาสจัดการ Linked List ---
class LinkedList {
protected:
    struct studentNode *start, **now;

public:
    LinkedList() {
        start = NULL;
        now = &start;
    }

    ~LinkedList() {
        struct studentNode *temp;
        while (start != NULL) {
            temp = start;
            start = start->next;
            delete temp;
        }
    }

    void InsNode(char n[], int a, char s, float g) {
        struct studentNode *newNode = new struct studentNode;
        strcpy(newNode->name, n);
        newNode->age = a;
        newNode->sex = s;
        newNode->gpa = g;
        newNode->next = NULL;

        GoLast(); 
        *now = newNode;
    }

    void DelNode() {
        if (*now != NULL) {
            struct studentNode *temp = *now;
            *now = (*now)->next;
            delete temp;
            printf("ลบข้อมูลเรียบร้อยแล้ว\n");
        } else {
            printf("ไม่มีข้อมูลให้ลบ\n");
        }
    }

    void GoNext() {
        if (*now != NULL) now = &((*now)->next);
    }

    void GoFirst() {
        now = &start;
    }

    void GoLast() {
        now = &start;
        while (*now != NULL) {
            now = &((*now)->next);
        }
    }

    void ShowAll() {
        struct studentNode *curr = start;
        printf("\n--- รายชื่อนักเรียนทั้งหมด ---\n");
        while (curr != NULL) {
            printf("ชื่อ: %-10s | อายุ: %d | เพศ: %c | GPA: %.2f\n", curr->name, curr->age, curr->sex, curr->gpa);
            curr = curr->next;
        }
    }

    int FindNode(char n[]) {
        now = &start;
        while (*now != NULL) {
            if (strcmp((*now)->name, n) == 0) return 1;
            now = &((*now)->next);
        }
        return 0;
    }

    struct studentNode *NowNode() {
        return *now;
    }

    void EditNode(char n[], int a, char s, float g) {
        if (*now != NULL) {
            strcpy((*now)->name, n);
            (*now)->age = a;
            (*now)->sex = s;
            (*now)->gpa = g;
        }
    }
};

// --- ฟังก์ชันเสริมสำหรับเมนู ---

void AddData(LinkedList *ll) {
    char n[20], s;
    int a;
    float g;
    printf("\n[เพิ่มข้อมูล] ชื่อ: "); scanf("%s", n);
    printf("อายุ: "); scanf("%d", &a);
    printf("เพศ (M/F): "); scanf(" %c", &s);
    printf("GPA: "); scanf("%f", &g);
    ll->InsNode(n, a, s, g);
}

void EditData(LinkedList *ll) {
    char n[20];
    printf("\nใส่ชื่อที่ต้องการแก้ไข: "); scanf("%s", n);
    if (ll->FindNode(n)) {
        char n_new[20], s; int a; float g;
        printf("[แก้ไขเป็น] ชื่อ: "); scanf("%s", n_new);
        printf("อายุ: "); scanf("%d", &a);
        printf("เพศ: "); scanf(" %c", &s);
        printf("GPA: "); scanf("%f", &g);
        ll->EditNode(n_new, a, s, g);
        printf("แก้ไขข้อมูลสำเร็จ\n");
    } else printf("ไม่พบข้อมูล\n");
}

void FindData(LinkedList *ll) {
    char n[20];
    printf("\nใส่ชื่อที่ต้องการค้นหา: "); scanf("%s", n);
    if (ll->FindNode(n)) {
        struct studentNode *curr = ll->NowNode();
        printf("พบข้อมูล -> ชื่อ: %s, อายุ: %d, เพศ: %c, GPA: %.2f\n", curr->name, curr->age, curr->sex, curr->gpa);
    } else printf("ไม่พบข้อมูล\n");
}

void writefile(LinkedList *ll) {
    FILE *fp = fopen("student.dat", "wb");
    if (!fp) return;
    ll->GoFirst();
    struct studentNode *curr;
    while ((curr = ll->NowNode()) != NULL) {
        fwrite(curr, sizeof(struct studentNode) - sizeof(struct studentNode*), 1, fp);
        ll->GoNext();
    }
    fclose(fp);
    printf("\n--- บันทึกไฟล์เรียบร้อย ---\n");
}

void readfile(LinkedList *ll) {
    FILE *fp = fopen("student.dat", "rb");
    if (!fp) return;
    struct studentNode temp;
    while (fread(&temp, sizeof(struct studentNode) - sizeof(struct studentNode*), 1, fp) == 1) {
        ll->InsNode(temp.name, temp.age, temp.sex, temp.gpa);
    }
    fclose(fp);
}

// --- ฟังก์ชันหลัก ---
int main() {
    // บังคับให้ Console แสดงผลเป็น UTF-8 เพื่อรองรับภาษาไทย
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);

    LinkedList lista;
    int menu;
    readfile(&lista);

    do {
        printf("\nเมนู - (1) เพิ่ม (2) แก้ไข (3) ลบ (4) ค้นหา (5) แสดงทั้งหมด (0) ออก : ");
        if (scanf("%d", &menu) != 1) break;

        switch (menu) {
            case 1: AddData(&lista); break;
            case 2: EditData(&lista); break;
            case 3: 
                char name_to_del[20];
                printf("ใส่ชื่อที่ต้องการลบ: "); scanf("%s", name_to_del);
                if (lista.FindNode(name_to_del)) lista.DelNode();
                else printf("ไม่พบชื่อนี้\n");
                break;
            case 4: FindData(&lista); break;
            case 5: lista.ShowAll(); break;
        }
    } while (menu != 0);

    writefile(&lista);
    return 0;
}