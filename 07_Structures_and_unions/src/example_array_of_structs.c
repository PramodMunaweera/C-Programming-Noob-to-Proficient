#include <stdio.h>

#define MAX_PEOPLE 3

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person people[MAX_PEOPLE] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    for (int i = 0; i < MAX_PEOPLE; i++) {
        printf("Person %d:\n", i + 1);
        printf("Name: %s\n", people[i].name);
        printf("Age: %d\n\n", people[i].age);
    }
    
    return 0;
}