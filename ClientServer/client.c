
// argv
// [0]FILENAME, [1]SERVER_IPADRESS, [2]PORT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg) {
    // Displays error message using stderr
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Synthax is: ./[program] [server_adress] [port]\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[255];

    int portno = atoi(argv[2]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error("Error opening socket! (client)");
    }

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "Error, no such host!");
        exit(EXIT_FAILURE);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr_list[0], (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed!");
    }

    while (1) {
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);

        if (write(sockfd, buffer, strlen(buffer)) < 0) {
            error("Error on writing");
        }

        bzero(buffer, 255);

        if (read(sockfd, buffer, 255) < 0) {
            error("Error on reading");
        }

        printf("Server: %s", buffer);

        if (strncmp("exit", buffer, 4) == 0) {
            break;
        }
    } 

    close(sockfd);
    return 0;
}