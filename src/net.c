
#include <stdio.h>          // perror
#include <stdlib.h>         // strtoul
#include <string.h>         // memset
#include <unistd.h>         // close
#include <sys/socket.h>     // socket, connect
#include <netinet/in.h>     // sockaddr_in, htons
#include <arpa/inet.h>      // inet_pton
#include <errno.h>          // errno, EINVAL
#include "net.h"

// This function converts a string representation of a port number into a 16-bit unsigned integer.
int parse_port(const char *port_string, uint16_t *output_port) {
    if (!port_string || !*port_string || !output_port) {
        errno = EINVAL;
        return -1;
    }
    char *end = NULL;
    unsigned long port_value = strtoul(port_string, &end, 10);
    if (*end != '\0' || port_value == 0 || port_value > 65535UL) {
        errno = EINVAL;
        return -1;
    }
    *output_port = (uint16_t)port_value;
    return 0;
}

// This function creates a TCP socket and connects to a remote server.
int connect_to_c2(const char *host, uint16_t port){
    if (!host || !*host || port == 0) {
        errno = EINVAL;
        return -1;
    }
    // create a scoket
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);
    // check if socket creation was successful
    // handle socket creation error
    if (network_socket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // set up the server address structure
    struct sockaddr_in server_addr_struct;
    memset(&server_addr_struct, 0, sizeof(server_addr_struct));
    server_addr_struct.sin_family = AF_INET;
    server_addr_struct.sin_port = htons(port);
    // server_addr_struct.sin_addr.s_addr = inet_addr(server_address);
    if (inet_pton(AF_INET, host, &server_addr_struct.sin_addr) != 1) {
        perror("inet_pton (expect dotted-quad IPv4 like 127.0.0.1)");
        close(network_socket);
        return -1;
    }

    // connect to the server
    int connection_status = connect(network_socket, (struct sockaddr *)&server_addr_struct, sizeof(server_addr_struct));
    if (connection_status == -1) {
        fprintf(stderr, "Error connecting to the server\n");
        close(network_socket);
        return -1;
    }

    return network_socket;
}

