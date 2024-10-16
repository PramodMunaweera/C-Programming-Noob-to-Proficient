[**🏠 Home**](../README.md) | [**◀️ System Programming**](../17_System_programming/system_programming.md)



- ### [**Security in C Programming**](#security-in-c-programming-1)

    - [**Buffer Overflow Protection**](#buffer-overflow-protection)
        - Understanding Buffer Overflow and Protection
    - [**Secure Coding Practices**](#secure-coding-practices)
        - Least Privilege, Error Handling, Input validation, 
    - [**Memory Management and Pointer Safety**](#memory-management-and-pointer-safety)
        - Safe Dynamic Memory Allocation
    - [**Cryptography**](#cryptography)
        - Using cryptographic library OpenSSL



# Security in C Programming

C is a powerful language that gives programmers a high degree of control over system resources. However, due to language's low-level capabilities and direct memory access, security vulnerabilities in C programs can lead to severe consequences, including data breaches, system crashes, and unauthorized access.

Let's dive into essential security concepts in C programming, from basic protective measures to advanced security implementations.


## Buffer Overflow Protection

A buffer overflow occurs when data exceeds the buffer’s storage capacity, leading to adjacent memory corruption. This can cause unpredictable behavior, crashes, or security vulnerabilities.

### Understanding Buffer Overflow

Vulnerable code:

```c
#include <stdio.h>
#include <string.h>

void vulnerable_function(char *input) {
    char buffer[64];
    strcpy(buffer, input);  // Dangerous!
    printf("%s\n", buffer);
}

int main() {
    char user_input[256];
    printf("Enter your name: ");
    scanf("%s", user_input);
    vulnerable_function(user_input);
    return 0;
}
```

This code is vulnerable because `strcpy` doesn't check the size of the destination buffer. If the user enters more than 64 characters, it will overflow the buffer.

### Protecting Against Buffer Overflow

1. **Use Safe Functions**: Replace unsafe functions like `strcpy`, `scanf`, and `gets` with their safer counterparts:

2. **Bounds Checking**: Always check array bounds before accessing or writing to arrays.

3. **Stack Canaries**: Modern compilers use stack canaries to detect buffer overflows. Enable them with compiler flags (e.g., `-fstack-protector` for GCC).

4. **Address Space Layout Randomization (ASLR)**: This is an OS-level protection that randomizes memory addresses, making it harder for attackers to predict where specific data is located.

Example:
```c
#include <stdio.h>
#include <string.h>

void safe_function(char *input) {
    char buffer[64];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';  // Ensure null-termination
    printf("%s\n", buffer);
}

int main() {
    char user_input[256];
    printf("Enter your name: ");
    fgets(user_input, sizeof(user_input), stdin);
    safe_function(user_input);
    return 0;
}
```

## Secure Coding Practices

Secure coding practices are essential for writing robust and safe C programs. Here are some key practices:

### Principle of Least Privilege

Only give a program the minimum permissions it needs to function. For example, if your program only needs to read a file, don't give it write permissions.

### Error Handling

Always check return values and handle errors appropriately. Don't ignore errors or exceptions.

```c
#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("important_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // File operations here...

    if (fclose(file) != 0) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

### Input Validation

Always validate and sanitize user input. Here's an example of validating a numeric input:

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_validated_integer() {
    char input[20];
    char *endptr;
    long num;

    while (1) {
        printf("Enter an integer: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }

        num = strtol(input, &endptr, 10);

        if (endptr == input || *endptr != '\n') {
            printf("Invalid input. Please enter a valid integer.\n");
        } else if (num > INT_MAX || num < INT_MIN) {
            printf("Number out of range. Please enter a smaller number.\n");
        } else {
            return (int)num;
        }
    }
}

int main() {
    int valid_num = get_validated_integer();
    printf("You entered: %d\n", valid_num);
    return 0;
}
```

### Sanitizing String Input

Here's an example of sanitizing string input to remove potentially dangerous characters:

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void sanitize_string(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (isalnum((unsigned char)*src) || *src == ' ') {
            *dst = *src;
            dst++;
        }
        src++;
    }
    *dst = '\0';
}

int main() {
    char input[100];
    printf("Enter a string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;  // Remove newline

    printf("Original input: %s\n", input);
    sanitize_string(input);
    printf("Sanitized input: %s\n", input);

    return 0;
}
```

This function removes all characters that are not alphanumeric or spaces, effectively sanitizing the input against many types of injection attacks.


## Memory Management and Pointer Safety

Proper allocation and deallocation of memory to avoid leaks and corruption. Valgrind tool can be used to detect memory issues.

### Safe Dynamic Memory Allocation

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* safe_strdup(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str) + 1;
    char *new_str = malloc(len);
    
    if (new_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    strncpy(new_str, str, len);
    new_str[len - 1] = '\0';  // Ensure null-termination
    
    return new_str;
}

int main() {
    const char *original = "Hello, World!";
    char *copy = safe_strdup(original);
    
    if (copy != NULL) {
        printf("Original: %s\n", original);
        printf("Copy: %s\n", copy);
        free(copy);  // Free allocated memory
    }
    
    return 0;
}
```

This demonstrates safe string duplication with proper memory allocation, error checking, and memory freeing.

## Cryptography

Cryptography involves encoding data to prevent unauthorized access. Common algorithms include AES, RSA, and SHA. Cryptography is essential for securing data in transit and at rest.

### Simple XOR Encryption

Here's a basic example of XOR encryption (Note: This is not secure for real-world use, it's just for demonstration):

```c
#include <stdio.h>
#include <string.h>

void xor_encrypt_decrypt(char *data, size_t data_len, const char *key, size_t key_len) {
    for (size_t i = 0; i < data_len; i++) {
        data[i] ^= key[i % key_len];
    }
}

int main() {
    char message[] = "This is a secret message";
    const char key[] = "KEY123";
    size_t message_len = strlen(message);
    size_t key_len = strlen(key);

    printf("Original: %s\n", message);

    // Encrypt
    xor_encrypt_decrypt(message, message_len, key, key_len);
    printf("Encrypted: ");
    for (size_t i = 0; i < message_len; i++) {
        printf("%02X", (unsigned char)message[i]);
    }
    printf("\n");

    // Decrypt
    xor_encrypt_decrypt(message, message_len, key, key_len);
    printf("Decrypted: %s\n", message);

    return 0;
}
```

For real-world applications, use established cryptographic libraries like OpenSSL or libsodium.

### OpenSSl Encryption

Use libraries like OpenSSL to implement cryptographic functions securely.

Example:
```c
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <string.h>

void encrypt(const unsigned char *plaintext, unsigned char *ciphertext, const unsigned char *key) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, NULL);

    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, strlen((char *)plaintext));
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);

    EVP_CIPHER_CTX_free(ctx);
}

int main() {
    unsigned char key = "01234567890123456789012345678901";
    unsigned char plaintext = "Hello, World!";
    unsigned char ciphertext;

    encrypt(plaintext, ciphertext, key);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}
```

Basic example of a secure socket connection using OpenSSL:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define CHK_NULL(x) if ((x)==NULL) exit(1)
#define CHK_ERR(err,s) if ((err)==-1) { perror(s); exit(1); }
#define CHK_SSL(err) if ((err)==-1) { ERR_print_errors_fp(stderr); exit(2); }

int main() {
    SSL_CTX *ctx;
    SSL *ssl;
    const SSL_METHOD *method;
    int sd;
    struct sockaddr_in server_addr;
    char *hostname = "example.com";
    int port = 443;

    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = TLS_client_method();
    ctx = SSL_CTX_new(method);
    CHK_NULL(ctx);

    ssl = SSL_new(ctx);
    CHK_NULL(ssl);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    CHK_ERR(sd, "socket");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(hostname);

    CHK_ERR(connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)), "connect");

    SSL_set_fd(ssl, sd);
    CHK_SSL(SSL_connect(ssl));

    printf("Connected with %s encryption\n", SSL_get_cipher(ssl));

    SSL_free(ssl);
    close(sd);
    SSL_CTX_free(ctx);
    return 0;
}
```

Compile with `-lssl -lcrypto`options.



[**🏠 Home**](../README.md) | [**◀️ System Programming**](../17_System_programming/system_programming.md)