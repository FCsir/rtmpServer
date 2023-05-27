#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <unistd.h>


#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <cstdio>

#include "rtmp_server.h"
#include "rtmp_connection.h"

using boost::asio::ip::tcp;
namespace this_coro = boost::asio::this_coro;

namespace rtmpserver
{
namespace transport
{

    RTMPServer::RTMPServer(const std::string &local_ip, uint16_t local_port)
        : local_ip_{local_ip}, local_port_{local_port}
    {
    }

    boost::asio::awaitable<void> RTMPServer::listener()
    {
        auto executor = co_await this_coro::executor;
        tcp::acceptor acceptor(executor, {tcp::v4(), local_port_});
        for (;;)
        {
            tcp::socket socket = co_await acceptor.async_accept(boost::asio::use_awaitable);
            connections.push_back(RtmpConnection(std::move(socket)));
        }
    }

    void RTMPServer::Start()
    {
        try
        {
            boost::asio::io_context io_context(1);

            boost::asio::signal_set signals(io_context, SIGINT, SIGTERM);
            signals.async_wait([&](auto, auto){ io_context.stop(); });

            boost::asio::co_spawn(io_context, listener(), boost::asio::detached);

            io_context.run();
        }
        catch (std::exception& e)
        {
            std::printf("Exception: %s\n", e.what());
        }

    }

    RTMPServer::~RTMPServer()
    {
    }

} // end namespace transport
} // end namespace rtmpserver