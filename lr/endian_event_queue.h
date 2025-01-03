#ifndef _ENDIAN_EVENT_QUEUE_H__
#define _ENDIAN_EVENT_QUEUE_H__

#include "reactor_event.h"

//should be 2 ^n
#define ENDIAN_CACHE_SIZE 8

class EndianEventQueue {
public:
    EndianEventQueue();

    int push_1wnr(const ReactorEvent &re);
    int pop_1wnr( ReactorEvent &re );
private:
    //ReactorEventItem *_head;
    //ReactorEventItem *_tail;

    std::atomic<ReactorEventItem *> _head;

    //hahahahahahahaha you yi si.

    std::atomic<ReactorEventItem *> _tail;

    //std::mutex _mutex_events;
    //std::condition_variable _cv_events;

private:
    void cache_in_nr(ReactorEventItem *re);
    ReactorEventItem *cache_out_1w();

    ReactorEventItem **_cache;
    std::atomic<unsigned int> _w_r_index;
    std::atomic<bool> _flag_nr;

    //ReactorEventItem *_cache_head;
    //unsigned int _cache_r_index;
    //ReactorEventItem *_cache_tail;
    //unsigned int _cache_w_index;
    //int _cache_size;
};


#endif //_ENDIAN_EVENT_QUEUE_H__

