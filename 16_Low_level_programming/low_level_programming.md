[**🏠 Home**](../README.md) | [**◀️ Networking**](../15_Networking/networking.md) | [**System Programming ▶️**](../17_System_programming/system_programming.md)



- ### [**16: Low-Level Programming**](#low-level-programming)

    - [**Inline Assembly**](#inline-assembly)
        - Embed assembly language code directly within C code
    - [**Bitwise Operations**](#bitwise-operations)
        - Manipulation of individual bits
    - [**Volatile Keyword**](#volatile-keyword)
    - [**Endianness**](#endianness)
        - Understanding endianness



# Low-Level Programming

Low-level programming in C allows developers to interact closely with the hardware and manage system resources efficiently, providing ability to write performant and hardware-aware code.

## Inline Assembly

Inline assembly allows you to embed assembly language code directly within C code, allowing for optimizing critical sections of code or accessing hardware-specific features.

### Basic Syntax

```c
#include <stdio.h>

int main() {
    int a = 10, b = 20, result;

    __asm__ (
        "movl %1, %%eax\n\t"
        "addl %2, %%eax\n\t"
        "movl %%eax, %0"
        : "=r" (result)
        : "r" (a), "r" (b)
    );

    printf("Result: %d\n", result);
    return 0;
}
```

Compiled code to Assembly in RISC-V architecture:

```nasm
.LC0:
        .string "Result: %d\n"
main:
        addi    sp,sp,-32
        sw      ra,28(sp)
        sw      s0,24(sp)
        addi    s0,sp,32
        li      a5,10
        sw      a5,-20(s0)
        li      a5,20
        sw      a5,-24(s0)
        lw      a5,-20(s0)
        lw      a4,-24(s0)
        movl a5, %eax
        addl a4, %eax
        movl %eax, a5
        sw      a5,-28(s0)
        lw      a1,-28(s0)
        lui     a5,%hi(.LC0)
        addi    a0,a5,%lo(.LC0)
        call    printf
        li      a5,0
        mv      a0,a5
        lw      ra,28(sp)
        lw      s0,24(sp)
        addi    sp,sp,32
        jr      ra
```


We use inline assembly to add two numbers. The `__asm__` directive is used to start an inline assembly block. The assembly code is written within quotation marks, and the input and output operands are specified after the colons.

Example: Implementing a Fast Square Root Function

```c
#include <stdio.h>

float fast_sqrt(float number) {
    float result;
    __asm__ (
        "sqrtss %1, %0"
        : "=x" (result)
        : "x" (number)
    );
    return result;
}

int main() {
    float num = 16.0f;
    printf("Fast square root of %.2f: %.4f\n", num, fast_sqrt(num));
    return 0;
}
```

## Bitwise Operations

Bitwise operations allow manipulation of individual bits within data types. They are essential for low-level programming tasks such as flag management, optimization, and hardware interaction, bit shifting for signal processing tasks in ASICs.

### Basic Bitwise Operators

- AND (&): Sets each bit to 1 if both bits are 1
- OR (|): Sets each bit to 1 if at least one bit is 1
- XOR (^): Sets each bit to 1 if exactly one bit is 1
- NOT (~): Inverts all bits
- Left Shift (<<): Shifts bits to the left
- Right Shift (>>): Shifts bits to the right

Example: Flag Management System

```c
#include <stdio.h>

#define FLAG_ACTIVE      0x01
#define FLAG_AUTHORIZED  0x02
#define FLAG_ADMIN       0x04
#define FLAG_SUSPENDED   0x08

void print_user_status(unsigned char flags) {
    printf("User status:\n");
    printf("Active: %s\n", (flags & FLAG_ACTIVE) ? "Yes" : "No");
    printf("Authorized: %s\n", (flags & FLAG_AUTHORIZED) ? "Yes" : "No");
    printf("Admin: %s\n", (flags & FLAG_ADMIN) ? "Yes" : "No");
    printf("Suspended: %s\n", (flags & FLAG_SUSPENDED) ? "Yes" : "No");
}

int main() {
    unsigned char user_flags = 0;

    // Set flags
    user_flags |= FLAG_ACTIVE | FLAG_AUTHORIZED;

    print_user_status(user_flags);

    // Toggle admin flag
    user_flags ^= FLAG_ADMIN;

    print_user_status(user_flags);

    // Clear authorized flag
    user_flags &= ~FLAG_AUTHORIZED;

    print_user_status(user_flags);

    return 0;
}
```

This demonstrates how to use bitwise operations to manage flags efficiently. Each flag is represented by a single bit, allowing us to store multiple boolean values in a single byte.

## Volatile Keyword

The `volatile` keyword is used to inform the compiler that a variable's value may change at any time without any action being taken by the code the compiler finds nearby. This is particularly important when dealing with hardware registers or memory-mapped I/O.

Example: Simulating a Hardware Register

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

volatile unsigned int hardware_register = 0;

void *hardware_interrupt_simulator(void *arg) {
    while (1) {
        sleep(1);
        hardware_register++;
    }
    return NULL;
}

int main() {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, hardware_interrupt_simulator, NULL);

    for (int i = 0; i < 10; i++) {
        printf("Hardware register value: %u\n", hardware_register);
        sleep(1);
    }

    pthread_cancel(thread_id);
    pthread_join(thread_id, NULL);

    return 0;
}
```

Here, we simulate a hardware register that's being updated by an external process (Ex: a separate thread). The `volatile` keyword ensures that the compiler always reads the current value of `hardware_register` from memory, rather than optimizing and potentially using a cached value.

## Endianness

Endianness refers to the order in which bytes are arranged in multi-byte data types. Understanding endianness is crucial when working with binary data, especially in network programming or when reading/writing binary files.

- **Little-endian:** Least significant byte first
- **Big-endian:** Most significant byte first

Example: Endianness Detection and Conversion

```c
#include <stdio.h>
#include <stdint.h>
#include <arpa/inet.h>

int is_little_endian() {
    uint16_t value = 0x1234;
    uint8_t *ptr = (uint8_t *)&value;
    return (ptr[0] == 0x34);
}

uint32_t swap_endian(uint32_t value) {
    return ((value & 0xFF000000) >> 24) |
           ((value & 0x00FF0000) >> 8) |
           ((value & 0x0000FF00) << 8) |
           ((value & 0x000000FF) << 24);
}

int main() {
    printf("System is %s-endian\n", is_little_endian() ? "little" : "big");

    uint32_t value = 0x12345678;
    printf("Original value: 0x%X\n", value);
    printf("Swapped value: 0x%X\n", swap_endian(value));

    // Using built-in network byte order functions
    printf("Host to network byte order: 0x%X\n", htonl(value));
    printf("Network to host byte order: 0x%X\n", ntohl(htonl(value)));

    return 0;
}
```

This demonstrates using structures and unions to parse an IP packet header, showcasing bit fields and network byte order handling.


These techniques allow us to write efficient, hardware-aware code and interact closely with system resources. Low-level programming requires careful consideration of platform-specific details and potential security implications.



[**🏠 Home**](../README.md) | [**◀️ Networking**](../15_Networking/networking.md) | [**System Programming ▶️**](../17_System_programming/system_programming.md)