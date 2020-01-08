#include "processer.h"
#define PORT 8888

int main(int argc, char* argv[])
{
    int s;
    struct sockaddr_in addr_server, addr_client;

    // printf("%d  %d \r\n",sizeof(struct sockaddr), 
                        //  sizeof(struct sockaddr_in));
    s = socket(AF_INET, SOCK_DGRAM, 0); //数据包套接字
    memset(&addr_server, 0, sizeof(addr_server));

    addr_server.sin_family = AF_INET;
    addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_server.sin_port = htons(PORT);

    bind(s, (struct sockaddr*)&addr_server, sizeof(addr_server));

    udpserv_echo(s, (struct sockaddr*)&addr_client);
    return 0;
}