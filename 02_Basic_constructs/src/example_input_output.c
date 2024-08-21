#include <stdio.h>

int main() {
    int age;
    float height;
    
    printf("Enter your age: ");
    scanf("%d", &age);
    
    printf("Enter your height in meters: ");
    scanf("%f", &height);
    
    printf("You are %d years old and %.2f meters tall.\n", age, height);
    
    return 0;
}