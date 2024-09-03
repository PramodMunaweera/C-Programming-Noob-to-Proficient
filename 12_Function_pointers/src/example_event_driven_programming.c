#include <stdio.h>

// Define a type for the callback
typedef void (*event_callback)(void);  

// A function that takes a callback and triggers an event
void on_event(event_callback callback) {
    // Simulate an event
    printf("Event occurred!\n");
    callback();  // Call the callback function
}

// Callback function
void my_callback() {
    printf("Callback executed.\n");
}

int main() {
    // Register the callback function
    on_event(my_callback);

    return 0;
}