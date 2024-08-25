#include <stdio.h>

struct StructExample {
    int i;
    float f;
    char c;
};

union UnionExample {
    int i;
    float f;
    char c;
};

int main() {
    struct StructExample s;
    union UnionExample u;
    
    printf("Size of structure: %lu bytes\n", sizeof(s));
    printf("Size of union: %lu bytes\n", sizeof(u));
    
    return 0;
}