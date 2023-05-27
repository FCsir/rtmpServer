#ifndef RTMPSERVER_RTMP_SOCKET
#define RTMPSERVER_RTMP_SOCKET

#include <string>
#include <memory>

#include "tcp/tcp_epoll_server.h"
#include "tcp/tcp_connection.h"

namespace rtmpserver
{
namespace transport
{
    typedef struct RTMPPacket {
        PacketPtr tcp_packet_ptr;
        bool is_c0c1;
        bool is_c2;
    } RTMPPacket;

    typedef std::shared_ptr<RTMPPacket> RTMPPacketPtr;

    class RTMPServer
    {
    public:
        RTMPServer()                                       = default;
        RTMPServer(const RTMPServer& other)            = delete;
        RTMPServer& operator=(const RTMPServer& other) = delete;
        RTMPServer(RTMPServer&& other)                 = delete;
        RTMPServer& operator=(RTMPServer&& other)      = delete;
        ~RTMPServer();

        RTMPServer(const std::string &local_ip, uint16_t local_port);

        void Start();
        void Stop();
        // void Send(RTMPPacketPtr);
        // RTMPPacketPtr recv();

    private:
        std::shared_ptr<EpollTcpServer> tcp_server_ = nullptr;
        std::string local_ip_;
        uint16_t local_port_;

        char version_ = 0x03;

        void registerConnection(int fd);

        std::string randomS0S1S2String_(int sed);

        void triggerRead_(int fd);

    };

} // end namespace transport
} // end namespace rtmpserver

#endif