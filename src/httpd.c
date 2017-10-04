#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <glib.h>

//Naming the server
const char *SERVER_NAME = "localhost";


// CONSTANTS

// Maximum number of concurrent connections
#define MAX_CONNECTIONS 30

//FUNCTIONS

// Handle the requests that the server receives
void requestHandler(int socket);
// Close the connection in slot number i
void closeConnection(int i);

//VARIBLES

//Monitor all connections in the server
int connections[MAX_CONNECTIONS];
//Monitor all connections that have been active in the server
int countActiveConnections[MAX_CONNECTIONS];
// Sockets
int create_socket, socket_fd;
// Server and client
struct sockaddr_in server, client;

// LOG FILE

// Requirement: ,,In addition, for each request print a single line to a log file"
FILE *log_fd;
//File descriptor socket() returned
int sockfd;
fd_set connfds;



void requestHandler(int){
    //initialise the buffer
    char message[4096];

    ssize_t n = recv(connections[i], message, sizeof(message), 0);

    if(n <= 0){
        if(n == 0){
            printf("There is nothing from the socket to read\n");
        }else{
            printf("Failed to read from socket");
        }
        closeConnection(i);
        return;
    }
    char message[4095] = '\0';
}

// Close connection
void closeConnection(int i){
    socket_fd = shutdown(connfds, SHUT_RDWR);
    if (socket_fd == -1){
        perror("Shutdown");
        exit(EXIT_FAILURE);
    }
    socket_fd = close(connfds);
    if (socket_fd == -1){
        prerror("Close");
        exit(EXIT_FAILURE);
    }
}
int main(){
    char message[512];

    // Create and bind a socket
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
        printf("New socket created\n");
    }else if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Failed creating a new socket");
        exit(EXIT_FAILURE);
    }

}
