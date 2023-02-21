//
//  table_msgs.cpp
//  serial_test
//
//  Created by brave_mac on 2023/2/14.
//
#include "table_msgs.hpp"

static unsigned short ccitt_tables[256] =
{
    0x0000,    0x1021,    0x2042,    0x3063,    0x4084,    0x50A5,    0x60C6,    0x70E7,
    0x8108,    0x9129,    0xA14A,    0xB16B,    0xC18C,    0xD1AD,    0xE1CE,    0xF1EF,
    0x1231,    0x0210,    0x3273,    0x2252,    0x52B5,    0x4294,    0x72F7,    0x62D6,
    0x9339,    0x8318,    0xB37B,    0xA35A,    0xD3BD,    0xC39C,    0xF3FF,    0xE3DE,
    0x2462,    0x3443,    0x0420,    0x1401,    0x64E6,    0x74C7,    0x44A4,    0x5485,
    0xA56A,    0xB54B,    0x8528,    0x9509,    0xE5EE,    0xF5CF,    0xC5AC,    0xD58D,
    0x3653,    0x2672,    0x1611,    0x0630,    0x76D7,    0x66F6,    0x5695,    0x46B4,
    0xB75B,    0xA77A,    0x9719,    0x8738,    0xF7DF,    0xE7FE,    0xD79D,    0xC7BC,
    0x48C4,    0x58E5,    0x6886,    0x78A7,    0x0840,    0x1861,    0x2802,    0x3823,
    0xC9CC,    0xD9ED,    0xE98E,    0xF9AF,    0x8948,    0x9969,    0xA90A,    0xB92B,
    0x5AF5,    0x4AD4,    0x7AB7,    0x6A96,    0x1A71,    0x0A50,    0x3A33,    0x2A12,
    0xDBFD,    0xCBDC,    0xFBBF,    0xEB9E,    0x9B79,    0x8B58,    0xBB3B,    0xAB1A,
    0x6CA6,    0x7C87,    0x4CE4,    0x5CC5,    0x2C22,    0x3C03,    0x0C60,    0x1C41,
    0xEDAE,    0xFD8F,    0xCDEC,    0xDDCD,    0xAD2A,    0xBD0B,    0x8D68,    0x9D49,
    0x7E97,    0x6EB6,    0x5ED5,    0x4EF4,    0x3E13,    0x2E32,    0x1E51,    0x0E70,
    0xFF9F,    0xEFBE,    0xDFDD,    0xCFFC,    0xBF1B,    0xAF3A,    0x9F59,    0x8F78,
    0x9188,    0x81A9,    0xB1CA,    0xA1EB,    0xD10C,    0xC12D,    0xF14E,    0xE16F,
    0x1080,    0x00A1,    0x30C2,    0x20E3,    0x5004,    0x4025,    0x7046,    0x6067,
    0x83B9,    0x9398,    0xA3FB,    0xB3DA,    0xC33D,    0xD31C,    0xE37F,    0xF35E,
    0x02B1,    0x1290,    0x22F3,    0x32D2,    0x4235,    0x5214,    0x6277,    0x7256,
    0xB5EA,    0xA5CB,    0x95A8,    0x8589,    0xF56E,    0xE54F,    0xD52C,    0xC50D,
    0x34E2,    0x24C3,    0x14A0,    0x0481,    0x7466,    0x6447,    0x5424,    0x4405,
    0xA7DB,    0xB7FA,    0x8799,    0x97B8,    0xE75F,    0xF77E,    0xC71D,    0xD73C,
    0x26D3,    0x36F2,    0x0691,    0x16B0,    0x6657,    0x7676,    0x4615,    0x5634,
    0xD94C,    0xC96D,    0xF90E,    0xE92F,    0x99C8,    0x89E9,    0xB98A,    0xA9AB,
    0x5844,    0x4865,    0x7806,    0x6827,    0x18C0,    0x08E1,    0x3882,    0x28A3,
    0xCB7D,    0xDB5C,    0xEB3F,    0xFB1E,    0x8BF9,    0x9BD8,    0xABBB,    0xBB9A,
    0x4A75,    0x5A54,    0x6A37,    0x7A16,    0x0AF1,    0x1AD0,    0x2AB3,    0x3A92,
    0xFD2E,    0xED0F,    0xDD6C,    0xCD4D,    0xBDAA,    0xAD8B,    0x9DE8,    0x8DC9,
    0x7C26,    0x6C07,    0x5C64,    0x4C45,    0x3CA2,    0x2C83,    0x1CE0,    0x0CC1,
    0xEF1F,    0xFF3E,    0xCF5D,    0xDF7C,    0xAF9B,    0xBFBA,    0x8FD9,    0x9FF8,
    0x6E17,    0x7E36,    0x4E55,    0x5E74,    0x2E93,    0x3EB2,    0x0ED1,    0x1EF0
};


