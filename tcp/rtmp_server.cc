#include <iostream>
#include <ctime>
#include <random>
#include <string>
#include <unistd.h>

#include "rtmp_server.h"
#include "tcp_epoll_server.h"

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
    }

    void RTMPServer::Start()
    {
        
        auto recv_call = [&](const PacketPtr &data) -> void
        {
            std::cout << "receive tcp apcket"
                      << std::endl;
            recvTcpPacket_(data);
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

    void RTMPServer::recvTcpPacket_(const PacketPtr &data)
    {
        auto origin_msg = data->msg;
        RTMPPacketPtr rtmp_data = std::make_shared<RTMPPacket>();
        rtmp_data->tcp_packet_ptr = data;
        // C1
        if (origin_msg.size() == 1537)
        {
            if (origin_msg[0] != version_)
            {
                std::cout << "client version no match server client"
                          << std::endl;
                return;
            }
            rtmp_data->is_c0c1 = true;
            // packet the orign msg
            sendMsg_(rtmp_data);

        } else if (origin_msg.size() == 1536){
            // send c2
            rtmp_data->is_c2 = true;
        } else {
            // parse normal msg
            std::cout << "receive normal msg" << origin_msg
                        << std::endl;
            // TD window acknowledgement size
            // TD set peer bandwidth
            // TD set chunk size
        }

    }

    void RTMPServer::sendMsg_(RTMPPacketPtr &data)
    {
        if (data->is_c0c1) {
            // send s0 s1 s2
            std::string s0 = randomS0S1S2String_(1);
            std::string s1 = randomS0S1S2String_(2);
            std::string s2 = randomS0S1S2String_(3);
            std::string msg = { version_ };
            const char *timestamp = "00000000";
            msg.append(timestamp);
            msg.append(s0);
            std::cout << "msg: " << msg << std::endl;

            msg.append(timestamp);
            msg.append(s1);
            std::cout << "msg2: " << s1 << std::endl;

            msg.append(timestamp);
            msg.append(s2);
            std::cout << "msg3: " << s2 << std::endl;

            std::cout << "rtmp send data: " << msg.size() << std::endl;
            tcp_server_->SendData(
                std::make_shared<Packet>(data->tcp_packet_ptr->fd, msg));
        } else if (data->is_c2) {

        } else {

        }

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

        std::cout << "tmp s : " << tmp_s.c_str() << std::endl;

        return tmp_s;
    }

} // end namespace transport
} // end namespace rtmpserver