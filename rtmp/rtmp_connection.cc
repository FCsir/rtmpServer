#include <string>
#include <vector>

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>

#include "rtmp_connection.h"

namespace rtmpserver
{
namespace transport
{

    RtmpConnection::RtmpConnection(boost::asio::ip::tcp::socket s)
        :socket_{std::move(s)}
    {}

    boost::asio::awaitable<void> RtmpConnection::listen()
    {
         try
        {
            for (;;)
            {
            // The asynchronous operations to echo a single chunk of data have been
            // refactored into a separate function. When this function is called, the
            // operations are still performed in the context of the current
            // coroutine, and the behaviour is functionally equivalent.
            // co_await echo_once(socket_);
                co_await handleMsg();
            }
        }
        catch (std::exception& e)
        {
            std::printf("echo Exception: %s\n", e.what());
        }
    }

    boost::asio::awaitable<void> RtmpConnection::handleMsg()
    {
        char data[128];
        std::size_t n = co_await socket_.async_read_some(
            boost::asio::buffer(data), boost::asio::use_awaitable);
        // co_await async_write(socket, boost::asio::buffer(data, n), use_awaitable);
    }

}
}