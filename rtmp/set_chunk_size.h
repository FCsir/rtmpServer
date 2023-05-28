#ifndef RTMPSERVER_RTMP_SET_CHUNK_SIZE
#define RTMPSERVER_RTMP_SET_CHUNK_SIZE

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class SetChunkSize
{

private:
    uint32_t value_;
};
}
}

#endif