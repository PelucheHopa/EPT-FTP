/*
** EPITECH PROJECT, 2021
** login
** File description:
** login
*/

#include "server.h"


int error_login(int status, int client_socket)
{
    if (status == 0) send_reply(client_socket, "530 : Please login with USER and PASS.\r\n");
    if (status == -1) send_reply(client_socket, "530 : Permission denied\r\n");
    if (status == 1) send_reply(client_socket, "530 : Permission denied\r\n");
    if (status != 2) return (-1);
}

int password(char message[], int client_socket, int error_checking)
{
    char tag[] = "PASS";
    int x = 0;

    for (; tag[x] != '\0' && message[x] == tag[x]; x++);
    if (tag[x] == '\0') return (2);
    if (error_checking == 1) error_login(0, client_socket);
    return (1);
}

int false_password(char message[], int client_socket, int error_checking)
{
    char tag[] = "PASS";
    int x = 0;

    for (; tag[x] != '\0' && message[x] == tag[x]; x++);
    if (tag[x] == '\0') {
        send_reply(client_socket, "530 : Login incorrect.\r\n");
        return (0);
    }
    if (error_checking == 1) error_login(0, client_socket);
    return (-3);
}

int checking_login_cmd(int status, char message[])
{
    char tag[] = "USER";
    char user[] = "Anonymous\r\n";
    int x = 0;
    int m = 0;

    for (; tag[x] != '\0' && message[x] == tag[x]; x++);
    if (tag[x] == '\0') {
        x++;
        status = 1;
    }
    if (tag[x] == '\0' && message[x] == '\r') status = -1;
    for (; status == 1 && user[m] != '\0' && message[x] == user[m]; x++, m++);
    if (user[m] == '\0') return (2);
    if (status == 1 && message[x] != '\0' && message[x] != '\r' && message[x] != '\n') return (-2);
    if (status == -1) return (-1);
    return (status);
}

int login(char message[], int client_socket)
{
    int status = 0;

    status = checking_login_cmd(status, message);
    if (status == -2) {
        send_reply(client_socket, "331 Please specify the password.\r\n");
        return (-3);
    }
    if (status == 2) {
        send_reply(client_socket, "331 : Please specify the password.\r\n");
        return (1);
    }
    if (password(message, client_socket, 0) == 2) {
        send_reply(client_socket, "503 : Login with USER first.\r\n");
        return (0);
    }
    else error_login(status, client_socket);
    return (0);
}
