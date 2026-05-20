#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int s_sock, c_sock;
    struct sockaddr_in server;
    char msg[100];

    // Create socket
    s_sock = socket(AF_INET, SOCK_STREAM, 0);

    if(s_sock < 0)
    {
        printf("Socket creation failed\n");
        exit(1);
    }

    // Server details
    server.sin_family = AF_INET;
    server.sin_port = htons(5555);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket
    if(bind(s_sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Bind failed\n");
        exit(1);
    }

    // Listen for client
    listen(s_sock, 5);

    printf("Server Waiting...\n");

    // Accept client
    c_sock = accept(s_sock, NULL, NULL);

    // Receive message
    recv(c_sock, msg, sizeof(msg), 0);

    printf("Client: %s\n", msg);

    // Send reply
    strcpy(msg, "Hello Client");
    send(c_sock, msg, strlen(msg), 0);

    // Close sockets
    close(c_sock);
    close(s_sock);

    return 0;
}
