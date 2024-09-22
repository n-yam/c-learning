#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

int _bind(int sock, int port) {
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);  // htons() converts the host byte order to network byte order (Big Endian).

    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("FAILED TO BIND ADDRESS");
        exit(EXIT_FAILURE);
    }
    printf("BINDING TO ADDRESS: %s:%d\n", "0.0.0.0", port);
}

int _listen(int sock, int queue_length) {
    if (listen(sock, queue_length) < 0) {
        perror("FAILED TO START LISTENING");
        exit(EXIT_FAILURE);
    }
    printf("START LISTENING\n");
}

int _create_server_socket() {
    int sock;
    int PROTOCOL = 0;

    if ((sock = socket(PF_INET, SOCK_STREAM, PROTOCOL)) < 0) {
        perror("FAILED TO CREATE SERVER SOCKET");
        exit(EXIT_FAILURE);
    }

    // Avoid "Address already in use" error
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    printf("SERVER SOCKET CREATED\n");
    printf("FILE DESCRIPTOR: %d\n", sock);

    return sock;
}

int _prepare_server_socket(int port, int queue_length) {
    int sock = _create_server_socket();

    _bind(sock, port);
    _listen(sock, queue_length);

    return sock;
}

int _accept(int server_socket) {
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
        perror("FAILED TO ACCEPT");
        exit(EXIT_FAILURE);
    }
    printf("ACCEPTED\n");

    return client_socket;
}
