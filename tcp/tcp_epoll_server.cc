#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>

#include "tcp/tcp_epoll_server.h"


namespace rtmpserver
{
namespace transport
{
    EpollTcpServer::EpollTcpServer(const std::string &local_ip, uint16_t local_port)
        : local_ip_{local_ip}, local_port_{local_port}
    {}


    bool EpollTcpServer::Start()
    {
        if (CreateEpoll() < 0)
            return false;

        int listenfd = CreateSocket();
        if (listenfd < 0)
            return false;

        int mr = MakeSocketNonBlock(listenfd);
        if (mr < 0)
            return false;

        int lr = Listen(listenfd);
        if (lr < 0)
            return false;

        std::cout << "EpollTcpServer Init success!" << std::endl;

        handle_ = listenfd;

        int er = UpdateEpollEvents(efd_, EPOLL_CTL_ADD, handle_, EPOLLIN | EPOLLET);

        if (er < 0)
        {
            close(handle_);
            return false;
        }


        th_loop_ = std::make_shared<std::thread>(&EpollTcpServer::EpollLoop, this);
        if (!th_loop_)
        {
            return false;
        }

        th_loop_->detach();

        return true;
    }

    bool EpollTcpServer::Stop()
    {
        loop_flag_ = false;
        close(handle_);
        close(efd_);
        std::cout << "stop epoll !" << std::endl;
        UnRegisterOnRecvCallback();

        return true;
    }

    // TD

} // end transport
} // end rtmpserver