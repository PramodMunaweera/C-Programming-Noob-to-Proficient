#include <stdio.h>

int main() {
    int x = 10, y = 20, z = 30;
    int *arr[] = {&x, &y, &z};

    for(int i = 0; i < 3; i++) {
        printf("Value at arr[%d]: %d\n", i, *arr[i]);
    }

    return 0;
}