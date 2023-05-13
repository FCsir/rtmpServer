#include <string>
#include <memory>
#include <iostream>


#include "tcp/tcp_epoll_server.h"

int main(int argc, char *argv[])
{
    std::string local_ip{"127.0.0.1"};
    uint16_t local_port{7777};
    if (argc >= 2)
    {
        local_ip = std::string(argv[1]);
    }
    if (argc >= 3)
    {
        local_port = std::atoi(argv[2]);
    }

    typedef rtmpserver::transport::EpollTcpServer ETS;

    auto epoll_server = std::make_shared<ETS>(local_ip, local_port);

    if (!epoll_server)
    {
        std::cout << "tcp server create failed !"
                  << std::endl;
        exit(-1);
    }

    typedef rtmpserver::transport::PacketPtr PacketPtr;
    auto recv_call = [&](const PacketPtr &data) -> void
    {
        epoll_server->SendData(data);
        return;
    };

    epoll_server->RegisterOnRecvCallback(recv_call);

    if(!epoll_server->Start())
    {
        std::cout << "tcp server start failed !"
                  << std::endl;
        exit(1);
    }

    std::cout << "########### tcp server started! #############"
              << std::endl;
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    epoll_server->Stop();

    return 0;
}