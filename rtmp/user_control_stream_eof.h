#ifndef RTMPSERVER_RTMP_USER_CONTROL_STREAM_EOF
#define RTMPSERVER_RTMP_USER_CONTROL_STREAM_EOF

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlStreamEof
{

private:
    uint32_t stream_id_;
};
}
}

#endif