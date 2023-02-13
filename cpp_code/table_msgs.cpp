//
//  table_msgs.cpp
//  demo-learn
//
//  Created by feifeiwei on 2023/2/13.
//

#include "table_msgs.hpp"


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

bool tabele_29_34::is_equal()
{
    return num11==get_checkSum();
}

int tabele_29_34::get_checkSum()
{
    int s2 = split_int<uint16_t>(num2);
    int s3 = split_int<uint8_t>(num3);
    int s4 = split_int<uint8_t>(num4);
    int s5 = split_int<uint8_t>(num5);
    int s6 = split_int<uint8_t>(num6);
    
    int s7 = split_char(num7, 24);
    int s8 = split_char(num8, 24);
    int s9 = split_char(num9, 24);
    int s10 = split_char(num10, 63);
    
    int all = s2+s3+s4+s5+s6 + s7+s8+s9+s10;
    
    return all & 0xff;
    
}
