#include <string>
#include <memory>
#include <iostream>


#include "tcp/tcp_epoll_server.h"
#include "tcp/rtmp_server.h"


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

    typedef rtmpserver::transport::RTMPServer RTMPServer;

    auto rtmp_server = std::make_shared<RTMPServer>(local_ip, local_port);

    if (!rtmp_server)
    {
        std::cout << "rtmp server create failed !"
                  << std::endl;
        exit(-1);
    }

    rtmp_server->Start();

    std::cout << "########### rtmp server started! #############"
              << std::endl;

    return 0;
}