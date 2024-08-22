[**🏠 Home**](../README.md) | [**◀️ Basic Constructs**](../02_Basic_constructs/basic_constructs.md) | [**Functions and Modular Programming ▶️**](../04_Functions_and_modular_programming/functions_and_modular_programming.md)



- ### [**03: Control Structures**](#03-control-structures-1)

    - [**Conditional Statements**](#conditional-statements)
        - `if`, `else if`, `else` statements
        - `switch` statement
    - [**Loops**](#loops)
        - `for`, `while`, and `do-while` loops
        - Nested loops
        - Loop control statements (`break`, `continue`)

#  **03: Control Structures**

Control structures are fundamental components in C programming that allow us to control the flow of our program's execution. This tutorial covers conditional statements and loops.

## **Conditional Statements**

Conditional statements allow our program to make decisions based on certain conditions. Run specific code block if the condition is satisfied, or select form diferent code blocks and decide which code block to execute.

### if, else if, else Statements

The `if` statement executes a block of code if a specified condition is true.

```c
if (condition) {
    // code block to be executed if condition is true
}
```

You can extend this with `else if` and `else` to handle multiple conditions:

```c
if (condition1) {
    // code block to be executed if condition1 is true
} else if (condition2) {
    // code block to be executed if condition2 is true
} else {
    // code block to be executed if all conditions are false
}
```

Example: [example_if_else.c](./src/example_if_else.c)

```c
#include <stdio.h>

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (number > 0) {
        printf("The number is positive.\n");
    } else if (number < 0) {
        printf("The number is negative.\n");
    } else {
        printf("The number is zero.\n");
    }

    return 0;
}
```

This program checks whether a number is positive, negative, or zero.

### switch Statement

The `switch` statement allows you to select one of many code blocks to be executed.

In general, `switch` statements are often preferred over `if-else` chains when you have multiple conditions to check against a single expression. This is because of Efficiency and Readability advantages of `switch` statement over `if-else` chains.

```c
switch(expression) {
    case constant1:
        // code block to be executed if expression == constant1
        break;
    case constant2:
        // code block to be executed if expression == constant2
        break;
    ...
    default:
        // code block to be executed if expression doesn't match any constant
}
```

Example: [example_switch_statement.c](./src/example_switch_statement.c)

```c
#include <stdio.h>

int main() {
    char grade;
    printf("Enter your grade (A, B, C, D, or F): ");
    scanf(" %c", &grade);

    switch(grade) {
        case 'A':
            printf("Excellent!\n");
            break;
        case 'B':
            printf("Good job!\n");
            break;
        case 'C':
            printf("Average performance.\n");
            break;
        case 'D':
            printf("You need to improve.\n");
            break;
        case 'F':
            printf("Failed. Please try again.\n");
            break;
        default:
            printf("Invalid grade entered.\n");
    }

    return 0;
}
```

This program gives feedback based on the grade entered by the user.

## **Loops**

Loops allow you to execute a block of code repeatedly.

There are several loop structures available in C:
- `for`
- `while`
- `do-while`

### for Loop

The `for` loop is used when you know in advance how many times you want to execute a statement or block of statements.

```c
for (initialization; condition; update) {
    // code to be repeated
}
```

Example: [example_for_loop.c](./src/example_for_loop.c)

```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
```

This program prints numbers from 1 to 5.

### while Loop

The `while` loop repeats a statement or block of statements while a given condition is true.

```c
while (condition) {
    // code to be repeated
}
```

Example: [example_while_loop.c](./src/example_while_loop.c)

```c
#include <stdio.h>

int main() {
    int i = 1;
    while (i <= 5) {
        printf("%d ", i);
        i++;
    }
    printf("\n");
    return 0;
}
```

This program also prints numbers from 1 to 5, but using a while loop.

### do-while Loop

The `do-while` loop is similar to the while loop, except that it tests the condition at the end of the loop body.

```c
do {
    // code to be repeated
} while (condition);
```

Example: [example_do_while_loop.c](./src/example_do_while_loop.c)

```c
#include <stdio.h>

int main() {
    int i = 1;
    do {
        printf("%d ", i);
        i++;
    } while (i <= 5);
    printf("\n");
    return 0;
}
```

This program prints numbers from 1 to 5 using a do-while loop.

### Nested Loops

We can place one loop inside another loop. This is called nesting.

Example: [example_nested_loop.c](./src/example_nested_loop.c)

```c
#include <stdio.h>

int main() {
    for (int i = 1; i <= 3; i++) {
        for (int j = 1; j <= 3; j++) {
            printf("(%d, %d) ", i, j);
        }
        printf("\n");
    }
    return 0;
}
```

This program demonstrates nested loops by printing a 3x3 grid of coordinate pairs.

### Loop Control Statements

The execution of a loop can be interrupted and altered the flow of loops using `break` and `continue` keywords.

- `break`: terminates the loop immediately
- `continue`: skips the rest of the loop body and continues with the next iteration

Example: [example_break_continue.c](./src/example_break_continue.c)

```c
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
```

This program demonstrates `continue` by skipping 3 and `break` by stopping at 8.



[**🏠 Home**](../README.md) | [**◀️ Basic Constructs**](../02_Basic_constructs/basic_constructs.md) | [**Functions and Modular Programming ▶️**](../04_Functions_and_modular_programming/functions_and_modular_programming.md)