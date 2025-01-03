#include "socket_buffer.h"

#include <string.h>

#include "bi_cache_pool.h"

SocketBuffer::SocketBuffer() {
    BufferItem *tbi = new BufferItem(true);
    if ( !tbi ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "new BufferItem(true);"
        );
    }
    _head.store(tbi);
    _tail.store(tbi);
}

SocketBuffer::~SocketBuffer() {
    clear();
    BufferItem *bi = _tail.load();
    if ( bi ) {
        delete bi;
    }
}

void SocketBuffer::clear() {
    while ( "hello ..." ) {
        BufferItem *ptail = _tail.load();
        BufferItem *phead = _head.load();

        if ( phead == ptail ) {
            return ;
        }
        _head.store(phead->_next.load());

        BI_CACHE_POOL.put(phead);
    }
}

int SocketBuffer::size() {
    int size = 0;
    BufferItem *phead = _head.load();
    BufferItem *ptail;
    while ( "xiang shui ne..." ) {
        ptail = _tail.load();
        if ( phead == ptail ) {
            break;
        }

        size += phead->size();
        phead = phead->_next.load();
    }
    return size;
}

BufferItem *SocketBuffer::front() {
    BufferItem *phead = _head.load();
    BufferItem *ptail = _tail.load();
    if ( phead == ptail ) {
        return 0;
    }
    return phead;
}

int SocketBuffer::read_front(char *dst, int len) {
    int rlen = 0;
    BufferItem *phead = _head.load();
    BufferItem *ptail;
    while ( rlen < len ) {
        ptail = _tail.load();
        if ( phead == ptail ) {
            return rlen;
        }
        rlen += phead->read(dst + rlen, len - rlen);
        phead = phead->_next.load();
    }
    return rlen;
}

int SocketBuffer::pop_front(char *dst, int len) {
    int rlen = 0;
    BufferItem *ptail = _tail.load();
    BufferItem *phead = _head.load();

    while ( rlen < len ) {
        if ( phead == ptail ) {
            break;
        }

        if ( dst ) {
            rlen += phead->remove(dst + rlen, len - rlen);
        } else {
            rlen += phead->remove(0, len - rlen);
        }

        if ( phead->size() > 0 ) {
            break;
        }
     
        BufferItem *pnext = phead->_next.load(); 

        _head.store(pnext);

        BI_CACHE_POOL.put( phead );

        phead = pnext;
    }
    return rlen;
}

BufferItem *SocketBuffer::pop_front() {
    BufferItem *phead = _head.load();
    BufferItem *ptail = _tail.load();
    if ( phead == ptail ) {
        return 0;
    }

    _head.store(phead->_next.load());

    return phead;
}

int SocketBuffer::push_front(BufferItem *bi) {
    if ( !bi || bi->size() < 1 ) {
        return 0;
    }

    int plen = bi->size();
    bi->_next.store(
        _head.load()
    );

    _head.store(bi);

    return plen;
}

int SocketBuffer::push_front(char *src, int len) {
    if ( !src || len < 1 ) {
        return 0;
    }

    int plen = 0;
    while ( plen < len ) {
        BufferItem *bi = BI_CACHE_POOL.get();
        if ( !bi ) {
            return plen;
        }
        bi->clear();

        plen += bi->write(src + plen, len - plen);
        push_front(bi);
    }

    return plen;
}

int SocketBuffer::push_back(BufferItem *bi) {
    if ( !bi || (bi->size() < 1) ) {
        return 0;
    }
    bi->_next.store( (BufferItem *)0 );
    int plen = bi->size();

    BufferItem * ptail = _tail.load();
    ptail->_next.store(bi);
    ptail->swap(bi);

    _tail.store( bi );
   
    return plen;
}

int SocketBuffer::push_back(char *src, int len) {
    if ( !src || len < 1 ) {
        return 0;
    }

    int plen = 0;
    while ( plen < len ) {
        BufferItem *t = BI_CACHE_POOL.get();
        if ( !t ) {
            return plen;
        }
        t->clear();

        plen += t->write(src + plen, len - plen);
        push_back(t);
    }
    return plen;
}

