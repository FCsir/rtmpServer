#ifndef RTMPSERVER_RTMP_C0S0
#define RTMPSERVER_RTMP_C0S0

#include <string>


namespace rtmpserver
{
namespace transport
{


class C0C1
{
const static int rtmp_version = 0x03;

public:
    C0C1() = default;

    void Write(int fd);
    void Read();
};

} // end transport
} // end rtmpserver

#endif