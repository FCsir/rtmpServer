#ifndef RTMPSERVER_RTMP_HANDSHAKE
#define RTMPSERVER_RTMP_HANDSHAKE

#include <string>

#include <tcp/tcp_epoll_server.h>


namespace rtmpserver
{
namespace transport
{

type struct C0C1
{
} C0C1;



class C0C1
{
const static int rtmp_version = 0x03;

public:
    C0C1(const PacketPtr& packet_ptr);
    C0C1() = default;

    void Write(int fd);
    void Read();
};

} // end transport
} // end rtmpserver

#endif