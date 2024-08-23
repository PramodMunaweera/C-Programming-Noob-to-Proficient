#include <stdio.h>
#include <string.h>

int main() {
    char str[20] = "Hello, world!";
    printf("Original string: %s\n", str);

    // Access individual character
    printf("Character at index 7: %c\n", str[7]);

    // Modify individual character
    str[7] = 'W';
    printf("Modified string: %s\n", str);

    // Insert a character
    int index = 6;
    for (int i = strlen(str); i > index; i--) {
        str[i] = str[i - 1];
    }
    str[index] = ' ';
    printf("String after insertion: %s\n", str);

    // Delete a character
    index = 7;
    for (int i = index; i < strlen(str); i++) {
        str[i] = str[i + 1];
    }
    printf("String after deletion: %s\n", str);

    return 0;
}