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


void t28_33_test_init(table_28& t28, table_33& t33)
{
    t28.header = 0xeb90;
    t28.data_len = 0x0705;
    t28.msg_code = 0x8a;
    t28.control_type = 0x0;
    t28.device_ssr = 0x1;
    t28.device_running_mode = 0x2;
//    message.num7 = "192.168.1.200:18000";
    strcpy((char*)t28.addr_rgb, "00000192.168.1.200:18000");
    strcpy((char*)t28.addr_ir, "00000192.168.1.200:18000");
    strcpy((char*)t28.addr_lidar, "00000192.168.1.200:18000");
    strcpy((char*)t28.keep, "keep"); //4bit
    
    t28.checkSum= 0xe35;//0x4f;
    t28.tail= 0xaa;
    
    t33 = t28;
    t33.error_msg = 0x00;
    t33.checkSum = t33.get_checkSum();
}

void t29_34_test_init(table_29& t29, table_34& t34)
{
    t29.header = 0xeb90;
    t29.data_len = 0x0705;
    t29.msg_code = 0x8a;
    t29.control_type = 0x0;
    
    t29.det_isBegin = 0x0;
    t29.det_pattern = 0x0;
    t29.det_dataSource = 0x0;
    t29.preprocess_method = 0x0;
    t29.obj_conf = 0x0;
    t29.obj_rec_conf = 0x0;
    t29.minimum_len = 0x0;
    t29.minimum_width = 0x0;
    
    t29.unknown_det_begin = 0x0;
    strcpy((char*)t29.keep, "keep"); //4bit
    
    t29.checkSum = 0x9551;
    t29.tail = 0xAA;
    
    t34 = t29; //
    t34.error_msg = 0x00;
    t34.checkSum = t34.get_checkSum();
}

int main(void)
{
    //实例化结构体，并赋值
    table_28 t28;
    table_33 t33;
    t28_33_test_init(t28, t33);
    
    Socket_tools sock("127.0.0.1", "127.0.0.1");
    sock.send_msg<table_28>(t28);
    sock.send_msg<table_33>(t33);
        
    if (t28.is_equal())
    {
        std::cout << "check out is ok!" << std::endl;
    }else
    {
        std::cout << "check out fails!" << std::endl;
    }
    std::cout <<"t28 checksum: " << t28.checkSum << std::endl;
    std::cout <<"t33 checksum: " << t33.checkSum << std::endl;
    
    std::cout << "------------------------------------------------" << std::endl;
    table_29 t29;
    table_34 t34;
    t29_34_test_init(t29, t34);
    
    if (t29.is_equal())
    {
        std::cout << "29 check out is ok!" << std::endl;
    }else
    {
        std::cout << "check out fails!" << std::endl;
    }
    std::cout <<"t29 checksum: " << t29.get_checkSum() << std::endl;
    std::cout <<"t34 checksum: " << t34.checkSum << std::endl;
    
    return 0;
}

