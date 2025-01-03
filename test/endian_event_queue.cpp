#include "endian_event_queue.h"

#include <stdio.h>
#include <stdlib.h>

EndianEventQueue::EndianEventQueue() {
    _cache = (ReactorEventItem **)malloc(sizeof(void *) * ENDIAN_CACHE_SIZE);
    if ( !_cache ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error malloc."
        );
        exit ( -1 );
    }

    _w_r_index.store(0);
    _flag_nr.store( false );

    ReactorEventItem *tail = cache_out_1w();
    if ( !tail ) {
         printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error cache_out."
        );
        exit ( -1 );
    }
    _head.store( tail );
    _tail.store( tail );
}

int EndianEventQueue::push_1wnr(const ReactorEvent &re) {
    ReactorEventItem *rei = cache_out_1w();
    if ( !rei ) {
        return -1;
    }
    rei->_next.store((ReactorEventItem *)0);

    ReactorEventItem *tail = _tail.load();
    if ( !tail ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "null tail"
        );
        return -1;
    }

    tail->_re = re;
    tail->_next.store(rei);

    _tail.store(rei);

    return 0;
}

int EndianEventQueue::pop_1wnr( ReactorEvent &re ) {
    while ( "zhe er..." ) {
        ReactorEventItem *head = _head.load();
        if ( !head ) {
            return 0;
        }
        ReactorEventItem *next = head->_next.load();
        if ( !next ) {
            return 0;
        }
        ReactorEventItem *tail = _tail.load();
        if ( !tail ) {
            return 0;
        }
      
        if ( head == tail ) {
            return 0;
        } 

        re = head->_re;

        if ( !_head.compare_exchange_weak(
            head, next
        ) ) {
            continue;
        }

        cache_in_nr( head );

        return 1;
    }
 
    return 0;
}

void EndianEventQueue::cache_in_nr(ReactorEventItem *rei) {
    bool f = false;
    bool t = true;
    unsigned int idx, ridx, widx, nwidx, nidx;
    while ( "you dian fei ..." ) {
        idx = _w_r_index.load();

        ridx = idx & 0xFFFF;
        widx = (idx >> 16) & 0xFFFF;
        nwidx = ((widx + 1) & 0xFFFF) & (ENDIAN_CACHE_SIZE - 1);

        if ( ridx == nwidx ) {
            delete rei;
            return ;
        }

        nidx = ((nwidx << 16) | ridx);

        if ( !_flag_nr.compare_exchange_weak(f, t)  ) {
            continue;
        }
        _w_r_index.store( nidx );
        _cache[widx] = rei;

        _flag_nr.store( false );

        break;
    }

    return ;
}

ReactorEventItem *EndianEventQueue::cache_out_1w() {
    ReactorEventItem *rei;
    unsigned int idx, ridx, widx, nridx, nidx;
    while ( "you dian fei ..." ) {
        idx = _w_r_index.load();
        ridx = idx & 0xFFFF;
        widx = (idx >> 16) & 0xFFFF;

        if ( ridx == widx ) {
            rei = new ReactorEventItem();
            if ( !rei ) {
                printf("%s %s %d %s\n",
                    __FILE__, __func__, __LINE__,
                    "error new."
                );
                return 0;
            }
            return rei;
        }

        rei = _cache[ridx];

        nridx = ((ridx + 1) & 0xFFFF) & (ENDIAN_CACHE_SIZE - 1);
        nidx = ((widx << 16) | nridx);
        if ( !_w_r_index.compare_exchange_weak(
            idx, nidx
        )) {
            continue;
        }

        break;
    }

    return rei;
}