// void reverse(unsigned char  * a,int n)
// {

//     unsigned char b[n];
//     for(int i=0;i<n;i++)
//     {
//         b[n-i-1]=a[i];
//     }
//     for(int i=0;i<n;i++)
//     {
//         a[i]=b[i];
//     }
// }


template<typename T>
int split_int(T num)
{
    int a = num & 0xff;
    int b = num >> 8;
    return a+b;
}

int split_char(unsigned char* s, int num)
{
    int sum{0};
    for (int i=0; i<num; i++) {
        sum += (int)s[i];
    }
    return sum;
}

uint16_t do_crc_checkSum(uint8_t* buff, uint16_t len)
{
    uint16_t crc = 0xFFFF;
    
    while (len-->0) {
        crc = ccitt_tables[(crc>>8 ^ *buff++) & 0xff] ^ (crc<<8);
    }
    return crc;
}
// ------------------------ table 28 33 ------------------------------------------

bool table_28::is_equal()
{
    return checkSum==get_checkSum();
}

uint16_t table_28::get_checkSum()
{
    uint16_t len = sizeof(table_28) - 5; // (exclude 帧头,帧wei,校验和)
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    buff[idx++] = device_ssr;
    buff[idx++] = device_running_mode;
    // std::cout <<"----------------------------" << std::endl;

    // std::cout <<"1: "<<  std::hex<<  (data_len >> 8) << std::endl;
    // std::cout <<"1: "<<  std::hex<<  (data_len & 0xff) << std::endl;
    // std::cout <<"2: "<<  std::hex<<  (msg_code >> 8) << std::endl;
    // std::cout <<"2: "<<  std::hex<<  (msg_code & 0xff) << std::endl;
    // std::cout <<"3: "<<  std::hex<<  (control_type) << std::endl;
    // std::cout <<"4: "<<  std::hex<<  (device_ssr) << std::endl;
    // std::cout <<"5: "<<  std::hex<<  (device_running_mode) << std::endl;


    // std::cout << "\ndata_len: " <<std::hex<< (data_len >> 8)  << ",  " << (data_len & 0xff) << std::endl;
    // std::cout << "msg_code: " << std::hex<<(msg_code >> 8)  << ",  " << (msg_code & 0xff) << std::endl;
    // std::cout << "control_type: "<< std::hex<< +control_type  << ",  " << +device_ssr << ", " << device_running_mode <<std::endl;
    // std::cout << "addr_rgb: " << addr_rgb << std::endl;
    // std::cout << "addr_ir: " << addr_rgb << std::endl;
    // std::cout << "addr_lidar: " << addr_lidar << std::endl;
    for(const auto &c: addr_rgb) buff[idx++] = c;
    for(const auto &c: addr_ir) buff[idx++] = c;
    for(const auto &c: addr_lidar) buff[idx++] = c;

    for(const auto &c: keep) buff[idx++] = c;
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);

    return crc;
}


table_33& table_33::operator=(const table_28& t28)
{


    header = t28.header;//t28.header;
    data_len = t28.data_len+1;
    msg_code = 0x0803;//t28.msg_code;
    control_type = t28.control_type;
    
    device_ssr = t28.device_ssr;
    device_running_mode = t28.device_running_mode;
    
    memcpy(addr_rgb, t28.addr_rgb, sizeof(addr_rgb)/sizeof(addr_rgb[0]));
    memcpy(addr_ir, t28.addr_ir, 24);
    memcpy(addr_lidar, t28.addr_lidar, 24);
    memcpy(keep, t28.keep, 4);
    
    tail = 0xAA; // same
    return *this;
}


uint16_t table_33::get_checkSum()
{
    
    uint16_t len = sizeof(table_33)-5; //84;
    uint8_t  buff[len];
    int idx=0;
    
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    buff[idx++] = device_ssr;
    buff[idx++] = device_running_mode;
    
    for(const auto &c: addr_rgb) buff[idx++] = c;
    for(const auto &c: addr_ir) buff[idx++] = c;
    for(const auto &c: addr_lidar) buff[idx++] = c;
    for(const auto &c: keep) buff[idx++] = c;
    
    buff[idx++] = error_msg;
    
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);

    return crc;
}



