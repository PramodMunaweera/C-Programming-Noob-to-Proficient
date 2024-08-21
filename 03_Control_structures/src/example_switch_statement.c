#include <stdio.h>

int main() {
    char grade;
    printf("Enter your grade (A, B, C, D, or F): ");
    scanf(" %c", &grade);

    switch(grade) {
        case 'A':
            printf("Excellent!\n");
            break;
        case 'B':
            printf("Good job!\n");
            break;
        case 'C':
            printf("Average performance.\n");
            break;
        case 'D':
            printf("You need to improve.\n");
            break;
        case 'F':
            printf("Failed. Please try again.\n");
            break;
        default:
            printf("Invalid grade entered.\n");
    }

    return 0;
}