#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

void udpserv_echo(int s, struct sockaddr *client);
void udpclie_echo(int s, struct sockaddr *to);