// ------------------------ table 28 33 ------------------------------------------


// ------------------------ table 29 34 ------------------------------------------

bool table_29::is_equal()
{
    return checkSum==get_checkSum();
}

uint16_t table_29::get_checkSum()
{
    uint16_t len = sizeof(table_29)-5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    buff[idx++] = det_isBegin;
    buff[idx++] = det_pattern;
    buff[idx++] = det_dataSource;
    buff[idx++] = preprocess_method;
    buff[idx++] = obj_conf;
    buff[idx++] = obj_rec_conf;
    buff[idx++] = minimum_len;
    buff[idx++] = minimum_width;
    buff[idx++] = unknown_det_begin;
    
    for(const auto &c: keep) buff[idx++] = c;
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);

    return crc;
}


table_34& table_34::operator=(const table_29& t29)
{
    header = t29.header;
    data_len = t29.data_len + 1;
    msg_code = 0x0803;//t29.msg_code;
    control_type = t29.control_type;
    
    det_isBegin = t29.det_isBegin;     // object detector start or stop. 00=stop 01=strat
    det_pattern = t29.det_pattern;    // object pattern
    det_dataSource = t29.det_dataSource; //
    preprocess_method = t29.preprocess_method;
    
    obj_conf = t29.obj_conf;   //detect confidence
    obj_rec_conf = t29.obj_rec_conf; // recognition confidence
    
    minimum_len = t29.minimum_len; // for obj detect minimum bbox len.
    minimum_width = t29.minimum_width; // for obj detect minimum bbox w.
    
    unknown_det_begin = t29.unknown_det_begin; //

    memcpy(keep, t29.keep, 4);
    tail = 0xAA; // same
    
    return *this;
}

uint16_t table_34::get_checkSum()
{
    uint16_t len = sizeof(table_34)-5;
    uint8_t  buff[len];
    int idx=0;
    
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    buff[idx++] = control_type;
    
    
    buff[idx++] = det_isBegin;
    buff[idx++] = det_pattern;
    buff[idx++] = det_dataSource;
    buff[idx++] = preprocess_method;
    buff[idx++] = obj_conf;
    buff[idx++] = obj_rec_conf;
    buff[idx++] = minimum_len;
    buff[idx++] = minimum_width;
    buff[idx++] = unknown_det_begin;

    for(const auto &c: keep) buff[idx++] = c;
    buff[idx++] = error_msg;
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);

    return crc;
}

// ------------------------ table 29 34 ------------------------------------------
// ------------------------ table 30 35 ------------------------------------------
bool table_30::is_equal()
{
    return checkSum==get_checkSum();
}

uint16_t table_30::get_checkSum()
{
    uint16_t len = sizeof(table_30)-5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    
    buff[idx++] = track_isBegin;
    buff[idx++] = track_pattern;
    buff[idx++] = track_principle;

    buff[idx++] = track_id_manual & 0xff;
    buff[idx++] = track_id_manual >> 8;
    
    
    buff[idx++] = track_conf;
    buff[idx++] = track_maximum & 0xff;
    buff[idx++] = track_maximum >> 8;

    buff[idx++] = track_free & 0xff;
    buff[idx++] = track_free >> 8;
    
    
    for(const auto &c: keep) buff[idx++] = c;
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);

    return crc;
}



table_35& table_35::operator=(const table_30& t30)
{
    header = t30.header;
    data_len = t30.data_len+1;
    msg_code = 0x0803;//t30.msg_code;
    control_type = t30.control_type;
    
    track_isBegin  =  t30.track_isBegin;     // object detector start or stop. 00=stop 01=strat
    track_pattern  =  t30.track_pattern;    // object pattern
    track_principle=  t30.track_principle; //
    track_id_manual=  t30.track_id_manual;
    track_conf     =  t30.track_conf;   //
    track_maximum  =  t30.track_maximum; //
    track_free     =  t30.track_free; //
    
    memcpy(keep, t30.keep, 4);; // 预留
//    error_msg; //错误码
    
    tail = 0xAA; // same
    
    return *this;
    
}


uint16_t table_35::get_checkSum()
{
    uint16_t len = sizeof(table_35)-5;
    uint8_t  buff[len];
    int idx=0;
    
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    buff[idx++] = control_type;
    
    buff[idx++] = track_isBegin;
    buff[idx++] = track_pattern;
    buff[idx++] = track_principle;
    
    buff[idx++] = track_id_manual & 0xff;
    buff[idx++] = track_id_manual >> 8;
    
    
    buff[idx++] = track_conf;
    buff[idx++] = track_maximum & 0xff;
    buff[idx++] = track_maximum >> 8;
    
    buff[idx++] = track_free & 0xff;
    buff[idx++] = track_free >> 8;
    
    for(const auto &c: keep) buff[idx++] = c;
    buff[idx++] = error_msg;
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);
    
    return crc;
}

