#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "table_msgs.hpp"



#define PORT 18000


class Socket_pullMsg
{
public:
    Socket_pullMsg(const char* ip_receive, int port):
    ip_receive(ip_receive), port(port), flag_pull(true)
    {
//        init socket pull msg.
        sockrc = socket(AF_INET, SOCK_DGRAM, 0);
        pulladdr.sin_family = AF_INET;
        pulladdr.sin_port = htons(port);
        pulladdr.sin_addr.s_addr = inet_addr(ip_receive);
         //not using std::
        if (bind(sockrc, (struct sockaddr*)&pulladdr, sizeof(pulladdr))<0)
        {
            flag_pull = false;
        }
    }
    
    template<class T>
    void pull_msg();
    
    void pull_image(cv::Mat& im, int width, int height) //接收图像
    {
        if(!flag_pull)
        {
            std::cerr << "bind fails for socket pull msg." << std::endl;
            return;
        }
        
        //设置缓冲区
        int optval=width*height*10;
        int optLEn=sizeof(int);
        setsockopt(sockrc,SOL_SOCKET,SO_RCVBUF,(char*)&optval,optLEn);
        
        int buffer;
        socklen_t len = sizeof(pulladdr);
        recvfrom(sockrc,&buffer,sizeof(buffer),0,(struct sockaddr*)&pulladdr,&len);
        
        unsigned char *data=new unsigned char[height*width*3];
        
        if(buffer==300)
        {
            for(int i=0;i<height;i=i+1)
            {
              int rec=recvfrom(sockrc,data+i*width*3,sizeof(unsigned char)*width*3,0,(struct sockaddr*)&pulladdr,&len);
             }
            memcpy(im.data,data,sizeof(unsigned char)*width*height*3);
        }
        
        
    }
    
    bool get_flag() //是否可以接收消息
    {
        return flag_pull;
    }
    
    ~Socket_pullMsg()
    {
        close(sockrc);
    }
    
    
private:
    
    std::string ip_receive;
    int port;
    bool flag_pull; //是否可以拉取数据
    
    struct sockaddr_in pulladdr;
    int sockrc; //定义socket套字 接收消息，图像等
    
};


class Socket_pushMsg
{
public:
    Socket_pushMsg(const char* ip_send, int port):
    ip_send(ip_send), port(port)
    {
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
    
    void push_image(unsigned char* data, int width, int height)
    {
        int optval=height*width*10; //设置缓冲区
        int optLEn=sizeof(int);
        setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&optval,optLEn);

        int buf;
//        recvfrom(sock,&buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
    }
    
    ~Socket_pushMsg()
    {
        close(sock);
    }
    
private:
    std::string ip_send;
    int port;
    struct sockaddr_in servaddr;
    int sock; //定义socket套字，  发送消息，图像等
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


void t30_35_test_init(table_30& t1, table_35& t2)
{
    t1.header = 0xeb90;
    t1.data_len = 0x0705;
    t1.msg_code = 0x8a;
    t1.control_type = 0x0;
    
    t1.track_isBegin = 0x1;     // object detector start or stop. 00=stop 01=strat
    t1.track_pattern = 0x2;    // object pattern
    t1.track_principle = 0x3; //
    t1.track_id_manual = 0x2;
    t1.track_conf = 0x22;   //
    t1.track_maximum = 0x2; //
    t1.track_free=0x1; //
    
    strcpy((char*)t1.keep, "keep"); //4bit
    
    t1.checkSum = 0x1653;//t1.get_checkSum();
    t1.tail = 0xaa;
    
    t2 = t1;
    t2.msg_code = 0x0;
    t2.checkSum = t2.get_checkSum();
    
}


void t31_36_test_init(table_31& t1, table_36& t2)
{
    t1.header = 0xeb90;
    t1.data_len = 0x0705;
    t1.msg_code = 0x8a;
    t1.control_type = 0x0;
    
    t1.alart_isBegin = 0x0;     // object detector start or stop. 00=stop 01=strat
    strcpy((char*)t1.alart_port, "00000192.168.1.200:18000");
    t1.alart_trigger_mode = 0x0; //
    t1.alart_classes = 0x0;
    t1.alart_threat_level = 0x0;   //
    t1.unknownObj_alart_conf = 0x0; //
    t1.alart_free = 0x0; //
    
    strcpy((char*)t1.keep, "keep"); //4bit
    
    t1.checkSum = 0x1653;//t1.get_checkSum();
    t1.tail = 0xaa;
    
    t2 = t1;
    t2.msg_code = 0x0;
    t2.checkSum = t2.get_checkSum();
    
}


void t32_37_test_init(table_32& t1, table_37& t2)
{
    t1.header = 0xeb90;
    t1.data_len = 0x0705;
    t1.msg_code = 0x8a;
    t1.control_type = 0x0;
    
    t1.obj_classes = 0x32;
    
    strcpy((char*)t1.keep, "keep"); //4bit
    
    t1.checkSum = 0x1653;//t1.get_checkSum();
    t1.tail = 0xaa;
    
    t2 = t1;
    t2.msg_code = 0x0;
    t2.checkSum = t2.get_checkSum();
}


void t38_39_40_test_init(table_38& t1, table_39& t39, table_40& t40)
{
    t1.header = 0xeb90;
    t1.data_len = 0x0705;
    t1.msg_code = 0x8a;
    t1.query_type = 0x01;
    
    t39.error_msg = 0x1;
    t40.error_msg = 0x1;
    
    
}


int main(void)
{
    //实例化结构体，并赋值
    table_28 t28;
    table_33 t33;
    t28_33_test_init(t28, t33);
    
    Socket_pushMsg sock("127.0.0.1", PORT);
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
    
    std::cout <<"t29 checksum: " << t29.get_checkSum() << std::endl;
    std::cout <<"t34 checksum: " << t34.checkSum << std::endl;
    
    
    std::cout << "------------------------------------------------" << std::endl;
    table_30 t30;
    table_35 t35;
    
    t30_35_test_init(t30, t35);
    if (t30.is_equal())
    {
        std::cout << "30 check out is ok!" << std::endl;
    }else
    {
        std::cout << "check out fails!" << std::endl;
    }
    std::cout <<"t30 checksum: " << t30.get_checkSum() << std::endl;
    std::cout <<"t35 checksum: " << t35.checkSum << std::endl;
    std::cout << "------------------------------------------------" << std::endl;
    table_31 t31;
    table_36 t36;
    t31_36_test_init(t31, t36);
    
    std::cout <<"t31 checksum: " << t31.get_checkSum() << std::endl;
    std::cout <<"t36 checksum: " << t36.checkSum << std::endl;
    
    std::cout << "------------------------------------------------" << std::endl;
    table_32 t32;
    table_37 t37;
    t32_37_test_init(t32, t37);
    
    std::cout << "------------------------------------------------" << std::endl;
    table_38 t38;
    table_39 t39;
    table_40 t40;
    t38_39_40_test_init(t38, t39, t40);
    std::cout <<"t38 checksum: " << t38.get_checkSum() << std::endl;
    std::cout <<"t39 checksum: " << t39.get_checkSum() << std::endl;
    std::cout <<"t40 checksum: " << t40.get_checkSum() << std::endl;
    
    Socket_pullMsg sp("127.0.0.1", PORT);
    
    cv::Mat im = cv::Mat(427,640,CV_8UC3);;  // h w
    sp.pull_image(im, 640, 427);
    imshow("im",im);
    cv::waitKey(0);
    cv::destroyAllWindows();
    im.release();
    
    return 0;
}

