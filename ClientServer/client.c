
// argv
// [0]FILENAME, [1]SERVER_IPADRESS, [2]PORT
#include "utils.h"

void start_listening_messages_in_new_thread(int sockfd) {
    
    pthread_t id;
    pthread_create(&id, NULL, (void*)recieve_and_print_messages, (void*) (intptr_t)sockfd);
}

char* choose_name() {
    char *name = NULL;
    size_t name_size = 0;
    printf("Enter you name: ");
    ssize_t name_count = getline(&name, &name_size, stdin);
    name[name_count - 1] = '\0';

    return name;
}

void read_console_and_send_to_server(int sockfd) {

    char *name = choose_name();

    char* color = choose_color();

    char buffer[BUFFER_SIZE];

    char *line = NULL;
    size_t line_size = 0;

    start_listening_messages_in_new_thread(sockfd);

    while (1) {

        ssize_t char_count = getline(&line, &line_size, stdin);
        line[char_count - 1] = '\0';
        sprintf(buffer, "%s%s: %s", color, name, line);

        if (char_count > 0) {
            if (strcmp(line, "exit\n") == 0) {
                break;
            } else {
                ssize_t amount_sent = send(sockfd, buffer, strlen(buffer), 0);
            }
        }
        
    } 
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        error("Synthax is: ./[program] [server_adress] [port]\n");
    }

    struct sockaddr_in serv_addr;
    struct hostent *server;

    server = gethostbyname(argv[1]); 
    if (server == NULL) {
        fprintf(stderr, "Error, no such host!\n");
        exit(EXIT_FAILURE);
    }
    int portno = atoi(argv[2]);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    

    if (sockfd < 0) {
        error("Error opening socket! (client)\n");
    } else {
        printf("[Socket] Open!\n");
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr_list[0], (char*)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed!\n");
    } else {
        printf("[Connect] Connected!\n");
    }

    read_console_and_send_to_server(sockfd);

    close(sockfd);
    return 0;
}