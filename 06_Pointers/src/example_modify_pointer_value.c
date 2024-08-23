#include <stdio.h>

int main() {
    int x = 10;
    int *ptr = &x;

    *ptr = 20; // Modifying the value through the pointer

    printf("New value of x: %d\n", x);

    return 0;
}