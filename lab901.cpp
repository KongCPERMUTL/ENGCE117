#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

struct StudentProfile {
    char studentName[20];
    int ageValue;
    char genderType;
    float gpaScore;
    struct StudentProfile* nextProfile;
};

class RegistrySystem {
private:
    struct StudentProfile* headPointer;

public:
    RegistrySystem() {
        headPointer = NULL;
    }

    ~RegistrySystem() {
        clearEntireList();
    }

    void clearEntireList() {
        struct StudentProfile* currentProfile;
        struct StudentProfile* temporaryProfile;

        currentProfile = headPointer;

        while (currentProfile != NULL) {
            temporaryProfile = currentProfile;
            currentProfile = currentProfile->nextProfile;
            delete temporaryProfile;
        }

        headPointer = NULL;
    }

    void insertNewProfile(char inputName[], int inputAge, char inputGender, float inputGpa) {
        struct StudentProfile* newProfile;
        newProfile = new struct StudentProfile;

        if (newProfile == NULL) {
            printf("System Memory Error.\n");
            return;
        }

        strncpy(newProfile->studentName, inputName, 19);
        newProfile->studentName[19] = '\0';
        newProfile->ageValue = inputAge;
        newProfile->genderType = inputGender;
        newProfile->gpaScore = inputGpa;
        newProfile->nextProfile = NULL;

        if (headPointer == NULL) {
            headPointer = newProfile;
            return;
        }

        appendAtTail(newProfile);
    }

    void appendAtTail(struct StudentProfile* newProfile) {
        struct StudentProfile* traversalPointer;
        traversalPointer = headPointer;

        while (traversalPointer->nextProfile != NULL) {
            traversalPointer = traversalPointer->nextProfile;
        }

        traversalPointer->nextProfile = newProfile;
    }

    struct StudentProfile* searchByStudentName(char targetName[]) {
        struct StudentProfile* currentProfile;
        currentProfile = headPointer;

        while (currentProfile != NULL) {
            if (strcmp(currentProfile->studentName, targetName) == 0) {
                return currentProfile;
            }
            currentProfile = currentProfile->nextProfile;
        }

        return NULL;
    }

    void removeProfileByName(char targetName[]) {
        if (headPointer == NULL) {
            printf("The registry is currently empty.\n");
            return;
        }

        if (strcmp(headPointer->studentName, targetName) == 0) {
            struct StudentProfile* temporaryProfile;
            temporaryProfile = headPointer;
            headPointer = headPointer->nextProfile;
            delete temporaryProfile;
            printf("Profile deleted successfully.\n");
            return;
        }

        struct StudentProfile* previousProfile;
        struct StudentProfile* currentProfile;

        previousProfile = headPointer;
        currentProfile = headPointer->nextProfile;

        while (currentProfile != NULL) {
            if (strcmp(currentProfile->studentName, targetName) == 0) {
                previousProfile->nextProfile = currentProfile->nextProfile;
                delete currentProfile;
                printf("Profile deleted successfully.\n");
                return;
            }
            previousProfile = currentProfile;
            currentProfile = currentProfile->nextProfile;
        }

        printf("Profile matching the name was not found.\n");
    }

    void displayAllProfiles() {
        struct StudentProfile* currentProfile;
        currentProfile = headPointer;

        printf("\n--- Registered Student Profiles ---\n");

        while (currentProfile != NULL) {
            printf("Name: %-10s | Age: %d | Gender: %c | GPA: %.2f\n",
                   currentProfile->studentName,
                   currentProfile->ageValue,
                   currentProfile->genderType,
                   currentProfile->gpaScore);
            currentProfile = currentProfile->nextProfile;
        }
    }

    struct StudentProfile* getFirstProfile() {
        return headPointer;
    }
};

void flushInputBuffer() {
    int bufferChar;
    bufferChar = getchar();
    
    while (bufferChar != '\n') {
        if (bufferChar == EOF) {
            break;
        }
        bufferChar = getchar();
    }
}

void processAddCommand(RegistrySystem* systemObject) {
    char inputName[20];
    int inputAge;
    char inputGender;
    float inputGpa;
    int readStatus;

    printf("\nEnter Student Name: ");
    scanf("%19s", inputName);

    printf("Enter Student Age: ");
    readStatus = scanf("%d", &inputAge);
    
    if (readStatus != 1) {
        inputAge = 0;
        flushInputBuffer();
    }

    printf("Enter Student Gender (M/F): ");
    scanf(" %c", &inputGender);

    printf("Enter Student GPA: ");
    readStatus = scanf("%f", &inputGpa);
    
    if (readStatus != 1) {
        inputGpa = 0.0f;
        flushInputBuffer();
    }

    systemObject->insertNewProfile(inputName, inputAge, inputGender, inputGpa);
    printf("Student added successfully.\n");
}

