#include <stdio.h>

struct Person {
    char name[50];
    int age;
    union {
        struct {
            char street[50];
            char city[50];
        };
        char full_address[100];
    };
};

int main() {
    struct Person p = {"John Doe", 30, .street = "123 Main St", .city = "Anytown"};
    
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Street: %s\n", p.street);
    printf("City: %s\n", p.city);
    
    sprintf(p.full_address, "%s, %s", p.street, p.city);
    printf("Full Address: %s\n", p.full_address);
    
    return 0;
}