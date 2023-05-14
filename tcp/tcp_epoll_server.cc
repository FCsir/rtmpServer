#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <fcntl.h>

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/epoll.h>

#include "tcp_epoll_server.h"


namespace rtmpserver
{
namespace transport
{
    EpollTcpServer::EpollTcpServer(const std::string &local_ip, uint16_t local_port)
        : local_ip_{local_ip}, local_port_{local_port}
    {}

    EpollTcpServer::~EpollTcpServer()
    {
        Stop();
    }

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
        std::cout << "EpollTcpServer start success!" << std::endl;

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

    int32_t EpollTcpServer::CreateEpoll()
    {
        int epollfd = epoll_create(1);
        if(epollfd < 0)
        {
            std::cout << "epoll create failed!" << std::endl;
            return -1;
        }

        efd_ = epollfd;
        return efd_;
    }

    int32_t EpollTcpServer::CreateSocket()
    {
        int listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if (listenfd <  0)
        {
            std::cout << "create socket " << local_ip_ << ":"
                      << local_port_ << " failed!"
                      << std::endl;
            return -1;
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(local_port_);
        addr.sin_addr.s_addr = inet_addr(local_ip_.c_str());

        int r = bind(listenfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
        if (r != 0)
        {
            std::cout << "bind socket " << local_ip_ << ":"
                      << local_port_ << " failed!"
                      << std::endl;
            close(listenfd);
            return -1;
        }


        std::cout << "create and bind socket " << local_ip_ << ":"
                    << local_port_ << " success"
                    << std::endl;

        return listenfd;
    }

    int32_t EpollTcpServer::MakeSocketNonBlock(int32_t fd)
    {
        int flags = fcntl(fd, F_GETFL, 0);
        if (flags < 0)
        {
            std::cout << "fcntl failed!"
                      << std::endl;
            return -1;
        }

        int r = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
        if (r < 0)
        {
            std::cout << "fcntl failed!"
                      << std::endl;
            return -1;
        }

        return 0;
    }

    int32_t EpollTcpServer::Listen(int32_t listenfd)
    {
        int r = listen(listenfd, SOMAXCONN);
        if (r < 0)
        {
            std::cout << "listen failed !"
                      << std::endl;
            return -1;
        }

        return 0;
    }

    int32_t EpollTcpServer::UpdateEpollEvents(int efd, int op, int fd, int events)
    {
        struct epoll_event ev;
        memset(&ev, 0, sizeof(ev));
        ev.events = events;
        ev.data.fd = fd;
        int r = epoll_ctl(efd, op, fd, &ev);
        if (r < 0)
        {
            std::cout << "epoll_ctl  failed!"
                      << std::endl;
            return -1;
        }

        return 0;
    }

    void EpollTcpServer::OnSocketAccept()
    {
        while (true)
        {
            struct sockaddr_in in_addr;
            socklen_t in_len = sizeof(in_addr);

            int cli_fd = accept(handle_, (struct sockaddr *)&in_addr, &in_len);
            if (cli_fd == -1)
            {
                if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                {
                    std::cout << "accept all coming connections!" << std::endl;
                    break;
                } else {
                    std::cout << "accept error!" << std::endl;
                    continue;
                }
            }

            sockaddr_in peer;
            socklen_t p_len = sizeof(peer);
            int r = getpeername(cli_fd, (struct sockaddr *)&peer, &p_len);
            if (r < 0)
            {
                std::cout << "getpeername error!" << std::endl;
                continue;
            }

            std::cout << "accpet connection from " << inet_ntoa(in_addr.sin_addr) << std::endl;
            int mr = MakeSocketNonBlock(cli_fd);
            if (mr < 0)
            {
                close(cli_fd);
                continue;
            }

            int er = UpdateEpollEvents(efd_, EPOLL_CTL_ADD, cli_fd, EPOLLIN | EPOLLRDHUP | EPOLLET);
            if (er < 0)
            {
                close(cli_fd);
                continue;
            }
        }
    }


    void EpollTcpServer::RegisterOnRecvCallback(callback_recv_t callback)
    {
        std::cout << "register callback" 
                  << std::endl;
        recv_callback_ = callback;
    }

    void EpollTcpServer::UnRegisterOnRecvCallback()
    {
        recv_callback_ = nullptr;
    }

    void EpollTcpServer::OnSocketRead(int32_t fd)
    {
        char read_buf[4096];
        bzero(read_buf, sizeof(read_buf));
        int n = -1;

        while (( n = read(fd, read_buf, sizeof(read_buf))) > 0)
        {
            std::cout << "fd: " << fd << " recv: " << (read_buf[0] == 0x03) << std::endl;
            std::string msg(read_buf, n);
            PacketPtr data = std::make_shared<Packet>(fd, msg);
            if (recv_callback_)
            {
                recv_callback_(data);
            }
        }

        if (n == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                // read all data finished
                return;
            }
            // something goes wrong for this fd, should close it
            close(fd);

            return;
        }

        if (n == 0)
        {
            close(fd);
            return;
        }
    }

    void EpollTcpServer::OnSocketWrite(int32_t fd)
    {
        std::cout << "fd: " << fd << " writeable!" << std::endl;
    }

    int32_t EpollTcpServer::SendData(const PacketPtr& data)
    {
        if (data->fd == -1)
        {
            return -1;
        }

        std::cout << "data msg: " << data->msg.size() << std::endl;
        int r = write(data->fd, data->msg.data(), data->msg.size());
        if (r == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                return -1;
            }
            // error happend
            close(data->fd);
            std::cout << "fd: " << data->fd << " write error, close it!" << std::endl;
            return -1;
        }
        std::cout << "fd: " << data->fd << " write size: " << r << " ok!" << std::endl;
        return r;
    }

    void EpollTcpServer::EpollLoop()
    {
        struct epoll_event *alive_events = static_cast<epoll_event*>(calloc(kMaxEvents, sizeof(epoll_event)));
        while (loop_flag_)
        {
            int num = epoll_wait(efd_, alive_events, kMaxEvents, kEpollWaitTime);
            for (int i = 0; i < num; i++)
            {
                int fd = alive_events[i].data.fd;
                int events = alive_events[i].events;

                if(((events & EPOLLERR) || (events & EPOLLHUP) ))
                {
                    std::cout << "epoll_wait error!" << std::endl;
                    close(fd);
                } else if (events & EPOLLRDHUP)
                {
                    std::cout << "fd:" << fd << " closed EPOLLRDHUP!" << std::endl;
                    close(fd);
                } else if (events & EPOLLIN )
                {
                    std::cout << "epollin" << std::endl;
                    if (fd == handle_)
                    {
                        OnSocketAccept();
                    }else {
                        OnSocketRead(fd);
                    }
                } else if (events & EPOLLOUT)
                {
                    std::cout << "epollout" << std::endl;
                    OnSocketWrite(fd);
                } else {
                    std::cout << "unknow epoll event!" << std::endl;
                }
            }
        }

        free(alive_events);
    }

} // end transport
} // end rtmpserver