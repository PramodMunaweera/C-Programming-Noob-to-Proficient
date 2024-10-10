[**🏠 Home**](../README.md) | [**◀️ Concurrency**](../14_Concurrency/concurrency.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)



- ### [**15: Networking**](#networking)

	- [**Networking in C**](#networking-in-c)
	- [**Socket Programming**](#socket-programming)
		- Socket Creation
		- Binding
		- Listening and Accepting Connections
		- Connecting to a Server
		- Sending and Receiving Data
	- [**TCP Programming**](#tcp-programming)
		- [TCP Server](#tcp-server)
		- [TCP Client](#tcp-client)
	- [**UDP Programming**](#udp-programming)
		- [UDP Server](#udp-server)
		- [UDP Client](#udp-client)
	- [**DNS and Hostname Resolution**](#dns-and-hostname-resolution)



# Networking

## Networking in C

Networking allows programs to communicate over computer networks, such as the internet and local networks. The C programming language provides low-level access to networking functions through system calls and libraries. This tutorial focuses on POSIX-compliant systems, which include Unix-like operating systems (Linux, macOS, etc.) and Windows with appropriate libraries.

Key concepts in networking:
- IP addresses and ports
- Sockets
- Protocols (e.g., TCP, UDP)
- Client-server model

To use networking functions in C, include the following headers:

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
```

## Socket Programming

A socket is a software endpoint that acts as a communication channel between two applications running on different or the same computer. It provides a way for these applications to exchange data.

### Socket Creation

Socket creation involves specifying the desired protocol (TCP or UDP), requesting the operating system to create a socket object, and optionally configuring various socket options to tailor the communication behavior.

Create a socket using the `socket()` function:

```c
int socket(int domain, int type, int protocol);
```

Example:
```c
int sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock == -1) {
    perror("Socket creation failed.");
    exit(1);
}
```

### Binding

Binding associates a socket with a specific network address (IP address and port number), making it accessible to other applications that want to connect to it.

Bind a socket to an address and port using the `bind()` function:

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Example:
```c
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
server_addr.sin_port = htons(8080);

if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    exit(1);
}
```

### Listening and Accepting Connections

Listening and Accepting Connections are essential steps in server-side socket programming. Listening mode indicates the server's readiness to accept incoming connection requests, while accepting connections creates new socket objects to handle communication with individual clients, enabling the server to manage multiple connections simultaneously.

For TCP servers, use `listen()` to mark a socket as passive and `accept()` to accept incoming connections:

```c
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

Example:
```c
if (listen(sock, 5) == -1) {
    perror("listen");
    exit(1);
}

struct sockaddr_in client_addr;
socklen_t client_len = sizeof(client_addr);
int client_sock = accept(sock, (struct sockaddr*)&client_addr, &client_len);
if (client_sock == -1) {
    perror("accept");
    exit(1);
}
```

### Connecting to a Server

For TCP clients, use the `connect()` function to establish a connection to a server:

```c
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Example:
```c
struct sockaddr_in server_addr;
memset(&server_addr, 0, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
server_addr.sin_port = htons(8080);

if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
    perror("connect");
    exit(1);
}
```

### Sending and Receiving Data

Use `send()` and `recv()` for TCP, or `sendto()` and `recvfrom()` for UDP:

```c
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
ssize_t recv(int sockfd, void *buf, size_t len, int flags);

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
               const struct sockaddr *dest_addr, socklen_t addrlen);
ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen);
```

## TCP Programming

TCP (Transmission Control Protocol) is a reliable, connection-oriented protocol used for data transmission over the internet. It guarantees delivery of data packets in the correct order and provides error checking and flow control mechanisms to ensure efficient and reliable communication between applications. TCP establishes a virtual connection between two endpoints before data transmission, ensuring that all data is delivered and acknowledged.

### TCP Server

A TCP server is a network application that listens for incoming connection requests on a specified port, establishes a reliable connection with each client using TCP, and handles communication with the connected clients.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("Server listening on port %d\n", PORT);
    
    while(1) {
        // Accept a new connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        // Receive data from the client
        int valread = recv(new_socket, buffer, BUFFER_SIZE, 0);
        printf("Received: %s\n", buffer);
        
        // Send a response
        char *response = "Hello from server";
        send(new_socket, response, strlen(response), 0);
        printf("Response sent\n");
        
        close(new_socket);
    }
    
    return 0;
}
```

### TCP Client

A TCP client is a network application that initiates a connection to a TCP server on a specified port, sends data to the server, and receives responses from the server.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    // Send data to the server
    char *message = "Hello from client";
    send(sock, message, strlen(message), 0);
    printf("Message sent\n");
    
    // Receive response from the server
    int valread = recv(sock, buffer, BUFFER_SIZE, 0);
    printf("Server response: %s\n", buffer);
    
    close(sock);
    return 0;
}
```

## UDP Programming

UDP (User Datagram Protocol) is a connectionless, unreliable protocol used for data transmission over the internet. It does not guarantee delivery of data packets, and packets may arrive out of order or be lost. UDP is suitable for applications that prioritize speed and efficiency over reliability, such as real-time audio and video streaming.

### UDP Server

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFFER_SIZE];
    
    // Create socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    
    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    printf("UDP server listening on port %d\n", PORT);
    
    while (1) {
        int len, n;
        len = sizeof(cliaddr);
        
        n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                     (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        
        char *response = "Hello from UDP server";
        sendto(sockfd, (const char *)response, strlen(response), MSG_CONFIRM,
               (const struct sockaddr *)&cliaddr, len);
        printf("Response sent.\n");
    }
    
    return 0;
}
```

### UDP Client

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[BUFFER_SIZE];
    
    // Create socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    
    // Fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    
    int n;
    socklen_t len;
    
    char *message = "Hello from UDP client";
    sendto(sockfd, (const char *)message, strlen(message), MSG_CONFIRM,
           (const struct sockaddr *)&servaddr, sizeof(servaddr));
    printf("Message sent.\n");
    
    n = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL,
                 (struct sockaddr *)&servaddr, &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    
    close(sockfd);
    return 0;
}
```

## DNS and Hostname Resolution

DNS is a system that translates human-readable domain names into machine-readable IP addresses. It's like a phonebook for the internet, helping computers find each other. When you type a website address, DNS looks up its corresponding IP address, allowing your computer to connect. This process is called hostname resolution.

Use the `getaddrinfo()` function for DNS resolution and to support both IPv4 and IPv6:

```c
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res);
```

Example:

```c
struct addrinfo hints, *res;
int status;

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
hints.ai_socktype = SOCK_STREAM; // TCP

if ((status = getaddrinfo("godotengine.org", "80", &hints, &res)) != 0) {
    fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
    exit(1);
}

// rest of work ...

freeaddrinfo(res); // free the linked list
```


[**🏠 Home**](../README.md) | [**◀️ Concurrency**](../14_Concurrency/concurrency.md) | [**Control Structures ▶️**](../02_Basic_constructs/basic_constructs.md)