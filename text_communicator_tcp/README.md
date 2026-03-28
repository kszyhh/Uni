# Text Messenger Service with Server-Side Accounts and History

**Author:** Krzysztof Szczepański  
**Course Project:** Network Programming (Programowanie Sieciowe)  
**Date:** January 29, 2026

## Project Overview
This project implements a text chat service using a client-server architecture designed for the Linux environment. It enables simultaneous, real-time communication among multiple users.

## Features
* **Multi-user Communication:** Messages sent by one client are instantly forwarded to all other active users.
* **User Authentication:** Chat access is password-protected. The server verifies login credentials against a local `users.txt` database.
* **Service Discovery:** The client features an automatic server IP detection mechanism in the local network using UDP Multicast, completely eliminating the need for manual configuration.
* **DNS Support:** For manual connections, the client can seamlessly resolve hostnames to IP addresses.
* **Daemon Mode:** The server can operate as a background system service, detached from the terminal, and log events directly to syslog.
* **History & Logging:** All conversations and events (such as logins and disconnections) are archived in a server-side file, and additionally in system logs when running in daemon mode.

## Architecture & Technical Solutions
### Communication Protocols
* **TCP (SOCK_STREAM):** Used for transmitting chat messages and handling the login process. It ensures error-free and ordered data delivery, transmitting data in a binary TLV (Type-Length-Value) format.
* **UDP (SOCK_DGRAM):** Used for the discovery mechanism. The server cyclically broadcasts "Beacon" packets to a multicast address to announce its presence to clients.

### Concurrency
* The server implements a multithreaded model. It creates a separate handler thread for each connected client to allow parallel request processing.
* Access to shared resources, such as the active client list and the history file, is strictly synchronized using mutexes.

### File Structure
* `server.c`: Source code for the server (connection logic, thread handling, daemonization, and logging).
* `client.c`: Source code for the client (user interface, network handling, and the receiving thread).
* `common.h`: Header file containing packet structure definitions, port numbers, and core constants.
* `users.txt`: User database stored in a `login:password` format.
* `Historia.txt` / `chat_historia.txt`: Archive containing all chats and server events.
* `CMakeLists.txt`: Project build script.

## User Manual
1. **Pre-compilation Configuration:** Open the `server.c` file. At the top of the file in the `#define` directives section, change the paths for `users.txt` and `chat_historia.txt` to absolute paths. This is required for the server to access them while running in daemon mode.
2. **Compilation:** Build the project using `cmake` and `make`. Ensure the login data file is located at the absolute path specified in your code.
3. **Running the Server:** Start the server using the `./server` command to view logs in the console, or `./server -d` to run it as a background daemon.
4. **Running the Client:** Open clients in separate terminal windows using `./client`. Select your connection method (automatic discovery or manual IP) and log in using credentials from `users.txt`.
5. **Chatting:** After logging in, you can freely exchange messages with other users. To exit the program safely, type the `exit` command.