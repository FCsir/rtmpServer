set(
    TCP_SOURCES
    rtmp_server.h
    rtmp_server.cc
    tcp_epoll_server.h
    tcp_epoll_server.cc
)

add_library(tcp STATIC ${TCP_SOURCES})