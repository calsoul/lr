#ifndef _SOCKET_H__
#define _SOCKET_H__

//#include <mutex>
#include <atomic>

#include "addr_info.h"
#include "socket_buffer.h"

enum _SSTATUS {
    STATUS_NULL,
    STATUS_INIT,
    STATUS_ACTIVE,
    STATUS_CLOSE,
};

class Endian;
class Reactor;
class Socket {
public:
    Socket();

    virtual ~Socket();

    virtual int init(AddrInfo *addr) { return 0; }
    virtual int bind() { return 0; }
    virtual Socket *accept() { return 0; }
    virtual int connect() { return 0; }
    virtual int listen() { return 0; }
    virtual int recv() { return 0; }
    virtual int send() { return 0; }
    virtual int close() { return 0; }

public:
    int empty_w() { return (_w_buffer.front() == 0)? 1: 0; }
    int empty_r() { return (_r_buffer.front() == 0)? 1: 0; }

    int size_r() { return _r_buffer.size(); }
    int size_w() { return _w_buffer.size(); }
public:
    int push_w(char *buf, int len);
    int push_w(BufferItem *bi);

    void clear_w();
    void clear_r();
protected:
    int push_r(char *buf, int len);

public:
    int read_r(char *dst, int len);
    int move_r(char *dst, int len);
    BufferItem *move_r();
protected:
    int read_w(char *dst, int len);
    int move_w(char *dst, int len);
    BufferItem *move_w();


public:
    //int events()             { return _events.load(); }
    //void set_event(int ev)   { _events.store( ev );   }
    //void clear_events()      { _events.store( 0 );    }
    //void add_event(int ev)   { _events |= (ev); }
    //void clear_event(int ev) { _events &= (~ev);      }

    int nonblock(bool);
    int reuseaddr(bool);

public:
    int _type;
    int _fd;
    AddrInfo _addr;

    int _status;
    //std::atomic<int> _events;

    SocketBuffer _r_buffer;

    SocketBuffer _w_buffer;
    //std::mutex _mutex_w_buffer;
    std::atomic<int> _flag_w_buffer;

    //std::mutex _mutex_r_buffer; //could not be used ,
public:
    Endian *_endian;
};

#endif//_SOCKET_H__
