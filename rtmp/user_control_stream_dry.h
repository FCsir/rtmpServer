#ifndef RTMPSERVER_RTMP_USER_CONTROL_STREAM_DRY
#define RTMPSERVER_RTMP_USER_CONTROL_STREAM_DRY

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlStreamDry
{

private:
    uint32_t stream_id_;
};
}
}

#endif