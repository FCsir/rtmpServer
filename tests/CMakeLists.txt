set(
    TESTS_SOURCES
    echo_server.cc
)

add_library(tests STATIC ${TESTS_SOURCES})