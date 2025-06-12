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

typedef struct {
    char keyword[10];
    char message[512];
} ArthurEasterEgg;

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

ArthurEasterEgg arthur = {
    "specter",
    "I confess. After graduating from university, I was blinded by the arrogance of starting a startup and recklessly blocked my friends' paths. I painfully learned that when I am the only one convinced by my idea, it leads to disastrous results. The past Arthur was a ghost of dogmatism and stubbornness."
};

// Function Prototypes
void traumaMenu();
void inputTrauma();
void counselingMenu();
void overcomeTrauma();
int findMemberIndex(const char* nickname);
void displayCounselingSummary();
void find_easter_egg();
int isRightChar(const char*, const char*);
int isEasterEgg(const char*);
void toBinary(char, char*);

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
    char input[30];
    while (1) {
        printf("\n-- Trauma Management Menu --\n");
        printf("1. Input Trauma\n");
        printf("2. Start Counseling Session\n");
        printf("3. View Counseling Summary\n");
        printf("0. Exit\n");
        printf("Select an option or enter 'Arthur': ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "Arthur") == 0) {
            find_easter_egg();
        } else {
            choice = atoi(input);
            switch (choice) {
                case 1: inputTrauma(); break;
                case 2: counselingMenu(); break;
                case 3: displayCounselingSummary(); break;
                case 0: return;
                default: printf("Invalid option. Try again.\n");
            }
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

void toBinary(char ch, char* bin) {
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = (ch & (1 << i)) ? '1' : '0';
    }
    bin[8] = '\0';
}

int isRightChar(const char* binary, const char* input) {
    for (int i = 0; i < 7; i++) {
        char bin[9];
        toBinary(arthur.keyword[6 - i], bin);
        if (input[i] != arthur.keyword[6 - i]) {
            return 0;
        }
    }
    return 1;
}

int isEasterEgg(const char* word) {
    return strcmp(word, arthur.keyword) == 0;
}

void find_easter_egg() {
    char inputChars[10];
    char word[10];

    printf("\n<<Arthur's Easter Egg>>\n");
    printf("Reversed Binary of keyword: \n");
    for (int i = 6; i >= 0; i--) {
        char bin[9];
        toBinary(arthur.keyword[i], bin);
        printf("%s ", bin);
    }
    printf("\n\nEnter each character (7 total): ");
    fgets(inputChars, sizeof(inputChars), stdin);
    inputChars[strcspn(inputChars, "\n")] = 0;

    if (!isRightChar(NULL, inputChars)) {
        printf("Incorrect characters. Try again.\n");
        return;
    }

    printf("\nNow enter the combined word: ");
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = 0;

    if (isEasterEgg(word)) {
        printf("\n##Easter Egg Discovered!$$\n");
        printf("%s\n", arthur.message);
    } else {
        printf("Incorrect word. Returning to menu.\n");
    }
}

void overcomeTrauma() {
    traumaMenu();
}

int main() {
    overcomeTrauma();
    return 0;
}

