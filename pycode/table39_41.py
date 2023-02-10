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
    _fields_ = [("member_1", c_uint16), #c_ubyte),eb90
                ("member_2", c_uint16), #c_ubyte), 0x0706

                ("member_3", c_uint8),
                ("member_4", c_uint8),
                ("member_5", c_char*11),#预留
                ("member_6", c_uint8),
                ("member_6", c_uint8),  #AAH
                ]




class SendData(Structure):
    _pack_ = 1   #让结构体内存连续
    _fields_ = [("member_1", c_uint16), #c_ubyte),
                ("member_2", c_uint16), #c_ubyte),

                ("member_3", c_uint8),
                ("member_4", c_uint8),
                ("member_5", c_uint8),
                ("member_6", c_char*24),

                ("member_7", c_uint8),
                ("member_8", c_uint8),
                ("member_9", c_uint8),
                ("member_10", c_uint8), 
                ("member_11", c_uint8), 
                ("member_12", c_uint8),
                ("member_13", c_uint8),
                ("member_14", c_uint8),
                ("member_15", c_uint8),
                ("member_16", c_uint8),
                ("member_17", c_uint8),
                ("member_18", c_uint8),

                ("member_19", c_uint16),
                ("member_20", c_uint8),
                ("member_21", c_uint8),

                ("member_22", c_char*24),

                ("member_23", c_uint8),
                ("member_24", c_uint16),
                ("member_25", c_uint8),
                ("member_26", c_uint8),
                ("member_27", c_char*7),

                ("member_28", c_uint8),
                ("member_29", c_uint8),
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
data_ret.member_2= 0x0804
data_ret.member_3= 29
data_ret.member_4= 1
data_ret.member_5= 0
data_ret.member_6= str("192.168.12.1:1630").encode()
data_ret.member_7= 7
data_ret.member_8= 8
data_ret.member_9= 9
data_ret.member_10= 1
data_ret.member_11= 12
data_ret.member_12= 12
data_ret.member_13= 1
data_ret.member_14= 12
data_ret.member_15= 12
data_ret.member_16= 1
data_ret.member_17= 12
data_ret.member_18= 12
data_ret.member_19= 1
data_ret.member_20= 12
data_ret.member_21= 12
data_ret.member_22= str("192.168.12.1:1111").encode()
data_ret.member_23= 12
data_ret.member_24= 12
data_ret.member_25= 1
data_ret.member_26= 12
data_ret.member_27= str("keep").encode()
data_ret.member_28= 1
data_ret.member_29= 0XAA

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
    sender_socket.sendto(data_ret, receiver_address)
    print("------------------------------------succes")

    # print ('member_1: %d\n' % data.member_1, 'member_2: %d\n' % data.member_2, 'member_3: %d\n' % data.member_3, \
    #       'member_4: %d\n' % data.member_4, 'member_5: %d\n' % data.member_5,'member_6: %d\n' % data.member_6)

    # print ('member_7: %s\n' % data.member_7, 'member_8: %s\n' % data.member_8, 'member_9: %s\n' % data.member_9)
    # print ('member_10: %d\n' % data.member_10, 'member_11: %d\n'% data.member_11)
    # time.sleep(1)

    break


