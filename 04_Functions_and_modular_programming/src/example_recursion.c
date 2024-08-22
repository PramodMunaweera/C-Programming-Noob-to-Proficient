#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) { // Base case
        return 1;
    } else {
        return n * factorial(n - 1); // Recursive call
    }
}

int main() {
    int result = factorial(5);
    printf("The factorial of 5 is: %d\n", result);
    return 0;
}