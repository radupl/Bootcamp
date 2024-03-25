#include "utils.h"

AcceptedSocket* accept_incoming_connection(int server_sockfd) {

    struct sockaddr_in cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    int client_socket = accept(server_sockfd, (struct sockaddr*) &cli_addr, &cli_len);

    AcceptedSocket* accepted_socket = malloc(sizeof(AcceptedSocket));
    accepted_socket->accepted_socket = client_socket;
    accepted_socket->address = cli_addr;
    accepted_socket->accepted_success = client_socket > 0;

    if (!accepted_socket->accepted_success) {
        accepted_socket->error = client_socket;
    } else {
        printf("[Accept] Client connected!\n");
    }

    return accepted_socket;
}

void start_accepting_connections(int server_socket_fd) {

    while (1) {
        AcceptedSocket *client_socket = accept_incoming_connection(server_socket_fd);
        accepted_sockets[accepted_sockets_count++] = *client_socket;
        recieve_and_print_data_in_separate_thread(client_socket);
    }
}

int main(int argc, char *argv[]) {

    // SOCKET -> BIND -> LISTEN -> ACCEPT -> READ/WRITE -> CLOSE

    if (argc != 2) {
        fprintf(stderr, "Synthax should be: ./[program] [PORT]\n");
        exit(EXIT_FAILURE);
    }

    int sockfd, newsockfd, portno;

    struct sockaddr_in serv_addr; 

    // Create a socket
    // IPv4, TCP/IP, 0 (default)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening socket\n");
    } else {
        printf("[Socket] Open!\n");
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // Convert integer from host byte order to network byte order (big-endian)
    serv_addr.sin_port = htons(portno);

    // Bind the socket to a local address
    if (bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding error!\n");
    } else {
        printf("[Bind] Binding succesful!\n");
    }

    // Listening for connection requests
    // Max queue before refusing connections is MAX_CLIENTS
    int listen_result = listen(sockfd, MAX_CLIENTS);

    start_accepting_connections(sockfd);

    close(sockfd);

    return 0;
}