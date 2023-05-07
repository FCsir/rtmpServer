#ifndef RTMPSERVER_EXCEPTIONS_SOCKET_EXCEPTION
#define RTMPSERVER_EXCEPTIONS_SOCKET_EXCEPTION

#include "exception"

class SocketInitException : public std::exception
{
    const char* what() const throw()
    {
        return "init the socket error";
    }
};

class SocketBindException : public std::exception
{

    const char* what() const throw()
    {
        return "bind the socket error";
    }
};


class SocketAcceptException : public std::exception
{

    const char* what() const throw()
    {
        return "accept the socket error";
    }
};

#endif