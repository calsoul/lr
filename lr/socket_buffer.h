#ifndef _SOCKET_BUFFER_H__
#define _SOCKET_BUFFER_H__

#include "buffer_item.h"

#define SOCKET_BUFFER_ITEM_NUMBER 1024

class SocketBuffer {
public:
    SocketBuffer();

    ~SocketBuffer();

public:

    void clear();
    int size();
    BufferItem *front();
    int read_front(char *dst, int len);
    int pop_front(char *dst, int len);
    BufferItem *pop_front();

    int push_front(BufferItem * bi);
    int push_front(char *src, int len);

public:
    int push_back(char *src, int len);
    int push_back(BufferItem *bi);

private:

    std::atomic<BufferItem *> _head;
    std::atomic<BufferItem *> _tail;
};

#endif//_SOCKET_BUFFER_H__
