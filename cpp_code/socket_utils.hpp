//
//  socket_utils.hpp
//  demo-learn
//
//  Created by feifeiwei on 2023/2/19.
//

#ifndef socket_utils_hpp
#define socket_utils_hpp

#include <stdio.h>
#include <iomanip>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "table_msgs.hpp"

class Socket_pushMsg
{
public:
    Socket_pushMsg(const char* ip_send, int port):
    ip_send(ip_send), port(port)
    {
        memset(&servaddr, 0, sizeof(servaddr)); //把servaddr内存清零
        sock = socket(AF_INET, SOCK_DGRAM, 0);
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        servaddr.sin_addr.s_addr = inet_addr(ip_send);
    }
    void push_msg_t44( table_44& t44, int chunk_size=1024) // -1 send once for all data,
    {
        
        int buffer_len = sizeof(table_44) + table_44::width*table_44::height*table_44::channel - 8; //数据总长度 + new
        int chunk = chunk_size; //每次发送长度‘
        unsigned char* data = new unsigned char[buffer_len];
//        unsigned char* header = data; // make pointer point to header
//        std::cout <<"buff len= " << buffer_len << std::endl;
        
        long idx = 0;
        data[idx++] = t44.header >> 8;
        data[idx++] = t44.header & 0xff;
        
        data[idx++] = t44.data_len >> 8;
        data[idx++] = t44.data_len & 0xff;
        
        data[idx++] = t44.msg_code >> 8;
        data[idx++] = t44.msg_code & 0xff;
        
        data[idx++] = t44.msg_class;
        
        data[idx++] = t44.image_id >> 24;
        data[idx++] = t44.image_id >> 16;
        data[idx++] = t44.image_id >> 8;
        data[idx++] = t44.image_id & 0xff;
 
        data[idx++] = t44.pkg_order >> 8;
        data[idx++] = t44.pkg_order & 0xff;
        
        data[idx++] = t44.pkg_type;
        data[idx++] = t44.pkg_total_num;
    
        for (int i=0; i<table_44::width*table_44::height*table_44::channel; i++) {
            data[idx++] = t44.img_data[i];
        }
        
//        cv::Mat im = ucharArray2Mat(t44.img_data.release(), 1920, 1080, 3);
//        imshow("im",im);
//        cv::waitKey(0);
        
        
        for(const auto& c: t44.keep) data[idx++]  = c;
        
        data[idx++] = t44.checkSum >> 8;
        data[idx++] = t44.checkSum & 0xff;
        
        data[idx++] = t44.tail;
        
        assert(buffer_len==idx); //ensure not  missing data.

        while (buffer_len>chunk) {
            ssize_t ret = sendto(sock, data, chunk, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
            buffer_len -= chunk;
            data = data + chunk;
            assert(ret>0);

            
        }
        if(buffer_len){
            ssize_t ret = sendto(sock, data, buffer_len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
            assert(ret>0);
        }
    }
    
    
    
    template<class T>
    void push_msg_chunk(T& table, int chunk_size=1024) //分断发送
    {
        int buffer_len = sizeof(T);
        int chunk = chunk_size; //每次发送长度
    
        unsigned char* data = reinterpret_cast<unsigned char*>(&table);
        
        while (buffer_len>chunk) {
            ssize_t ret = sendto(sock, data, chunk, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
            buffer_len -= chunk;
            data = data + chunk;
            assert(ret>0);
        }
        if(buffer_len){
            ssize_t ret = sendto(sock, &table, buffer_len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
            assert(ret>0);
        }
    }
    
    
    template<class T>
    void push_msg(T& table) //一次性发送
    {
        ssize_t ret = sendto(sock, &table, sizeof(T), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        assert(ret>0);
        
    }
    
    void push_image(const cv::Mat& img, int width, int height)
    {
        int optval=height*width*10; //设置缓冲区
        int optLEn=sizeof(int);
        setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&optval,optLEn);

//        int buf;
        unsigned char* data = img.data;
        int flag=300;
        sendto(sock,&flag,sizeof(flag),0,(struct sockaddr*)&servaddr,sizeof(servaddr));//发送帧头
        
        for(int i=0;i<height;i++)
        {
            sendto(sock,data+i*width*3,sizeof(unsigned char)*width*3,0,(struct sockaddr*)&servaddr,sizeof(servaddr));//一行一行的发送图像
        }
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




class Socket_pullMsg
{
public:
    Socket_pullMsg(const char* ip_receive, int port):
    ip_receive(ip_receive), port(port), flag_pull(true)
    {
//      init socket pull msg.
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
    void pull_msg_chunk(table_44& t44, int chunk_size=1024)
    {
        if(!flag_pull)
        {
            std::cerr << "bind fails for socket pull msg." << std::endl;
            return;
        }
        
        socklen_t len = sizeof(pulladdr);
        int buffer_len = sizeof(table_44) + table_44::width*table_44::height*table_44::channel - 8; //数据总长度 + new
//        std::cout << "\nbuffer_len: " << buffer_len << std::endl; //6220824=1080p
        int chunk = chunk_size; //每次发送长度‘
        unsigned char* data = new unsigned char[buffer_len];
        unsigned char* header = data; // make pointer point to header
        
        while(buffer_len>chunk){
            int ret = recvfrom(sockrc, data, chunk, 0, (struct sockaddr*)&pulladdr, &len);
            buffer_len -= chunk;
            data += chunk;
        }
        
        if (buffer_len) {
            int ret = recvfrom(sockrc, data, buffer_len, 0, (struct sockaddr*)&pulladdr, &len);
        }
        long idx = 0;
        t44.header = (header[idx++] << 8) + header[idx++];
        t44.data_len = (header[idx++] << 8) + header[idx++];
        t44.msg_code = (header[idx++] << 8) + header[idx++];
        t44.msg_class = header[idx++];
        
        t44.image_id = (header[idx++] << 24)+(header[idx++] << 16) +(header[idx++] << 8) + header[idx++];
        t44.pkg_order = (header[idx++] << 8) + header[idx++];
        t44.pkg_type = header[idx++];
        t44.pkg_total_num = header[idx++];

//        for(auto &c : t44.img_data) c = header[idx++]; // img
        for(int i=0; i< table_44::width * table_44::height * table_44::channel; i++)
            t44.img_data[i] = header[idx++];
        
        for(auto &c : t44.keep) c = header[idx++]; //
        
//        t44.checkSum = t44.get_checkSum();
    }
    
    
    
    template<class T>
    void pull_msg(T& table)
    {
        if(!flag_pull)
        {
            std::cerr << "bind fails for socket pull msg." << std::endl;
            return;
        }
        //        unsigned char buffer[buff_size];
        socklen_t len = sizeof(pulladdr);
        int ret = recvfrom(sockrc, &table, sizeof(T), 0, (struct sockaddr*)&pulladdr, &len);
    }
    
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
            {//如果未发生错误， recvfrom 将返回收到的字节数
              recvfrom(sockrc,data+i*width*3,sizeof(unsigned char)*width*3,0,(struct sockaddr*)&pulladdr,&len);
             }
            memcpy(im.data,data,sizeof(unsigned char)*width*height*3);
        }
        
        delete []data; // for new
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



#endif /* socket_utils_hpp */
