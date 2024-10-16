[**🏠 Home**](../README.md) | [**◀️ Low-Level Programming**](../16_Low_level_programming/low_level_programming.md) | [**Security in C Programming ▶️**](../18_Security_in_c_programming/security_in_c_programming.md)



- ### [**System Programming**](#system-programming-1)

    - [**Interprocess Communication (IPC)**](#interprocess-communication-ipc)
        - Pipes
        - FIFOs (Named Pipes)
        - Message Queues
        - Shared Memory
        - Semaphores
    - [**Signal Handling**](#signal-handling)
        - Signals in UNIX
        - Signal Handling Functions
        - Signal Masking
        - Real-time Signals
    - [**POSIX API and System Calls**](#posix-api-and-system-calls)
        - File I/O (open, read, write, close)
        - Process Management (fork, exec, wait)
        - Memory Management (mmap, munmap)



# System Programming

System programming focuses on developing software that provides services to the system or interacts with itl. This typically involves working with operating system services, hardware, and performing tasks like managing processes, memory, and file systems.

The C language, due to its low-level capabilities, is widely used for system programming, especially in UNIX-like operating systems.


## Interprocess Communication (IPC)

Interprocess Communication (IPC) allows processes to exchange data. IPC mechanisms include pipes, FIFOs, message queues, shared memory, and semaphores.

###  Pipes

Pipes allow communication between a parent and child process. They provide a unidirectional data stream.

Example:

```c
#include <stdio.h>#include <unistd.h>int main() {
    int pipefds[2];
    char buffer[30];

    if (pipe(pipefds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {  // Child process
        close(pipefds[0]);
        write(pipefds[1], "Hello!", 14);
        close(pipefds[1]);
    } else {  // Parent process
        close(pipefds[1]);
        read(pipefds[0], buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);
        close(pipefds[0]);
    }

    return 0;
}
```


###  FIFOs (Named Pipes)

FIFOs are similar to pipes but allow unrelated processes to communicate.

Example:

```c
#include <stdio.h>#include <stdlib.h>#include <unistd.h>#include <fcntl.h>#include <sys/stat.h>#define FIFO_NAME "/tmp/my_fifo"int main() {
    mkfifo(FIFO_NAME, 0666);

    pid_t pid = fork();
    if (pid == 0) {  // Child process
        int fd = open(FIFO_NAME, O_WRONLY);
        write(fd, "Hello!", 16);
        close(fd);
    } else {  // Parent process
        int fd = open(FIFO_NAME, O_RDONLY);
        char buffer[30];
        read(fd, buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);
        close(fd);
    }

    unlink(FIFO_NAME);
    return 0;
}
```

###  Message Queues

Message queues allow processes to exchange structured messages, which makes synchronization simpler compared to pipes.

Message queues allow processes to exchange messages in a queue.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text;
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;

    if (fork() == 0) {
        // Child process
        message.msg_type = 1;
        sprintf(message.msg_text, "Hello!");
        msgsnd(msgid, &message, sizeof(message), 0);
    } else {
        // Parent process
        msgrcv(msgid, &message, sizeof(message), 1, 0);
        printf("Received: %s\n", message.msg_text);
        msgctl(msgid, IPC_RMID, NULL);
    }
    return 0;
}
```

###  Shared Memory

Shared memory is the fastest IPC method because multiple processes can access a common memory segment.

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *str = (char*) shmat(shmid, (void*)0, 0);

    if (fork() == 0) {
        // Child process
        sprintf(str, "Hello!");
        shmdt(str);
    } else {
        // Parent process
        wait(NULL);
        printf("Received: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
```

###  Semaphores

Semaphores help manage access to shared resources in a multi-process environment, preventing race conditions.

```c
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;

void* thread_func(void* arg) {
    sem_wait(&sem);
    printf("Thread %d in critical section\n", *(int*)arg);
    sleep(1);
    printf("Thread %d leaving critical section\n", *(int*)arg);
    sem_post(&sem);
    return NULL;
}

int main() {
    pthread_t threads;
    int thread_ids = {1, 2};

    sem_init(&sem, 0, 1);

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);
    return 0;
}
```

## Signal Handling

Signals are used to notify a process of asynchronous events like user interruptions (Ctrl+C), or software exceptions (e.g., division by zero).

###   Signals in UNIX

Common signals:

- `SIGINT`: Interrupt (Ctrl+C)
- `SIGKILL`: Kill the process (non-catchable)
- `SIGTERM`: Termination signal
- `SIGCHLD`: Sent to parent when a child process terminates

###  Signal Handling Functions

`signal()` and `sigaction()` are used to handle signals.

Example:

```c
#include <stdio.h>#include <signal.h>#include <unistd.h>void handle_sigint(int sig) {
    printf("Caught signal %d, exiting...\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);  // Register signal handler
    while (1) {
        printf("Running...\n");
        sleep(1);
    }
    return 0;
}
```

###  Signal Masking

You can block signals from being delivered to a process using `sigprocmask()`.

###  Real-time Signals

Real-time signals provide a way to queue multiple signals and pass additional data with them.

```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handle_rtmin(int sig, siginfo_t *si, void *context) {
    printf("Caught real-time signal %d with value %d\n", sig, si->si_value.sival_int);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_rtmin;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGRTMIN, &sa, NULL);

    union sigval value;
    value.sival_int = 42;
    sigqueue(getpid(), SIGRTMIN, value);

    while (1) {
        printf("Running...\n");
        sleep(1);
    }
    return 0;
}
```

## POSIX API and System Calls

The POSIX API provides a standard interface for system-level programming. Let's cover important system calls:

###  File I/O (open, read, write, close)

File I/O is the cornerstone of system programming.

Example: File Handling

```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, "Hello, world!\n", 14);
    close(fd);

    fd = open("example.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buffer;
    read(fd, buffer, 14);
    buffer = '\0';
    printf("Read from file: %s\n", buffer);
    close(fd);

    return 0;
}
```

###  Process Management (fork, exec, wait)

Process management involves creating and synchronizing processes.

Example: Process creation with `fork` and `exec`

```c
#include <stdio.h>#include <unistd.h>#include <sys/wait.h>int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execl("/bin/ls", "ls", "-l", NULL);  // Child process
    } else {
        wait(NULL);  // Parent waits for child
        printf("Child process completed.\n");
    }
    return 0;
}
```

###  Memory Management (mmap, munmap)

`mmap` allows memory-mapped file access, which provides efficient file I/O by mapping files into the process address space.


Example:
```c
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char *data = mmap(NULL, 14, PROT_READ, MAP_PRIVATE, fd, 0);
    if (data == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    printf("Mapped file content: %.*s\n", 14, data);
    munmap(data, 14);
    close(fd);

    return 0;
}
```


System programming requires a strong grasp of OS internals, IPC, signal handling, and memory management. The POSIX API provides the standard tools for interacting with the OS.



[**🏠 Home**](../README.md) | [**◀️ Low-Level Programming**](../16_Low_level_programming/low_level_programming.md) | [**Security in C Programming ▶️**](../18_Security_in_c_programming/security_in_c_programming.md)