#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fputs("Hello, World!\n", file);
    fputs("This is a test.\n", file);

    fclose(file);
    return 0;
}