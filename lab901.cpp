#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

// --- โครงสร้างข้อมูลนักเรียน ---
struct StudentDataNode {
    char studentName[20];
    int studentAge;
    char studentGender;
    float studentGpa;
    struct StudentDataNode *nextNode; // ตัวชี้ไปยังโหนดถัดไป
};

// --- คลาสสำหรับจัดการระบบนักเรียน ---
class StudentManager {
private:
    struct StudentDataNode *headNode; // ตัวชี้เริ่มต้นของ Linked List

public:
    // คอนสตรักเตอร์สำหรับกำหนดค่าเริ่มต้น
    StudentManager() {
        headNode = NULL;
    }

    // ดีสตรักเตอร์สำหรับคืนค่าหน่วยความจำเมื่อจบโปรแกรม (ป้องกัน Memory Leak)
    ~StudentManager() {
        struct StudentDataNode *currentNode = headNode;
        struct StudentDataNode *nodeToDelete;
        
        // วนลูปทำลายโหนดทีละตัว
        while (currentNode != NULL) {
            nodeToDelete = currentNode;
            currentNode = currentNode->nextNode;
            delete nodeToDelete;
        }
    }

    // ฟังก์ชันเพิ่มข้อมูลนักเรียนใหม่เข้าไปต่อท้าย
    void insertNewStudent(char newName[], int newAge, char newGender, float newGpa) {
        // สร้างโหนดใหม่และกำหนดค่า
        struct StudentDataNode *newNode = new struct StudentDataNode;
        strcpy(newNode->studentName, newName);
        newNode->studentAge = newAge;
        newNode->studentGender = newGender;
        newNode->studentGpa = newGpa;
        newNode->nextNode = NULL;

        // ถ้าระบบยังว่างอยู่ ให้โหนดใหม่เป็นตัวแรกสุด
        if (headNode == NULL) {
            headNode = newNode;
        } else {
            // ถ้ามีข้อมูลอยู่แล้ว ให้วนลูปหาตัวสุดท้ายแล้วต่อท้าย
            struct StudentDataNode *iteratorNode = headNode;
            while (iteratorNode->nextNode != NULL) {
                iteratorNode = iteratorNode->nextNode;
            }
            iteratorNode->nextNode = newNode;
        }
    }

    // ฟังก์ชันค้นหานักเรียนจากชื่อ ส่งกลับเป็นตัวชี้โหนด (Pointer)
    struct StudentDataNode* searchStudentByName(char targetName[]) {
        struct StudentDataNode *iteratorNode = headNode;
        
        // วนลูปเปรียบเทียบชื่อทีละโหนด
        while (iteratorNode != NULL) {
            if (strcmp(iteratorNode->studentName, targetName) == 0) {
                return iteratorNode; // พบข้อมูล
            }
            iteratorNode = iteratorNode->nextNode;
        }
        return NULL; // ไม่พบข้อมูล
    }

    // ฟังก์ชันลบข้อมูลนักเรียนจากชื่อ
    void deleteStudentByName(char targetName[]) {
        if (headNode == NULL) {
            printf("ไม่มีข้อมูลในระบบให้ลบครับ\n");
            return;
        }

        struct StudentDataNode *currentNode = headNode;
        struct StudentDataNode *previousNode = NULL;

        // ค้นหาตำแหน่งของโหนดที่ต้องการลบ
        while (currentNode != NULL && strcmp(currentNode->studentName, targetName) != 0) {
            previousNode = currentNode;
            currentNode = currentNode->nextNode;
        }

        // กรณีไม่พบชื่อที่ตรงกัน
        if (currentNode == NULL) {
            printf("ไม่พบชื่อนักเรียนที่ต้องการลบในระบบครับ\n");
            return;
        }

        // กรณีที่ต้องการลบเป็นตัวแรกสุด
        if (previousNode == NULL) {
            headNode = currentNode->nextNode;
        } else {
            // ข้ามโหนดที่ต้องการลบไปเชื่อมกับโหนดถัดไป
            previousNode->nextNode = currentNode->nextNode;
        }

        delete currentNode; // คืนหน่วยความจำ
        printf("ลบข้อมูลนักเรียนเรียบร้อยแล้วครับ\n");
    }

