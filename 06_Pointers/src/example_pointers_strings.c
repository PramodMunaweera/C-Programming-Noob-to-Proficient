#include <stdio.h>

void printString(char *str) {
    while (*str != '\0') {
        printf("%c", *str);
        str++;
    }
    printf("\n");
}

int main() {
    char str[] = "Hello, Pointers!";
    printString(str);
    return 0;
}