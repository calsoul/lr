#include <stdio.h>

#include <string.h>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <iostream>

#include "buffer_item.h"
#include "socket_buffer.h"
#include "bi_cache_pool.h"
#include "line_configure.h"

#include "tcp_socket.h"
#include "thread_manager.h"

void proc_send(void *v) {
    TcpSocket *s = (TcpSocket *)v;
    int count = 0;
    char word[32] = {0};
    while ( "proc_send" ) {
        ++count;
        memset(word, 0x0, sizeof(word));
        sprintf(word, "%07d", count);
        s->push_w(word, 7);
std::this_thread::sleep_for(
    std::chrono::seconds(1)
);
        int ret = s->send();
        if ( ret < 0 ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "socket stop."
            );
            s->close();

            break;
        }
    }
}

void proc_recv(void *v) {
    Socket *s = (Socket *)v;
    char word[32] = {0};
    while ( "proc_recv" ) {
std::this_thread::sleep_for(
    std::chrono::milliseconds(30)
);
        int ret = s->recv();
        if ( ret < 0 ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "socket stop."
            );
            s->close();

            break;
        }

        if ( ret < 1 ) {
            continue;
        }
        memset(word, 0x0, sizeof(word));
        ret = s->move_r(word, sizeof(word));
        printf("recv: %s\n",
            word
        );
    }
}

void proc(void *v) {
    TcpSocket *s = (TcpSocket *)v;
    while ( "send & recv" ) {
        printf("press to stat a conver...\n");
        int dc;
        std::cin >> dc;

        proc_send(v);
//std::this_thread::sleep_for(std::chrono::seconds(10));

        proc_recv(v);

    }
        delete s;
}

int main(const int argc, const char **argv) {
    if ( CONFIGURE.load_line_conf("line.conf") < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__, "CONFIGURE.load_line_conf"
        );
        return -1;
    }
    AddrInfo ai = CONFIGURE.get_right_addr_info();

printf("server addr: %s:%d\n", ai._ip.c_str(), ai._port);

    TcpSocket ts;

    if ( ts.init(&ai) < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "TcpSocket init."
        );
        return -1;
    }

    if ( ts.connect() < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "TcpSocket bind."
        );
        return -1;
    }

    if ( ts.nonblock( true ) < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "TcpSocket nonblock."
        );
        return -1;
    }


    RUN_TASK(std::function<void(void *)>(
        std::bind(&proc_recv, std::placeholders::_1)
    ), (void *)&ts);

    RUN_TASK(std::function<void(void *)>(
        std::bind(&proc_send, std::placeholders::_1)
    ), (void *)&ts);

    //RUN_TASK(std::function<void(void *)>(
    //    std::bind(&proc, std::placeholders::_1)
    //), (void *)&ts);



    THREAD_MANAGER.join();

    printf("%s %s %d %s\n",
        __FILE__, __func__, __LINE__,
        "TcpSocket stop."
    );

    return 0;
}
