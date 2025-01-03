#ifndef _REACTOR_EPOLL_H__
#define _REACTOR_EPOLL_H__

#include "reactor.h"

#define EPOLL_WAIT_EVENTS 32

struct epoll_event;
class Socket;
class ReactorEpoll: public Reactor {
public:
    ReactorEpoll();
    virtual ~ReactorEpoll();

public:
    void _proc_reactor();
    int r_proc();
    int w_proc();

public:
    virtual int init();
    virtual int start();
    virtual void stop();

    virtual int add_socket(Socket *s, unsigned int ev);
    virtual int del_socket(Socket *s);
public:
    int _r_epoll_fd;
    int _w_epoll_fd;
    struct epoll_event* _r_w_events;
    //struct epoll_event* _w_events;
    int _r_w_wait_interval;
    //int _w_wait_interval;

private:
    void update_r_w_fds();
    //void update_w_fds();
};

#endif//_REACTOR_EPOLL_H__