// ------------------------ table 30 35 ------------------------------------------
// ------------------------ table 31 36 ------------------------------------------
bool table_31::is_equal()
{
    return checkSum==get_checkSum();
}

void table_31::set_value()
{
    
    int idx = 0;
//    header =  raw_data[1] + (raw_data[0]<<8); // same as table receive order.
    header = raw_data[idx++];
    header += (raw_data[idx++]<<8);
    data_len = raw_data[idx++];
    data_len += (raw_data[idx++]<<8);
    msg_code = raw_data[idx++];
    msg_code += (raw_data[idx++]<<8);
    
    control_type = raw_data[idx++];
    alart_isBegin = raw_data[idx++];

    for(auto& c: alart_port) c = raw_data[idx++];
    
    
    alart_trigger_mode = raw_data[idx++];
    
    while (raw_data[idx]!=0x00) {
        alart_classes.push_back(raw_data[idx]);
        idx++;
    }
    alart_classes.push_back(0x00);
    idx++;
    
    alart_threat_level = raw_data[idx++];
    unknownObj_alart_conf = raw_data[idx++];
    
    alart_free = raw_data[idx++];
    alart_free += (raw_data[idx++]<<8);
    
    for(auto& c: keep) c = raw_data[idx++]; // reverse?
        
    checkSum = raw_data[idx++];
    checkSum += (raw_data[idx++]<<8);
    
    tail = raw_data[idx++];
    
    std::cout <<"idx==buff_len" << idx<< ", " << buffer_len << std::endl;

    assert(idx==buffer_len);
}

uint16_t table_31::get_checkSum()
{
    uint16_t len = buffer_len-5;//sizeof(table_31)-5; //
    uint8_t buff[len];
//
    int idx=0;

    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;

    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    buff[idx++] = alart_isBegin;
    
//    reverse(alart_port, 24); //逆序？
    for(const auto &c: alart_port) buff[idx++] = c;
    
    buff[idx++] = alart_trigger_mode;
    
    for (auto it = alart_classes.begin(); it != alart_classes.end(); it++)
//    for (auto it = alart_classes.rbegin(); it != alart_classes.rend(); it++)
        buff[idx++] = *it;
    
    buff[idx++] = alart_threat_level;   //
    buff[idx++] = unknownObj_alart_conf; //
    buff[idx++] = alart_free & 0xff;
    buff[idx++] = alart_free >> 8;
    
//    reverse(keep, 4); //逆序
    for(const auto &c: keep) buff[idx++] = c;; // 预留
//
    assert(idx==len); //check!
//
    uint16_t crc = do_crc_checkSum(buff, len);
//
    return crc;

}

table_36& table_36::operator=(const table_31& t31)
{
    header = t31.header;
    data_len = t31.data_len+1;
    msg_code = 0x0803;//t31.msg_code;
    control_type = t31.control_type;
    
    
    alart_isBegin = t31.alart_isBegin;
    memcpy(alart_port, t31.alart_port, 24);; // 预留
    alart_trigger_mode = t31.alart_trigger_mode; //
//    alart_classes = t31.alart_classes;
    alart_classes.assign(t31.alart_classes.begin(), t31.alart_classes.end());

    alart_threat_level = t31.alart_threat_level;   //
    unknownObj_alart_conf = t31.unknownObj_alart_conf; //
    alart_free = t31.alart_free; //
    memcpy(keep, t31.keep, 4);; // 预留

    buffer_len = t31.buffer_len + 1; // error_code.
    
    tail = 0xAA; // same
    
    return *this;
    
}






uint16_t table_36::get_checkSum()
{
    uint16_t len = buffer_len-5; //sizeof(table_36)-5; //
    uint8_t buff[len];
    
    int idx=0;
    
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;

    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    buff[idx++] = alart_isBegin;
    
    for(const auto &c: alart_port) buff[idx++] = c;
    buff[idx++] = alart_trigger_mode; //

//    buff[idx++] = alart_classes;
    for (auto it = alart_classes.begin(); it != alart_classes.end(); it++)
//    for (auto it = alart_classes.rbegin(); it != alart_classes.rend(); it++)
        buff[idx++] = *it;
    
    
    buff[idx++] = alart_threat_level;   //
    buff[idx++] = unknownObj_alart_conf; //
    
    buff[idx++] = alart_free & 0xff;
    buff[idx++] = alart_free >> 8;
    
    
    for(const auto &c: keep) buff[idx++] = c;; // 预留
    buff[idx++] = error_msg;

    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);
    return crc;

}

