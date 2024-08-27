#include <stdio.h>

struct Person {
    char name[50];
    int age;
};

int main() {
    struct Person person = {"John Doe", 30};
    
    // Write to a binary file
    FILE *file = fopen("data.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return 1;
    }
    fwrite(&person, sizeof(struct Person), 1, file);
    fclose(file);

    // Read from a binary file
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