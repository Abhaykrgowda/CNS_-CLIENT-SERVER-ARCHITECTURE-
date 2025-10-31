#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "encryption.h"

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    char message[1024];
    int key = 5;
    int client_len, bytes_received;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock initialization failed.\n");
        return 1;
    }

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Bind failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 3) == SOCKET_ERROR) {
        printf("Listen failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port 8080...\n");

    client_len = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);

    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed.\n");
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    printf("Client connected. Type 'exit' to end chat.\n");

    while (1) {
        // Receive message
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0)
            break;

        buffer[bytes_received] = '\0';
        decrypt(buffer, key);

        if (strcmp(buffer, "exit") == 0) {
            printf("Client ended chat.\n");
            break;
        }

        printf("Client: %s\n", buffer);

        // Send response
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        if (strcmp(message, "exit") == 0) {
            encrypt(message, key);
            send(client_socket, message, strlen(message) + 1, 0);
            break;
        }

        encrypt(message, key);
        send(client_socket, message, strlen(message) + 1, 0);
    }

    closesocket(client_socket);
    closesocket(server_socket);
    WSACleanup();
    printf("Server closed.\n");
    return 0;
}
