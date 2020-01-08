#include "stdio.h"
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

extern void sig_proccess(int signo);
extern void sig_pipe(int sign);

#define PORT        8888

extern void process_conn_client(int s);

int main(int argc, char *argv[])
{
    int s;  //s为socket
    struct sockaddr_in server_addr;

    if(argc == 1){
        printf("请输入服务器地址\r\n");
        return 0;
    }

    signal(SIGINT, sig_proccess);
    signal(SIGPIPE, sig_pipe);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        printf("socket error\r\n");
        return -1;
    }
    
    /* 设置服务器地址 */
    bzero(&server_addr, sizeof(server_addr));  //清零
    server_addr.sin_family = AF_INET;          //协议族    
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //设置本地地址为任意地址
    server_addr.sin_port = htons(PORT);         //设置服务器端口为8888

    /*将用户输入的字符串类型的IP地址转为整形 */
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    /* 连接服务器 */
    connect(s, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    process_conn_client(s);
    
    close(s);
}

// void process_conn_client(int s)
// {
//     ssize_t size = 0;
//     char buffer[1024];

//     /* 使用read和write函数时，文件描述符0表示标准输入，1表示标准输出 */
//     while(1){
//         size = read(0, buffer, 1024); //从标准输入中读取数据放到buffer中
//         if(size > 0 ){
//             write(s, buffer, size); //发送给服务器
//             signal(SIGPIPE, sig_pip);//如果服务器关闭了，会发送信号SIGPIPE
//         }

//         // if(size > 0){ //读到数据
//         //     write(s, buffer, size); //发送给服务器
//         //     size = read(s, buffer, 1024); //从服务器读取数据
//         //     write(1, buffer, size);  //写到标准输出
//         // }
//     }
// }


