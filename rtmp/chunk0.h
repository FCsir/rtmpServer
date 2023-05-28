#ifndef RTMPSERVER_RTMP_CHUNK_0
#define RTMPSERVER_RTMP_CHUNK_0

#include <cstdint>

namespace rtmpserver
{
namespace transport
{


class Chunk0
{

private:
    uint8_t chunk_stream_id_;
    uint32_t timestamp_;
    uint8_t type_;
    uint32_t message_stream_id_;
    uint32_t body_len_;
    char *body_;
};
}
}

#endif