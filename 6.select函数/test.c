#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>

static __uint32_t child_event = 0;
void select_test(char *argv[]);
void pselect_test(char *argv[]);
void child_sig_handler(int x);

int main(int argc, char *argv[]){

    select_test(argv);
    // pselect_test(argv);
    return 0;
}

void select_test(char *argv[])
{
    fd_set rd; //读文件集合
    struct timeval tv; //时间间隔
    int err;

    FD_ZERO(&rd); //清空文件集合
    FD_SET(0, &rd); //将文件描述符0加入到集合中

    tv.tv_sec = 5; //设置5s的等待超时
    tv.tv_usec = 0;

    err = select(1, &rd, NULL, NULL, &tv);
    if(err == -1)
        perror(argv[0]);
    else if(err)
        printf("标准数据有数据输入，可读\r\n");
    else
        printf("超时，没有数据输入\r\n");
}

void pselect_test(char *argv[])
{
   
    fd_set rd,wr,er;

    /* 设定的信号掩码和原始的信号掩码 */
    sigset_t sigmask, orig_sigmask;
    int err;

    FD_ZERO(&rd); //清空文件集合
    FD_SET(0, &rd); //将文件描述符0加入到集合中
    FD_ZERO(&wr); //清空文件集合
    FD_SET(0, &wr); //将文件描述符0加入到集合中
    FD_ZERO(&er); //清空文件集合
    FD_SET(0, &er); //将文件描述符0加入到集合中


    sigemptyset(&sigmask); //清空信号
    sigaddset(&sigmask, SIGCHLD); //将SIGCHLD信号加入sigmask

    /* 设定信号SIG_BLOCK的掩码sigmask，并将原始的源码加入到orig_sigmask中 */
    sigprocmask(SIG_BLOCK, &sigmask, &orig_sigmask);
    signal(SIGCHLD, child_sig_handler);
    while(1){
        for(;child_event > 0; child_event--){

        }
        err = pselect(1, &rd, &wr, &er, 0, &orig_sigmask);
    
    }

}

void child_sig_handler(int x)
{
    child_event++;
    signal(SIGCHLD, child_sig_handler);

}