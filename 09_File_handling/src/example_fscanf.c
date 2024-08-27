#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int num;
    char str[50];
    while (fscanf(file, "%d %s", &num, str) == 2) {
        printf("Number: %d, String: %s\n", num, str);
    }

    fclose(file);
    return 0;
}