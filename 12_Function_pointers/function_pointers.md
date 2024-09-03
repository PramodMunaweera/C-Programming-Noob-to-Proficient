[**🏠 Home**](../README.md) | [**◀️ Data Structures and Algorithms**](../11_Data_structures_and_algorithms/data_structures_and_algorithms.md) | [**Preprocessor Directives and Macros ▶️**](../13_Preprocessor_directives_and_macros/preprocessor_directives_and_macros.md)

- ### [**Function Pointers**](#function-pointers-1)

    - [**Function Pointers**](#function-pointers-2)
        - Basics of Function Pointers
        - Function Pointers in Arrays
        - Passing Function Pointers as Arguments
        
    - [**Callbacks and Event-Driven Programming**](#callbacks-and-event-driven-programming)
        - Paradigm where the execution of a program is determined by the occurrence of events.

    - [**Dynamic Dispatch**](#dynamic-dispatch)
        - Determine method to be executed at runtime.

    - [**Abstraction of Object-oriented programming (OOP) in C**](#abstraction-of-object-oriented-programming-oop-in-c)
        - Abstraction of objects and methods in C



# Function Pointers

## Function Pointers

Function pointers are a powerful feature in C that allow you to store the address of a function in a pointer, and then call the function through the pointer. This enables dynamic function calls, which can be used for callbacks, implementing function tables, and achieving polymorphism-like behavior in C.

### Basics of Function Pointers
A function pointer is declared similarly to a normal pointer, but it points to a function instead of a data type. The syntax involves specifying the function's signature, which includes the return type and the parameters.

Example: [example_basics.c](./src/example_basics.c)

```c
#include <stdio.h>

// Function
int add(int a, int b) {
    return a + b;
}

int main() {
    // Declare function pointer
    int (*func_ptr)(int, int);
    
    // Assign the address of the function to the pointer
    func_ptr = &add;

    // Call the function using the function pointer
    int result = func_ptr(2, 3);

    printf("Result: %d\n", result);

    return 0;
}
```
### Function Pointers in Arrays

Function pointers can be stored in arrays, allowing you to create a table of functions that can be called dynamically based on certain conditions.

Example: [example_array_of_function_pointers.c](./src/example_array_of_function_pointers.c)

```c
#include <stdio.h>

// Sample functions
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

int main() {
    // Array of function pointers
    int (*operations[3])(int, int) = { add, subtract, multiply };

    int a = 10, b = 5;

    for (int i = 0; i < 3; i++) {
        printf("Result: %d\n", operations[i](a, b));
    }

    return 0;
}
```

In this example, depending on the index, different operations are performed on a and b.

### Passing Function Pointers as Arguments

Function pointers can be passed as arguments to other functions. This is particularly useful for implementing callback mechanisms.

Example: [example_function_pointer_as_argument.c](./src/example_function_pointer_as_argument.c)

```c
#include <stdio.h>

// Callback function
void greet(const char* message) {
    printf("Message: %s\n", message);
}

// Function that takes a function pointer as an argument
void execute(void (*func)(const char*), const char* text) {
    // Call the passed function
    func(text);  
}

int main() {
    // Pass the function 'greet' to 'execute'
    execute(greet, "Hello, World!");

    return 0;
}
```

This pattern is widely used in libraries and APIs where you need to execute a user-defined function at specific points in your code.

## Callbacks and Event-Driven Programming

Callbacks are a common use case for function pointers. You register a function (the callback) that will be called when a certain event occurs.

Example: [example_event_driven_programming.c](./src/example_event_driven_programming.c)

```c
#include <stdio.h>

// Define a type for the callback
typedef void (*event_callback)(void);  

// A function that takes a callback and triggers an event
void on_event(event_callback callback) {
    // Simulate an event
    printf("Event occurred!\n");
    callback();  // Call the callback function
}

// Callback function
void my_callback() {
    printf("Callback executed.\n");
}

int main() {
    // Register the callback function
    on_event(my_callback);

    return 0;
}
```

Here, on_event triggers an event and calls the registered my_callback function when the event occurs.

## Dynamic Dispatch

Function pointers can be used to achieve a form of dynamic dispatch, similar to virtual functions in C++. This is particularly useful in implementing state machines, command patterns, and polymorphic behavior in C.

Example: [example_dynamic_dispatch.c](./src/example_dynamic_dispatch.c)

```c
#include <stdio.h>

// Base "class" with function pointers
struct Animal {
    void (*speak)(void);
};

// Functions for different animal types
void dog_speak() {
    printf("Woof!\n");
}

void cat_speak() {
    printf("Meow!\n");
}

int main() {
    struct Animal dog = { dog_speak };
    struct Animal cat = { cat_speak };

    // Dynamic dispatch
    dog.speak();
    cat.speak();

    return 0;
}
```

In this example, the speak function is dynamically dispatched based on the type of animal, achieving a behavior similar to polymorphism in object-oriented programming.


## Abstraction of Object-Oriented Programming (OOP) in C

In C, while there are no built-in classes and objects as in C++ or other object-oriented languages, you can achieve a form of object-oriented programming (OOP) using structs and function pointers. This approach allows you to encapsulate data (like member variables) and behavior (like methods) within a structure, providing a way to create "objects" and "classes".

- **Struct as an Object:** A struct in C can represent an "object" by holding data that would typically be member variables.
- **Function Pointers as Methods:** You can include function pointers within a struct to represent methods associated with that object.

Example: [example_oop_abstraction.c](./src/example_oop_abstraction.c)

```c
#include <stdio.h>

// Define a "class" using a struct
struct Shape {
    double (*area)(struct Shape*);  // Function pointer for a method
    double width;
    double height;
};

// Define a method for calculating the area of a rectangle
double rectangle_area(struct Shape* shape) {
    return shape->width * shape->height;
}

// Constructor function to initialize a Shape object
void shape_init(struct Shape* shape, double width, double height) {
    shape->width = width;
    shape->height = height;
    shape->area = rectangle_area;  // Assign the appropriate method
}

int main() {
    // Create an instance of Shape (object)
    struct Shape rect;
    shape_init(&rect, 5.0, 3.0);

    // Call the method using the function pointer
    printf("Area of rectangle: %.2f\n", rect.area(&rect));

    return 0;
}
```

**Code Breakdown**

- **Struct (`Shape`):** Represents a class, containing data members like width and height, and a function pointer area to calculate the area.
- **Function Pointer (`area`):** This pointer is assigned to the rectangle_area function, which acts like a method.
- **Initialization Function (`shape_init`):** This function initializes a Shape object, setting its dimensions and assigning the correct method.



[**🏠 Home**](../README.md) | [**◀️ Data Structures and Algorithms**](../11_Data_structures_and_algorithms/data_structures_and_algorithms.md) | [**Preprocessor Directives and Macros ▶️**](../13_Preprocessor_directives_and_macros/preprocessor_directives_and_macros.md)