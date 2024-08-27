#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Make an error
    fseek(file, -5, SEEK_SET);
    
    if (ferror(file)) {
        printf("Error occurred.\n");
        clearerr(file);
        printf("Error indicator cleared.\n");
    }

    fclose(file);
    return 0;
}