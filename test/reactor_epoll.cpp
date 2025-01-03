#include "reactor_epoll.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <unistd.h>

#include <functional>

#include "line.h"
#include "socket.h"
#include "thread_manager.h"

ReactorEpoll::ReactorEpoll() {
    _r_epoll_fd = 0;
    _w_epoll_fd = 0;
    _r_w_wait_interval = WAIT_INTERVAL_MS / 2;
}

ReactorEpoll::~ReactorEpoll() {
    if ( _r_epoll_fd > 0 ) {
        close(_r_epoll_fd);
    }

    if ( _w_epoll_fd > 0 ) {
        close(_w_epoll_fd);
    }

    if ( !_r_w_events ) {
        delete[] _r_w_events;
    }
}

int ReactorEpoll::init() {
    _r_epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    _w_epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    if (
        (_r_epoll_fd < 0) ||
        (_w_epoll_fd < 0)
    ) {
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            "error epoll_create."
        );

        close( _r_epoll_fd );
        _r_epoll_fd = 0;

        close( _w_epoll_fd );
        _w_epoll_fd = 0;

        return -1;
    }

    _r_w_events = new struct epoll_event[EPOLL_WAIT_EVENTS];
    if ( !_r_w_events ) {
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            "error new struct epoll_event"
        );

        delete[] _r_w_events;
        _r_w_events = 0;

        return -1;
    }
    return 0;
}

int ReactorEpoll::start() {
    RUN_PROC( this );
    return 0;
}

int ReactorEpoll::add_socket(Socket *s, unsigned int ev) {
//printf("%s %s %d, %d, %d\n",
//    __FILE__, __func__, __LINE__,
//    s->_fd, ev
//);

    _r_w_event_queue.push_nw1r(
        ReactorEvent(s, ev)
    );

    return 0;
}

int ReactorEpoll::del_socket(Socket *s) {
//printf("%s %s %d, %d, %d\n",
//    __FILE__, __func__, __LINE__,
//    s->_fd, EV_CLOSE
//);
    _r_w_event_queue.push_nw1r(ReactorEvent(s, EV_CLOSE));

    return 0;

}

void ReactorEpoll::_proc() {
    while ( !_stop_flag ) {
        if ( r_proc() < 0 ) {
            break;
        }
        if ( w_proc() < 0 ) {
            break;
        }

        update_r_w_fds();
    }

    printf("%s %s %d %s\n",
        __FILE__, __func__, __LINE__,
        "engine stop."
    );
}

int ReactorEpoll::r_proc() {
//printf("%s %s %d %s\n",
//    __FILE__, __func__, __LINE__
//    "reactor start."
//);
    Socket *sock;

    int ret = epoll_wait(         \
        _r_epoll_fd, _r_w_events, \
        EPOLL_WAIT_EVENTS,        \
        _r_w_wait_interval        \
    );

    if ( ret < 0 ) {
        if ( ret == EINTR ) {
            printf("%s %d %s %s [%d]\n",
                __FILE__, __LINE__, __func__,
                strerror(errno), ret
            );
            return 0;
        }
  
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            strerror(errno)
        );
        return -1;
    }
  
    for ( int i = 0; i < ret; ++i ) {
        sock = (Socket *)(_r_w_events[i].data.ptr);
        if ( _r_w_events[i].events & EPOLLIN ) {
            _line->process(ReactorEvent(
                sock, EV_READ
            ));
        } else {
            _line->process(ReactorEvent(
                sock, EV_EXCEPT
            ));
        }
    }
    return 0;
}

int ReactorEpoll::w_proc() {
//printf("%s %s %d %s\n",
//    __FILE__, __func__, __LINE__,
//    "reactor start."
//);
    Socket *sock;

    int ret = epoll_wait(         \
        _w_epoll_fd, _r_w_events, \
        EPOLL_WAIT_EVENTS,        \
        _r_w_wait_interval        \
    );

    if ( ret < 0 ) {
        if ( ret == EINTR ) {
            printf("%s %d %s %s [%d]\n",
                __FILE__, __LINE__, __func__,
                strerror(errno), ret
            );
            return 0;
        }
  
        printf("%s %d %s %s\n",
            __FILE__, __LINE__, __func__,
            strerror(errno)
        );
        return -1;
    }
  
    for ( int i = 0; i < ret; ++i ) {
        sock = (Socket *)(_r_w_events[i].data.ptr);
        if ( _r_w_events[i].events & EPOLLOUT ) {
            _line->process(ReactorEvent(
                sock, EV_WRITE
            ));
        } else {
            _line->process(ReactorEvent(
                sock, EV_EXCEPT
            ));
        }
    }

    return 0;
}

void ReactorEpoll::update_r_w_fds() {
    struct epoll_event ev;
    ReactorEvent re;
    int ret;
    while ( "hello world !" ) {
        if ( _r_w_event_queue.pop_nw1r(re) < 1 ) {
            break;
        }

//printf("%s %s %d, %d %d\n", 
//    __FILE__, __func__, __LINE__,
//    re._sock->_fd, re._event
//);
        memset(&ev, 0x0, sizeof(ev));
        ev.data.ptr = (void *)(re._sock);
        if ( re._event & EV_ACCEPT ) {
            ev.events = EPOLLET | EPOLLIN;
            epoll_ctl(                     \
                _r_epoll_fd, EPOLL_CTL_ADD,\
                re._sock->_fd, &ev         \
            );

            continue;
        }

        if ( re._event == EV_READ_ADD ) {
            ev.events = EPOLLET | EPOLLIN | EPOLLONESHOT;
            epoll_ctl(                     \
                _r_epoll_fd, EPOLL_CTL_ADD,\
                re._sock->_fd, &ev         \
            );

            _sockets.insert(re._sock);

            continue;
        }


        if ( re._event & EV_CLOSE ) {
            epoll_ctl(                     \
                _r_epoll_fd, EPOLL_CTL_DEL,\
                re._sock->_fd, &ev         \
            );
            epoll_ctl(                     \
                _w_epoll_fd, EPOLL_CTL_DEL,\
                re._sock->_fd, &ev         \
            );

            _sockets.erase(re._sock);

            _line->process(ReactorEvent(
                re._sock, EV_CLOSE
            ));
            continue;
        }

        if ( _sockets.find(re._sock) == _sockets.end() ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "focket closed."
            );
            continue;
        }

        if ( re._event & EV_READ ) {
            ev.events = EPOLLET | EPOLLONESHOT | EPOLLIN;
            ret = epoll_ctl(       \
                _r_epoll_fd,           \
                EPOLL_CTL_MOD,         \
                re._sock->_fd, &ev     \
            );
            if ( ret < 0 ) {
                ret = epoll_ctl(       \
                    _r_epoll_fd,       \
                    EPOLL_CTL_ADD,     \
                    re._sock->_fd, &ev \
                );
            }

        }

        if ( re._event & EV_WRITE ) {
            ev.events = EPOLLET | EPOLLONESHOT | EPOLLOUT;
            ret = epoll_ctl(   \
                _w_epoll_fd,       \
                EPOLL_CTL_MOD,     \
                re._sock->_fd, &ev \
            );
            if ( ret < 0 ) {
                ret = epoll_ctl(       \
                    _w_epoll_fd,       \
                    EPOLL_CTL_ADD,     \
                    re._sock->_fd, &ev \
                );
            }

        }

        if (ret < 0) {
            printf("%s %d %s %s\n",
                __FILE__, __LINE__, __func__,
                strerror(errno)
            );
        }
    }
}

void ReactorEpoll::stop() {
    _stop_flag = true;
}

