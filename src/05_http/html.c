#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server.h"

#define BUFFER_SIZE 1024

int _read(int client_socket) {
    char buffer[BUFFER_SIZE];

    if ((read(client_socket, buffer, (size_t)sizeof(buffer))) < 0) {
        perror("FAILED TO READ");
        exit(EXIT_FAILURE);
    }
    printf("----- REQUEST -----\n");
    printf("%s", buffer);
    printf("\n-------------------\n");

    memset(buffer, 0, sizeof(buffer));

    return 0;
}

int _write(int client_socket, char *texts) {
    if ((write(client_socket, texts, (size_t)strlen(texts))) < 0) {
        perror("FAILED TO WRITE");
        exit(EXIT_FAILURE);
    }
    printf("----- RESPONSE -----\n");
    printf("%s", texts);
    printf("\n-------------------\n");

    return 0;
}

int main() {
    // PREPARE SERVER SOCKET
    int port = 8000;
    int queue_length = 1;
    int server_socket = _prepare_server_socket(8000, 1);

    // MAIN INFINITE LOOP
    do {
        int client_socket = _accept(server_socket);

        _read(client_socket);

        char *text =
            "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: 15\r\n\r\nこんにちは";
        _write(client_socket, text);

        close(client_socket);

    } while (1);

    close(server_socket);

    return 0;
}