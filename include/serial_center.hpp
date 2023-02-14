#include <iostream>
#include <string>
#include "serial/serial.h"
#include <vector>
#include "cyber/cyber.h"
#include "cyber/state.h"
#include "cyber/time/rate.h"
#include "cyber/time/time.h"

#include "control_base.pb.h"
#include "config.pb.h"

#include "table_msgs.hpp"


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



