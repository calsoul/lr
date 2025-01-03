#ifndef _REACTOR_EVENT_QUEUE_H__
#define _REACTOR_EVENT_QUEUE_H__

#include <atomic>

#include "reactor_event.h"

//should be 2 ^n
#define CACHE_SIZE 8

class ReactorEventQueue {
public:
    ReactorEventQueue();

    int push_nw1r(const ReactorEvent &re);
    int pop_nw1r( ReactorEvent &re );
private:
    //ReactorEventItem *_head;
    //ReactorEventItem *_tail;

    std::atomic<ReactorEventItem *> _head;

    //hahahahahahahaha you yi si.

    std::atomic<ReactorEventItem *> _tail;

private:
    void cache_in_1r(ReactorEventItem *re);
    ReactorEventItem *cache_out_nw();

    ReactorEventItem **_cache;
    std::atomic<unsigned int> _w_r_index;

    //ReactorEventItem *_cache_head;
    //unsigned int _cache_r_index;
    //ReactorEventItem *_cache_tail;
    //unsigned int _cache_w_index;
    //int _cache_size;
};

#endif//_REACTOR_EVENT_QUEUE_H__
