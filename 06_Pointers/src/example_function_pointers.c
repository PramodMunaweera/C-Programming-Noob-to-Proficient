#include <stdio.h>

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }

int main() {
    int (*operation)(int, int);
    
    operation = add;
    printf("Result of addition: %d\n", operation(10, 5));
    
    operation = subtract;
    printf("Result of subtraction: %d\n", operation(10, 5));
    
    return 0;
}