cmake_minimum_required(VERSION 3.0)

project(Test)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

set(SRC ${PROJECT_SOURCE_DIR}/timer.h
        ${PROJECT_SOURCE_DIR}/timer.cpp

        ${PROJECT_SOURCE_DIR}/addr_info.h
        ${PROJECT_SOURCE_DIR}/thread_manager.h
        ${PROJECT_SOURCE_DIR}/thread_manager.cpp
        ${PROJECT_SOURCE_DIR}/line_configure.h
        ${PROJECT_SOURCE_DIR}/line_configure.cpp

        ${PROJECT_SOURCE_DIR}/test_timer.cpp
)


add_compile_options(-mcx16 -std=c++11 -g -Wall -O0)

find_package(Threads REQUIRED)
add_executable(TestTimer ${SRC})
target_link_libraries(TestTimer PUBLIC Threads::Threads)


set(CONFIGURE_SRC
    ${PROJECT_SOURCE_DIR}/addr_info.h
    ${PROJECT_SOURCE_DIR}/line_configure.h
    ${PROJECT_SOURCE_DIR}/line_configure.cpp

    ${PROJECT_SOURCE_DIR}/test_line_configure.cpp
)
add_executable(TestLineConfigure ${CONFIGURE_SRC})


set(CACHE_POOL_SRC
    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.h
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.cpp

    ${PROJECT_SOURCE_DIR}/test_cache_pool.cpp

)
add_executable(TestCachePool ${CACHE_POOL_SRC})
target_link_libraries(TestCachePool PUBLIC Threads::Threads)

set(TEST_BUFFER_ITEM_SRC
    ${PROJECT_SOURCE_DIR}/buffer_item.h
    ${PROJECT_SOURCE_DIR}/test_buffer_item.cpp
)
add_executable(TestBufferItem ${TEST_BUFFER_ITEM_SRC})


set(SOCKET_BUFFER_SRC
    ${PROJECT_SOURCE_DIR}/buffer_item.h
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.h
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.cpp
    ${PROJECT_SOURCE_DIR}/socket_buffer.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.cpp
    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp

    ${PROJECT_SOURCE_DIR}/test_socket_buffer.cpp

)
add_executable(TestSocketBuffer ${SOCKET_BUFFER_SRC})

set(REACTOR_EVENT_QUEUE_SRC
    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp
    ${PROJECT_SOURCE_DIR}/reactor_event.h
    ${PROJECT_SOURCE_DIR}/reactor_event_queue.h
    ${PROJECT_SOURCE_DIR}/reactor_event_queue.cpp
    ${PROJECT_SOURCE_DIR}/endian_event_queue.h
    ${PROJECT_SOURCE_DIR}/endian_event_queue.cpp

    ${PROJECT_SOURCE_DIR}/test_reactor_event_queue.cpp
)
add_executable(TestReactorEventQueue ${REACTOR_EVENT_QUEUE_SRC})
target_link_libraries(TestReactorEventQueue PUBLIC Threads::Threads)

set(TEST_ENDIAN_EVENT_QUEUE_SRC
    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp
    ${PROJECT_SOURCE_DIR}/reactor_event.h
    ${PROJECT_SOURCE_DIR}/reactor_event_queue.h
    ${PROJECT_SOURCE_DIR}/reactor_event_queue.cpp
    ${PROJECT_SOURCE_DIR}/endian_event_queue.h
    ${PROJECT_SOURCE_DIR}/endian_event_queue.cpp

    ${PROJECT_SOURCE_DIR}/test_endian_event_queue.cpp
)
add_executable(TestEndianEventQueue ${TEST_ENDIAN_EVENT_QUEUE_SRC})
target_link_libraries(TestEndianEventQueue PUBLIC Threads::Threads)


