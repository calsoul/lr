cmake_minimum_required(VERSION 3.0)

project(XUNTA)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

find_package(Threads REQUIRED)

add_compile_options(-std=c++11 -g -Wall -O0)

#include_directories(${PROJECT_SOURCE_DIR}/lr)

set(TEST_LINE_EPOLL_SRC
    ${PROJECT_SOURCE_DIR}/lr/plt/net-inc.h
    ${PROJECT_SOURCE_DIR}/lr/plt/net-src.cpp
    ${PROJECT_SOURCE_DIR}/lr/buffer_item.h
    ${PROJECT_SOURCE_DIR}/lr/socket_buffer.h
    ${PROJECT_SOURCE_DIR}/lr/socket_buffer.cpp
    ${PROJECT_SOURCE_DIR}/lr/lr_socket.h
    ${PROJECT_SOURCE_DIR}/lr/lr_socket.cpp
    ${PROJECT_SOURCE_DIR}/lr/tcp_socket.h
    ${PROJECT_SOURCE_DIR}/lr/tcp_socket.cpp
    ${PROJECT_SOURCE_DIR}/lr/bi_cache_pool.h
    ${PROJECT_SOURCE_DIR}/lr/bi_cache_pool.cpp
    ${PROJECT_SOURCE_DIR}/lr/line_configure.h
    ${PROJECT_SOURCE_DIR}/lr/line_configure.cpp
    ${PROJECT_SOURCE_DIR}/lr/thread_manager.h
    ${PROJECT_SOURCE_DIR}/lr/thread_manager.cpp
    ${PROJECT_SOURCE_DIR}/lr/reactor.h
    ${PROJECT_SOURCE_DIR}/lr/reactor_epoll.h
    ${PROJECT_SOURCE_DIR}/lr/reactor_epoll.cpp
    ${PROJECT_SOURCE_DIR}/lr/reactor_event.h
    ${PROJECT_SOURCE_DIR}/lr/reactor_event_queue.h
    ${PROJECT_SOURCE_DIR}/lr/reactor_event_queue.cpp
    ${PROJECT_SOURCE_DIR}/lr/endian_event_queue.h
    ${PROJECT_SOURCE_DIR}/lr/endian_event_queue.cpp
    ${PROJECT_SOURCE_DIR}/lr/endian.h
    ${PROJECT_SOURCE_DIR}/lr/endian.cpp
    ${PROJECT_SOURCE_DIR}/lr/line.h
    ${PROJECT_SOURCE_DIR}/lr/line.cpp
    ${PROJECT_SOURCE_DIR}/lr/handler.h
    ${PROJECT_SOURCE_DIR}/lr/handler.cpp
    ${PROJECT_SOURCE_DIR}/lr/timer.h
    ${PROJECT_SOURCE_DIR}/lr/timer.cpp

    ${PROJECT_SOURCE_DIR}/test_line_epoll.cpp
)

add_executable(XUNTA ${TEST_LINE_EPOLL_SRC})
target_link_libraries(XUNTA PUBLIC Threads::Threads)
