/*
** EPITECH PROJECT, 2021
** connect
** File description:
** connec
*/

#include "server.h"

void accept_new_connection(int server_socket, int *client_socket)
{
    int addr_size = sizeof(struct sockaddr_in);
    struct sockaddr_in client_addr;

    client_socket[0] = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&addr_size);
}

fd_set connection(fd_set current_sockets)
{
    fd_set ready_sockets;

    ready_sockets = current_sockets;
    if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) {
        perror("select error");
        exit(EXIT_FAILURE);
    }
    return (ready_sockets);
}

fd_set accept_connection(int *client_socket, int server_socket, fd_set current_sockets)
{
    accept_new_connection(server_socket, client_socket);
    FD_SET((*client_socket), &current_sockets);
    send_reply(*client_socket, "220 : Connection Enable\r\n");
    return (current_sockets);
}
