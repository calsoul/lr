#ifndef _REACTOR_H__
#define _REACTOR_H__

#include "reactor_event_queue.h"

#include <atomic>
#include <set>

#define WAIT_INTERVAL_MS 10

//#define SOCKET_LIMIT (1024 * 20)

class Endian;
class Line;
class Socket;
class Reactor {
public:
    enum {
        RNULL   = 0,
        EPOLL   = 1,
        IOCP    = 2,
        KQUEUE  = 3,
        POLL    = 4,
        SELECT  = 5
    };
public:
    Reactor() {
        _stop_flag = false;
        _name = Reactor::RNULL;
        _line = 0;
    }

    virtual ~Reactor() {}

    virtual int init() { return 0; }
    virtual int start() { return 0; }
    virtual void stop() { };

    virtual int add_socket(Socket *s, unsigned int ev) { return 0; }
    virtual int del_socket(Socket *s) { return 0; }

public:
    bool _stop_flag;

public:
    int _name;

public:
    Line *_line;

    //Socket *_main_socket;
    std::set<Socket *> _sockets;

    //std::atomic<bool> _flag_sockets;

public:
    ReactorEventQueue _r_w_event_queue;
};

#endif //_REACTOR_H__

