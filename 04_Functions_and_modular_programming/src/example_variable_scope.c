#include <stdio.h>

int global_var = 10; // Global variable

void localFunction() {
    int local_var = 20; // Local variable
    static int static_var = 30; // Static variable
    printf("Inside localFunction:\n");
    printf("local_var = %d, static_var = %d, global_var = %d\n", local_var, static_var, global_var);
    local_var++;
    static_var++;
    global_var++;
}

int main() {
    printf("Inside main:\n");
    printf("global_var = %d\n", global_var);
    localFunction();
    localFunction();
    return 0;
}