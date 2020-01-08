#include <stdio.h>

union _data{
    unsigned short int value;
    unsigned char byte[2];
};

int main(int argc, char *argv[])
{
    union _data order;
    order.value = 0xabcd;
    printf("%d\r\n", sizeof(unsigned short int));
    printf("%d\r\n", sizeof(unsigned char));
    printf("%d\r\n", sizeof(union _data));

    printf("byte[0]=%x\r\n", order.byte[0]);
    printf("byte[1]=%x\r\n", order.byte[1]);
    if((order.byte[0] == 0xcd)&&(order.byte[1] == 0xab)){
        printf("本机为小端字节序\r\n");
    }else if((order.byte[1] == 0xcd)&&(order.byte[0] == 0xab)){
         printf("本机为大端字节序\r\n");
    }

}