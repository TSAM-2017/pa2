#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <glib.h>
#include <sys/socket.h>
#include <unistd.h>

//Naming the server
const char *SERVER_NAME = "localhost";
const int server_port = 8800;

// CONSTANTS

// Maximum number of concurrent connections
#define MAX_CONNECTIONS 10

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



void requestHandler(int i){
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
    // bellow line was causing errors
    // char message[4095];
}

// Close connection
void closeConnection(int i){
    shutdown(connections[i], SHUT_RDWR);
    close(connections[i]);
    connections[i] = 0;
}

int main(int argc, char* argv[]){
    return 0;
}
