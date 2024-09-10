[**🏠 Home**](../README.md) | [**◀️ Preprocessor Directives and Macros**](../13_Preprocessor_directives_and_macros/preprocessor_directives_and_macros.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)



- ### [**14: Concurrency**](#14-concurrency)

	- [**Multithreading**](#multithreading)
		- POSIX Threads(pthreads)
		- Thread Creation and Management
		- Thread Synchronization

	- [**Asynchronous I/O**](#asynchronous-io)
		- I/O operations without blocking the main execution thread

	- [**Atomic Operations**](#atomic-operations)
		- Using atomic variables and operations for lock-free programming

	- [**Thread Barriers**](#memory-barriers-and-synchronization)
		- Ensuring proper memory ordering in concurrent programs on multi-core processors

	- [**Advanced Concepts**](#advanced-concepts)
		- Thread Pools
		- Futures and Promises

	- [**Best Practices and Common Pitfalls**](#best-practices-and-common-pitfalls)



# Concurrency

Concurrency in programming refers to the ability of a program to execute multiple tasks simultaneously. In C, concurrency can be achieved through various mechanisms, primarily multithreading and asynchronous I/O. The main benefits of concurrency include:

- Improved performance on multi-core processors
- Better responsiveness in interactive applications
- Efficient utilization of system resources

But, concurrent programming also introduces challenges such as race conditions, deadlocks, and increased complexity in program design. So, better understanding of concurrency concepts is essential for using them avoiding pitfalls.

## Multithreading

Multithreading is a programming concept where a single process can have multiple threads of execution running concurrently. Each thread runs independently but shares the same memory space within the process.

### POSIX Threads (pthreads)

POSIX Threads, commonly known as pthreads, is a standardized C language threads programming interface for "Unix-like" operating systems. To use pthreads in your C program, include the `<pthread.h>` header.

When compiling the program, link the pthread library using the `-pthread` flag:

```
gcc -pthread program.c -o program
```

### Thread Creation and Management

To create a new thread, use the `pthread_create` function:

```c
int pthread_create(pthread_t *thread, const pthread_attr_t *attr,void *(*start_routine) (void *), void *arg);
```

To wait for a thread to finish, use `pthread_join`:

```c
int pthread_join(pthread_t thread, void **retval);
```


Example of creating a thread:

```c
#include <pthread.h>
#include <stdio.h>

void *thread_function(void *arg) {
    printf("Thread is running\n");
    return NULL;
}

int main() {
    pthread_t thread;
    int result = pthread_create(&thread, NULL, thread_function, NULL); // Create new thread
    if (result != 0) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    
    pthread_join(thread, NULL); // Wait for thread to finish
    printf("Thread has finished\n");
    return 0;
}
```
### Passing Arguments to Threads and Returning Values from Threads

In C, when creating threads using the pthread library, arguments can be passed to threads via pointers. Likewise, returning values from threads is possible using pointers and the pthread_join function.

**Key Concepts:**

- **Passing arguments:** Threads in C can only accept a single `void*` argument, we usually pass a pointer to a structure or scalar value (cast to `void*`).
- **Returning values:** The thread function returns a `void*`, so any return value needs to be allocated dynamically and cast to `void*`. The main thread can then retrieve this value using `pthread_join`.

Example:

```c
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Function
void* calculate_square(void* arg) {
    int num = *(int*)arg;
    int* result = (int*)malloc(sizeof(int));  // Allocate memory to store the result
    *result = num * num;  // Calculate square
    return (void*)result; // Return result
}

int main() {
    pthread_t thread;
    int number = 5;  // Number to calculate square of
    int* result;  // Pointer to hold the returned value

    // Create a thread and pass argument
    pthread_create(&thread, NULL, calculate_square, &number);

    // Wait for the thread to finish and get the result
    pthread_join(thread, (void**)&result);

    // Print result
    printf("Square of %d is %d\n", number, *result);

    // Free the allocated memory
    free(result);

    return 0;
}
```

**Break down of code**

- **Argument passing:** We pass the address of the integer (`&number`) to the thread function. Inside the thread, it is cast to `int*` and dereferenced to get the value.
- **Returning values:** The thread function returns a pointer to a dynamically allocated memory (`result`) that holds the computed square.
- **Retrieving the value:** `pthread_join(thread, (void**)&result)` captures the return value and assigns it to `result`.
- **Memory management:** `malloc()` is used to allocate memory for the return value, and `free()` is used to release it after use.


### Thread Synchronization

Thread synchronization is crucial to prevent race conditions and ensure proper coordination between threads.

#### Mutexes

Mutexes (mutual exclusion locks) are used to protect shared resources from concurrent access.

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_lock(&lock); // Lock
// Critical section
pthread_mutex_unlock(&lock); // Unlock
```

Example:

```c
#include <stdio.h>
#include <pthread.h>

int shared_counter = 0;
pthread_mutex_t lock;  // Mutex variable

// Routine
void* increment_counter(void* arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);    // Lock
        shared_counter++;             // Critical section
        pthread_mutex_unlock(&lock);  // Unlock
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Init mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    // Print value of shared_counter
    printf("Counter value: %d\n", shared_counter);

    return 0;
}
```

**Break down of code**

- **Mutex Initialization:** `pthread_mutex_init(&lock, NULL)` initializes the mutex.
- **Locking the Mutex:** `pthread_mutex_lock(&lock)` ensures that only one thread can access the critical section at a time.
- **Critical Section:** The increment of `shared_counter` is the critical section that must be protected by the mutex.
- **Unlocking the Mutex:** `pthread_mutex_unlock(&lock)` allows other threads to enter the critical section.
- **Mutex Destruction:** `pthread_mutex_destroy(&lock)` cleans up the mutex after use.

#### Condition Variables

Condition variables allow threads to synchronize based on the value of data.

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

pthread_mutex_lock(&lock);
while (condition_is_false) {
    pthread_cond_wait(&cond, &lock);
}
// Do work
pthread_mutex_unlock(&lock);

// In another thread:
pthread_mutex_lock(&lock);
// Change condition
pthread_cond_signal(&cond);
pthread_mutex_unlock(&lock);
```

Example:

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // For sleeping

// Shared data
int product_stock = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;  // Mutex
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;   // Condition

// Customer thread function: waits for the product to be available
void* customer_thread(void* arg) {
    pthread_mutex_lock(&lock);  // Lock the mutex

    // Wait until the product is available
    while (product_stock < 1) {
        printf("Customer is waiting for the product to be available...\n");
        pthread_cond_wait(&cond, &lock);  // Wait for condition signal from supplier
    }

    // Product is now available, customer buys it
    product_stock -= 1;
    printf("Customer is purchasing the product with stock: %d\n", product_stock);

    pthread_mutex_unlock(&lock);  // Unlock the mutex
    return NULL;
}

// Supplier thread function: fills the product and signals the customer
void* supplier_thread(void* arg) {
    pthread_mutex_lock(&lock);  // Lock the mutex

    // Simulate some delay in supplying the product
    printf("Supplier is preparing the product...\n");
    sleep(3);  // Simulate time taken to supply the product

    // Update the stock (make product available)
    product_stock += 10;  // Supplier fills 10 units of the product

    // Signal the customer that the product is now available
    printf("Supplier has stocked the product.\n");
    pthread_cond_signal(&cond);  // Signal the waiting customer

    pthread_mutex_unlock(&lock);  // Unlock the mutex
    return NULL;
}

int main() {
    pthread_t supplier, customer;

    // Init mutex and condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    // Create customer thread (it will wait for the product)
    pthread_create(&customer, NULL, customer_thread, NULL);

    // Create supplier thread (it will supply the product)
    pthread_create(&supplier, NULL, supplier_thread, NULL);

    // Wait for threads to finish
    pthread_join(supplier, NULL);
    pthread_join(customer, NULL);

    // Destroy the mutex and condition variable
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
```

**Break down of code**

- **Mutex and Condition Variable:**

    - `pthread_mutex_t lock`: Used to protect the shared variable `product_stock`.
    - `pthread_cond_t cond`: The condition variable used for signaling.

- **Thread 1 (`customer_thread`):**

    - Locks the mutex.
    - Waits for the condition to be signaled (`pthread_cond_wait`). This function atomically releases the mutex and waits for the condition.
    - Once the condition is met, the mutex is re-acquired, and the thread proceeds.

- **Thread 2 (`supplier_thread`):**

    - Locks the mutex.
    After simulating work (sleep for 3 seconds), it resupplies `product_stock += 10` and signals the condition variable (`pthread_cond_signal`).
    This wakes up the waiting thread (Thread 1).

- **Thread Synchronization:**

    - Thread 1 waits for the condition to be met, while Thread 2 performs work and signals Thread 1 when it's ready to proceed.
    
- **`pthread_cond_wait` and `pthread_cond_signal`:**

    - `pthread_cond_wait` waits for the condition and releases the mutex.
    - `pthread_cond_signal` wakes up one thread waiting on the condition variable.


## Asynchronous I/O

Asynchronous I/O allows a program to initiate I/O operations without blocking the main execution thread. In C, you can use the POSIX AIO library for asynchronous I/O operations.

```c
#include <aio.h>

struct aiocb cb;
char buffer[BUFFER_SIZE];

memset(&cb, 0, sizeof(struct aiocb));
cb.aio_fildes = fd;
cb.aio_buf = buffer;
cb.aio_nbytes = sizeof(buffer);
cb.aio_offset = 0;

if (aio_read(&cb) == -1) {
    // Handle error
}

// Do other work while I/O is in progress

// Check for completion
while (aio_error(&cb) == EINPROGRESS) {
    // Wait or do other work
}

ssize_t ret = aio_return(&cb);
if (ret == -1) {
    // Handle error
} else {
    // Process the read data
}
```

Example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <aio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

// Function to perform other tasks while the asynchronous read is in progress
void do_other_work() {
    printf("Doing other work...\n");
    usleep(500000); // Sleep for 500 milliseconds
}

int main() {
    // Open the file for reading
    FILE *fp = fopen("example.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        return 1; // Error: Exit with an error code
    }

    // Initialize the asynchronous I/O control block
    struct aiocb cb;
    memset(&cb, 0, sizeof(cb));

    // Set up the control block parameters
    cb.aio_fildes = fileno(fp); // File descriptor associated with the file
    cb.aio_buf = malloc(BUFFER_SIZE); // Allocate memory for the buffer
    cb.aio_nbytes = BUFFER_SIZE; // Number of bytes to read

    // Start the asynchronous read operation
    if (aio_read(&cb) != 0) {
        perror("aio_read");
        fclose(fp);
        free((void *)cb.aio_buf);
        return 1; // Error: Exit with an error code
    }

    printf("Asynchronous read started. Doing other work...\n");

    // Wait for the asynchronous read to complete or encounter an error
    while (aio_error(&cb) == EINPROGRESS) {
        do_other_work();
    }

    // Get the result of the asynchronous read
    ssize_t num_read = aio_return(&cb);
    if (num_read == -1) {
        perror("aio_return");
    } else {
        printf("\nRead %zd bytes from the file:\n%s\n", num_read, (char *)cb.aio_buf);
    }

    // Clean up resources
    fclose(fp);
    free((void *)cb.aio_buf);

    return 0;
}
```

Link the libraries (real-time library in this case) and compile:

```
gcc -o main main.c -lrt
```

## Atomic Operations

Atomic operations are indivisible operations that complete in a single step relative to other threads. They are essential for lock-free programming and can improve performance in concurrent programs.

In C11 and later, you can use the `<stdatomic.h>` header for atomic operations.

**Atomic Operations:**

- `atomic_load`: Atomically loads and returns the value of the atomic variable.
- `atomic_store`: Atomically stores a value in the atomic variable.
- `atomic_fetch_add`: Atomically adds a number to the atomic variable and returns its old value.

```c
#include <stdatomic.h>

atomic_int counter = ATOMIC_VAR_INIT(0);

// Atomic increment
atomic_fetch_add(&counter, 1);

// Atomic load
int value = atomic_load(&counter);
```

### Atomic Fetch Add

Example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

atomic_int counter = 0; // Create atomic variable 'counter'

// Function to increment the counter variable
void *increment_counter(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        atomic_fetch_add(&counter, 1); // Atomic increment
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Create the threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Wait for the threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter);

    return 0;
}
```

### Atomic Load and Store

```c
#include <stdatomic.h>
#include <stdio.h>

atomic_int counter = ATOMIC_VAR_INIT(0);

int main() {
    // Atomic store
    atomic_store(&counter, 10);

    // Atomic load
    int value = atomic_load(&counter);

    printf("Final counter value: %d\n", counter);

    return 0;
}
```

### Atomic Compare and Exchange

```c
#include <stdatomic.h>

atomic_int counter = ATOMIC_VAR_INIT(0);

void increment() {
    int old_value, new_value;
    do {
        old_value = atomic_load(&counter);
        new_value = old_value + 1;
    } while (!atomic_compare_exchange_weak(&counter, &old_value, new_value));
}
```

## Thread Barriers

Thread barriers are used to synchronize multiple threads at specific points in their execution. This is particularly useful in scenarios where you need all threads to complete a certain stage of computation before any of them can proceed to the next stage.

Example:

```c
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define BARRIER_COUNT 2

pthread_barrier_t barrier;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    
    for (int i = 0; i < BARRIER_COUNT; i++) {
        // Simulate some work
        sleep(1 + thread_id);  // Sleep for different durations
        
        printf("Thread %d reached barrier %d\n", thread_id, i + 1);
        
        // Wait at the barrier
        int rc = pthread_barrier_wait(&barrier);
        
        if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) {
            printf("Could not wait on barrier\n");
            exit(-1);
        }
        
        // After barrier
        printf("Thread %d passed barrier %d\n", thread_id, i + 1);
    }
    
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    // Initialize the barrier
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy the barrier
    pthread_barrier_destroy(&barrier);
    
    return 0;
}
```

## Advanced Concepts

### Thread Pools

Thread pools are a common pattern for managing a fixed number of worker threads to process tasks from a queue.

```c
#include <pthread.h>
#include <stdlib.h>

#define POOL_SIZE 4

typedef struct {
    void (*function)(void *);
    void *argument;
} Task;

Task task_queue[100];
int task_count = 0;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_cond = PTHREAD_COND_INITIALIZER;

void *worker(void *arg) {
    while (1) {
        Task task;
        pthread_mutex_lock(&queue_mutex);
        while (task_count == 0) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }
        task = task_queue[--task_count];
        pthread_mutex_unlock(&queue_mutex);
        
        (task.function)(task.argument);
    }
    return NULL;
}

void init_thread_pool() {
    pthread_t threads[POOL_SIZE];
    for (int i = 0; i < POOL_SIZE; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }
}

void add_task(void (*function)(void *), void *argument) {
    pthread_mutex_lock(&queue_mutex);
    task_queue[task_count].function = function;
    task_queue[task_count].argument = argument;
    task_count++;
    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}
```

### Futures and Promises

Futures and promises provide a way to synchronize asynchronous operations. While C doesn't have built-in support for futures and promises, you can implement a basic version:

```c
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    int is_ready;
    void *result;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Future;

Future *create_future() {
    Future *future = malloc(sizeof(Future));
    future->is_ready = 0;
    future->result = NULL;
    pthread_mutex_init(&future->mutex, NULL);
    pthread_cond_init(&future->cond, NULL);
    return future;
}

void set_future(Future *future, void *result) {
    pthread_mutex_lock(&future->mutex);
    future->result = result;
    future->is_ready = 1;
    pthread_cond_signal(&future->cond);
    pthread_mutex_unlock(&future->mutex);
}

void *get_future(Future *future) {
    pthread_mutex_lock(&future->mutex);
    while (!future->is_ready) {
        pthread_cond_wait(&future->cond, &future->mutex);
    }
    void *result = future->result;
    pthread_mutex_unlock(&future->mutex);
    return result;
}
```

## Best Practices and Common Pitfalls

1. Always initialize mutexes and other synchronization primitives before use.
2. Use the appropriate synchronization mechanism for your specific use case.
3. Be aware of deadlocks and use techniques like lock ordering to prevent them.
4. Minimize the scope of critical sections to improve concurrency.
5. Use thread-local storage for data that doesn't need to be shared between threads.
6. Be cautious of race conditions and use proper synchronization to prevent them.
7. Use tools like Valgrind and ThreadSanitizer to detect concurrency issues.
9. Concurrency bugs can be hard to reproduce and debug, Test concurrent code thoroughly, as c.

Remember that concurrent programming is complex, and it's essential to have a solid understanding of the underlying concepts before implementing concurrent solutions in production code.

## Resources

Unix Threads in C (CodeVault): https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2

Programming with Threads (Jacob Sorber): https://www.youtube.com/playlist?list=PL9IEJIKnBJjFZxuqyJ9JqVYmuFZHr7CFM

[**🏠 Home**](../README.md) | [**◀️ Preprocessor Directives and Macros**](../13_Preprocessor_directives_and_macros/preprocessor_directives_and_macros.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)