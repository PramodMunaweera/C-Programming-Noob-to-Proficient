#include <stdio.h>
#include <gc.h>

int main() {
    GC_INIT();
    int *p = (int*)GC_MALLOC(sizeof(int));
    *p = 10;
    printf("%d\n", *p);
    // No need to free p
    return 0;
}