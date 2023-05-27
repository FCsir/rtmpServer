#ifndef RTMPSERVER_RTMP_CONNECTION_MANAGER
#define RTMPSERVER_RTMP_CONNECTION_MANAGER

#include <string>

class RtmpConnectionManager
{

public:
    RtmpConnectionManager();

    void handshake();
    void removeConnection(int fd);

private:

};

#endif