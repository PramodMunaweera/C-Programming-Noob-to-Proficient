[**🏠 Home**](../README.md) | [**◀️ Pointers**](../06_Pointers/pointers.md) | [**C Memory Concepts ▶️**](../08_C_memory_concepts/c_memory_concepts.md)



- ### [**07: Structures and Unions**](#07-structures-and-unions-1)

    - [**Structures**](#structures)
        - Defining and using structures
        - Array of structures
        - Nested structures
        - Pointers to structures
	    - Typedef
	    - Self-referencing structures
    - [**Unions**](#unions)
        - Defining and using unions
        - Difference between structures and unions

    - [**Advanced Concepts**](#advanced-concepts)
        - Bit Fields
        - Anonymous Structures and Unions



# **07: Structures and Unions**

## **Structures**

Structures in C allow us to group related data items of different types under a single object. They are fundamental to organizing and managing complex data in C programs.

### Defining and Using Structures

To define a structure, use the `struct` keyword followed by the structure name and a list of members enclosed in curly braces.

- Defining structures

    ```c
    struct Person {
        char name[50];
        int age;
        float height;
    };
    ```

- Creating structure variables
    ```c
    struct Person person1;
    ```

- Accessing structure members
    ```c
    // Assignment
    person1.name = "Alice"; 

    // Access
    printf("Person 1: Name = %s\n", person1.name);
    ```    

- We can also initialize a structure when declaring it
    ```c
    struct Person person2 = {"Jane Smith", 25, 1.68};
    ```

Create and use a structure variable,

Example: [example_struct_basics.c](./src/example_struct_basics.c)

```c
#include <stdio.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
    float height;
}; // Define structure

int main() {
    struct Person person1; // Use structure
    
    strcpy(person1.name, "John Doe");
    person1.age = 30;
    person1.height = 1.75;
    
    printf("Name: %s\n", person1.name);
    printf("Age: %d\n", person1.age);
    printf("Height: %.2f m\n", person1.height);
    
    return 0;
}
```

### Array of Structures

We can create an array of structures to store multiple items of the same structure type.

Example: [example_array_of_structs.c](./src/example_array_of_structs.c)

```c
#include <stdio.h>

#define MAX_PEOPLE 3

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person people[MAX_PEOPLE] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35}
    };
    
    for (int i = 0; i < MAX_PEOPLE; i++) {
        printf("Person %d:\n", i + 1);
        printf("Name: %s\n", people[i].name);
        printf("Age: %d\n\n", people[i].age);
    }
    
    return 0;
}
```

### Nested Structures

Structures can contain other structures as members, allowing for more complex data organization.

Example: [example_nested_structs.c](./src/example_nested_structs.c)

```c
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
```

### Pointers to Structures

We can use pointers to structures to dynamically allocate memory and pass structures to functions by reference.

```c
struct Student *studentPtr = &student1;

// Two ways of accessing members
// Dereference and access
(*studentPtr).name = "Bob";
// Direct access with ->
studentPtr->age = 25;
```

### Typedef

The `typedef` keyword allows you to create aliases for structure types, making them easier to use.

Example: [example_typedef.c](./src/example_typedef.c)

```c
#include <stdio.h>

typedef struct {
    char name[50];
    int age;
} Person;

int main() {
    Person p1 = {"Alice", 30};
    
    printf("Name: %s\n", p1.name);
    printf("Age: %d\n", p1.age);
    
    return 0;
}
```

### Self-referencing Structures

Self-referencing structures contain a pointer to a structure of the same type. They are often used in data structures like linked lists:

```c
typedef struct Node {
    int data;
    struct Node* next;
} Node;
```

## **Unions**

Unions allow you to store different data types in the same memory location. They are useful when you need to use one out of several types of data in a single variable.

### Defining and Using Unions

To define a union, use the `union` keyword followed by the union name and a list of members enclosed in curly braces.

Example: [example_unions.c](./src/example_unions.c)

```c
#include <stdio.h>

union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;
    
    data.i = 10;
    printf("data.i: %d\n", data.i);
    
    data.f = 220.5;
    printf("data.f: %.2f\n", data.f);
    
    sprintf(data.str, "C Programming");
    printf("data.str: %s\n", data.str);
    
    return 0;
}
```

### Difference Between Structures and Unions

The main difference between structures and unions is memory allocation:

- Structures allocate memory for all members separately.
- Unions allocate memory that can be used by any of its members, but only one at a time.

Example: [example_struct_vs_union.c](./src/example_struct_vs_union.c)

```c
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
```

The size of the structure will be the sum of its members' sizes (with potential padding), while the size of the union will be the size of its largest member.

## Advanced Concepts

### Bit Fields

Bit fields allow you to specify the number of bits a member of a structure should occupy.

Example: [example_bit_fields.c](./src/example_bit_fields.c)

```c
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
```

### Anonymous Structures and Unions

C11 introduced anonymous structures and unions, which allow you to access their members directly.

Example: [example_anonymous_structs.c](./src/example_anonymous_structs.c)

```c
#include <stdio.h>

struct Person {
    char name[50];
    int age;
    union {
        struct {
            char street[50];
            char city[50];
        };
        char full_address[100];
    };
};

int main() {
    struct Person p = {"John Doe", 30, .street = "123 Main St", .city = "Anytown"};
    
    printf("Name: %s\n", p.name);
    printf("Age: %d\n", p.age);
    printf("Street: %s\n", p.street);
    printf("City: %s\n", p.city);
    
    sprintf(p.full_address, "%s, %s", p.street, p.city);
    printf("Full Address: %s\n", p.full_address);
    
    return 0;
}
```



[**🏠 Home**](../README.md) | [**◀️ Pointers**](../06_Pointers/pointers.md) | [**C Memory Concepts ▶️**](../08_C_memory_concepts/c_memory_concepts.md)