void table_36::set_buffer()
{
    uint16_t len = data_len + 7; //
//    uint8_t buff[len];
    raw_data = std::make_unique<unsigned char[]>(len);
    
    int idx=0;
    raw_data[idx++] = header & 0xff;
    raw_data[idx++] = header >> 8;

    raw_data[idx++] = data_len & 0xff;
    raw_data[idx++] = data_len >> 8;
    
    raw_data[idx++] = msg_code & 0xff;
    raw_data[idx++] = msg_code >> 8;

    raw_data[idx++] = control_type;
    raw_data[idx++] = alart_isBegin;

    for(const auto &c: alart_port) raw_data[idx++] = c;; // 预留
    raw_data[idx++] = alart_trigger_mode;    
    
    for (auto it = alart_classes.begin(); it != alart_classes.end(); it++)
        raw_data[idx++] = *it;

    raw_data[idx++] = alart_threat_level;
    raw_data[idx++] = unknownObj_alart_conf;

    raw_data[idx++] = alart_free & 0xff;
    raw_data[idx++] = alart_free >> 8;

    for(const auto &c: keep) raw_data[idx++] = c;; // 预留

    raw_data[idx++] = error_msg;    

    raw_data[idx++] = checkSum & 0xff;
    raw_data[idx++] = checkSum >> 8;

    raw_data[idx++] = tail;

    assert(idx==len);
    buffer_len = len;
}


// ------------------------ table 31 36 ------------------------------------------
// ------------------------ table 32 37 ------------------------------------------
bool table_32::is_equal()
{
    return checkSum==get_checkSum();
}

void table_32::set_value()
{
    int idx = 0;
    //    header =  raw_data[1] + (raw_data[0]<<8); // same as table receive order.
    header = raw_data[idx++];
    header += (raw_data[idx++]<<8);
    data_len = raw_data[idx++];
    data_len += (raw_data[idx++]<<8);
    msg_code = raw_data[idx++];
    msg_code += (raw_data[idx++]<<8);
    control_type = raw_data[idx++];
    
    while (raw_data[idx]!=0x00) {
        obj_classes.push_back(raw_data[idx]);
        idx++;
    }
    obj_classes.push_back(0x00);
    idx++;
    
    for(auto& c: keep) c = raw_data[idx++]; // reverse?
    
    checkSum = raw_data[idx++];
    checkSum += (raw_data[idx++]<<8);
    
    tail = raw_data[idx++];
    
    std::cout <<"idx==buff_len" << idx<< ", " << buffer_len << std::endl;

    assert(idx==buffer_len);
    
}
                        

uint16_t table_32::get_checkSum()
{
    uint16_t len = buffer_len-5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;

    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
        
    buff[idx++] = control_type;
    
//    buff[idx++] = obj_classes;     // see appendix 2
    for (auto it = obj_classes.begin(); it != obj_classes.end(); it++)
        buff[idx++] = *it;
    
    for(const auto &c: keep) buff[idx++] = c;; // 预留
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);

    return crc;

}

table_37& table_37::operator=(const table_32& t32)
{
    header = t32.header;
    data_len = t32.data_len+1;
    msg_code = 0x0803;// t32.msg_code;
    control_type = t32.control_type;
    
//    obj_classes = t32.obj_classes;
    obj_classes.assign(t32.obj_classes.begin(), t32.obj_classes.end());
    memcpy(keep, t32.keep, 2);; // 预留
    tail = 0xAA; // same

    buffer_len = t32.buffer_len + 1;

    return *this;
}

uint16_t table_37::get_checkSum()
{
    uint16_t len = buffer_len - 5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;

    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = control_type;
    
//    buff[idx++] = obj_classes;     // see appendix 2
    for (auto it = obj_classes.begin(); it != obj_classes.end(); it++)
        buff[idx++] = *it;
    
    for(const auto &c: keep) buff[idx++] = c;; // 预留
    buff[idx++] = error_msg;
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);
    return crc;

}



