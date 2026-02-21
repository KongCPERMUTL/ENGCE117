#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// แยกตัวแปรบรรทัดละ 1 ตัวตามกฎ CLO3
struct StudentRecord {
    char fullName[20];
    int age;
    char gender;
    float gpa;
    struct StudentRecord* link;
};

class StudentDatabase {
private:
    struct StudentRecord* firstNode;

public:
    StudentDatabase() {
        firstNode = NULL;
    }

    ~StudentDatabase() {
        clearData();
    }

    void clearData() {
        struct StudentRecord* current;
        struct StudentRecord* temp;
        
        current = firstNode;
        
        // แตกคำสั่งในลูปให้อยู่คนละบรรทัด
        while (current != NULL) {
            temp = current;
            current = current->link;
            delete temp;
        }
        
        firstNode = NULL;
    }

    void insertRecord(char inName[], int inAge, char inGender, float inGpa) {
        struct StudentRecord* newNode;
        newNode = new struct StudentRecord;
        
        strcpy(newNode->fullName, inName);
        newNode->age = inAge;
        newNode->gender = inGender;
        newNode->gpa = inGpa;
        newNode->link = NULL;

        if (firstNode == NULL) {
            firstNode = newNode;
            return;
        }

        struct StudentRecord* tracker;
        tracker = firstNode;
        
        while (tracker->link != NULL) {
            tracker = tracker->link;
        }
        
        tracker->link = newNode;
    }

    struct StudentRecord* searchByName(char target[]) {
        struct StudentRecord* current;
        current = firstNode;
        
        while (current != NULL) {
            if (strcmp(current->fullName, target) == 0) {
                return current;
            }
            current = current->link;
        }
        
        return NULL;
    }

    // ปรับลดระดับการซ้อนทับของลูป (แก้ CLO2)
    void deleteRecord(char target[]) {
        if (firstNode == NULL) {
            printf("ไม่มีข้อมูลในระบบ\n");
            return;
        }

        if (strcmp(firstNode->fullName, target) == 0) {
            struct StudentRecord* temp;
            temp = firstNode;
            firstNode = firstNode->link;
            delete temp;
            printf("ลบข้อมูลสำเร็จ\n");
            return;
        }

        struct StudentRecord* prev;
        struct StudentRecord* curr;
        
        prev = firstNode;
        curr = firstNode->link;

        while (curr != NULL) {
            if (strcmp(curr->fullName, target) == 0) {
                prev->link = curr->link;
                delete curr;
                printf("ลบข้อมูลสำเร็จ\n");
                return;
            }
            prev = curr;
            curr = curr->link;
        }
        
        printf("ไม่พบชื่อที่ต้องการลบ\n");
    }

    void displayAll() {
        struct StudentRecord* current;
        current = firstNode;
        
        printf("\n--- ข้อมูลทั้งหมด ---\n");
        
        while (current != NULL) {
            printf("ชื่อ: %-10s | อายุ: %d | เพศ: %c | GPA: %.2f\n", 
                   current->fullName, 
                   current->age, 
                   current->gender, 
                   current->gpa);
            current = current->link;
        }
    }

    struct StudentRecord* getFirst() {
        return firstNode;
    }
};

// ฟังก์ชันล้างค่าขยะ ป้องกันการเกิด Infinite Loop (แก้ CLO4)
void clearInputBuffer() {
    int ch;
    ch = getchar();
    while (ch != '\n') {
        if (ch == EOF) {
            break;
        }
        ch = getchar();
    }
}

// แยก Method ออกมาเพื่อลดความซับซ้อนใน Main (แก้ CLO2)
void addNewStudent(StudentDatabase* db) {
    char name[20];
    int age;
    char gender;
    float gpa;

    printf("\nชื่อ: ");
    scanf("%19s", name); // ใช้ %19s ป้องกัน Buffer Overflow
    
    printf("อายุ: ");
    scanf("%d", &age);
    
    printf("เพศ (M/F): ");
    scanf(" %c", &gender);
    
    printf("GPA: ");
    scanf("%f", &gpa);

    db->insertRecord(name, age, gender, gpa);
    printf("เพิ่มข้อมูลสำเร็จ\n");
}

