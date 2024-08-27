#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fputc('H', file);
    fputc('e', file);
    fputc('l', file);
    fputc('l', file);
    fputc('o', file);

    fclose(file);
    return 0;
}