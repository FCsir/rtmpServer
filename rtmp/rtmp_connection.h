#ifndef RTMPSERVER_RTMP_CONNECTION
#define RTMPSERVER_RTMP_CONNECTION

#include <string>
#include <vector>
#include <boost/asio/ip/tcp.hpp>

namespace rtmpserver
{
namespace transport
{

class RtmpConnection
{

public:
    RtmpConnection(boost::asio::ip::tcp::socket s);

private:
    boost::asio::ip::tcp::socket socket_;
    boost::asio::awaitable<void> listen();
    boost::asio::awaitable<void> handleMsg();
};
}
}

#endif