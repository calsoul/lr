#include "endian.h"

#include <functional>
#include <chrono>

#include "handler.h"
#include "line_configure.h"
#include "reactor.h"
#include "tcp_socket.h"
#include "thread_manager.h"

Endian::Endian() {
    _stop_flag = false;
    _side = ENDIAN_NULL;
    _i_main_socket = 0;
}

int Endian::init(int side) {
    _side = side;

    int ret;
    if ( _side == ENDIAN_LEFT ) {
        ret = l_main_socket_init();
    } else if ( _side == ENDIAN_RIGHT ) {
        ret = r_main_socket_init();
    } else {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "unknow endian side."
        );
        return -1;
    }
    return ret;
}

int Endian::l_main_socket_init() {
    AddrInfo ai = CONFIGURE.get_left_addr_info();

    switch (ai._protocol) {
    case AddrInfo::PRO_TCP: {
        _i_main_socket =  new TcpSocket();
printf("main_socket: %p\n", _i_main_socket);
    } break;

    case AddrInfo::PRO_UDP: {
       ; //_i_main_socket = new UdpSocket();
    } break;

    default: {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "unknown ai._protocol"
        );

        return -1;
    }}

    if ( !_i_main_socket ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "null _main_socket"
        );
        return -1;
    }

    _i_main_socket->_endian = this;

    if ( _i_main_socket->init(&ai) < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "_main_socket.init"
        );
        return -1;
    }

    if ( _i_main_socket->bind() < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "_main_socket.bind"
        );
        return -1;
    }

    return 0;
}

int Endian::r_main_socket_init() {
    AddrInfo ai = CONFIGURE.get_right_addr_info();

    switch (ai._protocol) {
    case AddrInfo::PRO_TCP: {
        _i_main_socket =  new TcpSocket();
printf("main_socket: %p\n", _i_main_socket);
    } break;

    case AddrInfo::PRO_UDP: {
       ; //_i_main_socket = new UdpSocket();
    } break;

    default: {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "unknown ai._protocol"
        );

        return -1;
    }}

    if ( !_i_main_socket ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "null _main_socket"
        );
        return -1;
    }

    _i_main_socket->_addr = ai;

    _i_main_socket->_endian = this;

    return 0;
}

void Endian::_proc() {
    ReactorEvent re;
    bool fre = false;
    while ( !_stop_flag ) {
        {
            //std::unique_lock<std::mutex> l(_mutex_event_queue);
            //_cv_event_queue.wait(l, [this, &re, &fre] {
std::this_thread::sleep_for(
    std::chrono::milliseconds(10)
);
                fre = _event_queue.pop_1wnr(re);
            //    return fre;
            //});

            if ( !fre ) {
                continue;
            }
        }

//printf("%s %s %d %d %d\n",
//    __FILE__, __func__, __LINE__,
//    re._sock->_fd, re._event
//);
        switch ( re._event ) {
        //case EV_ACCEPT:
        //  endian_accept(re._sock);
        //break;
        case EV_READ: {
            if ( re._sock == _i_main_socket ) {
                endian_accept(re._sock);
            } else {
                endian_recv(re._sock);
            }
        } break;

        case EV_WRITE: {
            endian_write(re._sock);
        } break;

        case EV_EXCEPT: {
            endian_except(re._sock);
        } break;

        case EV_CLOSE:
        default: {
            endian_close(re._sock);
        } }
    }
}

int Endian::l_start() {
    int tn = CONFIGURE.get_left_thread_number();
    if ( tn < 1 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "thread number error."
        );
        return -1;
    }

    for (int i = 0; i < tn; ++i) {
        RUN_PROC( this );
    }

    if ( _i_main_socket->listen() < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "_main_socket-listen."
        );
        return -1;
    }

    return 0;
}

int Endian::r_start() {
    int tn = CONFIGURE.get_right_thread_number();
    if ( tn < 1 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "thread number error."
        );
        return -1;
    }

    for (int i = 0; i < tn; ++i) {
        RUN_PROC( this );
    }
    return 0;
}

int Endian::start() {
    if ( _side == ENDIAN_LEFT ) {
        return l_start();
    }
    if ( _side == ENDIAN_RIGHT ) {
        return r_start();
    }
    return -1;
}

int Endian::fire() {
    return _reactor->add_socket(_i_main_socket, EV_ACCEPT);
}

int Endian::stop() {
    //{
    //std::unique_lock<std::mutex> l(_mutex_event_queue);
        _stop_flag = true;
    //}
    //_cv_event_queue.notify_all();
    return 0;
}

void Endian::push_event(const ReactorEvent &re) {
//printf("%s %s %d %d %d\n",
//    __FILE__, __func__, __LINE__,
//    re._sock->_fd, re._event
//);
    if ( _event_queue.push_1wnr(re) < 0 ) {
        printf("%s %s %d %d %d\n",
            __FILE__, __func__, __LINE__,
            re._sock->_fd, re._event
        );
    }
    //_cv_event_queue.notify_one();
}

void Endian::endian_accept(Socket *s) {
//printf("%s %s %d %d\n",
//    __FILE__, __func__, __LINE__,
//    s->_fd
//);

    Socket * sock = s->accept();
    if ( !sock ) {
        printf("%s %d %s %s",
            __FILE__, __LINE__, __func__,
            "accept error.\n"
        );
        return ;
    }

    sock->nonblock( true );

    if ( _handler->handle(ReactorEvent(sock, EV_ACCEPT)) < 0 ) {
        sock->close();
        delete sock;

        return ;
    }

    _reactor->add_socket(sock, EV_READ_ADD);
    return;
}

void Endian::endian_recv(Socket *s) {
//printf("%s %s %d %d\n",
//    __FILE__, __func__, __LINE__,
//    s->_fd
//);
    int ret = s->recv();
    if ( ret < 0 ) {
        _reactor->add_socket(s, EV_CLOSE);
        return;
    }

    ret = _handler->handle(ReactorEvent(s, EV_READ));
    if ( ret < 0 ) {
        _reactor->add_socket(s, EV_CLOSE);
        return;
    }

    _reactor->add_socket(s, EV_READ);
}

void Endian::endian_write(Socket *s) {
//printf("%s %s %d %d\n",
//    __FILE__, __func__, __LINE__,
//    s->_fd
//);

    int flag = 0;
    if ( !(s->_flag_w_buffer.compare_exchange_weak(
        flag, 1
    ) ) ) {
        return ;
    }
    if ( s->size_w() < 1 ) {
        s->_flag_w_buffer.store( 0 );
        return ;
    }

    int ret = s->send();
    if ( ret < 0 ) {
        printf("%s %d %s %s",
           __FILE__, __LINE__, __func__,
           "write\n"
        );
        //s->_flag_w_buffer.store( 0 );
        // to delete socket, no langer releasing permition
        // and 

        _reactor->add_socket(s, EV_CLOSE);
        return;
    }

    s->_flag_w_buffer.store( 0 );

    if ( !(s->empty_w()) ) {
        _reactor->add_socket(s, EV_WRITE);
    }

    return ;
}

void Endian::endian_close(Socket *s) {
//printf("%s %s %d\n", __FILE__, __func__, __LINE__);

    _handler->handle(ReactorEvent(s, EV_CLOSE));
    s->close();
    delete s;
}

void Endian::endian_except(Socket *s) {
//printf("%s %s %d\n", __FILE__, __func__, __LINE__);
    _reactor->add_socket(s, EV_CLOSE);
}

