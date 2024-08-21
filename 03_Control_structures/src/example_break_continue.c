#include <stdio.h>

int main() {
    for (int i = 1; i <= 10; i++) {
        if (i == 3) {
            continue;  // Skip 3
        }
        if (i == 8) {
            break;     // Stop at 8
        }
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}