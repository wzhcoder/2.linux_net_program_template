#include "processer.h"

#define buf_len 256

void udpserv_echo(int s, struct sockaddr *client)
{
    int n;
    char buf[buf_len];
    socklen_t len;
    while(1){
        len = sizeof(*client);
        n = recvfrom(s, buf, buf_len, 0, client, &len);
        sendto(s, buf, n, 0, client, len);
        printf("接受到的数据为:%s\r\n",buf);
    }
}

void udpclie_echo(int s, struct sockaddr *to)
{
    char buff[buf_len] = "UDP_TEST";
    struct sockaddr_in from;
    socklen_t len;
    len = sizeof(struct sockaddr);
    sendto(s, buff, buf_len, 0, to ,len);
    recvfrom(s, buff, buf_len, 0, to, &len);
    //recvfrom是阻塞IO模型，没有接受到数据时，程序会一直等待，不占用cpu资源
    printf("客户端接受到的数据为:%s\r\n",buff);
}