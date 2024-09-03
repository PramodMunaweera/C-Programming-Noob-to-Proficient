[**🏠 Home**](../README.md) | [**◀️ Libraries and Linking**](../10_Libraries_and_linking/libraries_and_linking.md) | [**Function Pointers ▶️**](../12_Function_pointers/function_pointers.md)



- ### [**11: Data Structures and Algorithms**](#11-data-structures-and-algorithms-1)
    - [**Data Structures**](#data-structures)
    	- [Linked Lists](#linked-lists)
    	- [Stack](#stack)
        - [Queue](#queue)
    	- [Trees](#trees)
    - [**Searching Algorithms**](#searching-algorithms)
    	- [Linear search](#linear-search)
    	- [Binary search](#binary-search)
    - [**Sorting Algorithms**](#sorting-algorithms)
    	- [Bubble sort](#bubble-sort)
    	- [Selection sort](#selection-sort)
    	- [Insertion sort](#insertion-sort)
    	- [Quick sort](#quick-sort)
    	- [Merge sort](#merge-sort)
    - [**Advanced Data Structures**](#advanced-data-structures)
        - [Hash Table](#hash-table)
        - [Heap](#heap)
        - [Graph](#graph)


# **11: Data Structures and Algorithms**

## **Data Structures**

Data structures are ways of organizing and storing data in a computer so that it can be accessed and modified efficiently. The choice of data structure often depends on the type of operations we need to perform and the constraints of our system.

### Basic Data Structures

#### Arrays

Arrays are fundamental and serve as a basis for understanding more complex data structures.

Example: [example_arrays.c](./src/example_arrays.c)

```c
#include <stdio.h>

#define SIZE 5

int main() {
    int numbers[SIZE] = {1, 2, 3, 4, 5};
    int sum = 0;

    // Calculate sum of array
    for (int i = 0; i < SIZE; i++) {
        sum += numbers[i];
    }

    printf("Sum of array elements: %d\n", sum);

    // Modify an element
    numbers[2] = 10;

    printf("Modified third element: %d\n", numbers[2]);

    return 0;
}
```

#### Linked Lists

A linked list is a linear data structure where elements are stored in nodes. Each node contains a data field and a reference (link) to the next node in the sequence.

Example: [example_linked_list.c](./src/example_linked_list.c)

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert a node at the beginning of the list
struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Insert a node at the end of the list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;

    head = insertAtBeginning(head, 3);
    head = insertAtBeginning(head, 2);
    head = insertAtBeginning(head, 1);

    printf("Linked List after insertAtBeginning: ");
    printList(head);

    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    printf("Linked List after insertAtEnd: ");
    printList(head);

    return 0;
}
```

#### Stack

A stack is a Last In First Out (LIFO) data structure. Elements are added and removed from the same end, called the top of the stack.

Example: [example_stack.c](./src/example_stack.c)

```c
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
```

#### Queue

A queue is a First In First Out (FIFO) data structure. Elements are added at one end (rear) and removed from the other end (front).

Example: [example_queue.c](./src/example_queue.c)

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

struct Queue {
    int items[MAX];
    int front;
    int rear;
};

void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(struct Queue* q) {
    return (q->rear == MAX - 1);
}

int isEmpty(struct Queue* q) {
    return (q->front == -1);
}

void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
    } else {
        if (isEmpty(q)) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            initQueue(q);
        }
        return item;
    }
}

void printQueue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
    } else {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

int main() {
    struct Queue q;
    initQueue(&q);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);

    printf("Queue: ");
    printQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printf("Queue after dequeue: ");
    printQueue(&q);

    return 0;
}
```

### Trees

Trees are hierarchical data structures consisting of nodes connected by edges. The most common type is the binary tree, where each node has at most two children.

#### Binary Trees

A binary tree is a tree data structure in which each node has at most two children, referred to as the left child and the right child.

Example: [example_binary_tree.c](./src/example_binary_tree.c)

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Inorder traversal of the binary tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
```

#### Binary Search Trees (BST)

A Binary Search Tree is a binary tree with the property that the left subtree of a node contains only nodes with keys less than the node's key, and the right subtree contains only nodes with keys greater than the node's key.

Example: [example_binary_search_tree.c](./src/example_binary_search_tree.c)

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }

    return root;
}

struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }

    return search(root->right, data);
}

void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");

    int searchKey = 60;
    struct Node* result = search(root, searchKey);
    if (result != NULL) {
        printf("%d found in the BST\n", searchKey);
    } else {
        printf("%d not found in the BST\n", searchKey);
    }

    return 0;
}
```

## Searching Algorithms

### Linear Search

Linear search is a simple searching algorithm that checks each element in the list sequentially until a match is found or the end of the list is reached.

Example: [example_linear_search.c](./src/example_linear_search.c)

```c
#include <stdio.h>

int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;  // Return the index if found
        }
    }
    return -1;  // Return -1 if not found
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;
    
    int result = linearSearch(arr, n, target);
    if (result != -1) {
        printf("Element found at index: %d\n", result);
    } else {
        printf("Element not found in the array\n");
    }
    
    return 0;
}
```
Time Complexity: O(n) in the worst case, where n is the number of elements in the array.

### Binary Search

Binary search is an efficient algorithm for searching a sorted array by repeatedly dividing the search interval in half.

Example: [example_binary_search.c](./src/example_binary_search.c)

```c
#include <stdio.h>

int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;  // Return the index if found
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // Return -1 if not found
}

int main() {
    int arr[] = {11, 12, 22, 25, 34, 64, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 22;
    
    int result = binarySearch(arr, 0, n - 1, target);
    if (result != -1) {
        printf("Element found at index: %d\n", result);
    } else {
        printf("Element not found in the array\n");
    }
    
    return 0;
}
```
Time Complexity: O(log n), where n is the number of elements in the array.

## Sorting Algorithms

### Bubble Sort

Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.

Example: [example_bubble_sort.c](./src/example_bubble_sort.c)

```c
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Unsorted array: ");
    printArray(arr, n);
    
    bubbleSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```
Time Complexity: O(n^2) in the worst and average cases.

### Selection Sort

Selection sort divides the input list into two parts: a sorted portion at the left end and an unsorted portion at the right end. It repeatedly selects the smallest element from the unsorted portion and adds it to the sorted portion.

Example: [example_selection_sort.c](./src/example_selection_sort.c)

```c
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Unsorted array: ");
    printArray(arr, n);
    
    selectionSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```
Time Complexity: O(n^2) in all cases.

### Insertion Sort

Insertion sort builds the final sorted array one item at a time. It iterates through an input array and removes one element per iteration, finds the location it belongs within the sorted list, and inserts it there.

Example: [example_insertion_sort.c](./src/example_insertion_sort.c)

```c
#include <stdio.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Unsorted array: ");
    printArray(arr, n);
    
    insertionSort(arr, n);
    
    printf("Sorted array: ");
    printArray(arr, n);
    
    return 0;
}
```

Time Complexity: O(n^2) in the worst and average cases, but can be O(n) in the best case (when the array is already sorted).

### Quick Sort

Quick sort is a divide-and-conquer algorithm. It works by selecting a 'pivot' element from the array and partitioning the other elements into two sub-arrays, according to whether they are less than or greater than the pivot.

Example: [example_quick_sort.c](./src/example_quick_sort.c)

```c
#include <stdio.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Unsorted array: ");
    printArray(arr, n);

    quickSort(arr, 0, n - 1);
    
    printf("Sorted array: ");
    printArray(arr, n);
    return 0;
}
```

### Merge Sort

Merge sort is an efficient, stable sorting algorithm that uses a divide-and-conquer strategy. It divides the unsorted list into n sublists, each containing one element, then repeatedly merges sublists to produce new sorted sublists until there is only one sublist remaining.

Example: [example_merge_sort.c](./src/example_merge_sort.c)

```c
#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
```

## Advanced Data Structures

### Hash Table

Hash tables are data structures that implement an associative array abstract data type, a structure that can map keys to values.

Example: [example_hash_table.c](./src/example_hash_table.c)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct Node {
    char* key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }

    value = value % TABLE_SIZE;
    return value;
}

void insert(HashTable* table, const char* key, int value) {
    unsigned int index = hash(key);
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

int search(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    Node* current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return -1;  // Key not found
}

// Delete a key-value pair from the hash table
void delete(HashTable* table, const char* key) {
    unsigned int index = hash(key);
    Node* current = table->buckets[index];
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) {
                // If it's the first node in the bucket
                table->buckets[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Free all memory used by the hash table
void freeHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = table->buckets[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        table->buckets[i] = NULL;
    }
}

int main() {
    HashTable table = {0};
    insert(&table, "apple", 5);
    insert(&table, "banana", 7);
    insert(&table, "cherry", 11);

    printf("Value of 'banana': %d\n", search(&table, "banana"));
    printf("Value of 'grape': %d\n", search(&table, "grape"));

    return 0;

    delete(&table, "banana");
    printf("Value of 'banana' after deletion: %d\n", search(&table, "banana"));

    freeHashTable(&table);
}
```

### Heap

Heap is a special type of binary tree where the value of each node is either greater than or equal to (in a max heap) or less than or equal to (in a min heap) the values of its children. This property ensures that the root node always contains the maximum (in a max heap) or minimum (in a min heap) element in the entire tree.

Example: [example_heap.c](./src/example_heap.c)

```c
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
```

### Graph

A graph is a non-linear data structure consisting of nodes (vertices) and edges. Graphs are used to represent networks, relationships, and many other real-world problems.

There are two main ways to represent a graph:

- **Adjacency Matrix:** A 2D array where arr[i][j] represents an edge from vertex i to vertex j.
- **Adjacency List:** An array of linked lists, where each list represents the neighbors of a vertex.

Example: [example_graph.c](./src/example_graph.c)

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjacencyList[MAX_VERTICES];
    int numVertices;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++)
        graph->adjacencyList[i] = NULL;

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        Node* temp = graph->adjacencyList[v];
        printf("\nAdjacency list of vertex %d\n", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjacencyList[vertex];
    while (temp) {
        if (!visited[temp->vertex])
            DFS(graph, temp->vertex, visited);
        temp = temp->next;
    }
}

void BFS(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjacencyList[currentVertex];
        while (temp) {
            if (!visited[temp->vertex]) {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }
            temp = temp->next;
        }
    }
}

int main() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    printGraph(graph);

    printf("\nDepth First Search (starting from vertex 0): ");
    int visited[MAX_VERTICES] = {0};
    DFS(graph, 0, visited);

    printf("\nBreadth First Search (starting from vertex 0): ");
    BFS(graph, 0);

    return 0;
}
```


[**🏠 Home**](../README.md) | [**◀️ Libraries and Linking**](../10_Libraries_and_linking/libraries_and_linking.md) | [**Function Pointers ▶️**](../12_Function_pointers/function_pointers.md)