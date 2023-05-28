#ifndef RTMPSERVER_RTMP_CHUNK_1
#define RTMPSERVER_RTMP_CHUNK_1

#include <cstdint>

namespace rtmpserver
{
namespace transport
{


class Chunk1
{

private:
    uint8_t chunk_stream_id_;
    uint32_t timestamp_delta_;
    uint8_t type_;
    uint32_t body_len_;
    char *body_;
};
}
}

#endif