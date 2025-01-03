#ifndef _LINE_H__
#define _LINE_H__

#include "endian.h"

#include "timer.h"

class Handler;
class Reactor;
class Line{
public:
    Line();

    virtual ~Line();

    void set_lr_handlers(Handler *lh, Handler *rh);

    int init(const char *fcfgpath);

    int start();

    int wait();

    void stop();


public:
    void process(const ReactorEvent &re);

public:
    Reactor   *_i_reactor;
    Endian _l_endian;
    Endian _r_endian;

    Timer _timer;

public:
    bool _stop_flag;
};

#endif//_LINE_H__
