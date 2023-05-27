#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <unistd.h>

#include "rtmp_server.h"
#include "tcp/tcp_epoll_server.h"
#include "tcp/tcp_connection.h"

namespace rtmpserver
{
namespace transport
{

    RTMPServer::RTMPServer(const std::string &local_ip, uint16_t local_port)
        : local_ip_{local_ip}, local_port_{local_port}
    {
        auto epoll_server = std::make_shared<EpollTcpServer>(local_ip, local_port);

        if (!epoll_server)
        {
            std::cout << "tcp server create failed !"
                    << std::endl;
            exit(-1);
        }

        tcp_server_ = epoll_server;
        tcp_server_.handleConnection(registerConnection)
    }

    void RTMPServer::Start()
    {
        auto recv_call = [&](int fd) -> void
        {
            std::cout << "receive tcp apcket"
                      << std::endl;
            triggerRead_(fd);
            return;
        };

        tcp_server_->RegisterOnRecvCallback(recv_call);

        if(!tcp_server_->Start())
        {
            std::cout << "rtmp server start failed !"
                    << std::endl;
            exit(1);
        }

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        tcp_server_->Stop();
        
    }

    RTMPServer::~RTMPServer()
    {
        // tcp_server_->Stop();
    }

    void RTMPServer::triggerRead_(int fd)
    {
        // TODO read msg
    }

    std::string RTMPServer::randomS0S1S2String_(int sed)
    {
        static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        auto t = std::time(0);
        std::cout << "t: " << t << std::endl;
        srand(t + sed);
        tmp_s.reserve(1528);

        for (int i = 0; i < 1528; ++i) {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
    }

} // end namespace transport
} // end namespace rtmpserver