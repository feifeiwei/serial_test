# -*- coding: utf-8 -*-
import socket
import time
import struct
from ctypes import *


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
                ("member_5", c_char*11),#预留
                ("member_6", c_uint8),
                ("member_6", c_uint8),
                ]




class SendData(Structure):
    _pack_ = 1   #让结构体内存连续
    _fields_ = [("member_1", c_uint16), #c_ubyte),
                ("member_2", c_uint16), #c_ubyte),

                ("member_3", c_uint8),
                ("member_4", c_uint8),
                ("member_5", c_uint8),
                ("member_6", c_uint8),

                ("member_7", c_uint8),
                ("member_8", c_uint8),
                ("member_9", c_uint8),
                ("member_10", c_uint8), 
                ("member_11", c_uint8), 
                ("member_12", c_uint8),
                ("member_13", c_uint8),
                ("member_14", c_uint8),
                ("member_15", c_uint8),
                ("member_16", c_char*11),
                ("member_17", c_uint8),
                ("member_18", c_uint8),
                ]


data = Data()
data_ret = SendData()
PORT = 18000
receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
address = ("192.168.1.200", PORT)
receiver_socket.bind(address)


sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_address = ("192.168.1.205", PORT)


data_ret.member_1= 0x90EB
data_ret.member_2= 0x0803
data_ret.member_3= 125
data_ret.member_4= 223
data_ret.member_5= 222
data_ret.member_6= 45
data_ret.member_7= 7
data_ret.member_8= 8
data_ret.member_9= 9
data_ret.member_10= 10
data_ret.member_11= 12
data_ret.member_12= 12
data_ret.member_13= 13
data_ret.member_14= 14
data_ret.member_15= 15
data_ret.member_16= str("keep").encode()
data_ret.member_17= 17
data_ret.member_18= 18


while True:
    now = time.time()
    print(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(now)))
    message, client = receiver_socket.recvfrom(1024)
    memmove(addressof(data), (message), sizeof(Data))

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
    print("------------------------------------send")
    data_ret.member_1  = data.member_1
    data_ret.member_2  = data.member_2
    data_ret.member_3  = data.member_3
    data_ret.member_4  = data.member_4
    data_ret.member_5  = data.member_5
    data_ret.member_6  = data.member_6
    data_ret.member_7  = data.member_7
    data_ret.member_8  = data.member_8
    data_ret.member_9  = data.member_9
    data_ret.member_10 = data.member_10
    data_ret.member_11 = 1 # 错误码
    data_ret.member_12 = data.member_11
    data_ret.member_13 = data.member_12

    sender_socket.sendto(data_ret, receiver_address)
    print("------------------------------------succes")

    # print ('member_1: %d\n' % data.member_1, 'member_2: %d\n' % data.member_2, 'member_3: %d\n' % data.member_3, \
    #       'member_4: %d\n' % data.member_4, 'member_5: %d\n' % data.member_5,'member_6: %d\n' % data.member_6)

    # print ('member_7: %s\n' % data.member_7, 'member_8: %s\n' % data.member_8, 'member_9: %s\n' % data.member_9)
    # print ('member_10: %d\n' % data.member_10, 'member_11: %d\n'% data.member_11)
    # time.sleep(1)

    break


