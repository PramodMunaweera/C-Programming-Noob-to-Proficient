#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    char name[50];
    struct Date birthdate;
    struct Date hiredate;
};

int main() {
    struct Employee emp = {"John Doe", {15, 5, 1990}, {1, 1, 2020}};
    
    printf("Employee: %s\n", emp.name);
    printf("Birthdate: %d/%d/%d\n", emp.birthdate.day, emp.birthdate.month, emp.birthdate.year);
    printf("Hire date: %d/%d/%d\n", emp.hiredate.day, emp.hiredate.month, emp.hiredate.year);
    
    return 0;
}