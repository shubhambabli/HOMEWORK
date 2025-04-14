#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JUDGES 100
#define MAX_LENGTH 1024

int count_commas(const char *str) {
    int count = 0;
    while (*str) {
        if (*str == ',') count++;
        str++;
    }
    return count;
}

int main() {
    char project_name[100];
    int total_judges, selected_members;
    char judges_array[MAX_JUDGES][MAX_LENGTH];

    printf("####################################\n");
    printf("#      Judge List Data Entry      #\n");
    printf("####################################\n");

    printf("Participating Project: ");
    fgets(project_name, sizeof(project_name), stdin);
    project_name[strcspn(project_name, "\n")] = 0;

    printf("Total Number of Judges: ");
    scanf("%d", &total_judges);
    printf("Number of Selected Members: ");
    scanf("%d", &selected_members);
    getchar(); // clear newline

    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Starting to input information for %d judges.\n", total_judges);
    printf("++++++++++++++++++++++++++++++++++++\n");

    for (int i = 0; i < total_judges; i++) {
        while (1) {
            printf("Judge %d: ", i + 1);
            fgets(judges_array[i], MAX_LENGTH, stdin);
            judges_array[i][strcspn(judges_array[i], "\n")] = 0;

            if (count_commas(judges_array[i]) != 6) {
                printf("The input items are incorrect. Please enter them again.\n");
            } else {
                break;
            }
        }
    }

    char choice;
    printf("++++++++++++++++++++++++++++++++++++\n");
    printf("Judge information entry is complete.\n");
    printf("++++++++++++++++++++++++++++++++++++\n");

    printf("\"%s\" Should we check the judge information? ", project_name);
    scanf(" %c", &choice);

    if (choice == 'Y') {
        printf("####################################\n");
        printf("#        Display Judge Data        #\n");
        printf("####################################\n");

        for (int i = 0; i < total_judges; i++) {
            printf("[Judge %d]\n", i + 1);

            char *token = strtok(judges_array[i], ",");
            const char *fields[] = {"Name", "Gender", "Affiliation", "Title", "Expertise", "Email", "Phone"};
            int j = 0;

            while (token != NULL && j < 7) {
                while (*token == ' ') token++; // remove leading space
                printf("%s: %s\n", fields[j], token);
                token = strtok(NULL, ",");
                j++;
            }
            printf("-----------------------------------\n");
        }
    }

    return 0;
}
