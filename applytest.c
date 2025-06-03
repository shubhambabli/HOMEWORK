#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CATEGORY_COUNT 9
#define MAX_SCHEDULES 9

const char categories[CATEGORY_COUNT][20] = {
    "Physical Strength", "Knowledge", "Self-Management", "Teamwork",
    "Korean Language", "Vocal", "Dance", "Visual", "Acting"
};

int scheduled_dates[MAX_SCHEDULES] = {0};  /* Stores exam dates */
int completed[CATEGORY_COUNT] = {0};       /* Marks passed exams */
int training_start;

int date_to_days(int yyyymmdd) {
    int yyyy = yyyymmdd / 10000;
    int mm = (yyyymmdd / 100) % 100;
    int dd = yyyymmdd % 100;
    return yyyy * 365 + mm * 30 + dd;  /* Simplified date to days */
}

int is_order_valid(int index) {
    if (index == 0 || index == 1) return 1;
    if (index == 2 || index == 3)
        return completed[0] && completed[1];
    return completed[2] && completed[3];
}

void show_reminder(int today) {
    int i, days_left;
    for (i = 0; i < CATEGORY_COUNT; i++) {
        if (scheduled_dates[i] == 0) continue;
        days_left = date_to_days(scheduled_dates[i]) - date_to_days(today);
        if (days_left > 0 && days_left <= 10) {
            printf("Reminder: '%s' exam is in %d days!\n", categories[i], days_left);
        }
    }
}

void assign_room_if_exam_today(int today) {
    int i, room;
    for (i = 0; i < CATEGORY_COUNT; i++) {
        if (scheduled_dates[i] == today) {
            srand(today);  /* Seed for randomness */
            room = rand() % 10 + 1;
            printf("Today is exam day for '%s'. Assigned Room: %d\n", categories[i], room);
        }
    }
}

int main() {
    int today, choice, exam_date, i, diff;

    printf("Enter today's date (YYYYMMDD): ");
    scanf("%d", &today);

    printf("Enter training start date (YYYYMMDD): ");
    scanf("%d", &training_start);

    show_reminder(today);
    assign_room_if_exam_today(today);

    while (1) {
        printf("\nSelect category to schedule exam (-1 to exit):\n");
        for (i = 0; i < CATEGORY_COUNT; i++) {
            printf("%d. %s\n", i, categories[i]);
        }
        scanf("%d", &choice);
        if (choice == -1) break;

        if (choice < 0 || choice >= CATEGORY_COUNT) {
            printf("Invalid category.\n");
            continue;
        }

        if (!is_order_valid(choice)) {
            printf("You must complete prior certifications first.\n");
            continue;
        }

        printf("Enter exam date for '%s' (YYYYMMDD): ", categories[choice]);
        scanf("%d", &exam_date);

        diff = date_to_days(exam_date) - date_to_days(training_start);
        if (diff < 30 || diff > 100) {
            printf("Exam must be between 30 and 100 days from training start.\n");
            continue;
        }

        scheduled_dates[choice] = exam_date;
        completed[choice] = 1;
        printf("Exam for '%s' scheduled on %d\n", categories[choice], exam_date);
    }

    return 0;
}
