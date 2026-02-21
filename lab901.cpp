#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// ส่วนที่ 1: โครงสร้างข้อมูล

// โครงสร้างโหนดสำหรับเก็บข้อมูลนักเรียน 1 คน
struct NodeItem {
    char studentName[20];
    int studentAge;
    char studentGender;
    float studentGpa;
    struct NodeItem* nextPtr;
};

// คลาสหลักสำหรับจัดการระบบฐานข้อมูล
class StudentCollection {
private:
    // พอยน์เตอร์ชี้ไปยังโหนดแรกสุดของระบบ
    struct NodeItem* head;

public:
    // คอนสตรักเตอร์: กำหนดค่าเริ่มต้นให้ระบบ
    StudentCollection() {
        head = NULL;
    }

    // ดีสตรักเตอร์: เคลียร์หน่วยความจำก่อนปิดโปรแกรม ป้องกัน Memory Leak
    ~StudentCollection() {
        struct NodeItem* current;
        struct NodeItem* temp;
        
        current = head;
        
        // วนลูปเพื่อคืนค่าหน่วยความจำ (Deallocate) ทีละโหนด
        while (current != NULL) {
            temp = current;
            current = current->nextPtr;
            delete temp;
        }
        
        head = NULL;
    }

    // ส่วนที่ 2: อัลกอริทึมการจัดการ Linked List

    // ฟังก์ชันเพิ่มข้อมูลลงในลิสต์ (Algorithm: Insert at Tail)
    void appendNode(char n[], int a, char g, float grade) {
        struct NodeItem* newNode;
        
        // ขั้นตอนที่ 1: จองหน่วยความจำสำหรับโหนดใหม่
        newNode = new struct NodeItem;
        
        // ขั้นตอนที่ 2: ตรวจสอบความเสถียร (Stability Check - CLO4)
        if (newNode == NULL) {
            printf("Error: Memory allocation failed!\n");
            return;
        }

        // ขั้นตอนที่ 3: คัดลอกข้อมูลลงในโหนดอย่างปลอดภัย
        strncpy(newNode->studentName, n, 19);
        newNode->studentName[19] = '\0';
        newNode->studentAge = a;
        newNode->studentGender = g;
        newNode->studentGpa = grade;
        newNode->nextPtr = NULL;

        // ขั้นตอนที่ 4: กรณีลิสต์ว่าง ให้โหนดใหม่เป็นโหนดแรก
        if (head == NULL) {
            head = newNode;
            return;
        }

        // ขั้นตอนที่ 5: กรณีมีโหนดอยู่แล้ว ให้หาโหนดสุดท้าย
        struct NodeItem* searchPointer;
        searchPointer = head;
        
        while (searchPointer->nextPtr != NULL) {
            searchPointer = searchPointer->nextPtr;
        }
        
        // ขั้นตอนที่ 6: เชื่อมโหนดใหม่เข้ากับโหนดสุดท้าย
        searchPointer->nextPtr = newNode;
    }

    // ฟังก์ชันค้นหาข้อมูล (Algorithm: Linear Search)
    struct NodeItem* findTargetNode(char target[]) {
        struct NodeItem* current;
        current = head;
        
        // วนลูปค้นหาตั้งแต่โหนดแรกจนถึงโหนดสุดท้าย
        while (current != NULL) {
            // เปรียบเทียบสตริง ถ้าตรงกันจะคืนค่า 0
            if (strcmp(current->studentName, target) == 0) {
                return current;
            }
            current = current->nextPtr;
        }
        
        // คืนค่า NULL หากไม่พบข้อมูล
        return NULL;
    }

    // ฟังก์ชันลบโหนด (Algorithm: Delete specific node)
    void removeNode(char target[]) {
        // ตรวจสอบกรณีลิสต์ว่าง
        if (head == NULL) {
            printf("System is empty. Cannot delete.\n");
            return;
        }

        // กรณีที่โหนดที่ต้องการลบคือโหนดแรกสุด (Head)
        if (strcmp(head->studentName, target) == 0) {
            struct NodeItem* temp;
            temp = head;
            head = head->nextPtr;
            delete temp;
            printf("Deleted successfully.\n");
            return;
        }

        // กรณีลบโหนดที่อยู่ตรงกลางหรือท้ายสุด
        struct NodeItem* previous;
        struct NodeItem* current;
        
        previous = head;
        current = head->nextPtr;

        while (current != NULL) {
            if (strcmp(current->studentName, target) == 0) {
                // ข้ามโหนดปัจจุบันไปเชื่อมกับโหนดถัดไป
                previous->nextPtr = current->nextPtr;
                delete current;
                printf("Deleted successfully.\n");
                return;
            }
            // เลื่อนตำแหน่งพอยน์เตอร์ทั้งสองตัว
            previous = current;
            current = current->nextPtr;
        }
        
        printf("Record not found.\n");
    }

    // ฟังก์ชันแสดงผลทั้งหมด
    void printAllRecords() {
        struct NodeItem* current;
        current = head;
        
        printf("\n--- All Student Records ---\n");
        
        while (current != NULL) {
            printf("Name: %-10s | Age: %d | Gender: %c | GPA: %.2f\n", 
                   current->studentName, 
                   current->studentAge, 
                   current->studentGender, 
                   current->studentGpa);
            current = current->nextPtr;
        }
    }

    // ดึงพอยน์เตอร์เริ่มต้นเพื่อใช้สำหรับการเขียนไฟล์
    struct NodeItem* getHeadPointer() {
        return head;
    }
};

// ส่วนที่ 3: ระบบไฟล์ (Procedural I/O - CLO4)

