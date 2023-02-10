# -*- coding: utf-8 -*-
import socket
import time
import struct
from ctypes import *
import binascii
import pdb

# import pdb
# class Data(Structure):
#     _pack_ = 1
#     _fields_ = [("member_1", c_ubyte),
#                 ("member_2", c_ubyte),
#                 ("member_3", c_float),
#                 ("member_4", c_float),
#                 ("member_5", c_double)]


class Data(Structure):
    _pack_ = 1   #让结构体内存连续
    _fields_ = [("member_1", c_uint16), #c_ubyte),
                ("member_2", c_uint16), #c_ubyte),

                ("member_3", c_uint8),
                ("member_4", c_uint8),
                ("member_5", c_uint8),
                ("member_6", c_uint8),

                ("member_7", c_char*24),
                ("member_8", c_char*24),
                ("member_9", c_char*24),

                ("member_10", c_char*63), # 预留

                ("member_11", c_uint8),   #校验和
                ("member_12", c_uint8),   #帧尾
                ]



class SendData(Structure):
    _pack_ = 1   #让结构体内存连续
    _fields_ = [("member_1", c_uint16), #c_ubyte),
                ("member_2", c_uint16), #c_ubyte),

                ("member_3", c_uint8),
                ("member_4", c_uint8),
                ("member_5", c_uint8),
                ("member_6", c_uint8),

                ("member_7", c_char*24),
                ("member_8", c_char*24),
                ("member_9", c_char*24),

                ("member_10", c_char*63), # 预留

                ("member_11", c_uint8), #错误码
                ("member_12", c_uint8),
                ("member_13", c_uint8),
                ]


def bin2sum(num):

    # import pdb
    # pdb.set_trace()
    try:
        num = hex(num)[2:]
    except:
        num = num.hex()#[2:]

    sum_0 = 0
    for i in range(0, len(num), 2):
        sum_0 += int(num[i:i+2], 16)
    print("--> ", sum_0)

    return sum_0 #bytes.fromhex(hex(int(bin(sum_0)[-8:],2))[2:])


#校验和  print(hex(0x1234&0xff))  0x34; 
#校验和  print(hex(0x1234>>8))    0x12 
def cal_checksum(data): # 低8位求和， 不包括帧头 帧尾 校验和

    # pdb.set_trace()

    # m1 = print(hex(data.member_1))
    m2 = bin2sum(data.member_2) #>> 8
    m3 = bin2sum(data.member_3) #>> 8
    m4 = bin2sum(data.member_4) #>> 8
    m5 = bin2sum(data.member_5) #>> 8
    m6 = bin2sum(data.member_6) #>> 8
    m7 = bin2sum(data.member_7) # binascii.unhexlify(data.member_7) #int(data.member_7) >> 8
    m8 = bin2sum(data.member_8) #>> 8
    m9 = bin2sum(data.member_9) #>> 8
    m10 = bin2sum(data.member_10) #>> 8

    sum_ = sum([m2,m3,m4,m5,m6,m7,m8,m9,m10])

    return int(bin(sum_)[-8:],2)

    # m1 = print(hex(data.member_11))
    # m1 = print(hex(data.member_12))





data = Data()
data_ret = SendData()
PORT = 18000
receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
address = ("192.168.1.200", PORT)
receiver_socket.bind(address)

PORT = 10000
sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_address = ("192.168.1.205", PORT)


# data_ret.member_1= 0x90EB
# data_ret.member_2= 0x0803
# data_ret.member_3= 125
# data_ret.member_4= 223
# data_ret.member_5= 222
# data_ret.member_6= 45
# data_ret.member_7= str("192.168.12.1:1630").encode()
# data_ret.member_8= str("192.168.12.1:1630").encode()
# data_ret.member_9= str("192.168.12.1:1630").encode()
# data_ret.member_10= 1
# data_ret.member_11= 12
# data_ret.member_11= 12


while True:
    now = time.time()
    print(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(now)))
    message, client = receiver_socket.recvfrom(1024)
    memmove(addressof(data), (message), sizeof(Data))

    print("------------------------------------receive:\n")


    print(hex(data.member_1))
    print(hex(data.member_2))
    print(hex(data.member_3))
    print(hex(data.member_4))
    print(hex(data.member_5))
    print(hex(data.member_6))
    print((data.member_7))
    print((data.member_8))
    print((data.member_9))
    print((data.member_10))
    print(hex(data.member_11))
    print(hex(data.member_12))


    time.sleep(1)
    print("------------------------------------send\n")
    data_ret.member_1  = data.member_1
    data_ret.member_2  = 0x0803
    data_ret.member_3  = data.member_3
    data_ret.member_4  = data.member_4
    data_ret.member_5  = data.member_5
    data_ret.member_6  = data.member_6
    data_ret.member_7  = data.member_7
    data_ret.member_8  = data.member_8
    data_ret.member_9  = data.member_9
    data_ret.member_10 = data.member_10
    data_ret.member_11 = 1 # 错误码
    data_ret.member_12 = cal_checksum(data) #data.member_11  [cal_checksum is ok??
    data_ret.member_13 = data.member_12

    sender_socket.sendto(data_ret, receiver_address)
    print("------------------------------------succes\n")

    print("校验和_romote: ", data.member_11)
    print("校验和_my: ",     cal_checksum(data))

    # print ('member_1: %d\n' % data.member_1, 'member_2: %d\n' % data.member_2, 'member_3: %d\n' % data.member_3, \
    #       'member_4: %d\n' % data.member_4, 'member_5: %d\n' % data.member_5,'member_6: %d\n' % data.member_6)

    # print ('member_7: %s\n' % data.member_7, 'member_8: %s\n' % data.member_8, 'member_9: %s\n' % data.member_9)
    # print ('member_10: %d\n' % data.member_10, 'member_11: %d\n'% data.member_11)
    # time.sleep(1)

    break


