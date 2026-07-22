/*
    Task 4
    ABC Bank Client
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int clientSocket;

    struct sockaddr_in server;

    char username[20];
    char password[20];
    char transaction[100];
    char reply[100];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr *)&server, sizeof(server));

    
    printf("         ABC Bank Client\n");
   

    printf("Username : ");
    scanf("%s", username);

    printf("Password : ");
    scanf("%s", password);

    if(strcmp(password,"12345")!=0)
    {
        printf("Invalid Login.\n");
        close(clientSocket);
        return 0;
    }

    printf("\nLogin Successful.\n");

    printf("Enter Transaction : ");
    scanf(" %[^\n]", transaction);

    send(clientSocket, transaction, sizeof(transaction), 0);

    recv(clientSocket, reply, sizeof(reply), 0);

    printf("\nServer : %s\n", reply);

    close(clientSocket);

    return 0;
}
