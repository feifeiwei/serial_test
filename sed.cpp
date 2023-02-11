#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <iostream>
#define PORT 18000

using namespace std;

// struct char24{
//     unsigned char data : 24;
// };
struct customStructure {

    customStructure(const string& str):s(str.c_str()) {}
    customStructure& operator=(const string& str)
    {
        s = str.c_str();
        return *this;
    }

    const char* s;
};


#pragma pack(push,1)
struct A    //要发送的数据结构
{
    uint16_t num1;
    uint16_t num2;

    uint8_t num3;
    uint8_t num4;
    uint8_t num5;
    uint8_t num6;

    unsigned char num7[24];  // how to get 24bit type?? string==24bit
    unsigned char num8[24];
    unsigned char num9[24];
    unsigned char num10[63]; // 预留
    
    uint8_t num11; //#校验和
    uint8_t num12;  //#帧尾

};
#pragma pack(pop)

int main(void)
{
    //实例化结构体，并赋值
    A message;
    
    message.num1 = 0xeb90;
    message.num2 = 0x0705;
    message.num3 = 0x8a;
    message.num4 = 0x0;
    message.num5 = 0x1;
    message.num6 = 0x2;
//    message.num7 = "192.168.1.200:18000";
    strcpy((char*)message.num7, "00000192.168.1.200:18000");
    strcpy((char*)message.num8, "00000192.168.1.200:18000");
    strcpy((char*)message.num9, "00000192.168.1.200:18000");
    strcpy((char*)message.num10, "00000000000000000000000000000000000000000000000000000000000keep");
    
    message.num11= 0x4f;
    message.num12= 0xaa;
    //定义socket套字
    int sock;
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr)); //把servaddr内存清零
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    while (1)
    {
        // printf("向服务器发送：%.f, %.f, %d\n",message.num1,message.num2,message.num3);
//        std::cout <<"1: "  << message.num1 << std::endl; //输出16进制
//        std::cout <<"2: "<< message.num2 << std::endl;
//        std::cout <<"3: " <<  +message.num3 << std::endl; //16进制显示
//        std::cout <<"4: " <<  +message.num4 << std::endl;
//        // printf("4: %d\n",message.num4);
//        // printf("4: %d\n",message.num4);
//        // printf("4: %d\n",message.num4);
//        std::cout <<"5: " <<  +message.num5 << std::endl;
//        std::cout <<"6: " <<  +message.num6 << std::endl;
//        std::cout <<"7: " <<  message.num7 << std::endl;
//        std::cout <<"8: " <<  message.num8 << std::endl;
//        std::cout <<"9: " <<  message.num9 << std::endl;
//        std::cout <<"10: " <<  +message.num10 << std::endl;
//        std::cout <<"11: " <<  +message.num11 << std::endl;
//        std::cout <<"--------------------------------------------------"<< std::endl;

        sendto(sock, &message, sizeof(A), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        sleep(1);
        
        break;
    }
    close(sock);
    std::cout <<"Done."<< std::endl;
    
    return 0;
}
