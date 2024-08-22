#include <stdio.h>

void showTriangle(); // Function declaration

int main() {
    showTriangle(); // Function call
    return 0;
}

void showTriangle() { // Function definition
    int i, j;

    for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
}