/* myclient.c */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "include/ClientInputHelper.h"

#define BUF 1024

int main(int argc, char **argv)
{
    int create_socket;
    char buffer[BUF];
    struct sockaddr_in address;
    int size;

    if (argc < 3)
    {
        printf("Usage: %s serveraddress port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int port = atoi(argv[2]);
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) // create socket for connection
    {
        perror("Socket error");
        return EXIT_FAILURE;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_aton(argv[1], &address.sin_addr);

    // establish connection with server
    if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == 0) // connect to server using socket
    {
        printf("Connection with server (%s) established\n", inet_ntoa(address.sin_addr));
        size = recv(create_socket, buffer, BUF - 1, 0);
        if (size > 0)
        {
            buffer[size] = '\0';
            if (strncmp(buffer, "quit", 4) == 0)
            {
                close(create_socket);
                printf("Connection closed. Your IP Address has been blocked.\n");
                return EXIT_SUCCESS;
            }
            printf("%s", buffer);
        }
    }
    else
    {
        perror("Connect error - no server available");
        return EXIT_FAILURE;
    }

    do
    {
        // command communication with server
        printf("Enter command: ");
        fgets(buffer, BUF, stdin);
        commandHandler(buffer, &create_socket);
    } while (strcmp(buffer, "quit\n") != 0);

    close(create_socket);
    return EXIT_SUCCESS;
}
