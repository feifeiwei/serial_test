
#include <stdio.h>
#include <string>
#include <iostream>

#include "table_msgs.hpp"
#include "socket_utils.hpp"


//#define PORT 18000

cv::Mat ucharArray2Mat(unsigned char* frame_char, int width, int height, int channel)
{
    cv::Mat image_mat;
    if (channel == 4)
        image_mat = cv::Mat(height, width, CV_8UC4, frame_char);
    if (channel == 3)
        image_mat = cv::Mat(height, width, CV_8UC3, frame_char);
    if (channel == 1)
        image_mat = cv::Mat(height, width, CV_8UC1, frame_char);
    return image_mat;
}



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
//    t33.error_msg = 0x0;
//
//    t33.checkSum = t33.get_checkSum();
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


void t44_init(table_44& t44)
{
    t44.header = 0xeb90;
    t44.data_len = 0x0705;
    t44.msg_code = 0x8a;
    
    
    strcpy((char*)t44.keep, "66keep");
}







int main(int argc, const char *argv[])
{
    if(argc!=5)
    {
        std::cout << "Usage: ./run_demo <t28> <ip> <pull_port> <push_port>" << std::endl;
        return 1;
    }
    
    const std::string test_config = argv[1];
    const std::string _ip = argv[2];
    const std::string pull_port = argv[3];
    const std::string push_port = argv[4];
    
    Socket_pullMsg gt(_ip.c_str(), atoi(pull_port.c_str()));
    Socket_pushMsg ps(_ip.c_str(), atoi(push_port.c_str()));
    
    
    if (test_config=="t28")
    {
        //实例化结构体，并赋值
        table_28 t28;
        table_33 t33;
        
        std::cout <<"waiting for t28 msg..." << std::endl;
        gt.pull_msg<table_28>(t28);
        t33 = t28;
        if (t28.is_equal())
        {
            t33.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else
        {
            t33.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
        t33.checkSum = t33.get_checkSum();
        std::cout <<"pushing t33 msg..." << std::endl;
        ps.push_msg<table_33>(t33);
    }
    else if(test_config=="t29")
    {
        
        table_29 t29;
        table_34 t34;
        std::cout <<"waiting for t29 msg..." << std::endl;
        gt.pull_msg<table_29>(t29);
        t34 = t29;
        if (t29.is_equal()) {
            t34.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
            t34.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
        t34.checkSum = t34.get_checkSum();
        std::cout <<"pushing t34 msg..." << std::endl;
        
        ps.push_msg<table_34>(t34);
    }
    else if(test_config=="t30")
    {
        
        table_30 t30;
        table_35 t35;
        std::cout <<"waiting for t30 msg..." << std::endl;
        gt.pull_msg<table_30>(t30);
        t35 = t30;
        if (t30.is_equal()) {
            t35.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
            t35.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
        t35.checkSum = t35.get_checkSum();
        std::cout <<"pushing t35 msg..." << std::endl;
        
        ps.push_msg<table_35>(t35);
    }
    else if(test_config=="t31")
    {
        
        table_31 t31;
        table_36 t36;
        std::cout <<"waiting for t31 msg..." << std::endl;
        gt.pull_msg<table_31>(t31);
        t36 = t31;
        if (t31.is_equal()) {
            t36.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
            t36.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
        t36.checkSum = t36.get_checkSum();
        std::cout <<"pushing t36 msg..." << std::endl;
        
        ps.push_msg<table_36>(t36);
    }
    else if(test_config=="t32")
    {
        
        table_32 t32;
        table_37 t37;
        std::cout <<"waiting for t32 msg..." << std::endl;
        gt.pull_msg<table_32>(t32);
        t37 = t32;
        if (t32.is_equal()) {
            t37.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
            t37.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
        t37.checkSum = t37.get_checkSum();
        std::cout <<"pushing t37 msg..." << std::endl;
        
        ps.push_msg<table_37>(t37);
    }
    
    else if(test_config=="t38")// 38，29，40
    {
        
        table_38 t38;
        table_39 t39;
        table_40 t40;
        std::cout <<"waiting for t38 msg..." << std::endl;
        gt.pull_msg<table_38>(t38);

        if (t38.is_equal()) {
//            t37.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
//            t37.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
//        t37.checkSum = t37.get_checkSum();
        
        if(t38.query_type== 0x01)
        {
            std::cout <<"pushing t39 msg..." << std::endl;
            ps.push_msg<table_39>(t39);
        }
        else if(t38.query_type == 0x02)
        {
            std::cout <<"pushing t40 msg..." << std::endl;
            ps.push_msg<table_40>(t40);
        }else
        {
            std::cout <<"error pushing msg for ... query type = "<< +t38.query_type << std::endl;
        }
    }
    else if(test_config=="t44")// upload image
    {
        
        std::cout <<"upload image testing..." << std::endl;
        cv::Mat im = cv::imread("/Users/feifeiwei/dog.jpg"); // need change
        std::cout <<"image info: " << im.cols <<" " << im.rows << std::endl;
        table_44 t44;
        int w = 1920;
        int h = 1080;
        unsigned char *data = new unsigned char[w*h*3];//im.data;
        memcpy(data, im.data, h*w*3);
        
        t44.header = 0x1234;
        t44.img_data.reset(data);
        
        ps.push_msg_t44(t44, 1024);
//        auto p = t44.img_data.release();
    //    cv::Mat image_mat = cv::Mat(1080, 1920, CV_8UC3, p);//
    //    cv::imshow("sss", image_mat);
    //    cv::waitKey(5000);
    //    delete p;
        
    }
    

//    std::cout << t28.checkSum << std::endl;
//    std::cout << t33.get_checkSum()<< " " << t33.checkSum << std::endl;
    
    
    
    
    
//
//    Socket_pushMsg sock("127.0.0.1", PORT);
//    sock.send_msg<table_28>(t28);
//    sock.send_msg<table_33>(t33);
//
    
//    std::cout <<"t28 checksum: " << t28.checkSum << std::endl;
//    std::cout <<"t33 checksum: " << t33.checkSum << std::endl;
//
//    std::cout << "------------------------------------------------" << std::endl;
//    table_29 t29;
//    table_34 t34;
//    t29_34_test_init(t29, t34);
//
//    std::cout <<"t29 checksum: " << t29.get_checkSum() << std::endl;
//    std::cout <<"t34 checksum: " << t34.checkSum << std::endl;
//
//
//    std::cout << "------------------------------------------------" << std::endl;
//    table_30 t30;
//    table_35 t35;
//
//    t30_35_test_init(t30, t35);
//    if (t30.is_equal())
//    {
//        std::cout << "30 check out is ok!" << std::endl;
//    }else
//    {
//        std::cout << "check out fails!" << std::endl;
//    }
//    std::cout <<"t30 checksum: " << t30.get_checkSum() << std::endl;
//    std::cout <<"t35 checksum: " << t35.checkSum << std::endl;
//    std::cout << "------------------------------------------------" << std::endl;
//    table_31 t31;
//    table_36 t36;
//    t31_36_test_init(t31, t36);
//
//    std::cout <<"t31 checksum: " << t31.get_checkSum() << std::endl;
//    std::cout <<"t36 checksum: " << t36.checkSum << std::endl;
//
//    std::cout << "------------------------------------------------" << std::endl;
//    table_32 t32;
//    table_37 t37;
//    t32_37_test_init(t32, t37);
//
//    std::cout << "------------------------------------------------" << std::endl;
//    table_38 t38;
//    table_39 t39;
//    table_40 t40;
//    t38_39_40_test_init(t38, t39, t40);
//    std::cout <<"t38 checksum: " << t38.get_checkSum() << std::endl;
//    std::cout <<"t39 checksum: " << t39.get_checkSum() << std::endl;
//    std::cout <<"t40 checksum: " << t40.get_checkSum() << std::endl;
    
//    std::cout << "------------------------------------------------" << std::endl;
//    table_44 t44; // 图像上报
//    t44_init(t44);
//
//    Socket_pullMsg sp("127.0.0.1", PORT);
//    sp.pull_msg_chunk(t44, 1024);
//
//    int w = 1920;
//    int h = 1080;
//
//
//    std::cout << t44.header << std::endl;
//    cv::Mat im = ucharArray2Mat(t44.img_data.release(), w, h, 3);
//////
//    imshow("im",im);
//    cv::waitKey(5000);
//
//    sp.pull_image(im, 640, 427);
//    imshow("im",im);
//    cv::waitKey(0);
//    cv::destroyAllWindows();
//    im.release();
//    Socket_pushMsg sp("127.0.0.1", PORT);
//    cv::Mat frame = cv::imread("/Users/brave_mac/cpp_learn/test_push_img_socket/test_push_img_socket/china.jpg");
//
//    sp.push_image(frame, 640, 427);
    
    
    return 0;
}


