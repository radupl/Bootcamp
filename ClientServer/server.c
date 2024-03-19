#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_CLIENTS 5

void error(const char *msg) {
    // Displays error message using stderr
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    // SOCKET -> BIND -> LISTEN -> ACCEPT -> READ/WRITE -> CLOSE

    if (argc != 2) {
        fprintf(stderr, "Synthax should be: ./[program] [PORT]\n");
        exit(EXIT_FAILURE);
    }

    int sockfd, newsockfd, portno;
    char buffer[255];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;

    // Create a socket
    // IPv4, TCP/IP, 0 (default)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket");
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Convert integer from host byte order to network byte order (big-endian)
    serv_addr.sin_port = htons(portno);

    // Bind the socket to a local address
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding error!");
    }

    // Listening for connection requests
    // Max queue before refusing connections is MAX_CLIENTS
    listen(sockfd, MAX_CLIENTS);

    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &cli_len);

    if (newsockfd < 0) {
        error("Error on accept!");
    }

    while (1) {
        bzero(buffer, 255);

        // Filling the buffer with the message from a client.
        if (read(newsockfd, buffer, 255) < 0) {
            error("Error reading from socket!");
        }

        printf("Client: %s", buffer);

        // Clearing the buffer filled with message from a client.
        bzero(buffer, 255);
        // Filling the buffer with a message from the keyboard (as server).
        fgets(buffer, 255, stdin);
        // Write to client
        if (write(newsockfd, buffer, strlen(buffer)) < 0) {
            error("Error writing to socket!");
        }
        
        if (strncmp("exit", buffer, 4) == 0) {
            break;
        }
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}