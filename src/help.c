/*
** EPITECH PROJECT, 2021
** help
** File description:
** help
*/

#include "server.h"

void help(int client_socket)
{
    send_reply(client_socket, "214-The following commands are recognized.\r\n");
    send_reply(client_socket, " ABOR ACCT ALLO APPE CDUP CWD  DELE EPRT EPSV FEAT HELP LIST MDTM MKD\r\n");
    send_reply(client_socket, " MODE NLST NOOP OPTS PASS PASV PORT PWD  QUIT REIN REST RETR RMD  RNFR\r\n");
    send_reply(client_socket, " RNTO SITE SIZE SMNT STAT STOR STOU STRU SYST TYPE USER XCUP XCWD XMKD\r\n");
    send_reply(client_socket, " XPWD XRMD\r\n");
    send_reply(client_socket, "214 : Help OK.\r\n");
}
