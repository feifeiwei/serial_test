//
//  table_msgs.hpp
//  serial_test
//
//  Created by brave_mac on 2023/2/14.
//
#ifndef table_msgs_hpp
#define table_msgs_hpp
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>


template<typename T>
int split_int(T num);
int split_char(unsigned char*);

uint16_t do_crc_checkSum(uint8_t* buff, uint16_t len);

// ------------------------ table 28 33 ------------------------------------------
// tabel 28 basic control msg
#pragma pack(push,1)
struct table_28    //要发送的数据结构
{   //len = 83(exclude 帧头,帧wei,校验和)
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    
    uint8_t control_type;
    uint8_t device_ssr;     // devive start stop reset.
    uint8_t device_running_mode;

    unsigned char addr_rgb[24];  // how to get 24bit type?? string==24bit
    unsigned char addr_ir[24];
    unsigned char addr_lidar[24];
    unsigned char keep[4]; // 预留

    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //获取校验和
    bool is_equal(); //校验和是否一致。
};
#pragma pack(pop)

#pragma pack(push,1)
struct table_33    //要发送的数据结构
{   //len = 83(exclude 帧头,帧wei,校验和)
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    
    uint8_t device_ssr;     // devive start stop reset.
    uint8_t device_running_mode;

    unsigned char addr_rgb[24];  // how to get 24bit type?? string==24bit
    unsigned char addr_ir[24];
    unsigned char addr_lidar[24];
    unsigned char keep[4]; // 预留
    
    uint8_t error_msg;  //#错误码
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    table_33& operator=(const table_28& t28);
};
#pragma pack(pop)
// ------------------------ table 28 33 ------------------------------------------

// ------------------------ table 29 34 ------------------------------------------
#pragma pack(push,1)
struct table_29    // control msg
{   //len = 83(exclude 帧头,帧wei,校验和)
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    uint8_t det_isBegin;     // object detector start or stop. 00=stop 01=strat
    uint8_t det_pattern;    // object pattern
    uint8_t det_dataSource; //
    uint8_t preprocess_method;
    
    uint8_t obj_conf;   //detect confidence
    uint8_t obj_rec_conf; // recognition confidence
    
    uint8_t minimum_len; // for obj detect minimum bbox len.
    uint8_t minimum_width; // for obj detect minimum bbox w.
    
    uint8_t unknown_det_begin; //
    unsigned char keep[4]; // 预留
    
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    bool is_equal(); //校验和是否一致。
};
#pragma pack(pop)

#pragma pack(push,1)
struct table_34    // control msg
{   //len = 83(exclude 帧头,帧wei,校验和)
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    uint8_t det_isBegin;     // object detector start or stop. 00=stop 01=strat
    uint8_t det_pattern;    // object pattern
    uint8_t det_dataSource; //
    uint8_t preprocess_method;
    
    uint8_t obj_conf;   //detect confidence
    uint8_t obj_rec_conf; // recognition confidence
    
    uint8_t minimum_len; // for obj detect minimum bbox len.
    uint8_t minimum_width; // for obj detect minimum bbox w.
    
    uint8_t unknown_det_begin; //

    unsigned char keep[4]; // 预留
    uint8_t error_msg;  //#错误码
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    table_34& operator=(const table_29& t29);
};
#pragma pack(pop)
// ------------------------ table 29 34 ------------------------------------------
// ------------------------ table 30 35 ------------------------------------------
#pragma pack(push,1)
struct table_30    // object tracking
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    
    uint8_t track_isBegin;     // object detector start or stop. 00=stop 01=strat
    uint8_t track_pattern;    // object pattern
    uint8_t track_principle; //
    uint16_t track_id_manual;
    uint8_t track_conf;   //
    uint16_t track_maximum; //
    uint16_t track_free; //
    
    unsigned char keep[4]; // 预留
    
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    bool is_equal(); //校验和是否一致。
};
#pragma pack(pop)

#pragma pack(push,1)
struct table_35    // object tracking
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    
    uint8_t track_isBegin;     // object detector start or stop. 00=stop 01=strat
    uint8_t track_pattern;    // object pattern
    uint8_t track_principle; //
    uint16_t track_id_manual;
    uint8_t track_conf;   //
    uint16_t track_maximum; //
    uint16_t track_free; //
    
    unsigned char keep[4]; // 预留
    uint8_t error_msg; //错误码
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    table_35& operator=(const table_30& t30);
};
#pragma pack(pop)

// ------------------------ table 30 35 ------------------------------------------
// ------------------------ table 31 36 ------------------------------------------

#pragma pack(push,1)
struct table_31    // object alart msg
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    
    uint8_t alart_isBegin;     // object detector start or stop. 00=stop 01=strat
    unsigned char alart_port[24];    // object pattern
    uint8_t alart_trigger_mode; //
    uint8_t alart_classes;
    uint8_t alart_threat_level;   //
    uint8_t unknownObj_alart_conf; //
    uint16_t alart_free; //
    
    unsigned char keep[4]; // 预留
    
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    bool is_equal(); //校验和是否一致。
};
#pragma pack(pop)


