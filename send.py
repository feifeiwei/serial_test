# -*- coding: utf-8 -*-

import socket
import time
import struct
from ctypes import *


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
data.member_1= 0x90EB
data.member_2= 0x0507
data.member_3= 125
data.member_4= 223
data.member_5= 222
data.member_6= 45
data.member_7= str("192.168.12.1:1630").encode()
data.member_8= str("192.168.12.1:1630").encode()
data.member_9= str("192.168.12.1:1630").encode()
data.member_10= 1
data.member_11= 12
data.member_11= 12

PORT = 18000
sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_address = ("192.168.1.205", PORT)

while True:
    start = time.time()
    print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(start)))
    sender_socket.sendto(data, receiver_address)
    print ('member_1: %d\n' % data.member_1, 'member_2: %d\n' % data.member_2, 'member_3: %d\n' % data.member_3, \
          'member_4: %d\n' % data.member_4, 'member_5: %d\n' % data.member_5,'member_6: %d\n' % data.member_6)

    print ('member_7: %s\n' % data.member_7, 'member_8: %s\n' % data.member_8, 'member_9: %s\n' % data.member_9)
    print ('member_10: %d\n' % data.member_10, 'member_11: %d\n'% data.member_11)
    time.sleep(1)



#"90eb05078a00000030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303030303050aa"