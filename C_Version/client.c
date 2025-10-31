#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "encryption.h"
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];
    char message[1024];
    int key = 5, bytes_received;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Winsock initialization failed.\n");
        return 1;
    }

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == INVALID_SOCKET) {
        printf("Socket creation failed.\n");
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connection failed.\n");
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server. Type 'exit' to end chat.\n");

    while (1) {
        printf("You: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        encrypt(message, key);
        send(client_socket, message, strlen(message) + 1, 0);

        if (strcmp(message, "exit") == 0)
            break;

        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0)
            break;

        buffer[bytes_received] = '\0';
        decrypt(buffer, key);

        if (strcmp(buffer, "exit") == 0) {
            printf("Server ended chat.\n");
            break;
        }

        printf("Server: %s\n", buffer);
    }

    closesocket(client_socket);
    WSACleanup();
    printf("Client closed.\n");
    return 0;
}
