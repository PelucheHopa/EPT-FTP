/*
** EPITECH PROJECT, 2021
** server
** File description:
** server
*/

#include "server.h"

int setup_socket(int backlog, char *port)
{
    int server_socket = 0;
    int client_socket = 0;
    struct sockaddr_in serv_addr;

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("Failed to create socket\n");
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(port));
    if (bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        printf("Bind Failed!\n");
    if (listen(server_socket, backlog) == -1) printf("Listen Failed!\n");
    return server_socket;
}

int client_service(int client_socket, int server_socket, fd_set current_sockets)
{
    fd_set ready_sockets;
    int status = 0;
    char message[100];
    
    while (1) {
        ready_sockets = connection(current_sockets);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &ready_sockets)) {
                if (i != server_socket) {
                    for (int x = 0; x < 100; x++) message[x] = '\0';
                    read(i, &message, 100);
                    if (strcmp(message, "QUIT\r\n") == 0) {
                        send_reply(client_socket, "221 Goodbye.\r\n");
                        close(i);
                        FD_CLR(i, &current_sockets);
                        exit(0);
                    }
                    if (status == 0) status = login(message, client_socket);
                    else if (status == 1) status = password(message, client_socket, 1);
                    else if (status == -3) status = false_password(message, client_socket, 1);
                    if (status == 2) {
                        send_reply(client_socket, "230 Login successful.\r\n");
                        status = 3;
                    }
                    if (status == 3 && strcmp(message, "HELP\r\n") == 0) help(client_socket);
                    if (status == 3 && strcmp(message, "NOOP\r\n") == 0)
                        send_reply(client_socket, "200 : Everything is okay\r\n");
                }
            }
        }
    }
}

void launch(char *port)
{
    int server_socket = setup_socket(10, port);
    fd_set current_sockets, ready_sockets;
    int client_socket;
    int pid;

    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);

    while(1) {
        ready_sockets = connection(current_sockets);
        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &ready_sockets)) {
                if (i == server_socket) {
                    current_sockets = accept_connection(&client_socket, server_socket, current_sockets);
                    pid = fork();
                    if (pid == 0) client_service(client_socket, server_socket, current_sockets);
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) return (84);
    if (strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./myftp port path\n");
        printf("       port is the port number on which the server socket listens\n");
        printf("       path is the path to the home directory for the Anonymous user\n");
        exit(0);
    }
    launch(argv[1]);
}
