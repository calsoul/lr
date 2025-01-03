#include "signals.h"

#include <signal.h>
#include <stdlib.h>
#include <stdarg.h>

//#include "plt/oth-inc.h"

#include "thread_manager.h"

bool Signals::_stop_flag = false;
Handler Signals::_handler = NULL;

int Signals::init() {

  Signals::_stop_flag = false;

  int ret = atexit(&Signals::clean_up);
  if (ret < 0) {
    ZLOG_ERROR(__FILE__, __LINE__, __func__, "atexit setting error");
    return ret;
  }

  set_signal_handler(SIGHUP,   &Signals::signal_handler);
  set_signal_handler(SIGINT,   &Signals::signal_handler);
  set_signal_handler(SIGQUIT,  &Signals::signal_handler);
  set_signal_handler(SIGBUS,   &Signals::signal_handler);
  set_signal_handler(SIGKILL,  &Signals::signal_handler);
  set_signal_handler(SIGSEGV,  &Signals::signal_handler);
  set_signal_handler(SIGALRM,  &Signals::signal_handler);
  set_signal_handler(SIGILL,   &Signals::signal_handler);
  set_signal_handler(SIGFPE,   &Signals::signal_handler);
  set_signal_handler(SIGTERM,  &Signals::signal_handler);
  //set_signal_handler(SIGBREAK , &Signals::signal_handler);
  //set_signal_handler(SIGABRT,  &Signals::signal_handler);
  
  //_r_event_pool_id = EventPool::reserve_event_queue();
  //_thread_group_id = PTHREADMANAGER->reserve_thread_group();
  //PTHREADMANAGER->start(_thread_group_id, 1);
  // this thread used by dispatcher ..

  return 0;
}

int Signals::start() {
    RUN_TASK(
        std::bind(
            &Signals::_proc_signal,
            std::placeholders::_1
        )
    );

    return 0;
}

void Signals::_proc_signal(int sig) {
    while ( !Signals::_stop_flag ) {
        switch ( sig ) {
        case SIGBUS:
        case SIGSEGV:
        case SIGQUIT:
        case SIGHUP:
        case SIGKILL:
        case SIGINT:
        case SIGALRM:
            _handler->process(ReactorEvent(
                EV_SIGNAL, (void *)sig
            ));
        break;

        default:
            printf("%s %d %s %s [%d]\n",
                __FILE__, __LINE__, __func__, 
                "unknown sig", sig
            );
        }
    }
}

void Signals::dump_stack(void) {
  char gdbcommand[160] = {0};

  sprintf(gdbcommand, "gdb -q  --pid %d --batch -ex generate-core-file -ex kill -ex quit", getpid());

  system(gdbcommand);

  return;
}


void Signals::clean_up(void) {
    /* Do any cleaning up chores here */
    printf("%s %d %s %s\n",
        __FILE__, __LINE__, __func__,
        ""
    );
    return ;
}

void Signals::stop() {
  ZLOG_WARN(__FILE__, __LINE__, __func__);
  
  Signals::_stop_flag = true;
}

