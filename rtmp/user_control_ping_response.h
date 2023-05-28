#ifndef RTMPSERVER_RTMP_USER_CONTROL_PING_RESPONSE
#define RTMPSERVER_RTMP_USER_CONTROL_PING_RESPONSE

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class UserControlPingResponse
{

private:
    uint32_t server_time_;
};
}
}

#endif