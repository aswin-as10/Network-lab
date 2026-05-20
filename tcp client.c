#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    char msg[100];

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        printf("Socket creation failed\n");
        exit(1);
    }

    // server details
    server.sin_family = AF_INET;
    server.sin_port = htons(5555);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // connect to server
    connect(sock, (struct sockaddr*)&server, sizeof(server));

    // send message
    strcpy(msg, "Hello Server");

    send(sock, msg, strlen(msg), 0);

    // receive reply
    recv(sock, msg, sizeof(msg), 0);

    printf("Server: %s\n", msg);

    // close socket
    close(sock);

    return 0;
}
