#ifndef RTMPSERVER_RTMP_CHUNK_3
#define RTMPSERVER_RTMP_CHUNK_3

#include <cstdint>

namespace rtmpserver
{
namespace transport
{


class Chunk3
{

private:
    uint8_t chunk_stream_id_;
    char *body_;
};
}
}

#endif