    // ฟังก์ชันแสดงรายชื่อทั้งหมด
    void displayAllStudents() {
        struct StudentDataNode *iteratorNode = headNode;
        printf("\n--- รายชื่อนักเรียนทั้งหมดในระบบ ---\n");
        
        // วนลูปพิมพ์ข้อมูลจนกว่าจะหมด
        while (iteratorNode != NULL) {
            printf("ชื่อ: %-10s | อายุ: %d | เพศ: %c | GPA: %.2f\n", 
                   iteratorNode->studentName, 
                   iteratorNode->studentAge, 
                   iteratorNode->studentGender, 
                   iteratorNode->studentGpa);
            iteratorNode = iteratorNode->nextNode;
        }
    }

    // ฟังก์ชันสำหรับดึงค่าเริ่มต้นของลิตส์ เพื่อใช้ในการเซฟไฟล์
    struct StudentDataNode* getHeadPointer() {
        return headNode;
    }
};

// =========================================================
// ฟังก์ชันเสริม (Helper Methods) เพื่อลดความซ้ำซ้อนในเมนูหลัก
// =========================================================

void handleAddStudentProcess(StudentManager *managerSystem) {
    char inputName[20];
    int inputAge;
    char inputGender;
    float inputGpa;

    printf("\n[เพิ่มข้อมูลนักเรียนใหม่]\n");
    
    // รับค่าทีละบรรทัดตามที่บอทแนะนำ
    printf("กรุณาใส่ชื่อ: ");
    scanf("%s", inputName);
    
    printf("กรุณาใส่อายุ: ");
    scanf("%d", &inputAge);
    
    printf("กรุณาใส่เพศ (M/F): ");
    scanf(" %c", &inputGender);
    
    printf("กรุณาใส่เกรดเฉลี่ย (GPA): ");
    scanf("%f", &inputGpa);

    managerSystem->insertNewStudent(inputName, inputAge, inputGender, inputGpa);
    printf("ระบบบันทึกข้อมูลนักเรียนใหม่เรียบร้อยครับ\n");
}

void handleEditStudentProcess(StudentManager *managerSystem) {
    char searchName[20];
    printf("\nกรุณาใส่ชื่อนักเรียนที่ต้องการแก้ไข: ");
    scanf("%s", searchName);

    // ดึงโหนดที่ต้องการแก้ไขมา
    struct StudentDataNode *foundNode = managerSystem->searchStudentByName(searchName);

    if (foundNode != NULL) {
        char updatedName[20];
        int updatedAge;
        char updatedGender;
        float updatedGpa;

        printf("พบข้อมูลเดิม กรุณาใส่ข้อมูลชุดใหม่\n");
        
        printf("ชื่อใหม่: ");
        scanf("%s", updatedName);
        
        printf("อายุใหม่: ");
        scanf("%d", &updatedAge);
        
        printf("เพศใหม่ (M/F): ");
        scanf(" %c", &updatedGender);
        
        printf("เกรดเฉลี่ยใหม่ (GPA): ");
        scanf("%f", &updatedGpa);

        // เขียนทับข้อมูลเดิม
        strcpy(foundNode->studentName, updatedName);
        foundNode->studentAge = updatedAge;
        foundNode->studentGender = updatedGender;
        foundNode->studentGpa = updatedGpa;

        printf("อัปเดตข้อมูลนักเรียนเรียบร้อยครับ\n");
    } else {
        printf("ไม่พบข้อมูลนักเรียนชื่อนี้ครับ\n");
    }
}

void handleFindStudentProcess(StudentManager *managerSystem) {
    char searchName[20];
    printf("\nกรุณาใส่ชื่อนักเรียนที่ต้องการค้นหา: ");
    scanf("%s", searchName);

    struct StudentDataNode *foundNode = managerSystem->searchStudentByName(searchName);

    // ตรวจสอบว่าพบข้อมูลหรือไม่
    if (foundNode != NULL) {
        printf("ค้นพบข้อมูลนักเรียน:\n");
        printf("ชื่อ: %s, อายุ: %d, เพศ: %c, GPA: %.2f\n", 
               foundNode->studentName, 
               foundNode->studentAge, 
               foundNode->studentGender, 
               foundNode->studentGpa);
    } else {
        printf("ไม่พบข้อมูลนักเรียนชื่อนี้ครับ\n");
    }
}

void handleDeleteStudentProcess(StudentManager *managerSystem) {
    char searchName[20];
    printf("\nกรุณาใส่ชื่อนักเรียนที่ต้องการลบข้อมูล: ");
    scanf("%s", searchName);
    
    // โยนหน้าที่ลบให้คลาสจัดการ
    managerSystem->deleteStudentByName(searchName);
}

