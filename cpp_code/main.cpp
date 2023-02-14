#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "table_msgs.hpp"

#define PORT 18000

using namespace std;



class Socket_tools
{
public:
    Socket_tools(const char* ip_send, const char* ip_receive):
    ip_send(ip_send), ip_receive(ip_receive){
        // init socket.
        memset(&servaddr, 0, sizeof(servaddr)); //把servaddr内存清零
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr(ip_send);
    }
    
    template<class T>
    void send_msg(T& table)
    {
        sendto(sock, &table, sizeof(T), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
    }
    
    template<class T>
    void receive_msg();
    
    
    ~Socket_tools()
    {
        close(sock);
    }
    
    
private:
    std::string ip_send;
    std::string ip_receive;
    
    struct sockaddr_in servaddr;
    int sock; //定义socket套字
};


int main(void)
{
    //实例化结构体，并赋值
    tabele_29_34 message;
    
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
    
    Socket_tools sock("127.0.0.1", "127.0.0.1");
    
    while (1)
    {
        sock.send_msg<tabele_29_34>(message);
        sleep(1);
        break;
    }
    
    std::cout <<"Done."<<  message.get_checkSum() << std::endl;
//    close(sock);
    std::cout <<"Done."<< std::endl;
    
    if (message.is_equal())
    {
        std::cout << "check out is ok!" << std::endl;
    }
    
    return 0;
}

