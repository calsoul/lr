#ifndef _ENDIAN_H__
#define _ENDIAN_H__

#include <condition_variable>
#include <mutex>

#include "socket.h"
#include "reactor_event.h"
#include "endian_event_queue.h"

enum {
    ENDIAN_NULL,
    ENDIAN_LEFT,
    ENDIAN_RIGHT,
};

class Handler;
class Reactor;
class Line;
class Endian {
public:
    Endian();
    virtual ~Endian() { }
  
    int init(int side);
  
    int start();
  
    void _proc();
  
    int fire();

    int stop();
  
    void endian_accept(Socket *s);
    void endian_recv(Socket *s);
    void endian_write(Socket *s);
    void endian_close(Socket *s);
    void endian_except(Socket *s);

private:
    int l_main_socket_init();
    int r_main_socket_init();

    int l_start();
    int r_start();

public:
    int _side;
    bool _stop_flag;
    Socket *_i_main_socket; // server socket for left, client socket for right.
    Reactor *_reactor;// reference to line reactor.
    Line *_line;// reference to line it belongs to .
    Handler *_handler;

private:
    //typedef std::unordered_map<int, Socket*> SocketContainer;
    //SocketContainer _sockets;
    //std::mutex _mutex_sockets;

public:
    void push_event(const ReactorEvent &re);
    //bool pop_event(ReactorEvent &rev);

private:
    EndianEventQueue _event_queue;

    //std::condition_variable _cv_event_queue;
    //std::mutex _mutex_event_queue;
};

#endif//_LISTENER_H__
