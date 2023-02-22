
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>


#include "table_msgs.hpp"
#include "socket_utils.hpp"
#include <thread>
#include <chrono>
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
//    t1.alart_classes = 0x0;
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
    
//    t1.obj_classes = 0x32;
    
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


//void t44_init(table_44& t44)
//{
//    t44.header = 0xeb90;
//    t44.data_len = 25 + table_44::img_buff_len - 7;
//    t44.msg_code = 0x0707;
//    t44.msg_class = 0x03;
//
//    t44.pkg_type = 0x00;
//
//    t44.image_id = 0x0;
//    t44.pkg_order = 0x00;
//
//
//    memcpy(t44.keep, "00keep",6);
//    t44.tail = 0xaa;
//}





int main(int argc, const char *argv[])
{
    if(argc!=2)
    {
        std::cout << "Usage: ./run_demo <t28>" << std::endl;
        return 1;
    }
    
    const std::string test_config = argv[1];
    // const std::string _ip = argv[2];
    // const std::string pull_port = argv[3];
    // const std::string push_port = argv[4];
    
//
    Socket_pullMsg gt("192.168.1.200", 18000);//atoi(pull_port.c_str()));
    Socket_pushMsg ps("192.168.1.206", 10000);//atoi(push_port.c_str()));
    
//    Socket_pullMsg gt("127.0.0.1", 18000);
//    Socket_pushMsg ps("127.0.0.1", 18000);
    
    
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

            // std::cout << "you check: " << t29.checkSum << std::endl;
            // std::cout << "my check: " << t29.get_checkSum() << std::endl;

        }else{
            t34.error_msg = 0x1;
            std::cout << "you check: " << +t29.checkSum << std::endl;
            std::cout << "my check: " << t29.get_checkSum() << std::endl;


            std::cout << "header: " << +t29.header << std::endl;
            std::cout << "data_len: " << +t29.data_len << std::endl;
            std::cout << "msg_code: " << +t29.msg_code << std::endl;
            std::cout << "control_type: " << +t29.control_type << std::endl;
            std::cout << "det_isBegin: " << +t29.det_isBegin << std::endl;
            std::cout << "det_pattern: " << +t29.det_pattern << std::endl;
            std::cout << "det_dataSource: " << +t29.det_dataSource << std::endl;

            std::cout << "preprocess_method: " << +t29.preprocess_method << std::endl;
            std::cout << "obj_conf: " << +t29.obj_conf << std::endl;
            std::cout << "obj_rec_conf: " << +t29.obj_rec_conf << std::endl;

            std::cout << "minimum_len: " << +t29.minimum_len << std::endl;
            std::cout << "minimum_width: " << +t29.minimum_width << std::endl;
            std::cout << "unknown_det_begin: " << +t29.unknown_det_begin << std::endl;


            std::cout << "keep: " << t29.keep << std::endl;
            

            std::cout << "tail: " << +t29.tail << std::endl;

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
        gt.pull_msg_t31(t31.raw_data, t31.buffer_len);
       int idx = 0;
       // t31.raw_data[idx++] = 144;
       // t31.raw_data[idx++] = 235;
       // t31.raw_data[idx++] = 43;
       // t31.raw_data[idx++] = 0;
       // t31.raw_data[idx++] = 5;
       // t31.raw_data[idx++] = 7;
       // t31.raw_data[idx++] = 3;
       // t31.raw_data[idx++] = 1;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 49;
       // t31.raw_data[idx++] = 57;
       // t31.raw_data[idx++] = 50;
       // t31.raw_data[idx++] = 46;
       // t31.raw_data[idx++] = 49;
       // t31.raw_data[idx++] = 54;
       // t31.raw_data[idx++] = 56;
       // t31.raw_data[idx++] = 46;
       // t31.raw_data[idx++] = 49;
       // t31.raw_data[idx++] = 46;
       // t31.raw_data[idx++] = 50;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 58;
       // t31.raw_data[idx++] = 49;

       // t31.raw_data[idx++] = 56;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;

       // t31.raw_data[idx++] = 1;
       // t31.raw_data[idx++] = 1;
       // t31.raw_data[idx++] = 2;
       // t31.raw_data[idx++] = 3;
       // t31.raw_data[idx++] = 4;
       // t31.raw_data[idx++] = 5;
       // t31.raw_data[idx++] = 0;
       // t31.raw_data[idx++] = 1;
       // t31.raw_data[idx++] = 100;
       // t31.raw_data[idx++] = 200;
       // t31.raw_data[idx++] = 1;

       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 48;
       // t31.raw_data[idx++] = 49;

       // t31.raw_data[idx++] = 206;
       // t31.raw_data[idx++] = 80;
       // t31.raw_data[idx++] = 170;
       // t31.buffer_len = 50;
        
        t31.set_value();
        t36 = t31;

        // t36.tail = 0xaa;
        
//        uint16_t checksum = t31.checkSum;
//        uint16_t my_checksum =  t31.get_checkSum();
        
//        std::cout << "31 ch_sum : " << checksum <<" " << my_checksum << std::endl;
//        std::cout << "36 ch_sum : " << t36.get_checkSum() << std::endl;
        if (t31.is_equal()) {
            t36.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
            t36.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        t36.checkSum = t36.get_checkSum();
        std::cout <<"pushing t36 msg..." << std::endl;

        t36.set_buffer();

        ps.push_msg_36(t36.raw_data, t36.buffer_len);
    }
    else if(test_config=="t32")
    {
        
        table_32 t32;
        table_37 t37;
        std::cout <<"waiting for t32 msg..." << std::endl;
//        gt.pull_msg<table_32>(t32);
        gt.pull_msg_t32(t32.raw_data, t32.buffer_len);
        t32.set_value();
        
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

        t37.set_buffer();
        
        // ps.push_msg<table_37>(t37);
        ps.push_msg_36(t37.raw_data, t37.buffer_len);

    }
    
    else if(test_config=="t38")// 38，29，40
    {
        
        table_38 t38;
        table_39 t39;
        table_40 t40;
        
        std::cout <<"waiting for t38 msg..." << std::endl;
        gt.pull_msg<table_38>(t38);
        // t38.query_type = 0x01;

        if (t38.is_equal()) {
            t39.error_msg = 0x0;
            t40.error_msg = 0x0;
            std::cout << "check out is ok!" << std::endl;
        }else{
            t39.error_msg = 0x1;
            t40.error_msg = 0x1;
            std::cout << "check out fails!" << std::endl;
        }
        
        if(t38.query_type== 0x01)
        {
            t39 = t38;
            t39.checkSum = t39.get_checkSum();
            
            t39.set_buffer();
            std::cout <<"pushing t39 msg..." << std::endl;
//            ps.push_msg<table_39>(t39);
            ps.push_msg_39(t39.raw_data, t39.buffer_len);
            
            
        }
        else if(t38.query_type == 0x02)
        {
            t40 = t38;
            t40.checkSum = t40.get_checkSum();

            std::cout <<"pushing t40 msg..." << std::endl;
            ps.push_msg<table_40>(t40);
        }else
        {
            std::cout <<"error pushing msg for ... query type = "<< +t38.query_type << std::endl;
        }
    }


    else if(test_config=="t44")// upload image
    {
        // ------ get image data --------
        std::cout <<"\nupload image testing..." << std::endl;
        // cv::Mat im = cv::imread("/userdata/223.jpg"); // need change
        // std::cout <<"image info: " << im.cols <<" " << im.rows << std::endl;

        // const char* file_name = "/userdata/223.jpg";
        // FILE* fp = fopen(file_name, "rb");

        // if (fp == NULL) 
        // {
        //     std::cout << "文件" << file_name << "出错或不存在" << std::endl;
        //     exit(-1);
        // }

        // fseek(fp, 0, SEEK_END);
        // int  length=ftell(fp);
        // char* ImgBuffer=(char*)malloc( length* sizeof(char) );
        // fread(ImgBuffer, length, 1, fp);
        // fclose(fp);
        int w = 640;//im.cols;
        int h = 480;//im.rows;
        std::cout <<"read image..." << std::endl;
        std::ifstream is("/userdata/223.jpg", std::ifstream::in | std::ios::binary);


        std::cout <<"read image done..." << std::endl;
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        char* buffer = new char[length];

        std::cout << "文件长度" << length << "== " << w*h*3 << std::endl;
        is.read(buffer, length);
        // delete buffer;

        // img_buff_len = length; //==18066

        unsigned char *raw_img_data = new unsigned char[length];//im.data;
        memcpy(raw_img_data, buffer, length);
        delete buffer;
        
//        for (int i=1000; i < 10000; i++) {
//            std::cout <<"d: " << +data[i] <<" "  << std::endl;
//        }
        // ------ split pkg --------
        table_44 t44;
        table_44::init_info(t44);

        // table_44::width = w;
        // table_44::height = h;
        
        std::cout <<"pkg_total_num: " <<  + t44.pkg_total_num <<" " << std::endl;

//        std::cout << t44 << std::endl;
        for (int j = 0; j < 2000; ++j)
        {
            /* code */
            for (int i = 0; i < t44.pkg_total_num; ++i) // from 1 to end.
            {

                unsigned char *data_tmp = new unsigned char[table_44::img_buff_len]{0}; //default value is 0;
                memcpy(data_tmp, raw_img_data + i * table_44::img_buff_len,  table_44::img_buff_len);

                t44.img_data.reset(data_tmp); //获取每包图像数据
                t44.pkg_order = i;            // 包id
                t44.image_id = j;
                t44.checkSum = t44.get_checkSum(); //

                t44.set_buffer();

                std::cout << +i << ":\n " << t44 << std::endl;
                ps.push_msg_39(t44.push_buffer, t44.buffer_len);
                // ps.push_msg_44_split(t44);
    //            break;
                t44.img_data.reset();

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(300));

        }


        
        for (int i = 0; i < t44.pkg_total_num; ++i) // from 1 to end.
        {

            unsigned char *data_tmp = new unsigned char[table_44::img_buff_len]{0}; //default value is 0;
            memcpy(data_tmp, raw_img_data + i * table_44::img_buff_len,  table_44::img_buff_len);

            t44.img_data.reset(data_tmp); //获取每包图像数据
            t44.pkg_order = i;            // 包id
            t44.image_id = 0x01;
            t44.checkSum = t44.get_checkSum(); //

            t44.set_buffer();

            std::cout << +i << ":\n " << t44 << std::endl;
            ps.push_msg_39(t44.push_buffer, t44.buffer_len);
            // ps.push_msg_44_split(t44);
//            break;
            t44.img_data.reset();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
        

        for (int i = 0; i < t44.pkg_total_num; ++i) // from 1 to end.
        {

            unsigned char *data_tmp = new unsigned char[table_44::img_buff_len]{0}; //default value is 0;
            memcpy(data_tmp, raw_img_data+i*table_44::img_buff_len,  table_44::img_buff_len);

            t44.img_data.reset(data_tmp); //获取每包图像数据
            t44.pkg_order = i;            // 包id

            t44.image_id = 0x02;
            t44.checkSum = t44.get_checkSum();
            t44.set_buffer();

            std::cout << +i << ":\n " << t44 << std::endl;
            ps.push_msg_39(t44.push_buffer, t44.buffer_len);
            // ps.push_msg_44_split(t44);
//            break;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        
        for (int i = 0; i < t44.pkg_total_num; ++i) // from 1 to end.
        {

            unsigned char *data_tmp = new unsigned char[table_44::img_buff_len]{0}; //default value is 0;
            memcpy(data_tmp, raw_img_data+i*table_44::img_buff_len,  table_44::img_buff_len);

            t44.img_data.reset(data_tmp); //获取每包图像数据
            t44.pkg_order = i;            // 包id

            t44.image_id = 0x03;
            t44.checkSum = t44.get_checkSum();
            t44.set_buffer();

            std::cout << +i << ":\n " << t44 << std::endl;
            ps.push_msg_39(t44.push_buffer, t44.buffer_len);
            // ps.push_msg_44_split(t44);
//            break;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        for (int i = 0; i < t44.pkg_total_num; ++i) // from 1 to end.
        {

            unsigned char *data_tmp = new unsigned char[table_44::img_buff_len]{0}; //default value is 0;
            memcpy(data_tmp, raw_img_data+i*table_44::img_buff_len,  table_44::img_buff_len);

            t44.img_data.reset(data_tmp); //获取每包图像数据
            t44.pkg_order = i;            // 包id

            t44.image_id = 0x04;
            t44.checkSum = t44.get_checkSum();
            t44.set_buffer();

            std::cout << +i << ":\n " << t44 << std::endl;
            ps.push_msg_39(t44.push_buffer, t44.buffer_len);
            // ps.push_msg_44_split(t44);
//            break;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        for (int i = 0; i < t44.pkg_total_num; ++i) // from 1 to end.
        {

            unsigned char *data_tmp = new unsigned char[table_44::img_buff_len]{0}; //default value is 0;

            memcpy(data_tmp, raw_img_data+i*table_44::img_buff_len,  table_44::img_buff_len);

            t44.img_data.reset(data_tmp); //获取每包图像数据
            t44.pkg_order = i;            // 包id

            t44.image_id = 0x05;
            t44.checkSum = t44.get_checkSum();
            t44.set_buffer();

            std::cout << +i << ":\n " << t44 << std::endl;
            ps.push_msg_39(t44.push_buffer, t44.buffer_len);
            // ps.push_msg_44_split(t44);
//            break;

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        
//        std::vector<table_44> t44s;
//
//        ps.push_msg_44_split(t441);
//        sleep(1);  //延迟1秒

//        for (int i = 1; i < t441.pkg_total_num; ++i) // from 1 to end.
//        {
//            unsigned char *data_tmp = new unsigned char[img_buff_len];
//            /* code */
//            table_44 t44(t441);
//
//            t44.pkg_order = t441.pkg_order + i;
//            memcpy(data_tmp, data+i*img_buff_len,  img_buff_len);
//
//
//            t44.img_data.reset(data_tmp);
//            t44.checkSum = t44.get_checkSum();
//
//            // t44s.push_back(t44);
//            ps.push_msg_44_split(t44);
//            // sleep(1);  //延迟1秒
//            std::this_thread::sleep_for(std::chrono::milliseconds(20));
//
//        }

        // std::cout <<"pkg_total_num : " << +t441.pkg_total_num << std::endl;
        // std::cout <<"total num: " << t44s.size() << std::endl;


        // for (int i = 0; i < t44s.size(); ++i)
        // {
        //     /* code */
            
        //     sleep(1);  //延迟1秒

        //     std::cout <<"push idx: " << i << std::endl;
        // }
        std::cout <<"Done." << std::endl;

        // table_44 t442(t441);
        // table_44 t443(t441);
        // table_44 t444(t441);

        // t442.pkg_order = 0x01;
        // t443.pkg_order = 0x02;
        // t444.pkg_order = 0x03;

        // t441.img_data.reset(data1);
        // t442.img_data.reset(data2);
        // t443.img_data.reset(data3);
        // t444.img_data.reset(data4);


        // t441.checkSum = t441.get_checkSum();
        // t442.checkSum = t442.get_checkSum();
        // t443.checkSum = t443.get_checkSum();
        // t444.checkSum = t444.get_checkSum();
        
        // ps.push_msg_44_split(t441);
        // sleep(1);  //延迟1秒
        // ps.push_msg_44_split(t441);
        // sleep(1);  //延迟1秒
        // ps.push_msg_44_split(t441);
        // sleep(1);  //延迟1秒
        // ps.push_msg_44_split(t441);

        // sleep(1);  //延迟1秒
        // std::cout <<"Done." << std::endl;


        // delete []data;

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


