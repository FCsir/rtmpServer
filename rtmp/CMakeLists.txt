set(
    RTMP_SOURCES
    rtmp_server.h
    rtmp_server.cc

    c0s0.h
    c0s0.cc
    c1s1.h
    c1s1.cc
    c2s2.h
    c2s2.cc
)

add_library(rtmp STATIC ${RTMP_SOURCES})