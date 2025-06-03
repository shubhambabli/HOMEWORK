// decision.c
#include <stdio.h>
#include <math.h>

#define NUM_CATEGORIES 9
#define MIN_INDIVIDUAL_SCORE 1
#define MAX_SCORE 100
#define EXCELLENT_THRESHOLD 95
#define FINAL_REVIEW_THRESHOLD 90
#define RETAKE_THRESHOLD 80

// Enum for categories
typedef enum {
    PHYSICAL_STRENGTH, KNOWLEDGE, SELF_MANAGEMENT, TEAMWORK,
    KOREAN_LANGUAGE, VOCAL, DANCE, VISUAL, ACTING
} Category;

// Category names
const char *category_names[NUM_CATEGORIES] = {
    "Physical Strength", "Knowledge", "Self-Management", "Teamwork",
    "Korean Language", "Vocal", "Dance", "Visual", "Acting"
};

// Function to get the fate of the group
void determine_fate(int scores[NUM_CATEGORIES]) {
    int total = 0;
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        total += scores[i];
    }

    int avg = total / NUM_CATEGORIES;

    if (avg < MIN_INDIVIDUAL_SCORE) {
        printf("Minimum individual score is %d.\n", MIN_INDIVIDUAL_SCORE);
        printf("The entire team must retake the category.\n");
        return;
    }

    if (total >= EXCELLENT_THRESHOLD) {
        printf("Congratulations! Your stage debut is confirmed!\n");
    } else if (total >= FINAL_REVIEW_THRESHOLD) {
        printf("The Debut Certification Team will hold a final evaluation meeting to make a decision.\n");
    } else if (total >= RETAKE_THRESHOLD) {
        // Find the 3 lowest scoring categories
        int idx1 = -1, idx2 = -1, idx3 = -1;
        for (int i = 0; i < NUM_CATEGORIES; i++) {
            if (idx1 == -1 || scores[i] < scores[idx1]) {
                idx3 = idx2;
                idx2 = idx1;
                idx1 = i;
            } else if (idx2 == -1 || scores[i] < scores[idx2]) {
                idx3 = idx2;
                idx2 = i;
            } else if (idx3 == -1 || scores[i] < scores[idx3]) {
                idx3 = i;
            }
        }
        printf("Retake the three lowest-scoring categories (%s, %s, %s) after 30 days.\n",
               category_names[idx1], category_names[idx2], category_names[idx3]);
    } else {
        printf("The entire team must retake the training.\n");
    }
}

int main() {
    int scores[NUM_CATEGORIES];

    // Prompt user to enter scores
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        int input;
        printf("Enter score for %s (0-%d): ", category_names[i], MAX_SCORE);
        scanf("%d", &input);

        // Check for invalid input
        if (input < MIN_INDIVIDUAL_SCORE) {
            printf("Minimum individual score is %d.\n", MIN_INDIVIDUAL_SCORE);
            printf("The entire team must retake the category.\n");
            return 0;
        }

        // Cap the score if needed
        if (input > MAX_SCORE) {
            input = MAX_SCORE;
        }

        scores[i] = input;
    }

    determine_fate(scores);

    return 0;
}
