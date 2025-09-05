## Goal
Develop a C-based reverse shell backdoor for macOS to learn and gain hands-on experience in C programming and macOS internals.

## Modules:
- main.c: Entry point
- config.h: Constants (C2 IP, port, retry delay)
- net.c/h: TCP connection logic
- shell.c/h: Spawning interactive shell
- utils.c/h: Logging, base64, string manipulation
- persistence.c/h: LaunchAgent persistence

## Resources used
### **Core C Programming & System Internals**
- Video: [Linux fork() Introduction](https://www.youtube.com/watch?v=9seb8hddeK4) - Brian Fraser
- Video: [Fork and Exec Linux Programming](https://www.youtube.com/watch?v=l64ySYHmMmY) - Brian Fraser


