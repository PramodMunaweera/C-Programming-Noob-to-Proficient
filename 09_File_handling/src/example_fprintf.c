#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int num = 42;
    char *str = "Hello";
    fprintf(file, "Number: %d, String: %s\n", num, str);

    fclose(file);
    return 0;
}