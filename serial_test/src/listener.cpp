#include "control_base.pb.h"

#include "cyber/cyber.h"
#include <iostream>

using test::control_base;

void MessageCallback(const std::shared_ptr<control_base>& msg) 
{
  // AINFO << "visible_image_addr-> " << msg->visible_image_addr();

  std::cout <<"listen: " << msg->visible_image_addr() << std::endl;
  //AINFO << "set_visible_image_addr->" << msg->set_visible_image_addr();
}



int main(int argc, char* argv[]) {
  // init cyber framework
  std::cout <<"listen:0 " << std::endl;
  apollo::cyber::Init(argv[0]);
  // create listener node
  auto listener_node = apollo::cyber::CreateNode("listener");
  // create listener
  std::cout <<"listen: 1" << std::endl;
  auto listener =
      listener_node->CreateReader<control_base>(
          "topic_test", MessageCallback);

  std::cout <<"listen: 2" << std::endl;
  apollo::cyber::WaitForShutdown();
  return 0;
}