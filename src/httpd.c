#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


const char *LOG_FILE = "log_file.log";
#define PORT 1500

//FUNCTIONS
void setup();
void sendMessage();
void closeConnection();

//VARIBLES
char message[512];
int sockfd, r;
struct sockaddr_in server, client;

// LOG FILE
FILE *log_fd;

void setup(){

    // Open log file
    log_fd = fopen(LOG_FILE, "a");
    if(log_fd == NULL){
        printf("Failed to open the log file.\n");
    }

    // Create sockets
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) > 0){
        printf("New socket created\n");
    }else if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Failed creating a new socket");
        exit(EXIT_FAILURE);
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if(bind(sockfd, (struct sockaddr *) &server, sizeof(server)) == 0){
        printf("Binding to socket");
        exit(EXIT_FAILURE);
    }

    for (;;){
        if(listen(sockfd, 10) < 0){
            perror("Server listen");
            exit(EXIT_FAILURE);
        }

        socklen_t len = (socklen_t) sizeof(client);
        int connfd = accept(sockfd, (struct sockaddr *) &client, &len);
        if (connfd < 0) {
            perror("Server accept");
            exit(EXIT_FAILURE);
        }

        if(r > 0){
            printf("Connection has already been made to this client\n");
        }

        // Receive from connfd, not sockfd
        ssize_t n = recv(connfd, message, sizeof(message) - 1, 0);
        if (n < 0){
            perror("Receiving message failed");
            exit(EXIT_FAILURE);
        }
        message[n] = '\0';
        fprintf(stdout, "Received: \n%s\n", message);

        sendMessage();
        closeConnection();
    }
}
// send message
void sendMessage(){

    socklen_t len = (socklen_t) sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr *) &client, &len);
    ssize_t n = recv(connfd, message, sizeof(message) - 1, 0);

    r = send(connfd, message, (ssize_t) n, 0);
    if(r < 0){
        perror("Send");
        exit(EXIT_FAILURE);
    }
}

void closeConnection(){
    socklen_t len = (socklen_t) sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr *) &client, &len);
    sockfd = shutdown(connfd, SHUT_RDWR);
    if (sockfd == -1){
        perror("Shutdown");
        exit(EXIT_FAILURE);
    }
    sockfd = close(connfd);
    if (sockfd == -1){
        perror("Close");
        exit(EXIT_FAILURE);
    }
}
int main(){



}
