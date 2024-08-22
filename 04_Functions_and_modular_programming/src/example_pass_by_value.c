#include <stdio.h>

int add(int a, int b) { // Function
    return a + b;
}

int main() {
    int result = add(5, 3); // Function call with parameters
    printf("The sum is: %d\n", result);
    return 0;
}