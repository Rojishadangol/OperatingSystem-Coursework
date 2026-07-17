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

    bind(serverSocket,
         (struct sockaddr*)&serverAddr,
         sizeof(serverAddr));

    listen(serverSocket, 5);

    printf("Server is waiting for clients...\n");

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
                printf("No data received.\n");
            }

            close(clientSocket);

            exit(0);
        }

        close(clientSocket);
    }

    return 0;
}
