#ifndef RTMPSERVER_TCP_SOCKET
#define RTMPSERVER_TCP_SOCKET

#include <string>
#include <arpa/inet.h>
#include <memory>
#include <functional>
#include <thread>

namespace rtmpserver
{
namespace transport
{

    static const int kEpollWaitTime = 10;
    static const int kMaxEvents = 100;

    // send/recv packet of msg
    typedef struct  Packet
    {
    public:
        std::string msg;
        int fd{-1};

        Packet()
            : msg {""}
        {}
        Packet(const std::string& msg)
            : msg{msg}
        {}

        Packet(int fd, const std::string& msg)
            : fd{fd}, msg{msg}
        {}

    } Packet;

    typedef std::shared_ptr<Packet> PacketPtr;

    using callback_recv_t = std::function<void(const PacketPtr &data)>;

    class EpollTcpBase {
    public:
        EpollTcpBase() = default;
        EpollTcpBase(const EpollTcpBase &) = delete;
        EpollTcpBase &operator=(const EpollTcpBase &) = delete;
        EpollTcpBase(EpollTcpBase &&) = delete;
        EpollTcpBase &operator=(EpollTcpBase &&) = delete;
        virtual ~EpollTcpBase() = default;

        virtual bool Start() = 0;
        virtual bool Stop() = 0;
        virtual int32_t SendData(const PacketPtr &data) = 0;
        virtual void RegisterOnRecvCallback(callback_recv_t callback) = 0;
        virtual void UnRegisterOnRecvCallback() = 0;
    };

    typedef std::shared_ptr<EpollTcpBase> EpollTcpBasePtr;

    class EpollTcpServer : public EpollTcpBase {
    public:
        EpollTcpServer()                                       = default;
        EpollTcpServer(const EpollTcpServer& other)            = delete;
        EpollTcpServer& operator=(const EpollTcpServer& other) = delete;
        EpollTcpServer(EpollTcpServer&& other)                 = delete;
        EpollTcpServer& operator=(EpollTcpServer&& other)      = delete;
        ~EpollTcpServer() override;

        EpollTcpServer(const std::string &local_ip, uint16_t local_port);

        bool Start() override;
        bool Stop() override;
        int32_t SendData(const PacketPtr &data) override;
        void RegisterOnRecvCallback(callback_recv_t callback) override;
        void UnRegisterOnRecvCallback() override;
    
    protected:
        int32_t CreateEpoll();
        int32_t CreateSocket();
        int32_t MakeSocketNonBlock(int32_t fd);
        int32_t Listen(int32_t listenfd);
        int32_t UpdateEpollEvents(int efd, int op, int fd, int events);

        void OnSocketAccept();
        void OnSocketRead(int32_t fd);
        void OnSocketWrite(int32_t fd);
        void EpollLoop();

    private:
        std::string local_ip_;
        uint16_t local_port_{0};
        int32_t handle_{-1};
        int32_t efd_ { -1 }; // epoll fd
        std::shared_ptr<std::thread> th_loop_ { nullptr };
        bool loop_flag_ { true };
        callback_recv_t recv_callback_ { nullptr };

    };

} // end transport
} // end rtmpserver namesapce

#endif
