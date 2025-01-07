#include "line.h"

#include "endian.h"
#include "handler.h"
#include "reactor.h"
#include "reactor_event.h"
#include "reactor_epoll.h"
#include "lr_socket.h"
#include "line_configure.h"
#include "thread_manager.h"

Handler _default_handler;

Line::Line(): _i_reactor(NULL),
              _stop_flag( false ) {

}

Line::~Line() {
    if ( _i_reactor ) {
        delete _i_reactor;
    }
}

void Line::set_lr_handlers(Handler *lh, Handler *rh) {
    _l_endian._handler = lh;
    if ( !lh ) {
        _l_endian._handler = &_default_handler;
    }

    _r_endian._handler = rh;
    if ( !rh ) {
        _r_endian._handler = &_default_handler;
    }

    lh->_line = this;
    rh->_line = this;
}

int Line::init(const char *fcfgpath) {
    if ( CONFIGURE.load_line_conf(fcfgpath) < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "CONFIGURE.load_line_conf."
        );
        return -1;
    }

    int reactor = CONFIGURE.get_reactor();
    switch ( reactor ) {
    case Reactor::IOCP:
        //_reactor = new ReactorIOCP();
    break;

    case Reactor::SELECT:
        //_reactor = new ReactorSelect();
    break;

    case Reactor::POLL:
        //_reactor = new ReactorPoll();
    break;

    case Reactor::KQUEUE:
        //_reactor = new ReactorKqueue();
    break;

    case Reactor::EPOLL:
        _i_reactor = new ReactorEpoll();
    break;

    default: {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "unknown reactor."
        );
        return -1;
    } }

    if ( !_i_reactor ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "unknown reactor null."
        );
        return -1;
    }

    if ( _i_reactor->init() < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error _i_reactor init."
        );
        return -1;
    }

    _l_endian._reactor = _i_reactor;
    _r_endian._reactor = _i_reactor;

    if ( _l_endian.init(ENDIAN_LEFT) < 0 ) {
        printf("%s %d %s %s\n", 
            __FILE__, __LINE__, __func__,
            "left endian init error."
        );
        return -1;
    }

    if ( _r_endian.init(ENDIAN_RIGHT) < 0 ) {
        printf("%s %d %s %s\n", 
            __FILE__, __LINE__, __func__,
            "right endian init error."
        );
        return -1;
    }

    _i_reactor->_line     = this;

    return 0;
}

int Line::start() {
    if ( _l_endian.start() < 0 ) {
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            "left endian stat error."
        );
        return -1;
    }

    if ( _r_endian.start() < 0 ) {
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            "right endian stat error."
        );
        return -1;
    }

    if ( CONFIGURE.timer_enable() ) {
        if ( _timer.start() < 0 ) {
            printf("%s %d %s %s",
                __FILE__, __LINE__, __func__,
                "timer start error.\n"
            );
            return -1;
        }
    }

    if ( _i_reactor->start() < 0 ) {
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            "reactor start error."
        );
        return -1;
    }

    if ( _l_endian.fire() < 0 ) {
        printf("%s %s %d\n",
            __FILE__, __func__, __LINE__
        );
        return -1;
    }

    return 0;
}

int Line::wait() {
    THREAD_MANAGER.join();

    printf("%s %d %s %s",
        __FILE__, __LINE__, __func__,
        "line stop.\n"
    );
    return 0;
}

void Line::process(const ReactorEvent &re) {
//printf("%s %s %d %d %d\n",
//    __FILE__, __func__, __LINE__,
//    re._sock->_fd, re._event
//);
    re._sock->_endian->push_event(re);
}

void Line::stop() {
    _i_reactor->stop();
    _timer.stop();

    _l_endian.stop();
    _r_endian.stop();
}
