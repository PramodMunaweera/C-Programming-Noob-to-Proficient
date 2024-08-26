#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    // Allocate memory for 5 integers
    ptr = (int*)malloc(n * sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize the array
    for (int i = 0; i < n; i++) {
        ptr[i] = i + 1;
    }

    // Resize the array to hold 10 integers
    n = 10;
    ptr = (int*)realloc(ptr, n * sizeof(int));

    if (ptr == NULL) {
        printf("Memory reallocation failed\n");
        return 1;
    }

    // Initialize the new elements
    for (int i = 5; i < n; i++) {
        ptr[i] = i + 1;
    }

    // Print all elements
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(ptr);

    return 0;
}