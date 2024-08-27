#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fseek(file, 10, SEEK_SET);  // Move 10 bytes from the beginning
    int c = fgetc(file);
    printf("Character at position 10: %c\n", c);

    fseek(file, -5, SEEK_END);  // Move 5 bytes before the end
    c = fgetc(file);
    printf("5th character from the end: %c\n", c);

    fclose(file);
    return 0;
}