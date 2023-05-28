#ifndef RTMPSERVER_RTMP_COMMAND_AMF0
#define RTMPSERVER_RTMP_COMMAND_AMF0

#include <string>


namespace rtmpserver
{
namespace transport
{

class CommandAMF0
{


private:
    uint8_t chunk_stream_id_;
    uint32_t message_stream_id_;
    std::string name_;
    int command_id_;
    char *arguments_;
};
}
}

#endif