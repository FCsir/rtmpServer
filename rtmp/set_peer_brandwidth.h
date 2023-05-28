#ifndef RTMPSERVER_RTMP_SET_PEER_BRANDWIDTH
#define RTMPSERVER_RTMP_SET_PEER_BRANDWIDTH

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class SetPeerBRANDWIDTH
{

private:
    uint32_t value_;
    uint8_t type_;
};
}
}

#endif