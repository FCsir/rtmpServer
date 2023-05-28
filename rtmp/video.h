#ifndef RTMPSERVER_RTMP_VIDEO
#define RTMPSERVER_RTMP_VIDEO

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class Video
{

private:
    uint8_t chunk_stream_id_;
    uint64_t dts_;
    uint32_t messege_stream_id_;
    // TODO enum
    uint8_t codec_;
    bool is_key_frame_;


    // TODO enum
    uint8_t type_;
    uint64_t pts_delta_;

    char *payload_;
};
}
}

#endif