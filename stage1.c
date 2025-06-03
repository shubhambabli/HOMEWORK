#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TRAINING_STAGES 8
#define MAX_MAIN_MENU_ITEMS 3

// Menu titles stored as 1D arrays (simulate 2D via arrays of strings)
const char *mainMenu[MAX_MAIN_MENU_ITEMS] = {
    "I. Audition Management",
    "II. Training",
    "III. Debut"
};

const char *trainingMenu[MAX_TRAINING_STAGES] = {
    "1. Physical Strength & Knowledge",
    "2. Self-Management & Teamwork",
    "3. Language & Pronunciation",
    "4. Vocal",
    "5. Dance",
    "6. Visual & Image",
    "7. Acting & Stage Performance",
    "8. Fan Communication"
};

// Evaluation results: ' ' = not attempted, 'P' = passed, 'F' = failed
char stageResults[MAX_TRAINING_STAGES] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

// Function declarations
void showMainMenu();
void handleTrainingMenu();
void evaluateStage(int stageIndex);

int main() {
    char input[10];

    while (1) {
        showMainMenu();
        printf("Select menu (1-3 or Q to quit): ");
        fgets(input, sizeof(input), stdin);

        // Exit conditions
        if (input[0] == '0' || input[0] == '\n' ||
            input[0] == 'q' || input[0] == 'Q') {
            printf("Exiting program.\n");
            break;
        }

        switch (input[0]) {
            case '1':
                printf("Entering Audition Management...\n");
                break;
            case '2':
                handleTrainingMenu();
                break;
            case '3':
                printf("Entering Debut...\n");
                break;
            default:
                printf("Invalid input. Try again.\n");
        }
    }

    return 0;
}

// Show Main Menu
void showMainMenu() {
    printf("\n=== Main Menu ===\n");
    for (int i = 0; i < MAX_MAIN_MENU_ITEMS; i++) {
        printf("%s\n", mainMenu[i]);
    }
}

// Handle Training Menu
void handleTrainingMenu() {
    char input[10];

    while (1) {
        printf("\n=== Training Menu ===\n");
        for (int i = 0; i < MAX_TRAINING_STAGES; i++) {
            printf("%s [%c]\n", trainingMenu[i], stageResults[i]);
        }

        printf("Select training stage (1-8), B to go back, or Q to quit: ");
        fgets(input, sizeof(input), stdin);

        if (input[0] == 'q' || input[0] == 'Q') {
            printf("Exiting program.\n");
            exit(0);
        } else if (input[0] == 'b' || input[0] == 'B') {
            return;
        }

        int stage = input[0] - '0';
        if (stage < 1 || stage > 8) {
            printf("Invalid stage. Try again.\n");
            continue;
        }

        int index = stage - 1;

        // Check if stage already completed
        if (stageResults[index] == 'P') {
            printf("This stage has already been passed. Cannot retake.\n");
            continue;
        }

        // Enforce stage order rules
        if (index > 0 && stageResults[index - 1] != 'P' && index < 2) {
            printf("You must pass stage %d first.\n", index);
            continue;
        } else if (index >= 2 && (stageResults[0] != 'P' || stageResults[1] != 'P')) {
            printf("Stages 1 and 2 must be passed before accessing stages 3 to 8.\n");
            continue;
        }

        evaluateStage(index);
    }
}

// Evaluate a stage
void evaluateStage(int stageIndex) {
    char input[10];
    printf("Would you like to enter the evaluation result? (Y/N): ");
    fgets(input, sizeof(input), stdin);
    if (input[0] == 'Y' || input[0] == 'y') {
        printf("Did you complete the training and pass the certification? (P/F): ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'P' || input[0] == 'p') {
            stageResults[stageIndex] = 'P';
            printf("Stage %d marked as passed.\n", stageIndex + 1);
        } else if (input[0] == 'F' || input[0] == 'f') {
            stageResults[stageIndex] = 'F';
            printf("Stage %d marked as failed.\n", stageIndex + 1);
        } else {
            printf("Invalid input. Returning to training menu.\n");
        }
    } else {
        printf("Returning to training menu.\n");
    }
}
