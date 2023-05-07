cmake_minimum_required(VERSION 3.0.0)
project(rtmpServer VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavdevice
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)


add_subdirectory(utils)

add_executable(rtmpServer main.cpp)

target_link_libraries(${PROJECT_NAME}
    PkgConfig::LIBAV
)
target_link_libraries(rtmpServer utils)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
