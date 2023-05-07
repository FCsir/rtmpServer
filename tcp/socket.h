#ifndef RTMPSERVER_TCP_SOCKET
#define RTMPSERVER_TCP_SOCKET

#include <string>
#include <arpa/inet.h>

class Socket
{
public:
    Socket(int domain, int protocol, int port);

    void handleMsg();

    void acceptSocket();
    void sendMsg();
    void recvMsg();
    void shutdownSocket();
    void closeSocket();

    ~Socket();

private:
    int _port;
    int _protocol;
    int _domain;
    int _socketfd;
    int _listen_backlog_queue = 5;

    struct sockaddr_in _serv_addr;
};

#endif