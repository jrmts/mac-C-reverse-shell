#pragma once

/**
 * Remap stdin/stdout/stderr to network_socket, then execve(shell_path, argv, envp).
 * On success, this does not return. On failure, returns -1 (and sets errno).
 */
int spawn_shell(int network_socket, const char *shell_path);