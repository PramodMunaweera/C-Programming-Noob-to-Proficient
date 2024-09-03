#include <stdio.h>

// Base "class" with function pointers
struct Animal {
    void (*speak)(void);
};

// Functions for different animal types
void dog_speak() {
    printf("Woof!\n");
}

void cat_speak() {
    printf("Meow!\n");
}

int main() {
    struct Animal dog = { dog_speak };
    struct Animal cat = { cat_speak };

    // Dynamic dispatch
    dog.speak();
    cat.speak();

    return 0;
}