void table_37::set_buffer()
{
    uint16_t len = data_len + 7; //
//    uint8_t buff[len];
    raw_data = std::make_unique<unsigned char[]>(len);
    
    int idx=0;
    raw_data[idx++] = header & 0xff;
    raw_data[idx++] = header >> 8;

    raw_data[idx++] = data_len & 0xff;
    raw_data[idx++] = data_len >> 8;
    
    raw_data[idx++] = msg_code & 0xff;
    raw_data[idx++] = msg_code >> 8;

    raw_data[idx++] = control_type;

    for (auto it = obj_classes.begin(); it != obj_classes.end(); it++)
        raw_data[idx++] = *it;

    for(const auto &c: keep) raw_data[idx++] = c;; // 预留

    raw_data[idx++] = error_msg;    

    raw_data[idx++] = checkSum & 0xff;
    raw_data[idx++] = checkSum >> 8;

    raw_data[idx++] = tail;

    assert(idx==len);
    buffer_len = len;

}

// ------------------------ table 32 37 ------------------------------------------
// ------------------------condition query------------------------------------------
// ------------------------ table 38 39 40------------------------------------------
bool table_38::is_equal()
{
    return checkSum==get_checkSum();
}

uint16_t table_38::get_checkSum()
{
    uint16_t len = sizeof(table_38)-5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
   
    
    buff[idx++] = query_type;

    for(const auto &c: keep) buff[idx++] = c;; // 预留
    
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);
    return crc;
}

table_39& table_39::operator=(const table_38& t38)
{
    alart_classes.push_back(0x01);
    alart_classes.push_back(0x02);
    alart_classes.push_back(0x03);
    alart_classes.push_back(0x00);//fake value
    
    header = t38.header;
    data_len = 155 + alart_classes.size() - 7;
    msg_code = 0x0804;// t32.msg_code;
    feedback_type = 0x01;


    obj_conf = 50;

    memcpy(data_source, "192.18e729472947294727373333330000000.222192.18e729472947294727373333330000000.2221234567891127", 96);
    memcpy(alart_port, "111111111111111111111234",24);

    // data_source = d_s;
    
    error_msg = 0x0;
    tail = 0xaa;
    return *this;
}

void table_39::set_buffer()
{
    uint16_t len = data_len + 7; //
//    uint8_t buff[len];
    raw_data = std::make_unique<unsigned char[]>(len);
    
    int idx=0;
    raw_data[idx++] = header & 0xff;
    raw_data[idx++] = header >> 8;

    raw_data[idx++] = data_len & 0xff;
    raw_data[idx++] = data_len >> 8;
    
    raw_data[idx++] = msg_code & 0xff;
    raw_data[idx++] = msg_code >> 8;
    
    
    raw_data[idx++] = feedback_type;
    raw_data[idx++] = device_condition;  // device condition feedback.// device condition feedback.
    for(const auto &c: data_source) raw_data[idx++] = c;; // 预留
    raw_data[idx++] = device_stop_status;
    
    raw_data[idx++] = det_pattern;
    raw_data[idx++] =  det_dataSource_status;
    raw_data[idx++] =  preprocess_method;
    raw_data[idx++] =  obj_conf;   //detect confidence
    raw_data[idx++] =  obj_rec_conf; // recognition confidence
    raw_data[idx++] =  minimum_len; // for obj detect minimum bbox len.
    raw_data[idx++] =  minimum_width; // for obj detect minimum bbox w.
    raw_data[idx++] =  unknown_det_status;
    
    raw_data[idx++] =  track_func_status;
    raw_data[idx++] =  track_pattern;    // object pattern
    raw_data[idx++] =  track_principle; //
    
    raw_data[idx++] = track_maximum & 0xff;
    raw_data[idx++] = track_maximum >> 8;
    raw_data[idx++] =  track_conf;   //
    
    raw_data[idx++] =  alart_func_status;
    for(const auto &c: alart_port) raw_data[idx++] = c;; // 预留
    raw_data[idx++] =  alart_trigger_mode; //
    
    for (auto it = alart_classes.begin(); it != alart_classes.end(); it++)
        raw_data[idx++] = *it;
    
    raw_data[idx++] =  alart_threat_level;   //
    raw_data[idx++] =  unknownObj_alart_conf; //
    
    
    for(const auto &c: keep) raw_data[idx++] = c;; // 预留
    raw_data[idx++] = error_msg;
    raw_data[idx++] = checkSum & 0xff;
    raw_data[idx++] = checkSum >> 8;
    raw_data[idx++] = tail;
    
    
    assert(idx==len);
    buffer_len = len;
}

