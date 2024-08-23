#include <stdio.h>

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};
    int size = 5;

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Insert a new element at index 2
    numbers[2] = 10;
    printf("Array after insertion: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Delete the element at index 1
    for (int i = 1; i < size - 1; i++) {
        numbers[i] = numbers[i + 1];
    }
    size--;
    printf("Array after deletion: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}