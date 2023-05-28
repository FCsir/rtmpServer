#ifndef RTMPSERVER_RTMP_USER_CONTROL_STREAM_IS_RECORDED
#define RTMPSERVER_RTMP_USER_CONTROL_STREAM_IS_RECORDED

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlStreamIsRecorded
{

private:
    uint32_t stream_id_;
};
}
}

#endif