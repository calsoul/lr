#include "timer.h"

#include "thread_manager.h"

#include "line_configure.h"

Timer TIMER;

Timer::Timer(): _stop_flag( false ) {
}

int Timer::init() {
    return 0;
}

int Timer::start() {
    if ( ! CONFIGURE.timer_enable() ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "timer not enable."
        );
        return 0;
    }

    _stop_flag = false;

    RUN_TASK(std::function<void()>(
        std::bind(&Timer::_proc_timer, this)
    ));

    return 0;
}

int Timer::add(const TimerEvent &te) {
    if ( ! CONFIGURE.timer_enable() ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "timer not enable."
        );
        return -1;
    }

    {
      std::unique_lock<std::mutex> l(_mutex_timer_events);
      _timer_events.emplace(te);
    }

    _cv_timer_events.notify_one();

    return 0;
}

void Timer::_proc_timer() {
    int span = 0;
    while ( !_stop_flag ) {
        std::unique_lock<std::mutex> l(_mutex_timer_events);
        while ( _timer_events.empty() || span > 0 ) {
            _cv_timer_events.wait_for(
               l, std::chrono::seconds(span)
            );

            if ( _stop_flag ) {
                break;
            }

            if ( !_timer_events.empty() ) {
                TimerEvent te = _timer_events.top();
                span = te._time - time(0);

                if ( span <= 0 ) {
                    _timer_events.pop();
                    te._func();
                    //RUN_TASK(te._func, true);
                }
            }
        }
    }
    printf("%s %s %d %s\n",
        __FILE__, __func__, __LINE__,
        "timer stop."
    );
}

void Timer::stop() {
  _stop_flag = true;
  _cv_timer_events.notify_one();
}




