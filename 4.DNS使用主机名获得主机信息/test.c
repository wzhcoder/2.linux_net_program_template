#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    char host[] = "www.baidu.com";
    struct hostent *ht = NULL;
    char str[30];

    ht = gethostbyname(host);

    if(ht){
        int i = 0;
        printf("原始域名 : %s\r\n", host);
        printf("主机名 : %s \r\n", ht->h_name);
        printf("协议族 : %s \r\n", (ht->h_addrtype==AF_INET)?"IPV4":"IPV6");
        printf("IP地址的长度 : %d \r\n", ht->h_length);
        /* 打印IP地址 */
        for(i=0;;i++){
            if(ht->h_addr_list[i] != NULL){//ip数组没到末尾
                printf("IP地址 ： %s\r\n", 
                inet_ntop(ht->h_addrtype, ht->h_addr_list[i], str, 30));
                
            }else{
                break;
            }
        }
        /* 打印域名地址 */
        for(i=0;;i++){
            if(ht->h_aliases[i] != NULL){
                printf("域名为：%d ; %s\r\n", i, ht->h_aliases[i]);
            }else{
                break;
            }
        }

    }
    return 0;
}