uint16_t table_39::get_checkSum()
{
    uint16_t len = data_len + 7 - 5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    
    buff[idx++] = feedback_type;
    buff[idx++] = device_condition;  // device condition feedback.// device condition feedback.
    for(const auto &c: data_source) buff[idx++] = c;; // 预留
    buff[idx++] = device_stop_status;
    
    buff[idx++] = det_pattern;
    buff[idx++] =  det_dataSource_status;
    buff[idx++] =  preprocess_method;
    buff[idx++] =  obj_conf;   //detect confidence
    buff[idx++] =  obj_rec_conf; // recognition confidence
    buff[idx++] =  minimum_len; // for obj detect minimum bbox len.
    buff[idx++] =  minimum_width; // for obj detect minimum bbox w.
    buff[idx++] =  unknown_det_status;
    
    buff[idx++] =  track_func_status;
    buff[idx++] =  track_pattern;    // object pattern
    buff[idx++] =  track_principle; //
    
    buff[idx++] = track_maximum & 0xff;
    buff[idx++] = track_maximum >> 8;
    buff[idx++] =  track_conf;   //
    
    buff[idx++] =  alart_func_status;
    for(const auto &c: alart_port) buff[idx++] = c;; // 预留
    buff[idx++] =  alart_trigger_mode; //
    
    for (auto it = alart_classes.begin(); it != alart_classes.end(); it++)
        buff[idx++] = *it;
    
    buff[idx++] =  alart_threat_level;   //
    buff[idx++] =  unknownObj_alart_conf; //
    
    
    for(const auto &c: keep) buff[idx++] = c;; // 预留
    buff[idx++] = error_msg;
    
//    std::cout << idx << " " << len << std::endl;
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);
    
    return crc;
    
}

table_40& table_40::operator=(const table_38& t38)
{
    
    header = t38.header;
    data_len = 24-7;
    msg_code = 0x0804;// t32.msg_code;
    feedback_type = 0x02;
    


    
    error_msg = 0x00;
    tail = 0xaa;
    
    return *this;
    
}

uint16_t table_40::get_checkSum()
{
    uint16_t len = sizeof(table_40)-5; //
    uint8_t buff[len];
    
    int idx=0;
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8;
    
    buff[idx++] = feedback_type;  // device condition feedback.

    buff[idx++] =  data_type_supported;
    buff[idx++] =  is_preprocess_method; // if set or not.
    buff[idx++] =  is_det_conf;
    buff[idx++] =  is_recog_conf;
    buff[idx++] =  is_minimumSize;
    buff[idx++] =  is_unknown;
    buff[idx++] =  is_track_conf;
    
    buff[idx++] =  is_alart_func;
    buff[idx++] =  is_3d_bbox;
    buff[idx++] =  is_recog_msg_conf;
    buff[idx++] =  is_obj_det_msg_conf;
    buff[idx++] =  is_unknown_conf;
    
    for(const auto &c: keep) buff[idx++] = c;; // 预留
    buff[idx++] = error_msg;
    assert(idx==len); //check!
    
    uint16_t crc = do_crc_checkSum(buff, len);
    
    return crc;

}
// ------------------------ table 38 39 40 ------------------------------------------
// ------------------------ table 44  image upload msg ------------------------------------------

table_44::table_44(const table_44& t44)
{
    header = t44.header;
    data_len = t44.data_len;
    msg_code = t44.msg_code;
    msg_class = t44.msg_class;
    image_id = t44.image_id;
    pkg_order = t44.pkg_order;
    pkg_type = t44.pkg_type;
    pkg_total_num = t44.pkg_total_num;

    //img_data
    memcpy(keep, t44.keep,6);

    // checkSum?
    tail = t44.tail;

}



uint16_t table_44::get_checkSum()
{
    long len = 20 + table_44::img_buff_len;//sizeof(table_44)-5; //
    uint8_t buff[len];
    
    int idx=0;
    
    buff[idx++] = data_len & 0xff;
    buff[idx++] = data_len >> 8;
    
    buff[idx++] = msg_code & 0xff;
    buff[idx++] = msg_code >> 8; //消息代码
    
    buff[idx++] = msg_class; //03H 图像信息
    
    buff[idx++] = (uint8_t)(image_id & 0xff);
    buff[idx++] = (uint8_t)(image_id >> 8);
    buff[idx++] = (uint8_t)(image_id >> 16);
    buff[idx++] = (uint8_t)(image_id >> 24); // there is not necessary explicit cast the type cos buff is uint8.
    
    
    buff[idx++] = pkg_order & 0xff;
    buff[idx++] = pkg_order >> 8;

    buff[idx++] = pkg_type;

    buff[idx++] = pkg_total_num & 0xff;
    buff[idx++] = pkg_total_num >> 8; //消息代码
    
//    for(const auto &c: img_data) buff[idx++] = c; // img data
    // for(int i=0; i<this->width * this->height * this->channel; i++)
    for(int i=0; i<table_44::img_buff_len; i++)
        buff[idx++] = img_data[i];
    
    for(const auto &c: keep) buff[idx++] = c; // 预留
    assert(idx==len); //check!
        
    uint16_t crc = do_crc_checkSum(buff, len);
    
    return crc;
}


