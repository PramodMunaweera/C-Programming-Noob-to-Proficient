[**🏠 Home**](../README.md) | [**◀️ Getting Started**](../01_Getting_started/getting_started.md) | [**Control Structures ▶️**](../03_Control_structures/control_structures.md)

- ### [**02: Basic Constructs**](#02-basic-constructs-1)

    - [**Variables and Data Types**](#variables-and-data-types)
        - Basic data types (int, float, char, etc.)
        - Variable declaration and initialization
        - Enumerated types
        - Constants
    - [**Operators and Expressions**](#operators-and-expressions)
        - Arithmetic, relational, logical, bitwise, and assignment operators
        - Operator precedence and associativity
    - [**Input and Output**](#input-and-output)
        - `printf()` and `scanf()` functions
        - Formatting output

#   **02: Basic Constructs**

## **Variables and Data Types**

Variables are containers for storing data. C is a statically typed language (unlike Python, which is a Dynamically typed language), Thus, before using a variable, you need to declare its type.

### Basic Data Types

C provides several basic data types:

- `int`: for integers
- `float`: for single-precision floating-point numbers
- `double`: for double-precision floating-point numbers
- `char`: for single characters


Extended list of C data types with their value ranges and typical memory size:

![alt text](img/image.png)

Image Source: https://csestudyzone.blogspot.com/2019/04/data-types-in-c-language.html

Understanding categories of data types in C is essential for writing efficient programs. Each type has its own memory requirements and range of values it can represent, which affects how and when you should use them in your code.

### Variable Declaration and Initialization

You can declare variables like this:

```c
int age;
float height;
char grade;
```

We can also initialize variables when declaring them by assigning a value to it:

```c
int age = 25;
float height = 1.75;
char grade = 'A';
```

Example:
[example_variables.c](./src/example_variables.c)
```c
#include <stdio.h>

int main() {
    int age = 25;
    float height = 1.75;
    char grade = 'A';
    
    printf("Age: %d\n", age);
    printf("Height: %.2f meters\n", height);
    printf("Grade: %c\n", grade);
    
    return 0;
}
```

This program declares and initializes variables of different types, then prints their values.

### Enumerated Types

Enumerated types allow you to create a set of named integer constants.

Example: [example_enum_type.c](./src/example_enum_type.c)
```c
#include <stdio.h>

enum Days {MON, TUE, WED, THU, FRI, SAT, SUN};

int main() {
    enum Days today = WED;
    printf("Today is day %d of the week.\n", today + 1);
    return 0;
}
```

### Constants

**Using #define Preprocessor Directive:**

The #define preprocessor directive is used to define a constant before the program is compiled.

```c
#define CONSTANT_NAME value
```

Example:

```c
#include <stdio.h>

#define PI 3.14159
#define MAX_ARRAY_SIZE 100

int main() {
    printf("Value of PI: %f\n", PI);
    int array[MAX_ARRAY_SIZE];
    printf("Size of array: %d\n", MAX_ARRAY_SIZE);
    return 0;
}
```

**Using const Keyword:**

The const keyword is used to declare constants within the program.

```c
const data_type CONSTANT_NAME = value;
```
Example:
```c
#include <stdio.h>

int main() {
    const float GRAVITY = 9.81;
    const int DAYS_IN_WEEK = 7;
    
    printf("Gravity: %f m/s^2\n", GRAVITY);
    printf("Days in a week: %d\n", DAYS_IN_WEEK);
    
    return 0;
}
```

**Best Practices for Using Constants:**
- Use UPPERCASE names for constants to distinguish them from variables.
- Use const for constants that are local to a function or file.
- Use #define for global constants or when you need to use the constant in preprocessor directives.
- Group related constants together using enums.
- Use constants instead of "magic numbers" to improve code readability and maintainability.

## **Operators and Expressions**

C supports various types of operators for performing operations on variables and values.

### Types of Operators

1. Arithmetic Operators: `+`, `-`, `*`, `/`, `%`
2. Relational Operators: `==`, `!=`, `>`, `<`, `>=`, `<=`
3. Logical Operators: `&&` (AND), `||` (OR), `!` (NOT)
4. Bitwise Operators: `&`, `|`, `^`, `~`, `<<`, `>>`
5. Assignment Operators: `=`, `+=`, `-=`, `*=`, `/=`, `%=`, etc.

### Operator Precedence and Associativity

Operators have different precedence levels. For example, multiplication has higher precedence than addition. We can use parentheses to override the default precedence.

Example:
[example_operator_precedence.c](./src/example_operator_precedence.c)

```c
#include <stdio.h>

int main() {
    int a = 5, b = 3, c = 2;
    int result;
    
    result = a + b * c;
    printf("a + b * c = %d\n", result);  // Outputs: 11
    
    result = (a + b) * c;
    printf("(a + b) * c = %d\n", result);  // Outputs: 16
    
    return 0;
}
```

This program demonstrates how operator precedence affects the result of expressions.

## **Input and Output**

C provides functions for input and output operations.

### printf() Function

`printf()` is used for formatted output. It can print text and variable values.

Syntax:
```c
printf("format_string", argument1, argument2, ...);
```

### scanf() Function

`scanf()` is used for taking input from the user.

Syntax:
```c
scanf("format_string", &variable1, &variable2, ...);
```

### Formatting Output

You can use format specifiers to control how values are displayed:

- `%d`: for integers
- `%f`: for floats
- `%c`: for characters
- `%s`: for strings

Example:
[example_input_output.c](./src/example_input_output.c)
```c
#include <stdio.h>

int main() {
    int age;
    float height;
    
    printf("Enter your age: ");
    scanf("%d", &age);
    
    printf("Enter your height in meters: ");
    scanf("%f", &height);
    
    printf("You are %d years old and %.2f meters tall.\n", age, height);
    
    return 0;
}
```

This program demonstrates both input `scanf()` and output `printf()` operations. It takes the user's age and height as input, then prints them back with formatted output.


[**🏠 Home**](../README.md) | [**◀️ Getting Started**](../01_Getting_started/getting_started.md) | [**Control Structures ▶️**](../03_Control_structures/control_structures.md)
