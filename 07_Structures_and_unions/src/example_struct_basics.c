#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    float height;
}; // Define structure

int main() {
    struct Person person1; // Use structure
    
    strcpy(person1.name, "John Doe");
    person1.age = 30;
    person1.height = 1.75;
    
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Height: %.2f m\n", person1.height);
    
    return 0;
}