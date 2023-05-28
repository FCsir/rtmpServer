#ifndef RTMPSERVER_RTMP_AUDIO
#define RTMPSERVER_RTMP_AUDIO

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class Audio
{

private:
    uint8_t chunk_stream_id_;
    uint64_t dts_;
    uint32_t messege_stream_id_;
    uint8_t codec_;
    uint8_t rate_;
    uint8_t depth_;
    uint8_t channels_;

    // TODO enum
    uint8_t aac_type_;

    char *payload_;
};
}
}

#endif