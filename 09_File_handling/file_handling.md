[**🏠 Home**](../README.md) | [**◀️ C Memory Concepts**](../08_C_memory_concepts/c_memory_concepts.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)



- ### [**09: File Handling**](#09-file-handling-1)

    - [**File I/O**](#file-io)
        - File operations (`fopen()`, `fclose()`, `fread()`, `fwrite()`, etc.)
        - Reading from and writing to files
        - `fgetc()`, `fgets()`, `fputc()`, `fputs()`
        - File positioning `fseek()`, `ftell()`, `rewind()`
        - Error handling `ferror()`, `clearerr()`
    - [**Binary file I/O**](#binary-file-io)
        - Binary file operations
    - [**File system operations**](#file-system-operations)
        - Creating and deleting files/directories
    - [**Advanced file handling concepts**](#advanced-file-handling-concepts)



# **09: File Handling**

## **File I/O**

File Input/Output (I/O) in C allows programs to read from and write to files on the computer's storage. This is crucial for persisting data, processing large datasets, and interacting with the file system.

In C, file operations are primarily handled through the `stdio.h` library, which provides functions for opening, reading, writing, and closing files.


### `fopen()` and `fclose()`

The `fopen()` function is used to open a file, while `fclose()` is used to close it.

Example: [example_fopen.c](./src/example_fopen.c)
```c
#include <stdio.h>

int main() {
    FILE *file;
    file = fopen("example.txt", "r");  // Open file for reading
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    // File operations here
    fclose(file);  // Close the file
    return 0;
}
```

The `fopen()` function takes two arguments: the filename and the mode. Common modes include:
- `"r"`: Read (file must exist)
- `"w"`: Write (creates new file or truncates existing file)
- `"a"`: Append (creates new file or appends to existing file)
- `"r+"`: Read and write (file must exist)
- `"w+"`: Read and write (creates new file or truncates existing file)
- `"a+"`: Read and append (creates new file or appends to existing file)

Always remember to close opened files. Closing an opened file in C is crucial for efficient resource management, data integrity, and error prevention.

### Reading from Files

There are several functions for reading from files:

#### `fgetc()`: Read a single character

Example: [example_fgetc.c](./src/example_fgetc.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        putchar(c);
    }

    fclose(file);
    return 0;
}
```

EOF (End-of-File) is a special character used in C to indicate the end of a file.

#### `fgets()`: Read a line of text

Example: [example_fgets.c](./src/example_fgets.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
    return 0;
}
```

A character buffer is created to store lines of text. The `fgets` function is used to read lines from the file into the buffer until the end of the file is reached.


#### `fscanf()`: Read formatted input

Example: [example_fscanf.c](./src/example_fscanf.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int num;
    char str[50];
    while (fscanf(file, "%d %s", &num, str) == 2) {
        printf("Number: %d, String: %s\n", num, str);
    }

    fclose(file);
    return 0;
}
```

This uses `fscanf` to read integers and strings from the file. The `fscanf` function returns 2 if both an integer and a string are successfully read. The read values are then printed to the console. This process continues until `fscanf` returns a value other than 2, indicating the end of the file or an error. 

### Writing to Files

Similarly, there are functions for writing to files:

#### `fputc()`: Write a single character

Example: [example_fputc.c](./src/example_fputc.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fputc('H', file);
    fputc('e', file);
    fputc('l', file);
    fputc('l', file);
    fputc('o', file);

    fclose(file);
    return 0;
}
```

#### `fputs()`: Write a string

Example: [example_fputs.c](./src/example_fputs.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fputs("Hello, World!\n", file);
    fputs("This is a test.\n", file);

    fclose(file);
    return 0;
}
```

#### `fprintf()`: Write formatted output

Example: [example_fprintf.c](./src/example_fprintf.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int num = 42;
    char *str = "Hello";
    fprintf(file, "Number: %d, String: %s\n", num, str);

    fclose(file);
    return 0;
}
```

### File Positioning

C provides functions to move the file pointer.

#### `fseek()`: Move to a specific position

Example: [example_fseek.c](./src/example_fseek.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fseek(file, 10, SEEK_SET);  // Move 10 bytes from the beginning
    int c = fgetc(file);
    printf("Character at position 10: %c\n", c);

    fseek(file, -5, SEEK_END);  // Move 5 bytes before the end
    c = fgetc(file);
    printf("5th character from the end: %c\n", c);

    fclose(file);
    return 0;
}
```

#### `ftell()`: Get current position

Example: [example_ftell.c](./src/example_ftell.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    printf("File size: %ld bytes\n", size);

    fclose(file);
    return 0;
}
```

#### `rewind()`: Move to the beginning of the file

Example: [example_rewind.c](./src/example_rewind.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fseek(file, 10, SEEK_SET);
    printf("Current position: %ld\n", ftell(file));

    rewind(file);
    printf("After rewind, position: %ld\n", ftell(file));

    fclose(file);
    return 0;
}
```

### Error Handling

C provides functions to check for and clear file handling errors.

#### `ferror()`: Check for errors

Example: [example_ferror.c](./src/example_ferror.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("missing.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    int c = fgetc(file);
    if (ferror(file)) {
        printf("Error reading the file!\n");
    }

    fclose(file);
    return 0;
}
```

#### `clearerr()`: Clear error indicators

Example: [example_clearerr.c](./src/example_clearerr.c)
```c
#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Make an error
    fseek(file, -5, SEEK_SET);
    
    if (ferror(file)) {
        printf("Error occurred.\n");
        clearerr(file);
        printf("Error indicator cleared.\n");
    }

    fclose(file);
    return 0;
}
```

## **Binary file I/O**

Binary file I/O allows us to read and write raw data directly to files. This is useful for storing structured data or for efficiency when dealing with large amounts of data.

Example: [example_binary_file_io.c](./src/example_binary_file_io.c)
```c
#include <stdio.h>

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person person = {"John Doe", 30};
    
    // Writing to a binary file
    FILE *file = fopen("data.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(&person, sizeof(struct Person), 1, file);
    fclose(file);

    // Reading from a binary file
    struct Person person1;
    file = fopen("data.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return 1;
    }
    fread(&person1, sizeof(struct Person), 1, file);
    fclose(file);

    printf("Name: %s, Age: %d\n", person1.name, person1.age);

    return 0;
}
```

## **File System Operations**

C provides functions in `<stdio.h>` and `<sys/stat.h>` for file system operations like creating, renaming and deleting directories.

#### Creating a directory

```c
#include <stdio.h>
#include <sys/stat.h>

int main() {
    int result = mkdir("new_directory", 0777);
    if (result == 0) {
        printf("Directory created successfully.\n");
    } else {
        printf("Failed to create directory.\n");
    }
    return 0;
}
```

#### Deleting a file

```c
#include <stdio.h>

int main() {
    int result = remove("file.txt");
    if (result == 0) {
        printf("File deleted successfully.\n");
    } else {
        printf("Failed to delete file.\n");
    }
    return 0;
}
```

#### Renaming a file

```c
#include <stdio.h>

int main() {
    int result = rename("old_name.txt", "new_name.txt");
    if (result == 0) {
        printf("File renamed successfully.\n");
    } else {
        printf("Failed to rename file.\n");
    }
    return 0;
}
```

## Advanced File Handling Concepts

### Memory-mapped Files

Memory-mapped files allow us to map a file directly into memory, which can be more efficient for certain operations. This is typically done using the `mmap()` function, which is part of the POSIX standard and available on Unix-like systems.

Example: [example_memory_mapped_files.c](./src/example_memory_mapped_files.c)
```c
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char *filepath = "example.txt";
    int fd = open(filepath, O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("Error getting file size");
        close(fd);
        return 1;
    }

    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (file_in_memory == MAP_FAILED) {
        perror("Error mapping file");
        close(fd);
        return 1;
    }

    // Now work with the file as if it were in memory
    printf("File contents: %.*s\n", (int)sb.st_size, file_in_memory);

    // Modifying the memory directly modifies the file
    strncpy(file_in_memory, "Hello, memory-mapped file!", sb.st_size);

    // Unmap the file and close
    if (munmap(file_in_memory, sb.st_size) == -1) {
        perror("Error unmapping file");
    }
    close(fd);

    return 0;
}
```


This concludeslesson on file handling in C that covered basic file operations, binary I/O, file system operations, and some advanced concepts. Remember to always check for errors when performing file operations and to close files when you're done with them.



[**🏠 Home**](../README.md) | [**◀️ C Memory Concepts**](../08_C_memory_concepts/c_memory_concepts.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)