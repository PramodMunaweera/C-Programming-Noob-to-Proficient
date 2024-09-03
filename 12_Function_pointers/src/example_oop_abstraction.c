#include <stdio.h>

// Define a "class" using a struct
struct Shape {
    double (*area)(struct Shape*);  // Function pointer for a method
    double width;
    double height;
};

// Define a method for calculating the area of a rectangle
double rectangle_area(struct Shape* shape) {
    return shape->width * shape->height;
}

// Constructor function to initialize a Shape object
void shape_init(struct Shape* shape, double width, double height) {
    shape->width = width;
    shape->height = height;
    shape->area = rectangle_area;  // Assign the appropriate method
}

int main() {
    // Create an instance of Shape (object)
    struct Shape rect;
    shape_init(&rect, 5.0, 3.0);

    // Call the method using the function pointer
    printf("Area of rectangle: %.2f\n", rect.area(&rect));

    return 0;
}