#pragma pack(push,1)
struct table_36    // object alart msg
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
    
    
    uint8_t alart_isBegin;     // object detector start or stop. 00=stop 01=strat
    unsigned char alart_port[24];    // object pattern
    uint8_t alart_trigger_mode; //
    uint8_t alart_classes;
    uint8_t alart_threat_level;   //
    uint8_t unknownObj_alart_conf; //
    uint16_t alart_free; //
    
    unsigned char keep[4]; // 预留
    uint8_t error_msg; //错误码
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    table_36& operator=(const table_31& t31);
};
#pragma pack(pop)

// ------------------------ table 31 36 ------------------------------------------
// ------------------------ table 32 37 ------------------------------------------
#pragma pack(push,1)
struct table_32    // object detection classes control msg
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
        
    uint8_t obj_classes;     // see appendix 2

    unsigned char keep[2]; // 预留
    
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    bool is_equal(); //校验和是否一致。
};
#pragma pack(pop)

#pragma pack(push,1)
struct table_37    // object detection classes control msg
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t control_type;
        
    uint8_t obj_classes;     // see appendix 2

    unsigned char keep[2]; // 预留
    uint8_t error_msg;
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    table_37& operator=(const table_32& t32);
};
#pragma pack(pop)


// ------------------------ table 32 37 ------------------------------------------
// ------------------------ table 38 39 ------------------------------------------
// device condition query.

#pragma pack(push,1)
struct table_38    // object detection device‘s condition query.
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
        
    uint8_t query_type;  // condition or ability query 01H 02H

    unsigned char keep[2]; // 预留
    
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
    bool is_equal(); //校验和是否一致。
};
#pragma pack(pop)


#pragma pack(push,1)
struct table_39    // object detection device‘s condition query.  return msg.
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
        
    uint8_t feedback_type;  // device condition feedback.
    unsigned char data_source[96];
    uint8_t device_stop_status;
    
    uint8_t det_pattern;
    uint8_t det_dataSource_status;
    uint8_t preprocess_method;
    uint8_t obj_conf;   //detect confidence
    uint8_t obj_rec_conf; // recognition confidence
    uint8_t minimum_len; // for obj detect minimum bbox len.
    uint8_t minimum_width; // for obj detect minimum bbox w.
    uint8_t unknown_det_status;
    
    uint8_t track_func_status;
    uint8_t track_pattern;    // object pattern
    uint8_t track_principle; //
    uint16_t track_maximum; //
    uint8_t track_conf;   //
    
    uint8_t alart_func_status;
    unsigned char alart_port[24];    // object pattern
    uint8_t alart_trigger_mode; //
    uint8_t alart_classes;
    uint8_t alart_threat_level;   //
    uint8_t unknownObj_alart_conf; //
    
    unsigned char keep[4]; // 预留
    uint8_t error_msg;
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
};
#pragma pack(pop)

#pragma pack(push,1)
struct table_40    // object detection device‘s ability query.  return msg.
{
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
        
    uint8_t feedback_type;  // condition or ability query 01H 02H

    uint8_t data_type_supported;
    uint8_t is_preprocess_method; // if set or not.
    uint8_t is_det_conf;
    uint8_t is_recog_conf;
    uint8_t is_minimumSize;
    uint8_t is_unknown;
    uint8_t is_track_conf;
    
    uint8_t is_alart_func;
    uint8_t is_3d_bbox;
    uint8_t is_recog_msg_conf;
    uint8_t is_obj_det_msg_conf;
    uint8_t is_unknown_conf;
    
    unsigned char keep[1]; // 预留
    uint8_t error_msg;
    uint16_t checkSum; //#校验和
    uint8_t tail;  //#帧尾
    
    uint16_t get_checkSum(); //成员函数不占空间
};
#pragma pack(pop)





// ------------------------ table 44  image upload msg ------------------------------------------
#pragma pack(push,1)
struct table_44    // object detection device‘s ability query.  return msg.
{
    table_44();
    ~table_44();
    const static int width   =1920;
    const static int height  =1080;
    const static int channel = 3;
    
    uint16_t get_checkSum(); //成员函数不占空间
    
    uint16_t header; //帧头
    uint16_t data_len; //数据长度
    uint16_t msg_code;  //消息代码
    uint8_t msg_class; //03H 图像信息
    
    uint32_t image_id;
    uint16_t pkg_order; //包序号
    uint8_t pkg_type;
    
    uint8_t pkg_total_num;
    
    std::unique_ptr<unsigned char[]> img_data;
//      unsigned char* img_data;  //数据，太大爆了size + 8
    
    unsigned char keep[6]; // 预留
    uint16_t checkSum; //#校验和
    uint8_t tail=0xAA;  //#帧尾
    
    
    
};
#pragma pack(pop)

// ------------------------ table 44  image upload msg ------------------------------------------



#endif /* table_msgs_hpp */


