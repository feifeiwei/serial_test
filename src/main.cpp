#include "common_include.h"

//#include "modules/drivers/contorl_center/contorl_component.h"

using apollo::cyber::Component;
using apollo::cyber::Reader;
using apollo::cyber::Writer;

using test::control_base;
using test::Config;

void shutdown(){}

void startup(){}
void reset(){}

void saveMode(){}
void normalMode(){}
void highMode(){}

serial::Serial ser_;
// std::string port_config;
const size_t MAX_MESSAGE_SIZE = 145;
int index_ = 0;



void run(const std::string& port_) {
  unsigned char chrBuffer[1000];
  unsigned char chrTemp[1000];
  unsigned short usLength=0,usRxLength=0;
  while (!apollo::cyber::IsShutdown()) {
    try
    {
        if (ser_.isOpen())
        {
            // read string from serial device
            if(ser_.available())
            {
                size_t n = ser_.available();
                //std::cout << "the number of bytes in buffer is " << n << std::endl;
                usLength = ser_.read(chrBuffer, n); // size_t should be 43
                if (usLength>0)
                {
                    usRxLength += usLength;
                    // std::cout << "the number of bytes in buffer is " << usRxLength << std::endl;
                    while (usRxLength >= MAX_MESSAGE_SIZE)
                    {
                        memcpy(chrTemp,chrBuffer,usRxLength);
                        // std::cout << "uchar head: " << (unsigned char)0x55 << "header: " << 0x55 << std::endl;
                        if (!((chrTemp[0] == 0xEB) && (chrTemp[1] == 0x90)))
                        {

                            for (int i = 1; i < usRxLength; i++) chrBuffer[i - 1] = chrBuffer[i];
                            usRxLength--;
                            continue;
                        }

                        unsigned short totalLength;

                        // 控制消息
                        if ((chrTemp[2] == 0x07) && (chrTemp[3] == 0x05))
                        {
                            uint8_t controlType;
                            memcpy(&controlType, chrTemp + 5, 1);
                            // switch (controlType)
                            switch (chrTemp[5])
                            {
                                // 设备基本控制消息
                                case 0x00:
                                {
                                    uint8_t msgLength, runningStatus, runningMode;
                                    memcpy(&msgLength, chrTemp + 4, 1);
                                    memcpy(&runningStatus, chrTemp + 6, 1);
                                    memcpy(&runningMode, chrTemp + 7, 1);

                                    totalLength = msgLength + 7;

                                    // 获取图像来源地址
                                    char visibleAddr[24], infraredAddr[24], sarAddr[24];
                                    memcpy(&visibleAddr, chrTemp + 8, sizeof(visibleAddr));
                                    memcpy(&infraredAddr, chrTemp + 32, sizeof(infraredAddr));
                                    memcpy(&sarAddr, chrTemp + 56, sizeof(sarAddr));

                                    // 校验和、帧尾
                                    uint8_t checkSum, tail;
                                    memcpy(&checkSum, chrTemp + totalLength - 2, 1);
                                    memcpy(&tail, chrTemp + totalLength - 1, 1);

                                    // switch (runningStatus)
                                    switch (chrTemp[6])
                                    {
                                        case 0x00: shutdown(); //关机
                                            break;
                                        case 0x01: startup();  //启动
                                            break;
                                        case 0x02: reset();    //复位
                                            break;
                                        default :
                                            AERROR << "Error: unsupported device running status";
                                    }
                                    // switch (runningMode)
                                    switch (chrTemp[7])
                                    {
                                        case 0x00: saveMode(); //节能
                                            break;
                                        case 0x01: normalMode();  //一般
                                            break;
                                        case 0x02: highMode();    //高性能
                                            break;
                                        default :
                                            AERROR << "Error: unsupported device running status";
                                    }
                                    
                                    break;
                                }
                                // 检测识别控制消息
                                case 0x01:
                                {
                                    uint8_t msgLength, enable_recog, enable_multimodal;
                                    memcpy(&msgLength, chrTemp + 4, 1);
                                    memcpy(&enable_recog, chrTemp + 6, 1);
                                    memcpy(&enable_multimodal, chrTemp + 7, 1);

                                    totalLength = msgLength + 7;

                                    // 获取图像来源地址
                                    char visibleAddr[24], infraredAddr[24], sarAddr[24];
                                    memcpy(&visibleAddr, chrTemp + 8, sizeof(visibleAddr));
                                    memcpy(&infraredAddr, chrTemp + 32, sizeof(infraredAddr));
                                    memcpy(&sarAddr, chrTemp + 56, sizeof(sarAddr));

                                    // 校验和、帧尾
                                    uint8_t checkSum, tail;
                                    memcpy(&checkSum, chrTemp + totalLength - 2, 1);
                                    memcpy(&tail, chrTemp + totalLength - 1, 1);

                                    break;
                                }
                                // 跟踪控制消息
                                case 0x02:
                                {
                                    uint8_t msgLength, runningStatus, runningMode;
                                    memcpy(&msgLength, chrTemp + 4, 1);
                                    memcpy(&runningStatus, chrTemp + 6, 1);
                                    memcpy(&runningMode, chrTemp + 7, 1);

                                    totalLength = msgLength + 7;

                                    // 获取图像来源地址
                                    char visibleAddr[24], infraredAddr[24], sarAddr[24];
                                    memcpy(&visibleAddr, chrTemp + 8, sizeof(visibleAddr));
                                    memcpy(&infraredAddr, chrTemp + 32, sizeof(infraredAddr));
                                    memcpy(&sarAddr, chrTemp + 56, sizeof(sarAddr));

                                    // 校验和、帧尾
                                    uint8_t checkSum, tail;
                                    memcpy(&checkSum, chrTemp + totalLength - 2, 1);
                                    memcpy(&tail, chrTemp + totalLength - 1, 1);

                                    break;
                                }
                                // 告警控制消息
                                case 0x03:
                                {
                                    uint8_t msgLength, runningStatus, runningMode;
                                    memcpy(&msgLength, chrTemp + 4, 1);
                                    memcpy(&runningStatus, chrTemp + 6, 1);
                                    memcpy(&runningMode, chrTemp + 7, 1);

                                    totalLength = msgLength + 7;

                                    // 获取图像来源地址
                                    char visibleAddr[24], infraredAddr[24], sarAddr[24];
                                    memcpy(&visibleAddr, chrTemp + 8, sizeof(visibleAddr));
                                    memcpy(&infraredAddr, chrTemp + 32, sizeof(infraredAddr));
                                    memcpy(&sarAddr, chrTemp + 56, sizeof(sarAddr));

                                    // 校验和、帧尾
                                    uint8_t checkSum, tail;
                                    memcpy(&checkSum, chrTemp + totalLength - 2, 1);
                                    memcpy(&tail, chrTemp + totalLength - 1, 1);

                                    break;
                                }
                                // 识别类别控制消息
                                case 0x04:
                                {
                                    uint8_t msgLength, runningStatus, runningMode;
                                    memcpy(&msgLength, chrTemp + 4, 1);
                                    memcpy(&runningStatus, chrTemp + 6, 1);
                                    memcpy(&runningMode, chrTemp + 7, 1);

                                    totalLength = msgLength + 7;

                                    // 获取图像来源地址
                                    char visibleAddr[24], infraredAddr[24], sarAddr[24];
                                    memcpy(&visibleAddr, chrTemp + 8, sizeof(visibleAddr));
                                    memcpy(&infraredAddr, chrTemp + 32, sizeof(infraredAddr));
                                    memcpy(&sarAddr, chrTemp + 56, sizeof(sarAddr));

                                    // 校验和、帧尾
                                    uint8_t checkSum, tail;
                                    memcpy(&checkSum, chrTemp + totalLength - 2, 1);
                                    memcpy(&tail, chrTemp + totalLength - 1, 1);

                                    break;
                                }
                                default :
                                {
                                   AERROR << "Error: unsupported control message type"; 
                                }
                            }
                            
                        }
                        // 查询消息
                        else if ((chrTemp[2] == 0x07) && (chrTemp[3] == 0x06))
                        {

                        }
                        else
                        {
                           AERROR << "Error: unsupported message code"; 
                        }

                        for (int i = totalLength; i < usRxLength; i++)
                            chrBuffer[i - totalLength] = chrBuffer[i];
                        usRxLength -= totalLength;
                    }
                }
            }
            else  // ser_ not available
            {
                AINFO << "Serial is not available.";
            }
        }
        else
        {
            // try and open the serial port
            try
            {
                ser_.setPort(port_);
                ser_.setBaudrate(115200);
                serial::Timeout to = serial::Timeout::simpleTimeout(1000);
                ser_.setTimeout(to);
                ser_.open();
            }
            catch (serial::IOException& e)
            {
                AERROR << "Unable to open serial port " << ser_.getPort() << ". Trying again in 5 seconds.";
                apollo::cyber::Duration(5).Sleep();
            }

            if(ser_.isOpen())
            {
                ADEBUG << "serial port " << ser_.getPort() << " initialized.";
            }
            else
            {
                AINFO << "Could not initialize serial port.";
            }

        }
    }
    catch (serial::IOException& e)
    {
        AERROR << "Error reading from the serial port " << ser_.getPort() << ". Closing connection.";
        ser_.close();
    }

  }
}




void MessageCallback(const std::shared_ptr<Config>& msg) 
{
  // AINFO << "visible_image_addr-> " << msg->visible_image_addr();

  std::cout <<"listen: " << msg->port() << std::endl;
  run(msg->port());

  //AINFO << "set_visible_image_addr->" << msg->set_visible_image_addr();
}


int main(int argc, char* argv[])
{
	// init cyber framework
	apollo::cyber::Init(argv[0]);
	// create talker node
	auto talker_node = apollo::cyber::CreateNode("main");

	std::cout <<"listener serial!" << std::endl;
	auto listener_node = apollo::cyber::CreateNode("listener");

	auto listener = listener_node->CreateReader<Config>(
          "Config", MessageCallback);

	apollo::cyber::WaitForShutdown();
	return 0;
}