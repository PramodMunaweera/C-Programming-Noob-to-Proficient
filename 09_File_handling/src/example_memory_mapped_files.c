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