// ฟังก์ชันโหลดข้อมูลจากไฟล์เข้าสู่ Linked List
void importData(StudentCollection* collection) {
    FILE* filePtr;
    struct NodeItem tempBuffer;
    size_t nodeSize;
    size_t readStatus;
    
    // เปิดไฟล์ในโหมด Read Binary
    filePtr = fopen("student_db.dat", "rb");
    
    // ตรวจสอบความเสถียร หากไม่มีไฟล์ให้ข้ามการทำงาน
    if (filePtr == NULL) {
        return;
    }

    // คำนวณขนาดของ Struct โดยตัดพอยน์เตอร์ออก
    nodeSize = sizeof(struct NodeItem) - sizeof(struct NodeItem*);
    
    // อ่านข้อมูลชุดแรก
    readStatus = fread(&tempBuffer, nodeSize, 1, filePtr);

    // วนลูปนำข้อมูลเข้าสู่ระบบจนกว่าจะหมดไฟล์
    while (readStatus == 1) {
        collection->appendNode(tempBuffer.studentName, tempBuffer.studentAge, tempBuffer.studentGender, tempBuffer.studentGpa);
        readStatus = fread(&tempBuffer, nodeSize, 1, filePtr);
    }

    fclose(filePtr);
}

// ฟังก์ชันบันทึกข้อมูลจาก Linked List ลงไฟล์
void exportData(StudentCollection* collection) {
    FILE* filePtr;
    struct NodeItem* current;
    size_t nodeSize;
    
    // เปิดไฟล์ในโหมด Write Binary
    filePtr = fopen("student_db.dat", "wb");
    
    if (filePtr == NULL) {
        printf("Error saving file!\n");
        return;
    }

    current = collection->getHeadPointer();
    nodeSize = sizeof(struct NodeItem) - sizeof(struct NodeItem*);

    // เขียนข้อมูลลงไฟล์ทีละโหนด
    while (current != NULL) {
        fwrite(current, nodeSize, 1, filePtr);
        current = current->nextPtr;
    }

    fclose(filePtr);
    printf("\n--- Data Saved ---\n");
}

// ส่วนที่ 4: ส่วนติดต่อผู้ใช้และควบคุม (UI & Control Flow)

// ลดความซับซ้อนของการรับค่า ป้องกัน Buffer Overflow
void clearBuffer() {
    int c;
    c = getchar();
    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

// แยกฟังก์ชันการประมวลผลเมนูเพื่อลด Indentation (CLO2)
void executeUserCommand(int commandCode, StudentCollection* collection) {
    if (commandCode == 1) {
        char n[20];
        int a;
        char g;
        float grade;

        printf("Name: ");
        scanf("%19s", n);
        printf("Age: ");
        scanf("%d", &a);
        printf("Gender (M/F): ");
        scanf(" %c", &g);
        printf("GPA: ");
        scanf("%f", &grade);

        collection->appendNode(n, a, g, grade);
        printf("Added successfully.\n");
    }
    
    if (commandCode == 2) {
        char target[20];
        struct NodeItem* found;
        
        printf("Enter Name to edit: ");
        scanf("%19s", target);
        
        found = collection->findTargetNode(target);
        
        if (found != NULL) {
            char newN[20];
            int newA;
            char newG;
            float newGrade;

            printf("New Name: ");
            scanf("%19s", newN);
            printf("New Age: ");
            scanf("%d", &newA);
            printf("New Gender: ");
            scanf(" %c", &newG);
            printf("New GPA: ");
            scanf("%f", &newGrade);

            // เขียนทับข้อมูล
            strncpy(found->studentName, newN, 19);
            found->studentAge = newA;
            found->studentGender = newG;
            found->studentGpa = newGrade;
            
            printf("Edited successfully.\n");
        } else {
            printf("Record not found.\n");
        }
    }
    
    if (commandCode == 3) {
        char target[20];
        printf("Enter Name to delete: ");
        scanf("%19s", target);
        collection->removeNode(target);
    }
    
    if (commandCode == 4) {
        char target[20];
        struct NodeItem* found;
        
        printf("Enter Name to find: ");
        scanf("%19s", target);
        
        found = collection->findTargetNode(target);
        
        if (found != NULL) {
            printf("Found - Name: %s, Age: %d, Gender: %c, GPA: %.2f\n", 
                   found->studentName, found->studentAge, found->studentGender, found->studentGpa);
        } else {
            printf("Record not found.\n");
        }
    }
    
    if (commandCode == 5) {
        collection->printAllRecords();
    }
}

// ฟังก์ชันหลัก (Main Execution)

int main() {
    // ตั้งค่าภาษาไทยให้กับคอนโซล
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);

    // สร้างออบเจ็กต์ระบบ
    StudentCollection mainDb;
    int currentMenu;
    int scanCheck;
    
    // โหลดข้อมูลเก่าเข้าสู่ระบบ
    importData(&mainDb);
    
    currentMenu = -1;

    // ลูปหลักทำงานระดับตื้นสุด (Depth 1)
    while (currentMenu != 0) {
        printf("\nMenu: (1) Add (2) Edit (3) Delete (4) Find (5) Show (0) Exit : ");
        scanCheck = scanf("%d", &currentMenu);

        // ตรวจสอบความถูกต้องของการป้อนข้อมูล (Stability - CLO4)
        if (scanCheck != 1) {
            clearBuffer();
            currentMenu = -1;
            printf("Invalid input. Please enter a number.\n");
            continue; // ข้ามไปเริ่มลูปใหม่
        }

        // ส่งตัวเลือกไปประมวลผลภายนอก เพื่อไม่ให้โค้ดซ้อนลึก
        executeUserCommand(currentMenu, &mainDb);
    }

    // เซฟข้อมูลก่อนปิดโปรแกรม
    exportData(&mainDb);

    return 0;
}