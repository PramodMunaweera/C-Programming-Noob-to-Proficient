[**🏠 Home**](../README.md) | [**Basic Constructs ▶️**](../02_Basic_constructs/basic_constructs.md)

- ### [**01: Getting Started**](#01-getting-started-1)

    - [**Introduction to C Programming**](#introduction-to-c-programming)
        - History and features of C
    - [**Development Environment Setup**](#development-environment-setup)
        - Setting up the development environment (Compiler/IDE installation)
    - [**First C Program**](#first-c-program)
        - Writing and understanding the structure of a simple C program
        - Compiling and executing a C program
        - Basic syntax

#   **01: Getting Started**
## **Introduction to C Programming**

## **Development Environment Setup**

## **First C Program**
Let's start with the usual classic example, the "Hello World!" program. This simple program prints the message "Hello World!" to the console. With this program we'll understand the basic structure of a C program.


[main.c](./src/main.c)
```C title="main.c"
#include <stdio.h>

int main() {
    printf("Hello World!\n");
    return 0;
}
```

**Breaking Down of Code**

- **#include <stdio.h>**

    This line tells the compiler to include the standard input/output header file "stdio.h". This header file provides basic functions like printing output.

- **int main()**

    This line defines the main function. The main function is the entry point of a C program. It's where the program execution begins. The int keyword indicates that the function returns an integer value.

- **printf("Hello World!\n");**

    This line calls the printf function to print the message "Hello World!" to the console. The \n character represents a newline, which moves the cursor to the beginning of the next line.

- **return 0;**

    This line returns the value 0 from the main function. In C, a return value of 0 typically indicates successful program execution.


**Compiling and Executing the code**
1. Save the code as a .c file (e.g., main.c).

2. Lets use GCC to compile the code.

    ```sh
    gcc main.c -o main.exe
    ```
    This creates an exe (Windows executable) file which we can run.

3. Execute the compiled program.
    ```sh
    ./main.exe
    ```
    Output:
    ```sh
    Hello World!
    ```

[**🏠 Home**](../README.md) | [**Basic Constructs ▶️**](../02_Basic_constructs/basic_constructs.md)