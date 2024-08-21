#include <stdio.h>

int main() {
    int a = 5, b = 3, c = 2;
    int result;
    
    result = a + b * c;
    printf("a + b * c = %d\n", result);  // Outputs: 11
    
    result = (a + b) * c;
    printf("(a + b) * c = %d\n", result);  // Outputs: 16
    
    return 0;
}