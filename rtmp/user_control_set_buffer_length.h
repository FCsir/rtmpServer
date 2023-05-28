#ifndef RTMPSERVER_RTMP_USER_CONTROL_SET_BUFFER_LENGTH
#define RTMPSERVER_RTMP_USER_CONTROL_SET_BUFFER_LENGTH

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlSetBufferLength
{

private:
    uint32_t stream_id_;
    uint32_t buffer_length_;
};
}
}

#endif