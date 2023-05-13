cmake_minimum_required(VERSION 3.0.0)
project(rtmpServer VERSION 0.1.0)

include(CTest)
enable_testing()

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

add_executable(rtmpServer main.cpp)

target_link_libraries(${PROJECT_NAME}
    PkgConfig::LIBAV
)
target_link_libraries(
    rtmpServer
    ${CMAKE_THREAD_LIBS_INIT}
    utils
    tcp
)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
