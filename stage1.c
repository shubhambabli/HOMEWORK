#include <stdio.h>
#include <string.h>

#define MAX_MEMBERS 10
#define MAX_DAYS 7

// Member names (from Problem 6 of Assignment 1 or placeholders)
char *members[MAX_MEMBERS] = {
    "Alice", "Bob", "Charlie", "Diana", "Eve",
    "Frank", "Grace", "Heidi", "Ivan", "Judy"
};

// Days of the week
const char *days[MAX_DAYS] = {
    "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

// Structures
typedef struct {
    float height;  // in cm
    float weight;  // in kg
    int age;
} PhysicalCondition;

typedef struct {
    char routine[MAX_DAYS][100];  // Workout per day
} WorkoutPlan;

typedef struct {
    char meals[MAX_DAYS][100];    // Meal per day
} DietPlan;

// Global arrays
PhysicalCondition physical_conditions[MAX_MEMBERS];
WorkoutPlan workout_plans[MAX_MEMBERS];
DietPlan diet_plans[MAX_MEMBERS];

// Function declarations
void show_menu();
void enter_physical_condition(int index);
void view_physical_condition(int index);
void set_workout_routine(int index);
void view_workout_routine(int index);
void set_diet_plan(int index);
void view_diet_plan(int index);

int main() {
    int choice, member;

    while (1) {
        show_menu();
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Exiting program.\n");
            break;
        }

        printf("Select member index (0 to %d): ", MAX_MEMBERS - 1);
        scanf("%d", &member);
        if (member < 0 || member >= MAX_MEMBERS) {
            printf("Invalid member index. Try again.\n");
            continue;
        }

        switch (choice) {
            case 1:
                enter_physical_condition(member);
                break;
            case 2:
                view_physical_condition(member);
                break;
            case 3:
                set_workout_routine(member);
                break;
            case 4:
                view_workout_routine(member);
                break;
            case 5:
                set_diet_plan(member);
                break;
            case 6:
                view_diet_plan(member);
                break;
            default:
                printf("Invalid menu choice. Try again.\n");
        }
    }

    return 0;
}

// Menu display
void show_menu() {
    printf("\n=== Millieway’s Health Manager ===\n");
    printf("1. Enter Physical Condition\n");
    printf("2. View Physical Condition\n");
    printf("3. Set Workout Routine\n");
    printf("4. View Workout Routine\n");
    printf("5. Set Diet Plan\n");
    printf("6. View Diet Plan\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

// Physical Condition Functions
void enter_physical_condition(int index) {
    printf("Enter height (cm): ");
    scanf("%f", &physical_conditions[index].height);
    printf("Enter weight (kg): ");
    scanf("%f", &physical_conditions[index].weight);
    printf("Enter age: ");
    scanf("%d", &physical_conditions[index].age);
    printf("Physical condition updated for %s.\n", members[index]);
}

void view_physical_condition(int index) {
    printf("\n--- %s's Physical Condition ---\n", members[index]);
    printf("Height: %.1f cm\n", physical_conditions[index].height);
    printf("Weight: %.1f kg\n", physical_conditions[index].weight);
    printf("Age   : %d\n", physical_conditions[index].age);
}

// Workout Plan Functions
void set_workout_routine(int index) {
    printf("\n--- Set Workout Routine for %s ---\n", members[index]);
    for (int i = 0; i < MAX_DAYS; i++) {
        printf("Enter workout for %s: ", days[i]);
        scanf(" %[^\n]", workout_plans[index].routine[i]);
    }
    printf("Workout routine saved for %s.\n", members[index]);
}

void view_workout_routine(int index) {
    printf("\n--- %s's Workout Routine ---\n", members[index]);
    for (int i = 0; i < MAX_DAYS; i++) {
        printf("%s: %s\n", days[i], workout_plans[index].routine[i]);
    }
}

// Diet Plan Functions
void set_diet_plan(int index) {
    printf("\n--- Set Diet Plan for %s ---\n", members[index]);
    for (int i = 0; i < MAX_DAYS; i++) {
        printf("Enter meal for %s: ", days[i]);
        scanf(" %[^\n]", diet_plans[index].meals[i]);
    }
    printf("Diet plan saved for %s.\n", members[index]);
}

void view_diet_plan(int index) {
    printf("\n--- %s's Diet Plan ---\n", members[index]);
    for (int i = 0; i < MAX_DAYS; i++) {
        printf("%s: %s\n", days[i], diet_plans[index].meals[i]);
    }
}
