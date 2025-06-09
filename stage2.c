#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRAINEES 8
#define MAX_NAME_LEN 30
#define MAX_MENTORS 8

// Structs
typedef struct {
    char nickname[MAX_NAME_LEN];
    int nicknameValue;
    int ability;
} Trainee;

typedef struct {
    int id;  // 1~8
    char name[MAX_NAME_LEN];
    int menteeIndex; // Index of trainee
} Mentor;

// Global Arrays
Trainee trainees[MAX_TRAINEES];
Mentor mentors[MAX_MENTORS];
int traineeCount = 0;
int mentorCount = 0;

// Function Prototypes
int parseIntMember(const char *nickname);
int getRandomAbility();
void initTrainees();
void inputMentors();
void matchMentoring();
void printMentoring();

// Function Definitions
int parseIntMember(const char *nickname) {
    int sum = 0;
    for (int i = 0; nickname[i] != '\0'; i++) {
        sum += (int)nickname[i];
    }
    return sum;
}

int getRandomAbility() {
    return rand() % 901 + 100; // Range: 100–1000
}

void initTrainees() {
    const char *names[MAX_TRAINEES] = {
        "Leo", "Mina", "Juno", "Yuna",
        "Kai", "Haru", "Nari", "Sora"
    };

    for (int i = 0; i < MAX_TRAINEES; i++) {
        strncpy(trainees[i].nickname, names[i], MAX_NAME_LEN);
        trainees[i].nicknameValue = parseIntMember(names[i]);
        trainees[i].ability = getRandomAbility();
    }

    traineeCount = MAX_TRAINEES;
    printf("Trainees initialized.\n");
}

void inputMentors() {
    char input[MAX_NAME_LEN];
    printf("Enter up to %d mentor names:\n", MAX_MENTORS);

    for (int i = 0; i < MAX_MENTORS; i++) {
        printf("Mentor %d name: ", i + 1);
        scanf("%s", input);

        mentors[i].id = i + 1;
        strncpy(mentors[i].name, input, MAX_NAME_LEN);
        mentors[i].menteeIndex = -1;
        mentorCount++;
    }
}

void matchMentoring() {
    if (mentorCount < MAX_MENTORS || traineeCount < MAX_TRAINEES) {
        printf("Ensure both mentors and trainees are fully registered (8 each).\n");
        return;
    }

    int usedMentees[MAX_TRAINEES] = {0};

    for (int i = 0; i < MAX_MENTORS; i++) {
        int found = 0;
        for (int j = 0; j < MAX_TRAINEES; j++) {
            if (!usedMentees[j] && (j % MAX_MENTORS == mentors[i].id % MAX_MENTORS)) {
                mentors[i].menteeIndex = j;
                usedMentees[j] = 1;
                found = 1;
                break;
            }
        }

        // If no mentee with same remainder, assign first available
        if (!found) {
            for (int j = 0; j < MAX_TRAINEES; j++) {
                if (!usedMentees[j]) {
                    mentors[i].menteeIndex = j;
                    usedMentees[j] = 1;
                    break;
                }
            }
        }
    }

    printf("Mentoring matched (1:1).\n");
}

void printMentoring() {
    printf("\n=== Mentoring Results ===\n");
    for (int i = 0; i < MAX_MENTORS; i++) {
        int menteeIdx = mentors[i].menteeIndex;
        if (menteeIdx >= 0 && menteeIdx < MAX_TRAINEES) {
            printf("Trainee #%d (%s) matched with Mentor #%d (%s)\n",
                   menteeIdx + 1, trainees[menteeIdx].nickname,
                   mentors[i].id, mentors[i].name);
        } else {
            printf("Mentor #%d (%s) has no mentee assigned.\n", mentors[i].id, mentors[i].name);
        }
    }
    printf("=========================\n");
}

// Menu
void displayMenu() {
    printf("\n=== Mentoring System Menu ===\n");
    printf("1. Initialize Trainee List\n");
    printf("2. Input Mentor List\n");
    printf("3. Match Mentoring\n");
    printf("4. Show Mentoring Results\n");
    printf("0. Exit\n");
    printf("Select an option: ");
}

int main() {
    srand((unsigned int)time(NULL));

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: initTrainees(); break;
            case 2: inputMentors(); break;
            case 3: matchMentoring(); break;
            case 4: printMentoring(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
