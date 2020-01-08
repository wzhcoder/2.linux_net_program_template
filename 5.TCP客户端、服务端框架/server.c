#include "stdio.h"
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT        8888
#define BACKLOG     2

extern void sig_proccess(int signo);
extern void sig_pipe(int sign);
extern void process_conn_server(int s);

int main(int argc, char *argv[])
{
    int ss, sc;  //ss服务器的socket描述付, sc 客户端的socket 
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int err;
    pid_t pid;

    signal(SIGINT, sig_proccess);
    signal(SIGPIPE, sig_pipe);

    ss = socket(AF_INET, SOCK_STREAM, 0);
    if(ss < 0){
        printf("socket error\r\n");
        return -1;
    }
    
    /* 设置服务器地址 */
    bzero(&server_addr, sizeof(server_addr));  //清零
    server_addr.sin_family = AF_INET;          //协议族    
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //本地地址,字节序转换，主机字节序转为网络字节序
    server_addr.sin_port = htons(PORT);         //服务器端口 ，主机字节序转为网络字节序

    /* 绑定地址结构到套接字 */
    err = bind(ss, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(err < 0){
        printf("bind error\r\n");
        perror("bind");
        return -1;
    }
    /* 设置帧听 */
    err = listen(ss, BACKLOG);
    if(err < 0){
        printf("listen error\r\n");
        return -1;
    }


    while(1){
        socklen_t addrlen = sizeof(struct sockaddr);
        /* 接受客户端连接 */
        sc = accept(ss , (struct sockaddr*)&client_addr, &addrlen);
        if(sc < 0){  //出错
            continue; //结束本次循环
        }

        /* 建立一个新的进程处理到来的连接 */
        pid = fork();  //分叉进程
        if(pid == 0){  //子进程中
            close(ss); //关闭服务器帧听
            process_conn_server(sc); //处理连接
        }else{          //父进程中
            close(sc); //关闭客户端连接
        }
    }
}

/* 服务器对客户端的处理 */
// void process_conn_server(int s)
// {
//     ssize_t size = 0;
//     char buffer[1024];

//     while(1){
//         size = read(s, buffer, 1024); //从套接字中读取数据放到buffer中
//         if(size == 0){ //没有数据
//             return ;   //退出函数
//         }

//         write(1, buffer, size);
//         // sprintf(buffer, "%d bytes\n",size); //向buffer追加“x bytes”       
//         // write(s, buffer, strlen(buffer)+1);//发送给客户端
//     }
// }