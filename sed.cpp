#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <iostream>
#define PORT 18000

// struct char24{
//     unsigned char data : 24;
// };

#pragma pack(push,1)  
struct A    //要发送的数据结构
{
    uint16_t num1;
    uint16_t num2;

    uint8_t num3;
    uint8_t num4;
    uint8_t num5;
    uint8_t num6;

    // char24 num7;
    // char24 num7;
    // char24 num9;

    uint8_t num10;
    uint8_t num11;

};
#pragma pack(pop)

int main(void)
{
    //实例化结构体，并赋值
    A message;  
    message.num1 = 0x90EB;
    message.num2 = 0x0507;
    message.num3 = 125;
    message.num4 = 125;
    message.num5 = 125;
    message.num6 = 125;
    // message.num7 = "192.168.12.1:1630";
    // message.num8 = "192.168.12.1:1630";
    // message.num9 = "192.168.12.1:1630";
    message.num10= 125;
    message.num11= 125;
    //定义socket套字
    int sock;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr)); //把servaddr内存清零
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("172.20.10.12");
    while (1)  
    {
        // printf("向服务器发送：%.f, %.f, %d\n",message.num1,message.num2,message.num3);
        std::cout <<"1: " <<  std::hex << message.num1 << std::endl; //输出16进制
        std::cout <<"2: " <<  std::hex << message.num2 << std::endl;
        std::cout <<"3: " <<  +message.num3 << std::endl; //16进制显示
        std::cout <<"4: " <<  +message.num4 << std::endl;
        // printf("4: %d\n",message.num4);
        // printf("4: %d\n",message.num4);
        // printf("4: %d\n",message.num4);
        std::cout <<"5: " <<  +message.num5 << std::endl;
        std::cout <<"6: " <<  +message.num6 << std::endl;
        // std::cout <<"7: " <<  message.num7 << std::endl;
        // std::cout <<"8: " <<  message.num8 << std::endl;
        // std::cout <<"9: " <<  message.num9 << std::endl;
        std::cout <<"8: " <<  +message.num10 << std::endl;
        std::cout <<"9: " <<  +message.num11 << std::endl;
        std::cout <<"--------------------------------------------------"<< std::endl;

        sendto(sock, &message, sizeof(A), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        sleep(1);
    }
    close(sock);
    return 0;
}
