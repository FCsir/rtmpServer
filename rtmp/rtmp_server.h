#ifndef RTMPSERVER_RTMP_SOCKET
#define RTMPSERVER_RTMP_SOCKET

#include <string>
#include <memory>
#include <vector>

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <cstdio>

#include "rtmp_connection.h"

namespace rtmpserver
{
namespace transport
{
    class RTMPServer
    {
    public:
        RTMPServer()                                   = default;
        RTMPServer(const RTMPServer& other)            = delete;
        RTMPServer& operator=(const RTMPServer& other) = delete;
        RTMPServer(RTMPServer&& other)                 = delete;
        RTMPServer& operator=(RTMPServer&& other)      = delete;
        ~RTMPServer();

        RTMPServer(const std::string &local_ip, uint16_t local_port);

        void Start();
        // void Send(RTMPPacketPtr);
        // RTMPPacketPtr recv();

    private:
        char version_ = 0x03;

        std::string local_ip_;
        uint16_t local_port_;
        std::vector<RtmpConnection> connections;
        boost::asio::awaitable<void> listener();
    };



} // end namespace transport
} // end namespace rtmpserver

#endif