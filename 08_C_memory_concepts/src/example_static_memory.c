#include <stdio.h>

int global_var = 10;  // Global variable (initialized data segment)
static int static_global_var;  // Static global variable (BSS segment)

void function() {
    static int static_local_var = 0;  // Static local variable (initialized data segment)
    int local_var = 5;  // Local variable (stack)
    
    static_local_var++;
    printf("Static local variable: %d\n", static_local_var);
    printf("Local variable: %d\n", local_var);
}

int main() {
    function();
    function();
    return 0;
}