void processEditCommand(RegistrySystem* systemObject) {
    char targetName[20];
    struct StudentProfile* foundProfile;

    printf("\nEnter Name of the student to edit: ");
    scanf("%19s", targetName);

    foundProfile = systemObject->searchByStudentName(targetName);

    if (foundProfile == NULL) {
        printf("Student not found in the registry.\n");
        return;
    }

    char updatedName[20];
    int updatedAge;
    char updatedGender;
    float updatedGpa;
    int readStatus;

    printf("Enter Updated Name: ");
    scanf("%19s", updatedName);

    printf("Enter Updated Age: ");
    readStatus = scanf("%d", &updatedAge);
    
    if (readStatus != 1) {
        updatedAge = foundProfile->ageValue;
        flushInputBuffer();
    }

    printf("Enter Updated Gender (M/F): ");
    scanf(" %c", &updatedGender);

    printf("Enter Updated GPA: ");
    readStatus = scanf("%f", &updatedGpa);
    
    if (readStatus != 1) {
        updatedGpa = foundProfile->gpaScore;
        flushInputBuffer();
    }

    strncpy(foundProfile->studentName, updatedName, 19);
    foundProfile->studentName[19] = '\0';
    foundProfile->ageValue = updatedAge;
    foundProfile->genderType = updatedGender;
    foundProfile->gpaScore = updatedGpa;

    printf("Student profile updated successfully.\n");
}

void processDeleteCommand(RegistrySystem* systemObject) {
    char targetName[20];

    printf("\nEnter Name to delete: ");
    scanf("%19s", targetName);

    systemObject->removeProfileByName(targetName);
}

void processFindCommand(RegistrySystem* systemObject) {
    char targetName[20];
    struct StudentProfile* foundProfile;

    printf("\nEnter Name to search: ");
    scanf("%19s", targetName);

    foundProfile = systemObject->searchByStudentName(targetName);

    if (foundProfile != NULL) {
        printf("Record Found -> Name: %s, Age: %d, Gender: %c, GPA: %.2f\n",
               foundProfile->studentName,
               foundProfile->ageValue,
               foundProfile->genderType,
               foundProfile->gpaScore);
    } else {
        printf("Record not found.\n");
    }
}

void saveDatabaseToFile(RegistrySystem* systemObject) {
    FILE* filePointer;
    struct StudentProfile* currentProfile;
    size_t structureSize;

    filePointer = fopen("university_registry.dat", "wb");

    if (filePointer == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    currentProfile = systemObject->getFirstProfile();
    structureSize = sizeof(struct StudentProfile) - sizeof(struct StudentProfile*);

    while (currentProfile != NULL) {
        fwrite(currentProfile, structureSize, 1, filePointer);
        currentProfile = currentProfile->nextProfile;
    }

    fclose(filePointer);
    printf("\n--- Database Saved Successfully ---\n");
}

void loadDatabaseFromFile(RegistrySystem* systemObject) {
    FILE* filePointer;
    struct StudentProfile temporaryBuffer;
    size_t structureSize;
    size_t bytesRead;

    filePointer = fopen("university_registry.dat", "rb");

    if (filePointer == NULL) {
        return;
    }

    structureSize = sizeof(struct StudentProfile) - sizeof(struct StudentProfile*);
    bytesRead = fread(&temporaryBuffer, structureSize, 1, filePointer);

    while (bytesRead == 1) {
        systemObject->insertNewProfile(
            temporaryBuffer.studentName,
            temporaryBuffer.ageValue,
            temporaryBuffer.genderType,
            temporaryBuffer.gpaScore
        );
        bytesRead = fread(&temporaryBuffer, structureSize, 1, filePointer);
    }

    fclose(filePointer);
}

void displayMenuOptions() {
    printf("\n=== Student Registry System ===\n");
    printf("(1) Add Student Profile\n");
    printf("(2) Edit Student Profile\n");
    printf("(3) Delete Student Profile\n");
    printf("(4) Find Student Profile\n");
    printf("(5) Show All Profiles\n");
    printf("(0) Save and Exit\n");
    printf("Please select an option: ");
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    RegistrySystem mainSystem;
    int userChoice;
    int scanResult;

    loadDatabaseFromFile(&mainSystem);

    userChoice = -1;

    while (userChoice != 0) {
        displayMenuOptions();
        scanResult = scanf("%d", &userChoice);

        if (scanResult != 1) {
            flushInputBuffer();
            userChoice = -1;
            printf("Invalid input. Please enter a numerical value.\n");
            continue;
        }

        if (userChoice == 1) {
            processAddCommand(&mainSystem);
        } else if (userChoice == 2) {
            processEditCommand(&mainSystem);
        } else if (userChoice == 3) {
            processDeleteCommand(&mainSystem);
        } else if (userChoice == 4) {
            processFindCommand(&mainSystem);
        } else if (userChoice == 5) {
            mainSystem.displayAllProfiles();
        } else if (userChoice != 0) {
            printf("Command not recognized. Try again.\n");
        }
    }

    saveDatabaseToFile(&mainSystem);

    return 0;
}