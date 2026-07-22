/*
    Task 4
    ABC Bank Server
    Multi-threaded Server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

void *handleClient(void *arg)
{
    int client = *(int *)arg;
    free(arg);

    char msg[100];

    recv(client, msg, sizeof(msg), 0);

    printf("\nCustomer Request : %s\n", msg);

    strcpy(msg, "Transaction Successful");

    send(client, msg, sizeof(msg), 0);

    printf("Customer Disconnected.\n");

    close(client);

    return NULL;
}

int main()
{
    int serverSocket;
    struct sockaddr_in server;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr *)&server, sizeof(server));

    listen(serverSocket, 5);

   
    printf("      ABC Bank Server Started\n");
    

    while(1)
    {
        int *client = malloc(sizeof(int));

        *client = accept(serverSocket, NULL, NULL);

        printf("\nCustomer Connected.\n");

        pthread_t tid;

        pthread_create(&tid, NULL, handleClient, client);

        pthread_detach(tid);
    }

    close(serverSocket);

    return 0;
}
