## Goal
Develop a C-based reverse shell backdoor for macOS to learn and gain hands-on experience in C programming and macOS internals.

## Modules:
- main.c: Entry point
- config.h: Constants (C2 IP, port, retry delay)
- net.c/h: TCP connection logic
- shell.c/h: Spawning interactive shell
- utils.c/h: Logging, base64, string manipulation
- persistence.c/h: LaunchAgent persistence