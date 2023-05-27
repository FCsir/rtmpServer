cmake_minimum_required(VERSION 3.0.0)
project(rtmpServer VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(PkgConfig REQUIRED)
find_package( Threads REQUIRED )
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

message(${CMAKE_THREAD_LIBS_INIT} "found")

add_subdirectory(utils)
add_subdirectory(tcp)
add_subdirectory(rtmp)
add_subdirectory(tests)

add_executable(rtmpServer main.cpp)

target_link_libraries(${PROJECT_NAME}
    PkgConfig::LIBAV
)
target_link_libraries(
    rtmpServer
    ${CMAKE_THREAD_LIBS_INIT}
    utils
    tcp
    rtmp
    tests
)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
