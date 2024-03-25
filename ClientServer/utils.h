#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdint.h>

#define MAX_CLIENTS 5
#define BUFFER_SIZE 255

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

char colors[8][10] = {KNRM, KRED, KGRN, KYEL, KBLU, KMAG, KCYN, KWHT};

char* choose_color() {

    int index;
    printf("Colors: 1. RED; 2. GREEN; 3. YELLOW; 4. BLUE; 5. MAGENTA; 6. CYAN; 7. WHITE\n");
    printf("Choose a color: ");
    scanf("%d", &index);

    return colors[index];
}

typedef struct AcceptedSocket {
        int accepted_socket;
        struct sockaddr_in address;
        int error;
        bool accepted_success;
}AcceptedSocket;

AcceptedSocket accepted_sockets[MAX_CLIENTS];
int accepted_sockets_count = 0;

void error(const char *msg) {
    // Displays error message using stderr
    perror(msg);
    exit(EXIT_FAILURE);
}

void send_message_to_all_clients(char *buffer, int sockfd) {

    for (int i = 0; i < accepted_sockets_count; i++) {
        //if (accepted_sockets[i].accepted_socket != sockfd) {
            send(accepted_sockets[i].accepted_socket, buffer, strlen(buffer), 0);
        //}
    }
}

void recieve_and_print_messages(void *arg) {

    int sockfd = (intptr_t)arg;

    char buffer[BUFFER_SIZE];
    
    while (1) {

        ssize_t amount_recieved = recv(sockfd, buffer, BUFFER_SIZE, 0);

        if (amount_recieved <= 0) {
            break;
        }

        buffer[amount_recieved] = '\0';
        printf("%s\n", buffer);

        send_message_to_all_clients(buffer, sockfd);
    }

    close(sockfd);
}

void recieve_and_print_data_in_separate_thread(AcceptedSocket *p_socket) {
    pthread_t id;
    pthread_create(&id, NULL, (void*)recieve_and_print_messages, (void*)(intptr_t) p_socket->accepted_socket);
}
