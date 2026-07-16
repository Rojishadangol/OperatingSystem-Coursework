#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;

    char message[100];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    listen(serverSocket, 5);

    printf("Server is waiting for connection...\n");

    clientSocket = accept(serverSocket, NULL, NULL);

    printf("Client Connected.\n");

    read(clientSocket, message, sizeof(message));

    printf("Client: %s\n", message);

    close(clientSocket);
    close(serverSocket);

    return 0;
}
