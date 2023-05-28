#ifndef RTMPSERVER_RTMP_RAW_MESSAGE
#define RTMPSERVER_RTMP_RAW_MESSAGE

#include <cstdint>

namespace rtmpserver
{
namespace transport
{


class RawMessage
{
public:
    RawMessage(
        uint8_t chunk_stream_id,
        uint64_t timestamp,
        uint8_t type,
        uint32_t message_stream_id,
        char* body
    ): chunk_stream_id_{chunk_stream_id},
        timestamp_{timestamp},
        type_{type},
        message_stream_id_{message_stream_id},
        body_{body}
    {}

private:
    uint8_t chunk_stream_id_;
    uint64_t timestamp_;
    uint8_t type_;
    uint32_t message_stream_id_;
    char *body_;
};

}
}

#endif