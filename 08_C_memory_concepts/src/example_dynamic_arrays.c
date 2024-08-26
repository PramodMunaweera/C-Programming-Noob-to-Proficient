#include <stdio.h>
#include <stdlib.h>

int main() {
    int rows = 3, cols = 4;
    int **array;

    // Allocate memory for rows
    array = (int**)malloc(rows * sizeof(int*));

    // Allocate memory for each row
    for (int i = 0; i < rows; i++) {
        array[i] = (int*)malloc(cols * sizeof(int));
    }

    // Initialize the array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            array[i][j] = i * cols + j;
        }
    }

    // Print the array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }

    // Free the allocated memory
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}