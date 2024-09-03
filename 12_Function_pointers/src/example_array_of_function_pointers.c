#include <stdio.h>

// Sample functions
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main() {
    // Array of function pointers
    int (*operations[3])(int, int) = { add, subtract, multiply };

    int a = 10, b = 5;

    for (int i = 0; i < 3; i++) {
        printf("Result: %d\n", operations[i](a, b));
    }

    return 0;
}