set(
    RTMP_SOURCES
    rtmp_server.h
    rtmp_server.cc
)

add_library(rtmp STATIC ${RTMP_SOURCES})