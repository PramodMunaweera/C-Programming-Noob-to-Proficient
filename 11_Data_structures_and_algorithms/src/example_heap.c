#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int* arr;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->arr = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int index) {
    int parent = (index - 1) / 2;
    if (index > 0 && heap->arr[index] < heap->arr[parent]) {
        swap(&heap->arr[index], &heap->arr[parent]);
        heapifyUp(heap, parent);
    }
}

void insert(MinHeap* heap, int key) {
    if (heap->size >= heap->capacity) {
        printf("Heap is full\n");
        return;
    }
    heap->arr[heap->size] = key;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}

void heapifyDown(MinHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->arr[left] < heap->arr[smallest])
        smallest = left;
    
    if (right < heap->size && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        printf("Heap is empty\n");
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);

    return root;
}

int main() {
    MinHeap* heap = createMinHeap(MAX_SIZE);
    insert(heap, 3);
    insert(heap, 2);
    insert(heap, 1);
    insert(heap, 5);
    insert(heap, 4);

    printf("Extracted min: %d\n", extractMin(heap));
    printf("Extracted min: %d\n", extractMin(heap));

    return 0;
}