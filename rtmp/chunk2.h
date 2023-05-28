#ifndef RTMPSERVER_RTMP_CHUNK_2
#define RTMPSERVER_RTMP_CHUNK_2

#include <cstdint>

namespace rtmpserver
{
namespace transport
{


class Chunk2
{

private:
    uint8_t chunk_stream_id_;
    uint32_t timestamp_delta_;
    char *body_;
};
}
}

#endif