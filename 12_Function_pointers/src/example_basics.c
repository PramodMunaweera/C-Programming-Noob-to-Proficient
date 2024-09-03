#include <stdio.h>

// Function
int add(int a, int b) {
    return a + b;
}

int main() {
    // Declare function pointer
    int (*func_ptr)(int, int);
    
    // Assign the address of the function to the pointer
    func_ptr = &add;

    // Call the function using the function pointer
    int result = func_ptr(2, 3);

    printf("Result: %d\n", result);

    return 0;
}