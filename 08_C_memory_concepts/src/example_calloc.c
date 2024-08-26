#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr;
    int n = 5;

    // Allocate and initialize memory for 5 integers
    ptr = (int*)calloc(n, sizeof(int));

    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Print the values (should all be 0)
    for (int i = 0; i < n; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(ptr);

    return 0;
}