void table_44::init_info(table_44& t44)
{
    t44.header = 0xeb90;
    t44.data_len = 24 + table_44::img_buff_len - 7;
    t44.msg_code = 0x0707;
    t44.msg_class = 0x03;

    t44.pkg_type = 0x0;

    t44.image_id = 0x0;
    t44.pkg_order = 0x00;
    t44.pkg_type = 0x00;

    t44.pkg_total_num = table_44::width * table_44::height * table_44::channel / table_44::img_buff_len;
    
//    img_data;  // diff
    
    memcpy(t44.keep, "00keep",6);
    
    t44.checkSum = t44.get_checkSum();
    t44.tail = 0xaa;
}



std::ostream& operator << (std::ostream &os, const table_44 &t44)
{
    os <<"--------- table 44 info:------------- \n";
    os << std::hex ;
    os << "header: \t" <<    +t44.header << std::endl;
    os << "data_len: \t" <<  +t44.data_len << std::endl;
    os << "msg_code: \t" <<  +t44.msg_code << std::endl;
    os << "msg_class: \t" << +t44.msg_class << std::endl;
    os << "image_id: \t" <<  +t44.image_id << std::endl;
    os << "pkg_order: \t" << +t44.pkg_order << std::endl;
    os << "pkg_type: \t" <<  +t44.pkg_type << std::endl;
    os << "pkg_total_num: \t" <<  +t44.pkg_total_num << std::endl;
    os << "img_data len: \t" <<  +t44.table_44::img_buff_len << std::endl;
    os << "push buffer_len: \t" <<  +t44.table_44::buffer_len << std::endl;
    
    os << "keep: \t";
    for(const auto& c: t44.keep) os << c ;
    os <<std::endl;
    
    os << "checkSum: \t" <<  +t44.table_44::checkSum << std::endl;
    os << "tail: \t" <<  +t44.table_44::tail << std::endl;;
    
    os<< std::dec;
    
    return os;
}



void table_44::set_buffer()
{
    buffer_len = 24 + table_44::img_buff_len;  // all elements with t44
    push_buffer = std::make_unique<unsigned char[]>(buffer_len);
    
    long idx = 0;
    push_buffer[idx++] = header & 0xff;
    push_buffer[idx++] = header >> 8;
    push_buffer[idx++] = data_len & 0xff;
    push_buffer[idx++] = data_len >> 8;
    push_buffer[idx++] = msg_code & 0xff;
    push_buffer[idx++] = msg_code >> 8;
    
    push_buffer[idx++] = msg_class;
    
    push_buffer[idx++] = image_id & 0xff;
    push_buffer[idx++] = image_id >> 8;
    push_buffer[idx++] = image_id >> 16;
    push_buffer[idx++] = image_id >> 24;
    
    push_buffer[idx++] = pkg_order & 0xff;
    push_buffer[idx++] = pkg_order >> 8;
    
    push_buffer[idx++] = pkg_type;

    push_buffer[idx++] = pkg_total_num;
    
    for (int i=0; i<table_44::img_buff_len; i++) {
        push_buffer[idx++] = img_data[i];
    }
    
    for(const auto& c: keep) push_buffer[idx++]  = c;
    push_buffer[idx++] = checkSum & 0xff;
    push_buffer[idx++] = checkSum >> 8;
    push_buffer[idx++] = tail;
    
//    std::cout <<"-->  " <<buffer_len <<" " << idx << std::endl;
    
    assert(buffer_len==idx); //ensure not  missing data.
    img_data.reset();
    
}



table_44::table_44()
{
//    img_data = new unsigned char[this->width*this->height*this->channel];
    img_data = std::make_unique<unsigned char[]>(this->width*this->height*this->channel);
}

table_44::~table_44()
{
//    delete []img_data;
}

// ------------------------ table 44  image upload msg ------------------------------------------

