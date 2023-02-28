
#include "common_include.h"


using test::control_base;

using apollo::cyber::Rate;
using apollo::cyber::Time;
// using apollo::cyber::examples::proto::Chatter;

int main(int argc, char *argv[]) {
  // init cyber framework
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto talker_node = apollo::cyber::CreateNode("talker");
  // create talker
  auto talker = talker_node->CreateWriter<control_base>("topic_test");
  Rate rate(1.0);
  uint64_t seq = 0;
  
  std::cout <<"init publisher .." << std::endl;
  while (apollo::cyber::OK()) {
    auto msg = std::make_shared<control_base>();


    // msg->set_timestamp(Time::Now().ToNanosecond());
    // msg->set_lidar_timestamp(Time::Now().ToNanosecond());
    // msg->set_seq(seq);
    msg->set_visible_image_addr("Hello, apollo!");
    talker->Write(msg);
    AINFO << "talker sent a message!. " << seq;
    std::cout <<"start .." << std::endl;
    seq++;
    rate.Sleep();
  }


  return 0;
}