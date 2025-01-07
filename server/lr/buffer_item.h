#ifndef _BUFFER_ITEM_H__
#define _BUFFER_ITEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <atomic>

#define BUFFER_ITEM_SIZE (1024)

class BufferItem {
public:
    BufferItem(bool tflag = false): _data(0), 
                                    _beg(0),
                                    _end(0),
                                    _tail(0) {

        _next.store( (BufferItem *)0);

        if ( tflag ) {
            // tail flag;
            return ;
        }
        _data = (char *)::malloc(BUFFER_ITEM_SIZE);
        if ( !_data ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "error malloc"
            );
        }
        _beg = _data;
        _end = _data;

        _tail = _data + BUFFER_ITEM_SIZE;
    }

    ~BufferItem() {
        if ( _data ) {
            ::free(_data);
        }
    }

    void clear() {
        _beg = _data;
        _end = _data;
        _next.store((BufferItem *)0);
    }

    int space()  { return _tail - _end; }
    int size()   { return _end  - _beg; }
    int length() { return _end  - _data; }
    //int seek(int offset) {
       //_offset = (_offset + offset + BUFFER_ITEM_SIZE) & (BUFFER_ITEM_SIZE - 1);
       //return _offset;
    //}

    int read(char *dst, int len) {
        int i = 0;
        while ( (i < len) && (_beg + i < _end) ) {
            *(dst + i) = *(_beg + i);
            ++i;
        }
        return i;
    }

    int remove(char *dst, int len) {
        int i = 0;
        if ( dst ) {
            while ( (i < len) && (_beg + i < _end) ) {
                *(dst + i) = *(_beg + i);
                ++i;
            }
        } else {
            i = len;
            if ( _end - _beg < len ) {
                i = _end - _beg;
            }
        }

        _beg += i;
        return i;
    }

    int write(char *src, int len) {
        int i = 0;
        while ( (i < len) && (_end + i < _tail) ) {
            *(_end + i)= *(src + i);
            ++i;
        }

        _end += i;

        return i;
    }

    void swap(BufferItem *bi) {
        char *tmp = _data;
        _data = bi->_data;
        bi->_data = tmp;

        tmp  = _beg;
        _beg  = bi->_beg;
        bi->_beg  = tmp;

        tmp  = _end;
        _end  = bi->_end;
        bi->_end  = tmp;

        tmp = _tail;
        _tail = bi->_tail;
        bi->_tail = tmp;
    }

public:
    char *_data;

    char *_beg;

    char *_end;

    char *_tail;

public:
    std::atomic<BufferItem *> _next;
};

#endif//_BUFFER_ITEM_H__

