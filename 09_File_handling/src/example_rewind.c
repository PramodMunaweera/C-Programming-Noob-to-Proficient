#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fseek(file, 10, SEEK_SET);
    printf("Current position: %ld\n", ftell(file));

    rewind(file);
    printf("After rewind, position: %ld\n", ftell(file));

    fclose(file);
    return 0;
}