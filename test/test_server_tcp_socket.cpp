
#include <stdio.h>
#include <string.h>

#include <chrono>
#include <condition_variable>
#include <mutex>

#include "buffer_item.h"
#include "socket_buffer.h"
#include "bi_cache_pool.h"
#include "line_configure.h"

#include <time.h>

#include "tcp_socket.h"
#include "thread_manager.h"

//std::mutex _mutex_send;
//std::condition_variable _cv_send;

void proc_recv(void *v) {
    TcpSocket *s = (TcpSocket *)v;

    //struct timespec ts;
    //ts.tv_nsec = 0.5 * 1000 * 1000 * 1000;
    int ret;
    //int ret = nanosleep(&ts);
    while ( "recv" ) {
printf("pre s->recv [%d]\n", s->size_r());
//std::this_thread::sleep_for(std::chrono::seconds(1));
        ret = s->recv();
printf("aft s->recv [%d], [%d]\n", ret, s->size_r());
        if ( ret < 0 ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "socket stop."
            );
            s->close();
//            delete s;

            return ;
        }

        if ( ret == 0 ) {
            s->close();
//            delete s;
            continue;
        }
//printf("notify send.\n");
//_cv_send.notify_one();
      //break;
    }

        //if recv == 0, then we read again.
        // until an error.

        //char data[64] = { 0 } ;
        //while ( (ret = s->move_r(data, 63)) > 0 ) {
        //    printf("recv: %s",
        //        data
        //    );
        //    s->push_w(data, ret);
        //    memset(data, 0x0, sizeof(data));
        //}
        //printf("\n");

        //while ( "send" ) {
        //    ret = s->send();
        //    if ( ret < 0 ) {
        //        printf("%s %s %d %s\n",
        //            __FILE__, __func__, __LINE__,
        //            "socket stop."
        //        );
        //        s->close();
        //        delete s;

        //        return ;
        //    }

           //if ( ret == 0 ) {
            //   continue;
          // }
        //   break;
        //}
    //}
}


void proc_send(void *v) {
//printf("%s %s %d\n", __FILE__, __func__, __LINE__);
    static int count = 0;
    char word[8];
    TcpSocket *s = (TcpSocket *)v;
//printf("wait for notify.\n");
//printf("send notified.\n");

    //struct timespec ts;
    //ts.tv_nsec = 0.5 * 1000 * 1000 * 1000;
    int ret;
    //while ( "proc_rs" ) {
        //int ret = nanosleep(&ts);
        //while ( "recv" ) {
        //    ret = s->recv();
        //    if ( ret < 0 ) {
        //        printf("%s %s %d %s\n",
        //            __FILE__, __func__, __LINE__,
        //            "socket stop."
        //        );
        //        s->close();
        //        delete s;

        //        return ;
        //    }

        //    if ( ret == 0 ) {
        //        continue;
        //    }

        //    break;
        //}
        //if recv == 0, then we read again.
        // until an error.
        //char data[64] = { 0 } ;
        //while ( (ret = s->move_r(data, 63)) > 0 ) {
        //    printf("recv: %s",
        //        data
        //    );
        //    s->push_w(data, ret);
        //    memset(data, 0x0, sizeof(data));
        //}
        //printf("\n");

    while ( "send" ) {

//std::unique_lock<std::mutex> l(_mutex_send);
//_cv_send.wait(l);
        memset(word, 0x0, sizeof(word));
        sprintf(word, "%03d", count);
        s->push_w(word, 3);

printf("pre s->send [%d]\n", s->size_w());
//std::this_thread::sleep_for(std::chrono::seconds(1));
        ret = s->send();
printf("aft s->send [%d], [%d]\n", ret, s->size_w());
        if ( ret < 0 ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "socket stop."
            );
            s->close();
  //          delete s;

            return ;
        }

        //if ( ret == 0 ) {
   //         s->close();
 //           delete s;
        //    continue;
        //}
            continue;
   }
    //}
}

void proc(void *v) {
    while ( " recv and send " ) {
        proc_recv(v);

std::this_thread::sleep_for(std::chrono::seconds(1));
       proc_send(v);

    }
      delete (TcpSocket *)v; 
}

int main(const int argc, const char **argv) {
    if ( CONFIGURE.load_line_conf("line.conf") < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__, "CONFIGURE.load_line_conf"
        );
        return -1;
    }
    AddrInfo ai = CONFIGURE.get_left_addr_info();

printf("ip: %s:%d", ai._ip.c_str(), ai._port);

    TcpSocket ts;

    if ( ts.init(&ai) < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "TcpSocket init."
        );
        return -1;
    }

    if ( ts.bind() < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "TcpSocket bind."
        );
        return -1;
    }


    if ( ts.listen() < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "TcpSocket listen."
        );
        return -1;
    }

printf("server listen on %s:%d\n", ai._ip.c_str(), ai._port);
    while ( "hello world !" ) {

        Socket *s = ts.accept();
        if ( !s ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "TcpSocket stop."
            );
            continue;
        }

        //if ( s->nonblock( true ) < 0 ) {
        //    printf("%s %s %d %s\n",
        //        __FILE__, __func__, __LINE__,
        //        "nonblock error."
        //    );
        //    delete s;
        //    continue;
        //}

        RUN_TASK(std::function<void(void *)>(
            std::bind(&proc_recv, std::placeholders::_1)
        ), (void *)s);

        RUN_TASK(std::function<void(void *)>(
            std::bind(&proc_send, std::placeholders::_1)
        ), (void *)s);
    }

    THREAD_MANAGER.join();

    printf("%s %s %d %s\n",
        __FILE__, __func__, __LINE__,
        "TcpSocket stop."
    );

    return 0;
}
