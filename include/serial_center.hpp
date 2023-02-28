#ifndef SERIAL_CENTER_HPP
#define SERIAL_CENTER_HPP

#include "common_include.h"
#include "table_msgs.hpp"

//处理串口读取的所有消息中心
class Cyber_serial_center
{

public:
	Cyber_serial_center(std::string& port, int _baudrate): _port(port), _baudrate(_baudrate) {}

	bool is_seialOpened(); // try and open the serial port


private:
	std::string _port; //串口
	int _baudrate;     //波特率
	tabele_29_34 _msg2934; //接收29返回34的消息协议

}

#endif

