#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // For Sleep function and system("cls")

void clear_screen() {
    system("cls"); // Clears the screen in Windows
}

void display_splash_screen(const char *name, const char *date) {
    clear_screen();
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    
    
    // Left right-angled triangle
    for (int i = 1; i <= 5; i++) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("                                        [Magrathea ver 0.1]                              \n");
    printf("                   Magrathea, where a shining planet is created in a wasteland with no grass,         \n");
    printf("           a place where unseen potential is discovered and gems are polished by the hands of experts,    \n");
    printf("                                        Welcome to Magrathea.   \n");
    
    // Right inverted right-angled triangle
    for (int i = 5; i >= 1; i--) {
        for (int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }
    
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %s                                   [Execution Time]: %s\n", name, date);
    printf("=============================================================================================================\n");
}

int main() {
    char name[50];
    char date[11];
    
    printf("[Please enter the current date in the \"yyyy-mm-dd\" format]: ");
    scanf("%10s", date);
    
    printf("[Please enter your name]: ");
    scanf(" %49[^]", name); // Reads full name including spaces
    
    printf("**The input has been processed successfully.**\n");
    Sleep(3000); // Wait for 3 seconds before clearing the screen
    
    display_splash_screen(name, date);
    
    return 0;
}