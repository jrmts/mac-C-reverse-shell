#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argv, char *argc[])  {
    // parse server address and port from command line arguments
    if (argv < 3) {
        fprintf(stderr, "Usage: %s <server_address> <port>\n", argc[0]);
        return 0;
    }
    // store server address and port
    const char *server_address = argc[1];
    const char *port = argc[2];

    // create a scoket
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);
    // check if socket creation was successful
    //TODO: handle socket creation error

    // set up the server address structure
    struct sockaddr_in server_addr_struct;
    memset(&server_addr_struct, 0, sizeof(server_addr_struct));
    server_addr_struct.sin_family = AF_INET;
    server_addr_struct.sin_port = htoins(atoi(port));
    server_addr_struct.sin_addr.s_addr = inet_addr(server_address);

    // connect to the server
    int connection_status = connect(network_socket, (struct sockaddr *)&server_addr_struct, sizeof(server_addr_struct));
    if (connection_status == -1) {
        fprintf(stderr, "Error connecting to the server\n");
        close(network_socket);
        return 1;
    }
    // ! missing something?

    // close the socket after use
    close(network_socket);




    
    // end of the main function
    return 0;
}