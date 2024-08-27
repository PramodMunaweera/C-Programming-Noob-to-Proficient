#include <stdio.h>

int main() {
    FILE *file = fopen("missing.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int c = fgetc(file);
    if (ferror(file)) {
        printf("Error reading the file!\n");
    }

    fclose(file);
    return 0;
}