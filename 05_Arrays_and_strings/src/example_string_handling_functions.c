#include <stdio.h>
#include <string.h>

int main() {
    char str1[20] = "Hello";
    char str2[20] = ", world!";
    char str3[40];

    printf("Length of str1: %lu\n", strlen(str1));
    strcpy(str3, str1);
    strcat(str3, str2);
    printf("Concatenated string: %s\n", str3);

    if (strcmp(str1, str2) < 0) {
        printf("str1 is less than str2\n");
    } else {
        printf("str1 is greater than or equal to str2\n");
    }

    return 0;
}