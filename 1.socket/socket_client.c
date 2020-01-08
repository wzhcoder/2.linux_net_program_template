#include "stdio.h"
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT        8888

void process_conn_client(int s);
void sig_pip(int sign);
void sig_pip2(int sign);

int main(int argc, char *argv[])
{
    int s;  //s为socket
    struct sockaddr_in server_addr;

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        printf("socket error\r\n");
        return -1;
    }
    
    /* 设置服务器地址 */
    bzero(&server_addr, sizeof(server_addr));  //清零
    server_addr.sin_family = AF_INET;          //协议族    
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //本地地址
    server_addr.sin_port = htons(PORT);         //服务器端口

    /*将用户输入的字符串类型的IP地址转为整形 */
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    /* 连接服务器 */
    connect(s, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    process_conn_client(s);
}

void process_conn_client(int s)
{
    ssize_t size = 0;
    char buffer[1024];

    /* 使用read和write函数时，文件描述符0表示标准输入，1表示标准输出 */
    while(1){
        size = read(0, buffer, 1024); //从标准输入中读取数据放到buffer中
        if(size > 0 ){
            write(s, buffer, size); //发送给服务器
            signal(SIGPIPE, sig_pip);//如果服务器关闭了，会发送信号SIGPIPE
        }

        // if(size > 0){ //读到数据
        //     write(s, buffer, size); //发送给服务器
        //     size = read(s, buffer, 1024); //从服务器读取数据
        //     write(1, buffer, size);  //写到标准输出
        // }
    }
}

void sig_pip(int sign)
{
    printf("服务器已经关闭\r\n");
}


