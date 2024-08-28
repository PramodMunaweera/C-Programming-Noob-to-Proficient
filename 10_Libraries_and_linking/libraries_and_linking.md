[**🏠 Home**](../README.md) | [**◀️ File Handling**](../09_File_handling/file_handling.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)



- ### [**10: Libraries and Linking**](#10-libraries-and-linking-1)
    - [**Modular Programming**](#modular-programming)
        - Splitting programs into multiple files
        - Using header files
    - [**Standard C Libraries**](#standard-c-libraries)
        - Commonly used standard C libraries
    - [**C Libraries**](#c-libraries)
        - Types of libraries
        - Static Libraries
        - Dynamic Libraries
    - [**Best Practices**](#best-practices)
        - Code organization and modularity
        - Using header guards
        - Avoiding circular dependencies
	    - Understanding linker errors
    - [**Advanced Concepts**](#advanced-concepts)
        - Dynamic loading
        - Weak symbols

# **10: Libraries and Linking**

## **Modular Programming**

Modular programming is an approach to software development that emphasizes separating the functionality of a program into independent, interchangeable modules. Each module contains everything necessary to execute only one aspect of the desired functionality.

Benefits of modular programming include:
- Improved maintainability
- Code reusability
- Easier debugging
- Better organization of code
- Improved collaboration among developers

### Splitting Programs into Multiple Files

Let's start with a simple example of splitting a program into multiple files.

main.c:
```c
#include <stdio.h>
#include "math_operations.h"

int main() {
    int a = 10, b = 5;
    printf("Sum: %d\n", add(a, b));
    printf("Difference: %d\n", subtract(a, b));
    return 0;
}
```

math_operations.h:
```c
#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

int add(int a, int b);
int subtract(int a, int b);

#endif
```

math_operations.c:
```c
#include "math_operations.h"

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}
```

To compile this program:
```
gcc -c main.c
gcc -c math_operations.c
gcc main.o math_operations.o -o program
```

This approach allows you to:
1. Organize your code into logical units
2. Compile only the parts of your program that have changed
3. Reuse functions in multiple programs

### Using Header Files

Header files are used to share declarations between source files. They typically contain:
- Function prototypes
- Macro definitions
- Type definitions
- External variable declarations

Best practices for header files:
1. Use header guards to prevent multiple inclusion
2. Include only what's necessary
3. Avoid putting function definitions in header files (with some exceptions like inline functions)

Example of a more complex header file:

complex_math.h:
```c
#ifndef COMPLEX_MATH_H
#define COMPLEX_MATH_H

typedef struct {
    double real;
    double imag;
} Complex;

Complex add_complex(Complex a, Complex b);
Complex multiply_complex(Complex a, Complex b);

#define PI 3.14159265358979323846

#endif
```

## Standard C Libraries

The C standard library provides a set of functions and data types that form the core of C programming, which we have already used extensively in previous lessons. These libraries are typically included by default in C compilers. Here are some of the most commonly used ones:

1. **stdio.h**: Handles input/output operations, including reading from and writing to files and the console.
Common functions: `printf`, `scanf`, `fopen`, `fclose`, `fgets`, `fputs`, `fprintf`, `fscanf`.

2. **stdlib.h**: Provides general-purpose functions, such as memory allocation, random number generation, and mathematical functions.
Common functions: `malloc`, `free`, `rand`, `srand`, `qsort`, `abs`, `atoi`, `atof`, `itoa`.

3. **string.h**: Deals with string manipulation, including copying, concatenation, comparison, and searching.
Common functions: `strcpy`, `strcat`, `strcmp`, `strlen`, `strstr`, `strtok`.

4. **math.h**: Offers mathematical functions, including trigonometric, logarithmic, and exponential operations.
Common functions: `sin`, `cos`, `tan`, `log`, `exp`, `sqrt`, `pow`.

5. **ctype.h**: Provides functions for character classification and conversion.
Common functions: `isalpha`, `isdigit`, `isspace`, `toupper`, `tolower`.

6. **time.h**: Handles time and date operations, including obtaining the current time and formatting dates.
Common functions: `time`, `localtime`, `strftime`, `ctime`.

7. **assert.h**: Used for debugging, providing a mechanism to check conditions at runtime and terminate the program if they are not met.
Common functions: `assert`

Example using C Standard libraries:

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));  // Seed random number generator
    int random_num = rand() % 100 + 1;  // Generate random number between 1 and 100
    printf("Random number: %d\n", random_num);
    return 0;
}
```

## **C Libraries**

Shared libraries allow code to be shared between programs. There are two types of libraries in C: static and dynamic.

### Static Libraries

C libraries (.a files on Unix-like systems, .lib files on Windows) are linked at compile-time. The library code becomes part of the executable.

Creating a static library:

1. Compile the source files into object files:
   ```
   gcc -c math_operations.c
   ```

2. Create the static library:
   ```
   ar rcs libmathops.a math_operations.o
   ```

3. Use the library in your program:
   ```
   gcc main.c -L. -lmathops -o program
   ```

### Dynamic Libraries

Dynamic libraries (.so files on Unix-like systems, .dll files on Windows) are linked at runtime. Multiple programs can share the same library file.

Creating a dynamic library:

1. Compile the source files with position-independent code:
   ```
   gcc -fPIC -c math_operations.c
   ```

2. Create the shared library:
   ```
   gcc -shared -o libmathops.so math_operations.o
   ```

3. Use the library in your program:
   ```
   gcc main.c -L. -lmathops -o program
   ```

4. Set the library path:
   ```
   export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
   ```

## Best Practices

### Code Organization and Modularity

- Group related functions into separate files
- Use meaningful names for files and functions
- Keep functions small and focused on a single task
- Use consistent naming conventions

### Using Header Guards

Header guards prevent multiple inclusion of header files:

```c
#ifndef MYHEADER_H
#define MYHEADER_H

// Header content goes here

#endif
```

Alternatively, you can use `#pragma once` which is widely supported but not part of the C standard.

### Avoiding Circular Dependencies

Circular dependencies occur when two or more modules depend on each other. To avoid this:

- Use forward declarations
- Reorganize your code to break the cycle
- Use pointers to incomplete types

Example of breaking a circular dependency:

a.h:
```c
#ifndef A_H
#define A_H

struct B;  // Forward declaration

typedef struct {
    struct B* b_ptr;
} A;

void a_function(A* a);

#endif
```

b.h:
```c
#ifndef B_H
#define B_H

#include "a.h"

typedef struct {
    A* a_ptr;
} B;

void b_function(B* b);

#endif
```

### Understanding Linker Errors

Common linker errors include:

1. Undefined reference: You've declared a function but haven't defined it.
   ```
   undefined reference to `function_name'
   ```

2. Multiple definition: You've defined a function or variable in multiple places.
   ```
   multiple definition of `function_name'
   ```

3. Unresolved external symbol: The linker can't find a function or variable (common when working with libraries).
   ```
   unresolved external symbol "function_name" referenced in function "main"
   ```

To resolve these, check for:
- Typos in function names
- Missing source files in compilation
- Incorrect library paths
- Forgetting to link necessary libraries

## Advanced Concepts

### Dynamic Loading

Dynamic loading allows you to load libraries at runtime using functions like `dlopen()` on Unix-like systems or `LoadLibrary()` on Windows.

Example using `dlopen()`:

```c
#include <stdio.h>
#include <dlfcn.h>

int main() {
    void *handle;
    int (*add)(int, int);
    char *error;

    handle = dlopen("libmathops.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }

    add = dlsym(handle, "add");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }

    printf("3 + 4 = %d\n", (*add)(3, 4));
    dlclose(handle);
    return 0;
}
```

Compile with:
```
gcc -rdynamic -o program program.c -ldl
```

### Weak Symbols

Weak symbols allow you to provide a default implementation of a function that can be overridden by a strong symbol.

Example:

weak.c:
```c
#include <stdio.h>

__attribute__((weak)) void custom_print(const char* message) {
    printf("Default implementation: %s\n", message);
}

int main() {
    custom_print("Hello, World!");
    return 0;
}
```

strong.c:
```c
#include <stdio.h>

void custom_print(const char* message) {
    printf("Strong implementation: %s\n", message);
}
```

Compile and run:
```
gcc -c weak.c
gcc -c strong.c
gcc weak.o strong.o -o program
./program
```

The output will be "Strong implementation: Hello, World!" because the strong symbol overrides the weak one.

This concludes the lesson on Libraries and Linking in C. We've covered modular programming, working with multiple files, header files, static and dynamic libraries and best practices. Remember that good organization and understanding of these concepts can greatly improve the quality and maintainability of your C programs.


[**🏠 Home**](../README.md) | [**◀️ File Handling**](../09_File_handling/file_handling.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)