#ifndef RTMPSERVER_RTMP_ACKNOWLEDGEMENT
#define RTMPSERVER_RTMP_ACKNOWLEDGEMENT

#include <cstdint>

namespace rtmpserver
{
namespace transport
{

class Acknowledgement
{

private:
    uint32_t value_;
};
}
}

#endif