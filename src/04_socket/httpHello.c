#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    // CREATE SERVER SOCKET
    int server_socket;
    int PROTOCOL = 0;
    if ((server_socket = socket(PF_INET, SOCK_STREAM, PROTOCOL)) < 0) {
        perror("FAILED TO OPEN SOCKET");
        exit(EXIT_FAILURE);
    }
    printf("SOCKET HAS BEEN CREATED: %d\n", server_socket);

    // BIND ADDRESS TO SOCKET
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // INADDR_ANY means 0.0.0.0
    server_addr.sin_port = htons(8080);        // convert to Big Endian

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("FAILED TO BIND");
        exit(EXIT_FAILURE);
    }
    printf("BIND TO: %s:%d\n", "0.0.0.0", 8000);

    // LISTEN
    int queueLength = 1;
    if (listen(server_socket, queueLength) < 0) {
        perror("FAILED TO LISTEN");
        exit(EXIT_FAILURE);
    }
    printf("LISTEN: %d\n", 8000);

    // ACCEPT
    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    do {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

        if (client_socket < 0) {
            perror("FAILED TO ACCEPT");
            exit(EXIT_FAILURE);
        }
        printf("ACCEPTED\n");

        // ECHO (RECEIVE AND SEND)
        char read_buffer[1024];
        char write_buffer[1024];

        ssize_t read_size = read(client_socket, read_buffer, (size_t)sizeof(read_buffer));
        if (read_size < 0) {
            perror("FAILED TO RECEIVE");
            exit(EXIT_FAILURE);
        }
        printf("RECEIVED: %s", read_buffer);

        char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 5\r\n\r\nHELLO\0";

        int i;
        for (i = 0; i < 1024; i++) write_buffer[i] = response[i];

        ssize_t write_size = write(client_socket, write_buffer, (size_t)sizeof(write_buffer));
        if (write_size < 0) {
            perror("FAILED TO SEND");
            exit(EXIT_FAILURE);
        }

        printf("SENT: %s", write_buffer);

        close(client_socket);

    } while (1);

    close(server_socket);
}
