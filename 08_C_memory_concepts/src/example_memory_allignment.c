#include <stdio.h>

struct Aligned {
    char c;
    int i;
    char d;
};

struct Packed {
    char c;
    int i;
    char d;
} __attribute__((packed));

int main() {
    printf("Size of Aligned: %zu\n", sizeof(struct Aligned));
    printf("Size of Packed: %zu\n", sizeof(struct Packed));
    return 0;
}