#ifndef _HANDLER_H__
#define _HANDLER_H__

#include "reactor_event.h"

class Line;
class Socket;
class Endian;
class Handler {
public:
    Handler() {
        _stype  = Handler::H_LEFT;
        _endian = 0;
        _line   = 0;
    }

    virtual ~Handler() {}

    virtual int handle(ReactorEvent re);

    void send_back(Socket *sock);

public:
    enum {
        H_NULL  = 0,
        H_LEFT  = 1,
        H_RIGHT = 2,
    };
    int _stype;

public:
    Endian *_endian;
    Line *_line;
};




#endif //_HANDLER_H__
