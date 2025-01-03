#ifndef _EVENT_REACTOR_H__
#define _EVENT_REACTOR_H__

#include <atomic>

enum {
    EV_NULL      = 0x00,
    EV_ACCEPT    = 0x01,
    EV_READ      = 0x02,
    EV_READ_ADD  = 0x12,
    EV_WRITE     = 0x04,
    EV_EXCEPT    = 0x08,
    EV_CLOSE     = 0x10,
};

class Socket;
class ReactorEvent {
public:
  ReactorEvent():_sock(0), _event(EV_NULL){}
  ReactorEvent(Socket *s, unsigned int ev):_sock(s),_event(ev){}

public:
  Socket *_sock;
  unsigned int _event;
};

class ReactorEventItem {
public:
    ReactorEventItem() {
        _next.store((ReactorEventItem *)0);
    }
    //ReactorEventItem *_next;

    ReactorEvent _re;

    std::atomic<ReactorEventItem *> _next;
};


#endif//_EVENT_REACTOR_H__
