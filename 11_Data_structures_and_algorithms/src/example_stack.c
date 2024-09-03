#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Stack {
    int items[MAX];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

int isFull(struct Stack* s) {
    return s->top == MAX - 1;
}

int isEmpty(struct Stack* s) {
    return s->top == -1;
}

void push(struct Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack is full!\n");
    } else {
        s->top++;
        s->items[s->top] = value;
    }
}

int pop(struct Stack* s) {
    if (isEmpty(s)) {
        printf("Stack is empty!\n");
        return -1;
    } else {
        return s->items[s->top--];
    }
}

void printStack(struct Stack* s) {
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

int main() {
    struct Stack s;
    initStack(&s);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    printf("Stack: ");
    printStack(&s);

    printf("Popped: %d\n", pop(&s));
    printf("Stack after pop: ");
    printStack(&s);

    return 0;
}