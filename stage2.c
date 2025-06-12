#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MEMBERS 10
#define MAX_TRAUMA_LEN 256
#define MAX_RESPONSE_LEN 100
#define MAX_QUESTIONS 5
#define MAX_COUNSELING 30

// Struct Definitions
typedef struct {
    char nickname[30];
    int age;
    char trauma[MAX_TRAUMA_LEN];
} Trauma;

typedef struct {
    int id;
    char content[150];
} Question;

typedef struct {
    char nickname[30];
    char question[150];
    char response[MAX_RESPONSE_LEN + 1];
} CounselingResponse;

// Global Arrays
Trauma traumaList[MAX_MEMBERS] = {
    {"Luna", 19, ""},
    {"Kai", 20, ""},
    {"Mina", 18, ""},
    {"Jin", 21, ""},
    {"Sora", 22, ""}
};

const Question questionList[MAX_QUESTIONS] = {
    {1, "In what situations have you experienced this trauma?"},
    {2, "How has this situation affected your daily life and emotions?"},
    {3, "How have you tried to overcome this trauma?"},
    {4, "What emotions do you associate with this trauma?"},
    {5, "What kind of support do you think is necessary to overcome this trauma?"}
};

CounselingResponse counselingData[MAX_COUNSELING];
int counselingCount = 0;

// Function Prototypes
void traumaMenu();
void inputTrauma();
void counselingMenu();
void overcomeTrauma();
int findMemberIndex(const char* nickname);
void displayCounselingSummary();

// Helper Function: Find index of a nickname in trauma list
int findMemberIndex(const char* nickname) {
    for (int i = 0; i < MAX_MEMBERS; ++i) {
        if (strcmp(traumaList[i].nickname, nickname) == 0) {
            return i;
        }
    }
    return -1;
}

void traumaMenu() {
    int choice;
    while (1) {
        printf("\n-- Trauma Management Menu --\n");
        printf("1. Input Trauma\n");
        printf("2. Start Counseling Session\n");
        printf("3. View Counseling Summary\n");
        printf("0. Exit\n");
        printf("Select an option: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: inputTrauma(); break;
            case 2: counselingMenu(); break;
            case 3: displayCounselingSummary(); break;
            case 0: return;
            default: printf("Invalid option. Try again.\n");
        }
    }
}

void inputTrauma() {
    char nickname[30];
    char trauma[MAX_TRAUMA_LEN];

    while (1) {
        printf("\nEnter nickname (or type 'exit' to return): ");
        fgets(nickname, sizeof(nickname), stdin);
        nickname[strcspn(nickname, "\n")] = 0;

        if (strcmp(nickname, "exit") == 0) break;

        int index = findMemberIndex(nickname);
        (index != -1) ? (
            printf("Enter trauma description: "),
            fgets(trauma, sizeof(trauma), stdin),
            trauma[strcspn(trauma, "\n")] = 0,
            strcpy(traumaList[index].trauma, trauma),
            printf("Trauma saved for %s.\n", nickname))
        : printf("Nickname not found. Try again.\n");
    }
}

void counselingMenu() {
    char nickname[30];
    int index;
    int asked[3] = {-1, -1, -1};
    srand((unsigned int)time(NULL));

    printf("\nAvailable members with trauma entries:\n");
    for (int i = 0; i < MAX_MEMBERS; ++i) {
        if (strlen(traumaList[i].trauma) > 0) {
            printf("- %s\n", traumaList[i].nickname);
        }
    }

    printf("Enter nickname to start session: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    index = findMemberIndex(nickname);
    if (index == -1 || strlen(traumaList[index].trauma) == 0) {
        printf("Invalid or no trauma entry for nickname.\n");
        return;
    }

    for (int i = 0; i < 3; ++i) {
        int q;
        do {
            q = rand() % MAX_QUESTIONS;
        } while (q == asked[0] || q == asked[1]);
        asked[i] = q;

        char response[MAX_RESPONSE_LEN + 2];
        printf("\nQ%d: %s\n", questionList[q].id, questionList[q].content);
        while (1) {
            printf("Your response (max 100 characters): ");
            fgets(response, sizeof(response), stdin);
            response[strcspn(response, "\n")] = 0;

            if (strlen(response) == 0 || strlen(response) > MAX_RESPONSE_LEN) {
                printf("Invalid input. Please enter again.\n");
            } else {
                CounselingResponse cr;
                strcpy(cr.nickname, nickname);
                strcpy(cr.question, questionList[q].content);
                strcpy(cr.response, response);
                counselingData[counselingCount++] = cr;
                break;
            }
        }
    }
    printf("Counseling session for %s completed.\n", nickname);
}

void displayCounselingSummary() {
    char nickname[30];
    printf("\nEnter nickname to view counseling summary: ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    int index = findMemberIndex(nickname);
    if (index == -1) {
        printf("Nickname not found.\n");
        return;
    }

    printf("\n--- Counseling Summary for %s ---\n", nickname);
    printf("Trauma: %s\n", traumaList[index].trauma);

    for (int i = 0; i < counselingCount; ++i) {
        if (strcmp(counselingData[i].nickname, nickname) == 0) {
            printf("\nQ: %s\nA: %s\n", counselingData[i].question, counselingData[i].response);
        }
    }
}

void overcomeTrauma() {
    traumaMenu();
}

// Main Entry Point for Testing
int main() {
    overcomeTrauma();
    return 0;
}