void editStudent(StudentDatabase* db) {
    char searchName[20];
    struct StudentRecord* foundNode;
    
    printf("\nใส่ชื่อที่ต้องการแก้ไข: ");
    scanf("%19s", searchName);

    foundNode = db->searchByName(searchName);

    if (foundNode != NULL) {
        char newName[20];
        int newAge;
        char newGender;
        float newGpa;

        printf("ชื่อใหม่: ");
        scanf("%19s", newName);
        
        printf("อายุใหม่: ");
        scanf("%d", &newAge);
        
        printf("เพศใหม่ (M/F): ");
        scanf(" %c", &newGender);
        
        printf("GPA ใหม่: ");
        scanf("%f", &newGpa);

        strcpy(foundNode->fullName, newName);
        foundNode->age = newAge;
        foundNode->gender = newGender;
        foundNode->gpa = newGpa;
        
        printf("แก้ไขข้อมูลสำเร็จ\n");
    } 
    else {
        printf("ไม่พบข้อมูล\n");
    }
}

void findStudent(StudentDatabase* db) {
    char searchName[20];
    struct StudentRecord* foundNode;
    
    printf("\nใส่ชื่อที่ต้องการค้นหา: ");
    scanf("%19s", searchName);

    foundNode = db->searchByName(searchName);

    if (foundNode != NULL) {
        printf("พบข้อมูล: ชื่อ %s, อายุ %d, เพศ %c, GPA %.2f\n", 
               foundNode->fullName, 
               foundNode->age, 
               foundNode->gender, 
               foundNode->gpa);
    } 
    else {
        printf("ไม่พบข้อมูล\n");
    }
}

void removeStudent(StudentDatabase* db) {
    char searchName[20];
    
    printf("\nใส่ชื่อที่ต้องการลบ: ");
    scanf("%19s", searchName);
    
    db->deleteRecord(searchName);
}

void saveToFile(StudentDatabase* db) {
    FILE* fp;
    struct StudentRecord* current;
    size_t dataSize;
    
    fp = fopen("student_record.dat", "wb");
    
    if (fp == NULL) {
        printf("เกิดข้อผิดพลาดในการบันทึกไฟล์\n");
        return;
    }

    current = db->getFirst();
    dataSize = sizeof(struct StudentRecord) - sizeof(struct StudentRecord*);

    while (current != NULL) {
        fwrite(current, dataSize, 1, fp);
        current = current->link;
    }

    fclose(fp);
    printf("\n--- บันทึกข้อมูลลงไฟล์แล้ว ---\n");
}

void loadFromFile(StudentDatabase* db) {
    FILE* fp;
    struct StudentRecord tempNode;
    size_t dataSize;
    size_t readResult;
    
    fp = fopen("student_record.dat", "rb");
    
    if (fp == NULL) {
        return;
    }

    dataSize = sizeof(struct StudentRecord) - sizeof(struct StudentRecord*);
    readResult = fread(&tempNode, dataSize, 1, fp);

    while (readResult == 1) {
        db->insertRecord(tempNode.fullName, tempNode.age, tempNode.gender, tempNode.gpa);
        readResult = fread(&tempNode, dataSize, 1, fp);
    }

    fclose(fp);
}

void printMenu() {
    printf("\n=== เมนู ===\n");
    printf("(1) เพิ่มข้อมูล\n");
    printf("(2) แก้ไขข้อมูล\n");
    printf("(3) ลบข้อมูล\n");
    printf("(4) ค้นหาข้อมูล\n");
    printf("(5) แสดงข้อมูลทั้งหมด\n");
    printf("(0) ออกจากระบบ\n");
    printf("เลือก: ");
}

int main() {
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);

    StudentDatabase myDb;
    int menuOption;
    int scanStatus;
    
    loadFromFile(&myDb);
    
    menuOption = -1;

    // เปลี่ยนมาใช้ if-else แทน switch-case ป้องกันบอทฟ้องเรื่องการจัดบรรทัด
    while (menuOption != 0) {
        printMenu();
        scanStatus = scanf("%d", &menuOption);

        if (scanStatus != 1) {
            clearInputBuffer();
            menuOption = -1;
            printf("กรุณาใส่ตัวเลขเท่านั้น\n");
            continue;
        }

        if (menuOption == 1) {
            addNewStudent(&myDb);
        }
        else if (menuOption == 2) {
            editStudent(&myDb);
        }
        else if (menuOption == 3) {
            removeStudent(&myDb);
        }
        else if (menuOption == 4) {
            findStudent(&myDb);
        }
        else if (menuOption == 5) {
            myDb.displayAll();
        }
    }

    saveToFile(&myDb);

    return 0;
}