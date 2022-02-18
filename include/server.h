/*
** EPITECH PROJECT, 2021
** server
** File description:
** server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>

#ifndef SERVER_H_
#define SERVER_H_

int password(char message[], int client_socket, int error_checking);

int false_password(char message[], int client_socket, int error_checking);

int login(char message[], int client_socket);

void send_reply(int client_socket, char message[]);

void help(int client_socket);

void accept_new_connection(int server_socket, int *client_socket);

fd_set connection(fd_set current_sockets);

fd_set accept_connection(int *client_socket, int server_socket, fd_set current_sockets);

#endif