// ฟังก์ชันเซฟข้อมูลลงไฟล์แบบ Binary
void saveSystemDataToFile(StudentManager *managerSystem) {
    FILE *filePointer = fopen("student_data.dat", "wb");
    if (filePointer == NULL) {
        printf("เกิดปัญหาในการเปิดไฟล์เพื่อบันทึกครับ\n");
        return;
    }

    struct StudentDataNode *currentNode = managerSystem->getHeadPointer();
    
    // คำนวณขนาดของข้อมูลโดยไม่รวม Pointer
    size_t dataSize = sizeof(struct StudentDataNode) - sizeof(struct StudentDataNode*);

    // วนลูปเซฟทีละโหนด
    while (currentNode != NULL) {
        fwrite(currentNode, dataSize, 1, filePointer);
        currentNode = currentNode->nextNode;
    }

    fclose(filePointer);
    printf("\n--- สำรองข้อมูลลงไฟล์เรียบร้อยแล้ว ---\n");
}

// ฟังก์ชันโหลดข้อมูลจากไฟล์
void loadSystemDataFromFile(StudentManager *managerSystem) {
    FILE *filePointer = fopen("student_data.dat", "rb");
    if (filePointer == NULL) {
        return; // ถ้ายังไม่มีไฟล์ (เปิดโปรแกรมครั้งแรก) ให้ข้ามไป
    }

    struct StudentDataNode temporaryNode;
    size_t dataSize = sizeof(struct StudentDataNode) - sizeof(struct StudentDataNode*);

    // อ่านข้อมูลขึ้นมาทีละชุดจนกว่าจะหมดไฟล์
    while (fread(&temporaryNode, dataSize, 1, filePointer) == 1) {
        managerSystem->insertNewStudent(temporaryNode.studentName, 
                                        temporaryNode.studentAge, 
                                        temporaryNode.studentGender, 
                                        temporaryNode.studentGpa);
    }

    fclose(filePointer);
}

// =========================================================
// ฟังก์ชันควบคุมหลัก (Main Routine)
// =========================================================
int main() {
    // กำหนดให้ระบบรองรับภาษาไทย
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);

    // สร้างออบเจ็กต์จัดการนักเรียน
    StudentManager mainSystem;
    
    // โหลดไฟล์เริ่มต้น
    loadSystemDataFromFile(&mainSystem);

    int menuChoice = -1;

    // ลูปเมนูหลัก
    while (menuChoice != 0) {
        printf("\n============================\n");
        printf("เมนูระบบจัดการนักเรียน\n");
        printf("============================\n");
        printf("(1) เพิ่มข้อมูลนักเรียน\n");
        printf("(2) แก้ไขข้อมูล\n");
        printf("(3) ลบข้อมูล\n");
        printf("(4) ค้นหาข้อมูล\n");
        printf("(5) แสดงรายชื่อทั้งหมด\n");
        printf("(0) บันทึกและออกจากระบบ\n");
        printf("กรุณาเลือกเมนู: ");
        
        // ป้องกัน Error กรณีผู้ใช้พิมพ์ตัวอักษรแทนตัวเลข
        if (scanf("%d", &menuChoice) != 1) {
            while (getchar() != '\n'); // ล้างค่าในบัฟเฟอร์ทิ้ง
            menuChoice = -1;
            continue;
        }

        // แยกการทำงานตามเมนูที่เลือก (แตกโค้ดออกเป็น Helper methods แล้ว)
        switch (menuChoice) {
            case 1:
                handleAddStudentProcess(&mainSystem);
                break;
            case 2:
                handleEditStudentProcess(&mainSystem);
                break;
            case 3:
                handleDeleteStudentProcess(&mainSystem);
                break;
            case 4:
                handleFindStudentProcess(&mainSystem);
                break;
            case 5:
                mainSystem.displayAllStudents();
                break;
            case 0:
                printf("กำลังปิดระบบ...\n");
                break;
            default:
                printf("ตัวเลือกไม่ถูกต้อง กรุณาลองใหม่อีกครั้งครับ\n");
                break;
        }
    }

    // เซฟไฟล์ทุกครั้งก่อนปิดโปรแกรม
    saveSystemDataToFile(&mainSystem);

    return 0;
}