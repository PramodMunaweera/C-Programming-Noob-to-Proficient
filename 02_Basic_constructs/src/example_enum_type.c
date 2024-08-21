#include <stdio.h>

enum Days {MON, TUE, WED, THU, FRI, SAT, SUN};

int main() {
    enum Days today = WED;
    printf("Today is day %d of the week.\n", today + 1);
    return 0;
}