set(TCP_SOCKET_SRC_SERVER_SRC
    ${PROJECT_SOURCE_DIR}/plt/net-inc.h
    ${PROJECT_SOURCE_DIR}/plt/net-src.cpp
    
    ${PROJECT_SOURCE_DIR}/buffer_item.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.cpp
    ${PROJECT_SOURCE_DIR}/socket.h
    ${PROJECT_SOURCE_DIR}/socket.cpp
    ${PROJECT_SOURCE_DIR}/tcp_socket.h
    ${PROJECT_SOURCE_DIR}/tcp_socket.cpp
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.h
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.cpp
    ${PROJECT_SOURCE_DIR}/line_configure.h
    ${PROJECT_SOURCE_DIR}/line_configure.cpp

    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp

    ${PROJECT_SOURCE_DIR}/test_server_tcp_socket.cpp

)
add_executable(TestTcpSocketServer ${TCP_SOCKET_SRC_SERVER_SRC})
target_link_libraries(TestTcpSocketServer PUBLIC Threads::Threads)

set(TCP_SOCKET_SRC_CLIENT_SRC
    ${PROJECT_SOURCE_DIR}/plt/net-inc.h
    ${PROJECT_SOURCE_DIR}/plt/net-src.cpp
    
    ${PROJECT_SOURCE_DIR}/buffer_item.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.cpp
    ${PROJECT_SOURCE_DIR}/socket.h
    ${PROJECT_SOURCE_DIR}/socket.cpp
    ${PROJECT_SOURCE_DIR}/tcp_socket.h
    ${PROJECT_SOURCE_DIR}/tcp_socket.cpp
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.h
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.cpp
    ${PROJECT_SOURCE_DIR}/line_configure.h
    ${PROJECT_SOURCE_DIR}/line_configure.cpp

    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp

    ${PROJECT_SOURCE_DIR}/test_client_tcp_socket.cpp

)
add_executable(TestTcpSocketClient ${TCP_SOCKET_SRC_CLIENT_SRC})
target_link_libraries(TestTcpSocketClient PUBLIC Threads::Threads)

set(TEST_LINE_EPOLL_SRC
    ${PROJECT_SOURCE_DIR}/plt/net-inc.h
    ${PROJECT_SOURCE_DIR}/plt/net-src.cpp
    
    ${PROJECT_SOURCE_DIR}/buffer_item.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.h
    ${PROJECT_SOURCE_DIR}/socket_buffer.cpp
    ${PROJECT_SOURCE_DIR}/socket.h
    ${PROJECT_SOURCE_DIR}/socket.cpp
    ${PROJECT_SOURCE_DIR}/tcp_socket.h
    ${PROJECT_SOURCE_DIR}/tcp_socket.cpp
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.h
    ${PROJECT_SOURCE_DIR}/bi_cache_pool.cpp
    ${PROJECT_SOURCE_DIR}/line_configure.h
    ${PROJECT_SOURCE_DIR}/line_configure.cpp

    ${PROJECT_SOURCE_DIR}/thread_manager.h
    ${PROJECT_SOURCE_DIR}/thread_manager.cpp

    
    ${PROJECT_SOURCE_DIR}/reactor.h
    ${PROJECT_SOURCE_DIR}/reactor_epoll.h
    ${PROJECT_SOURCE_DIR}/reactor_epoll.cpp
    ${PROJECT_SOURCE_DIR}/reactor_event.h
    ${PROJECT_SOURCE_DIR}/reactor_event_queue.h
    ${PROJECT_SOURCE_DIR}/reactor_event_queue.cpp
    ${PROJECT_SOURCE_DIR}/endian_event_queue.h
    ${PROJECT_SOURCE_DIR}/endian_event_queue.cpp

    ${PROJECT_SOURCE_DIR}/endian.h
    ${PROJECT_SOURCE_DIR}/endian.cpp

    ${PROJECT_SOURCE_DIR}/line.h
    ${PROJECT_SOURCE_DIR}/line.cpp
    ${PROJECT_SOURCE_DIR}/handler.h
    ${PROJECT_SOURCE_DIR}/handler.cpp

    
    ${PROJECT_SOURCE_DIR}/timer.h
    ${PROJECT_SOURCE_DIR}/timer.cpp

    ${PROJECT_SOURCE_DIR}/test_line_epoll.cpp
)

add_executable(TestLineEpoll ${TEST_LINE_EPOLL_SRC})
target_link_libraries(TestLineEpoll PUBLIC Threads::Threads)

