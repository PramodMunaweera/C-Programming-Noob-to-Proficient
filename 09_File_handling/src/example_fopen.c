#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("example.txt", "r");  // Open file for reading
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    // File operations here
    fclose(file);  // Close the file
    return 0;
}