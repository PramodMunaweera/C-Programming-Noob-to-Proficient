#include <stdio.h>

#define SIZE 5

int main() {
    int numbers[SIZE] = {1, 2, 3, 4, 5};
    int sum = 0;

    // Calculate sum of array
    for (int i = 0; i < SIZE; i++) {
        sum += numbers[i];
    }

    printf("Sum of array elements: %d\n", sum);

    // Modify an element
    numbers[2] = 10;

    printf("Modified third element: %d\n", numbers[2]);

    return 0;
}