#include <stdio.h>

// Callback function
void greet(const char* message) {
    printf("Message: %s\n", message);
}

// Function that takes a function pointer as an argument
void execute(void (*func)(const char*), const char* text) {
    // Call the passed function
    func(text);  
}

int main() {
    // Pass the function 'greet' to 'execute'
    execute(greet, "Hello, World!");

    return 0;
}