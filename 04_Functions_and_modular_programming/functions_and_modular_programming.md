[**🏠 Home**](../README.md) | [**◀️ Control Structures**](../03_Control_structures/control_structures.md) | [**Arrays and Strings ▶️**](../05_Arrays_and_strings/arrays_and_strings.md)



- ### [**04: Functions and Modular Programming**](#04-functions-and-modular-programming-1)

    - [**Functions**](#functions)
	    - Function declaration and definition
	    - Function calling 
	    - Passing arguments: Pass by value, Pass by reference
	    - Scope of variables
	    - Return statement
    - [**Recursion**](#recursion)
        - Understanding recursion
        - Examples of recursive functions


# **04: Functions and Modular Programming**

Functions are the building blocks of modular programming in C. They allow you to break down a complex problem into smaller, reusable pieces.

Using functions offer several key benefits:

- **Modularity**: Functions break down complex problems into smaller, more manageable units. This improves code organization and readability.
- **Reusability**: Once a function is defined, it can be called multiple times from different parts of your code. This eliminates redundant code and reduces the risk of errors.
- **Abstraction**: Functions hide the implementation details of a task, allowing you to focus on the overall functionality. This promotes code maintainability and makes it easier to work with larger projects.
- **Collaboration**: Functions can be shared and reused among different programmers, facilitating collaboration and teamwork.
- **Better Code Structure**: Functions can help you organize your code into logical sections, making it easier to understand and maintain.

This tutorial will cover the various aspects of functions and how to use them effectively in your C programs.

## **Functions**

### Function Declaration and Definition

A function declaration, also known as a function prototype, specifies the function's name, return type, and parameter list.

```c
return_type function_name(parameter_list);
```

A function definition includes the function body, where the actual code is implemented.

```c
return_type function_name(parameter_list) {
    // function body
    return value; // optional
}
```

Example: [example_function_basics.c](./src/example_function_basics.c)

```c
#include <stdio.h>

void showTriangle(); // Function declaration

int main() {
    showTriangle(); // Function call
    return 0;
}

void showTriangle() { // Function definition
    int i, j;

    for (i = 1; i <= 5; i++) {
        for (j = 1; j <= i; j++) {
            printf("* ");
        }
        printf("\n");
    }
}
```

### Passing Arguments: Pass by Value and Pass by Reference

**Pass by value**

In C, arguments are passed to functions by value by default.
To pass arguments by value, the value of the variable is passed to the function. Any changes made inside the function do not affect the original variable.

Example: [example_pass_by_value.c](./src/example_pass_by_value.c)

```c
#include <stdio.h>

int add(int a, int b) { // Function
    return a + b;
}

int main() {
    int result = add(5, 3); // Function call with parameters
    printf("The sum is: %d\n", result);
    return 0;
}
```

**Pass by reference**

To pass arguments by reference, a pointer to the variable is passed to the function. Changes made inside the function can affect the original variable.

Example: [example_pass_by_ref.c](./src/example_pass_by_ref.c)

```c
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    printf("Before swap: x = %d, y = %d\n", x, y);
    swap(&x, &y); // Pass the addresses of x and y
    printf("After swap: x = %d, y = %d\n", x, y);
    return 0;
}
```

### Scope of Variables

Variables in C have different scopes, which determine where they can be accessed.

- **Local variables**: Defined within a function or block, and are only accessible within that scope.
- **Global variables**: Defined outside any function, and can be accessed from anywhere in the program.
- **Static variables**: Maintain their value between function calls, but are only accessible within the scope they are defined in.

Example: [example_variable_scope.c](./src/example_variable_scope.c)

```c
#include <stdio.h>

int global_var = 10; // Global variable

void localFunction() {
    int local_var = 20; // Local variable
    static int static_var = 30; // Static variable
    printf("Inside localFunction:\n");
    printf("local_var = %d, static_var = %d, global_var = %d\n", local_var, static_var, global_var);
    local_var++;
    static_var++;
    global_var++;
}

int main() {
    printf("Inside main:\n");
    printf("global_var = %d\n", global_var);
    localFunction();
    localFunction();
    return 0;
}
```

### Return Statement

The `return` statement is used to send a value back from a function to the caller.

Example: [example_return_statement.c](./src/example_return_statement.c)

```c
#include <stdio.h>

int square(int num) {
    return num * num;
}

int main() {
    int result = square(5);
    printf("The square of 5 is: %d\n", result);
    return 0;
}
```


## **Recursion**

Recursion is a programming technique where a function calls itself to solve a problem. Recursive functions are useful for solving problems that can be broken down into smaller, similar sub-problems.

### Understanding Recursion

A recursive function must have a base case, which is the condition that stops the recursion. The function should also have at least one recursive call that moves the problem closer to the base case.

Example: Factorial Calculation [example_recursion.c](./src/example_recursion.c)

```c
#include <stdio.h>

int factorial(int n) {
    if (n == 0 || n == 1) { // Base case
        return 1;
    } else {
        return n * factorial(n - 1); // Recursive call
    }
}

int main() {
    int result = factorial(5);
    printf("The factorial of 5 is: %d\n", result);
    return 0;
}
```

### Examples of Recursive Functions

Here are a few more examples of recursive functions:

1. **Fibonacci Sequence**:

```c
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return (fibonacci(n - 1) + fibonacci(n - 2));
    }
}
```

2. **Binary Search**:

```c
int binarySearch(int arr[], int left, int right, int target) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] > target) {
            return binarySearch(arr, left, mid - 1, target);
        } else {
            return binarySearch(arr, mid + 1, right, target);
        }
    }
    return -1;
}
```

3. **Towers of Hanoi**:

```c
void towerOfHanoi(int n, char from, char to, char aux) {
    if (n == 1) {
        printf("Move disk 1 from rod %c to rod %c\n", from, to);
        return;
    }
    towerOfHanoi(n - 1, from, aux, to);
    printf("Move disk %d from rod %c to rod %c\n", n, from, to);
    towerOfHanoi(n - 1, aux, to, from);
}
```

Mastering functions and recursion is essential for writing modular, maintainable, and reusable C code. By breaking down complex problems into smaller, manageable pieces, you can create more organized and efficient programs.



[**🏠 Home**](../README.md) | [**◀️ Control Structures**](../03_Control_structures/control_structures.md) | [**Arrays and Strings ▶️**](../05_Arrays_and_strings/arrays_and_strings.md)