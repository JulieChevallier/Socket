# Socket

```

  Socket programming is a way of connecting two nodes on a network to communicate with
each other.
  One socket(node) listens on a particular port at an IP, while the other socket reaches 
out to the other to form a connection. The server forms the listener socket while the 
client reaches out to the server.

```

#### Diagram for server and client model

![](ressources/conceptSocket.png)

## Server
### 1. Socket creation

```
int sockfd = socket(domain, type, protocol)
```
 * __sockfd__: socket descriptor, an integer (like a file-handle)
 * __domain__: integer, specifies communication domain. We use AF_ LOCAL as defined in the POSIX standard for communication between processes on the same host. For communicating between processes on different hosts connected by IPV4, we use AF_INET and AF_I NET 6 for processes connected by IPV6.
 * __type__: communication type
 
*SOCK_STREAM: TCP(reliable, connection oriented)*

*SOCK_DGRAM: UDP(unreliable, connectionless)*
 * __protocol__: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.(man protocols for more details)
 
 ### 2. Bind
 
 ```
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

The bind function binds the socket to the address and port number specified in addr(custom data structure).

### 3. Listen

 ```
int listen(int sockfd, int backlog);
```

It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection.

### 4. Accept

 ```
int new_socket= accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```
It extracts the first connection request on the queue of pending connections for the listening socket, sockfd, creates a new connected socket, and returns a new file descriptor referring to that socket. At this point, the connection is established between client and server, and they are ready to transfer data.

## Client
### 1. Socket creation

```
int sockfd = socket(domain, type, protocol)
```

Exactly same as that of server’s socket creation

### 2. Connect

```
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr. Server’s address and port is specified in addr.

# TCP-IP

#### Diagram for server and client model

![](ressources/Socket_TCP-IP.png)

