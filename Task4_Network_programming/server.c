#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    if(bind(serverSocket,
           (struct sockaddr*)&serverAddr,
           sizeof(serverAddr)) < 0)
    {
        printf("Bind Failed.\n");
        close(serverSocket);
        return 1;
    }

    if(listen(serverSocket,5) < 0)
    {
        printf("Listen Failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("TCP Server Started.\n");
    printf("Waiting for client...\n");

    while(1)
    {
        clientSocket = accept(serverSocket, NULL, NULL);

        if(clientSocket < 0)
        {
            printf("Connection Failed.\n");
            continue;
        }

        pid_t pid = fork();

        if(pid == 0)
        {
            printf("\nClient Connected.\n");

            int bytes = read(clientSocket,
                             message,
                             sizeof(message)-1);

            if(bytes > 0)
            {
                message[bytes] = '\0';

                printf("Client Message: %s\n", message);
            }
            else
            {
                printf("Cleint disconnected without sending data.\n");
            }

            printf("Connection Closed.\n");

            close(clientSocket);

            exit(0);
        }
    printf("Session Completed");

        close(clientSocket);
    }

    return 0;
}
