#ifndef RTMPSERVER_RTMP_USER_CONTROL_STREAM_BEGIN
#define RTMPSERVER_RTMP_USER_CONTROL_STREAM_BEGIN

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlStreamBegin
{

private:
    uint32_t stream_id_;
};
}
}

#endif