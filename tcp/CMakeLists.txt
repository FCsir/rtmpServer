set(
    TCP_SOURCES
    tcp_epoll_server.h
    tcp_epoll_server.cc
)

add_library(tcp STATIC ${TCP_SOURCES})