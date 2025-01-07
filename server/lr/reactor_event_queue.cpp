#include "reactor_event_queue.h"

#include <stdio.h>
#include <stdlib.h>

ReactorEventQueue::ReactorEventQueue() {
    _cache = (ReactorEventItem **)malloc(sizeof(void *) * CACHE_SIZE);
    if ( !_cache ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error malloc."
        );
        exit ( -1 );
    }

    _w_r_index.store(0);

    _head.store( (ReactorEventItem *)0 );
    _tail.store( (ReactorEventItem *)0 );
}

int ReactorEventQueue::push_nw1r(const ReactorEvent &re) {
    ReactorEventItem *rei = cache_out_nw();
    if ( !rei ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__, "error cache_out"
        );
        return -1;
    }

    rei->_re = re;

    while ( "not bad" ) {
        ReactorEventItem *phead = _head.load();
        rei->_next.store( phead );
        if (!(_head.compare_exchange_weak(
            phead, rei
        ))) {
            continue;
        }

        break;
    }

    return 1;
}

int ReactorEventQueue::pop_nw1r( ReactorEvent &re ) {
    while ( "zhe er..." ) {
        ReactorEventItem *tail = _tail.load();
        if ( !tail ) {
            break;
        }

        re = tail->_re;

        _tail.store(tail->_next.load());

        cache_in_1r( tail );

        return 1;
    }

    while ( "na er..." ) {
        ReactorEventItem *head = _head.load();
        if ( !head ) {
            return 0;
        }
        if ( !_head.compare_exchange_weak(
            head, (ReactorEventItem *)0
        ) ) {
            continue;
        }
        _tail.store(head);
        continue;
    }

    return 0;
}

void ReactorEventQueue::cache_in_1r(ReactorEventItem *rei) {
    unsigned int idx, ridx, widx, nwidx, nidx;
    while ( "you dian fei ..." ) {
        idx = _w_r_index.load();

        ridx = idx & 0xFFFF;
        widx = (idx >> 16) & 0xFFFF;
        nwidx = ((widx + 1) & 0xFFFF) & (CACHE_SIZE - 1);
        if ( ridx == nwidx ) {
            delete rei;
            return ;
        }

        _cache[widx] = rei;

        nidx = ((nwidx << 16) | ridx);
        if ( !_w_r_index.compare_exchange_weak(
            idx, nidx
        )) {
            continue;
        }

        break;
    }

    return ;
}

ReactorEventItem *ReactorEventQueue::cache_out_nw() {
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

        nridx = ((ridx + 1) & 0xFFFF) & (CACHE_SIZE - 1);
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
