#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>
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
             boost::uuids::uuid a_uuid = boost::uuids::random_generator()();
             std::string uuid_string = boost::uuids::to_string(a_uuid);
             connections[uuid_string] = RtmpConnection(std::move(socket), uuid_string);
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

            // start the manage connection
            runManageConnection();
        }
        catch (std::exception& e)
        {
            std::printf("Exception: %s\n", e.what());
        }
    }

    void RTMPServer::runManageConnection()
    {
        std::cout << "Starting manage connection thread caller.\n";
        auto func = []() {
            std::cout << "manage the connection \n";
        };
        std::thread t(func);
        t.detach();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Exiting manage connection caller.\n";
    }

    RTMPServer::~RTMPServer()
    {
    }

} // end namespace transport
} // end namespace rtmpserver