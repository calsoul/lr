#include "bi_cache_pool.h"

#include <stdlib.h>

BICachePool BI_CACHE_POOL;

BICachePool::BICachePool() {
    _cache = (BufferItem **)malloc(
        sizeof(void *) * BI_CACHE_POOL_SIZE
    );

    if ( !_cache ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
           "error malloc"
        );
        exit( -1 );
    }

    _w_r_index.store(0);
}
 

BufferItem *BICachePool::get() {
    BufferItem *bi = NULL;
    unsigned int idx, ridx, nridx, widx, nidx;
    while ( "you dian fei ..." ) {
        idx = _w_r_index.load();

        ridx = idx & 0xFFFF;
        nridx = (ridx + 1) & 0xFFFF;
        widx  = ((idx >> 16) & 0xFFFF);
        if ( ridx == widx ) {
            bi = new BufferItem();
            if ( bi ) {
                return bi;
            }

            printf("%s %s %d %s\n",
               __FILE__, __func__, __LINE__,
               "error new"
            );

            return 0;
        }

        nidx = ((widx << 16) | nridx);
        if ( !_w_r_index.compare_exchange_weak(
            idx, nidx
        )) {
            continue;
        }
        bi = _cache[ridx & (BI_CACHE_POOL_SIZE - 1)];

        break;
    }

    if ( !(bi->_data) ) {
        delete bi;
        return 0;
    }

    return bi;

    //BufferItem *bi = NULL;
    //{
    //    std::unique_lock<std::mutex> l(_mutex_r_index);

    //    if ( _r_index == _w_index ) {
    //        bi = new BufferItem();
    //        if ( bi ) {
    //            return bi;
    //        }

    //        printf("%s %s %d %s\n",
    //           __FILE__, __func__, __LINE__,
    //           "error new"
    //        );

    //        return 0;
    //    }

    //    bi = _cache[_r_index];
    //    _r_index = (_r_index + 1) & (BI_CACHE_POOL_SIZE - 1);
    //}

    //if ( !(bi->_data) ) {
    //    delete bi;
    //    return 0;
    //}

    //return bi;
}

void BICachePool::put(BufferItem *bi) {
    unsigned int idx, ridx, widx, nwidx, nidx;
    while ( "you dian fei ..." ) {
        idx = _w_r_index.load();

        ridx   = idx & 0xFFFF;
        widx   = (idx >> 16) & 0xFFFF;
        nwidx  = (widx + 1) & 0xFFFF;

        if ( ridx == nwidx ) {
            delete bi;
            return ;
        }

        nidx = ((nwidx << 16) | ridx);
        if ( !_w_r_index.compare_exchange_weak(
            idx, nidx
        )) {
            continue;
        }

        _cache[(widx & (BI_CACHE_POOL_SIZE - 1))] = bi;

        break;
    }
}

