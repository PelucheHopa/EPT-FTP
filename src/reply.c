/*
** EPITECH PROJECT, 2021
** reply
** File description:
** reply
*/

#include "server.h"

void send_reply(int client_socket, char message[])
{
    write(client_socket, message, strlen(message));
}

