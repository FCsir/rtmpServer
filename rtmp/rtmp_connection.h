#ifndef RTMPSERVER_RTMP_CONNECTION
#define RTMPSERVER_RTMP_CONNECTION

#include <string>
#include <vector>
namespace rtmpserver
{
namespace transport
{

class RtmpConnectionPublisher
{

public:
    RtmpConnectionPublisher(int fd);
    void handShake();

private:
    std::string push_url_;
    int fd_;

    std::vector<std::string &> msg_list_;
};

class RtmpConnectionReceiver
{

public:
    RtmpConnectionReceiver(int fd);
    void handShake();
    void sendMsg();

private:
    std::string sub_url_;
    int fd_;
};
}
}

#endif