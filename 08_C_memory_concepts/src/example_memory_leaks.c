#include <stdlib.h>

void memory_leak() {
    int *ptr = (int*)malloc(sizeof(int));
    // ptr is not freed before function returns
}

int main() {
    while(1) {
        memory_leak();
    }
    return 0;
}