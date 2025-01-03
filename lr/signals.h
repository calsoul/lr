#ifndef _SIGNALS_H__
#define _SIGNALS_H__

#include <conditional_variable>
#include <mutex>

#include <list>

#include "reactor_event.h"

class Handler;
class Signals {
public:
  static int init();

  static int start();

  static void _proc_signal(int sig);

  static void dump_stack(void);
  static void clean_up(void);

  static void stop();
public:
  static Handler *_handler;

private:
  static bool _stop_flag;
  static std::conditional_variable _cv_signal;
  static std::mutex _mutex_signal
  static std::list<ReactorEvent> _ev_signal;
};

#endif //_SIGNALS_H__
