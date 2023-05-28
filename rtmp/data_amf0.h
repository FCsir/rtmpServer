#ifndef RTMPSERVER_RTMP_DATA_AMF0
#define RTMPSERVER_RTMP_DATA_AMF0

#include <string>


namespace rtmpserver
{
namespace transport
{

class DataAMF0
{


private:
    uint8_t chunk_stream_id_;
    uint32_t message_stream_id_;
    std::string name_;
    char *payload_;
};
}
}

#endif