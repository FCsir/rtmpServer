#ifndef RTMPSERVER_RTMP_SET_WINDOW_ACK_SIZE
#define RTMPSERVER_RTMP_SET_WINDOW_ACK_SIZE

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class SetWindowAckSize
{

private:
    uint32_t value_;
};
}
}

#endif