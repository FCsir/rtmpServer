#ifndef RTMPSERVER_RTMP_USER_CONTROL_PING_REQUEST
#define RTMPSERVER_RTMP_USER_CONTROL_PING_REQUEST

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlPingRequest
{

private:
    uint32_t server_time_;
};
}
}

#endif