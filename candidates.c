#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define CANDIDATES 6
#define MAX_STR 100

char candidate01[MAX_STR], candidate02[MAX_STR], candidate03[MAX_STR];
char candidate04[MAX_STR], candidate05[MAX_STR], candidate06[MAX_STR];

char member_info[CANDIDATES][11][MAX_STR];

int calculate_age(const char *dob)
{
    int year, month, day;
    sscanf(dob, "%d/%d/%d", &year, &month, &day);

    int current_year = 2025, current_month = 4, current_day = 14;
    int age = current_year - year;
    if (current_month < month || (current_month == month && current_day < day))
    {
        age--;
    }
    return age;
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main()
{
    char group_name[MAX_STR];
    int i = 0;

    printf("Enter audition group name: ");
    int idx = 0;
    char ch;
    while ((ch = getchar()) != '\n' && idx < MAX_STR - 1)
    {
        group_name[idx++] = ch;
    }
    group_name[idx] = '\0';

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Entry\n", group_name);
    printf("####################################\n");

    while (i < CANDIDATES)
    {
        printf("\nEntering information for candidate %d.\n", i + 1);
        printf("---------------------------------\n");

        printf("1. Name: ");
        fgets(member_info[i][0], MAX_STR, stdin);
        member_info[i][0][strcspn(member_info[i][0], "\n")] = 0;

        printf("2. Date of Birth (YYYY/MM/DD format): ");
        fgets(member_info[i][1], MAX_STR, stdin);
        member_info[i][1][strcspn(member_info[i][1], "\n")] = 0;

        printf("3. Gender (F for Female, M for Male): ");
        fgets(member_info[i][2], MAX_STR, stdin);
        member_info[i][2][strcspn(member_info[i][2], "\n")] = 0;

        printf("4. Email: ");
        fgets(member_info[i][3], MAX_STR, stdin);
        member_info[i][3][strcspn(member_info[i][3], "\n")] = 0;

        printf("5. Nationality: ");
        fgets(member_info[i][4], MAX_STR, stdin);
        member_info[i][4][strcspn(member_info[i][4], "\n")] = 0;

        printf("6. BMI: ");
        fgets(member_info[i][5], MAX_STR, stdin);
        member_info[i][5][strcspn(member_info[i][5], "\n")] = 0;

        printf("7. Primary Skill: ");
        fgets(member_info[i][6], MAX_STR, stdin);
        member_info[i][6][strcspn(member_info[i][6], "\n")] = 0;

        printf("8. Secondary Skill: ");
        fgets(member_info[i][7], MAX_STR, stdin);
        member_info[i][7][strcspn(member_info[i][7], "\n")] = 0;

        printf("9. Korean Proficiency Level (TOPIK): ");
        fgets(member_info[i][8], MAX_STR, stdin);
        member_info[i][8][strcspn(member_info[i][8], "\n")] = 0;

        printf("10. MBTI: ");
        fgets(member_info[i][9], MAX_STR, stdin);
        member_info[i][9][strcspn(member_info[i][9], "\n")] = 0;

        printf("11. Introduction: ");
        fgets(member_info[i][10], MAX_STR, stdin);
        member_info[i][10][strcspn(member_info[i][10], "\n")] = 0;

        i++;
    }

    printf("\n####################################\n");
    printf("[%s] Audition Candidate Data Review\n", group_name);
    printf("####################################\n");
    printf("=============================================================================================\n");
    printf("Name                | DOB       | Age | Gender | Email               | Nationality | BMI  | Primary Skill | Secondary Skill      | TOPIK  | MBTI |\n");
    printf("=============================================================================================\n");

    for (i = 0; i < CANDIDATES; i++)
    {
        int age = calculate_age(member_info[i][1]);
        int topik = atoi(member_info[i][8]);
        char *level = topik == 0 ? "Native" : member_info[i][8];

        char dob_fmt[9];
        sscanf(member_info[i][1], "%d/%d/%d", &dob_fmt[0], &dob_fmt[4], &dob_fmt[6]);
        sprintf(dob_fmt, "%.4s%.2s%.2s", member_info[i][1], member_info[i][1] + 5, member_info[i][1] + 8);

        printf("%-18s | %s | %-3d | %-6s | %-20s | %-11s | %-4s | %-13s | %-20s | %-6s | %-4s |\n",
               member_info[i][0], dob_fmt, age, member_info[i][2], member_info[i][3],
               member_info[i][4], member_info[i][5], member_info[i][6], member_info[i][7], level, member_info[i][9]);

        printf("-------------------------------------------------------------------------------------\n");
        printf("%s\n", member_info[i][10]);
        printf("---------------------------------------------------------------------------------------------\n");
    }

    return 0;
}
