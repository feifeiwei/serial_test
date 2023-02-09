# -*- coding: utf-8 -*-

import socket
import time
import struct
from ctypes import *
import pdb
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

                ("member_10", c_uint8),
                ("member_11", c_uint8),
                ]

data = Data()
PORT = 8000
receiver_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
address = ("192.168.56.1", PORT)
receiver_socket.bind(address)

while True:
    now = time.time()
    print(time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(now)))
    message, client = receiver_socket.recvfrom(1024)
    memmove(addressof(data), (message), sizeof(Data))


    print(hex(data.member_1))

    # print ('member_1: %d\n' % data.member_1, 'member_2: %d\n' % data.member_2, 'member_3: %d\n' % data.member_3, \
    #       'member_4: %d\n' % data.member_4, 'member_5: %d\n' % data.member_5,'member_6: %d\n' % data.member_6)

    # print ('member_7: %s\n' % data.member_7, 'member_8: %s\n' % data.member_8, 'member_9: %s\n' % data.member_9)
    # print ('member_10: %d\n' % data.member_10, 'member_11: %d\n'% data.member_11)
    # time.sleep(1)

    break


