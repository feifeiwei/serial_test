//
//  table_msgs.hpp
//  demo-learn
//
//  Created by feifeiwei on 2023/2/13.
//

#ifndef table_msgs_hpp
#define table_msgs_hpp
#include <iostream>
#include <unistd.h>
#include <stdio.h>

template<typename T>
int split_int(T num);

int split_char(unsigned char*);


// tabel 29_
#pragma pack(push,1)
struct tabele_29_34    //要发送的数据结构
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
    
    int get_checkSum();
    bool is_equal(); //校验和是否一致。
    
};
#pragma pack(pop)



#endif /* table_msgs_hpp */
