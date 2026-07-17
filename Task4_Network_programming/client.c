#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    char username[20];
    char password[20];
    char message[100];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(clientSocket,
              (struct sockaddr*)&serverAddr,
              sizeof(serverAddr)) < 0)
    {
        printf("Connection failed.\n");
        return 1;
    }

    printf("Connected to Server.\n");

    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    getchar();

    if(strcmp(username,"admin") != 0 ||
       strcmp(password,"1234") != 0)
    {
        printf("Authentication Failed.\n");

        close(clientSocket);
        return 0;
    }

    printf("Authentication Successful.\n");

    printf("Enter Message: ");
    fgets(message,sizeof(message),stdin);

    if(strlen(message) <= 1)
    {
        printf("Message cannot be empty.\n");

        close(clientSocket);
        return 0;
    }

    write(clientSocket,message,strlen(message));

    printf("Message Sent Successfully.\n");

    close(clientSocket);

    return 0;
}
