#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10
#define DAYS_IN_WEEK 7
#define NAME_LENGTH 30
#define FOOD_ITEM_LENGTH 50

// Days of the week
const char *days[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

// Structures
typedef struct {
    char name[NAME_LENGTH];
    float height;
    float weight;
} PhysicalCondition;

typedef struct {
    char workout[DAYS_IN_WEEK][100];
} WorkoutRoutine;

typedef struct {
    char diet[DAYS_IN_WEEK][FOOD_ITEM_LENGTH];
    int calories[DAYS_IN_WEEK];
    int isVegan;  // 1 for vegan, 0 for not
} DietPlan;

// Data Arrays
PhysicalCondition physicalConditions[MAX_MEMBERS];
WorkoutRoutine workoutRoutines[MAX_MEMBERS];
DietPlan dietPlans[MAX_MEMBERS];
int memberCount = 0;

// Helper Functions
int findMemberIndex(const char *name) {
    for (int i = 0; i < memberCount; i++) {
        if (strcmp(physicalConditions[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// Menu Functions
void enterPhysicalCondition() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Member list is full.\n");
        return;
    }

    printf("Enter member name: ");
    scanf("%s", physicalConditions[memberCount].name);
    printf("Enter height (cm): ");
    scanf("%f", &physicalConditions[memberCount].height);
    printf("Enter weight (kg): ");
    scanf("%f", &physicalConditions[memberCount].weight);
    memberCount++;
    printf("Physical condition saved.\n");
}

void viewPhysicalCondition() {
    char name[NAME_LENGTH];
    printf("Enter member name to view: ");
    scanf("%s", name);

    int index = findMemberIndex(name);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Name: %s\n", physicalConditions[index].name);
    printf("Height: %.2f cm\n", physicalConditions[index].height);
    printf("Weight: %.2f kg\n", physicalConditions[index].weight);
}

void setWorkoutRoutine() {
    char name[NAME_LENGTH];
    printf("Enter member name to set workout: ");
    scanf("%s", name);

    int index = findMemberIndex(name);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("Enter workout for %s: ", days[i]);
        scanf(" %[^\n]", workoutRoutines[index].workout[i]);
    }
    printf("Workout routine set.\n");
}

void viewWorkoutRoutine() {
    char name[NAME_LENGTH];
    printf("Enter member name to view workout: ");
    scanf("%s", name);

    int index = findMemberIndex(name);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s: %s\n", days[i], workoutRoutines[index].workout[i]);
    }
}

void setDietPlan() {
    char name[NAME_LENGTH];
    printf("Enter member name to set diet: ");
    scanf("%s", name);

    int index = findMemberIndex(name);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Is the member vegan? (1: Yes, 0: No): ");
    scanf("%d", &dietPlans[index].isVegan);

    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("Enter food for %s: ", days[i]);
        scanf(" %[^\n]", dietPlans[index].diet[i]);
        printf("Enter calories for %s: ", days[i]);
        scanf("%d", &dietPlans[index].calories[i]);
    }
    printf("Diet plan set.\n");
}

void viewDietPlan() {
    char name[NAME_LENGTH];
    printf("Enter member name to view diet: ");
    scanf("%s", name);

    int index = findMemberIndex(name);
    if (index == -1) {
        printf("Member not found.\n");
        return;
    }

    printf("Diet Plan for %s (%s)\n", name, dietPlans[index].isVegan ? "Vegan" : "Not Vegan");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s: %s (%d cal)\n", days[i], dietPlans[index].diet[i], dietPlans[index].calories[i]);
    }
}

// Main Menu
void displayMenu() {
    printf("\n=== Millieway’s Health Management System ===\n");
    printf("1. Enter Physical Condition\n");
    printf("2. View Physical Condition\n");
    printf("3. Set Workout Routine\n");
    printf("4. View Workout Routine\n");
    printf("5. Set Diet Plan\n");
    printf("6. View Diet Plan\n");
    printf("0. Exit\n");
    printf("Select an option: ");
}

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: enterPhysicalCondition(); break;
            case 2: viewPhysicalCondition(); break;
            case 3: setWorkoutRoutine(); break;
            case 4: viewWorkoutRoutine(); break;
            case 5: setDietPlan(); break;
            case 6: viewDietPlan(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
