#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CANDIDATES 6
#define NUM_CATEGORIES 5

typedef struct {
    char name[50];
    int id;
} Candidate;

typedef struct {
    int judge_id;
    int scores[NUM_CATEGORIES];
    int total_score;
} ScoringSheet;

void inputScores(ScoringSheet *sheet, Candidate candidates[]);
void reviewScores(ScoringSheet sheets[], Candidate candidates[]);
void modifyScores(ScoringSheet sheets[], Candidate candidates[]);
void displayFinalSelection(ScoringSheet sheets[], Candidate candidates[]);

int main() {
    Candidate candidates[NUM_CANDIDATES] = {
        {"Jiyeon Park", 123456},
        {"Ethan Smith", 234567},
        {"Helena Silva", 345678},
        {"Liam Wilson", 456789},
        {"Alex Johnson", 567890},
        {"Mina Lee", 678901}
    };

    ScoringSheet sheets[NUM_CANDIDATES];
    
    printf("####################################\n");
    printf("#     Audition Evaluation Entry    #\n");
    printf("####################################\n");

    inputScores(sheets, candidates);
    reviewScores(sheets, candidates);

    char choice;
    printf("Would you like to submit? (Y/N): ");
    scanf(" %c", &choice);

    if (choice == 'N' || choice == 'n') {
        modifyScores(sheets, candidates);
    }

    displayFinalSelection(sheets, candidates);

    return 0;
}

void inputScores(ScoringSheet *sheet, Candidate candidates[]) {
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("Candidate: %s\n", candidates[i].name);
        sheet[i].judge_id = candidates[i].id;
        sheet[i].total_score = 0;

        for (int j = 0; j < NUM_CATEGORIES; j++) {
            int score;
            do {
                printf("Enter score for category %d (10-100): ", j + 1);
                scanf("%d", &score);
                if (score < 10 || score > 100) {
                    printf("Invalid score! Please enter a valid value.\n");
                }
            } while (score < 10 || score > 100);

            sheet[i].scores[j] = score;
            sheet[i].total_score += score;
        }
        printf("------------------------------------\n");
    }
}

void reviewScores(ScoringSheet sheets[], Candidate candidates[]) {
    printf("\nSubmission completed. Please review your input!\n");
    for (int i = 0; i < NUM_CANDIDATES; i++) {
        printf("%s: Total Score = %d\n", candidates[i].name, sheets[i].total_score);
    }
}

void modifyScores(ScoringSheet sheets[], Candidate candidates[]) {
    int id;
    printf("Enter Candidate ID to modify scores: ");
    scanf("%d", &id);

    for (int i = 0; i < NUM_CANDIDATES; i++) {
        if (candidates[i].id == id) {
            sheets[i].total_score = 0;
            printf("Modifying scores for %s:\n", candidates[i].name);
            
            for (int j = 0; j < NUM_CATEGORIES; j++) {
                int score;
                do {
                    printf("Enter new score for category %d (10-100): ", j + 1);
                    scanf("%d", &score);
                    if (score < 10 || score > 100) {
                        printf("Invalid score! Please enter a valid value.\n");
                    }
                } while (score < 10 || score > 100);

                sheets[i].scores[j] = score;
                sheets[i].total_score += score;
            }
            printf("Modification completed.\n");
            return;
        }
    }
    printf("Candidate ID not found.\n");
}

void displayFinalSelection(ScoringSheet sheets[], Candidate candidates[]) {
    printf("\n=======================================\n");
    printf("Compiling final selection results...\n");
    printf("=======================================\n");
    printf("###########################################\n");
    printf("# Congratulations! Welcome to Milliways!  #\n");
    printf("###########################################\n");

    // Sorting by total scores in descending order
    for (int i = 0; i < NUM_CANDIDATES - 1; i++) {
        for (int j = i + 1; j < NUM_CANDIDATES; j++) {
            if (sheets[i].total_score < sheets[j].total_score) {
                ScoringSheet temp = sheets[i];
                sheets[i] = sheets[j];
                sheets[j] = temp;
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
}