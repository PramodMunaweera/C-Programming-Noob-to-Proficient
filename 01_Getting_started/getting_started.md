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

C is a general-purpose programming language developed in the early 1970s by Dennis Ritchie at Bell Labs. It's known for its efficiency, flexibility, and close-to-hardware control, low-level access to memory with a static type system making it popular for system programming, embedded systems, and developing operating systems.

Key features:
1. Low-level access to memory
2. Simple keywords set 
3. Fast and efficient
4. Structured programming support
5. Portability across different platforms

C has influenced many modern programming languages and remains widely used due to its performance and reliability. It serves as a foundation for learning other languages and is essential for understanding computer architecture and systems programming.

## **Development Environment Setup**

We eill be using a simple and minimal development environment without using advanced IDEs. This will help us to grab the basics of the language without interventions from advanced IDE functions. Later when we are familier with the language, we can seek the support of an IDE.

This tutorial is based on a Windows development environment setup. But, you will be able to build an environment with similar function on Linux and Mac without any difficulties.
Download and install Visual Studio Code and MinGW.

**Windows :**

- **IDE - Visual Studio Code :** https://code.visualstudio.com/download
- **C Compiler - MinGW :** https://www.mingw-w64.org/downloads

**Linux :**

https://www.geeksforgeeks.org/setting-up-c-development-environment/

**Mac :**

https://www.cs.auckland.ac.nz/~paul/C/Mac/

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
1. Save the code as a .c file (ex: main.c).

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