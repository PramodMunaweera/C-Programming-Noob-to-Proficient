#include <stdio.h>

struct PackedData {
    unsigned int : 3;  // 3 bits padding
    unsigned int f1: 1;
    unsigned int f2: 4;
    unsigned int f3: 3;
};

int main() {
    struct PackedData data = {0};
    data.f1 = 1;   // Can hold 0 or 1
    data.f2 = 15;  // Can hold 0 to 15
    data.f3 = 7;   // Can hold 0 to 7
    
    printf("Size of PackedData: %lu bytes\n", sizeof(data));
    
    return 0;
}