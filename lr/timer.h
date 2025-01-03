#ifndef _TIMER_H__
#define _TIMER_H__

#include <functional>
#include <queue>

#include <mutex>
#include <condition_variable>

#include <chrono>

//#define TIMER Timer::instance()

class TimerEvent {
    friend class TimerEventComparator;
public:
    TimerEvent(): _time(0), _func(0) { }
    TimerEvent(int t, std::function<void()> f): _time(t), _func(f) {}

    int _time;

    std::function<void()> _func;
};

class TimerEventComparator {
public:
    bool operator () (const TimerEvent &lhs, const TimerEvent &rhs) {
        return lhs._time > rhs._time;
    }
};

class Timer {
public:
    Timer();

    Timer(const Timer &) = delete;
    Timer(const Timer &&) = delete;
    Timer &operator=(const Timer &) = delete;



    virtual ~Timer() { }

    int init();

    int start();

    int add(const TimerEvent &te);

    void stop();

public:
    void _proc_timer();

private:

    typedef std::priority_queue<TimerEvent, std::vector<TimerEvent>, TimerEventComparator> TimerEventContainer;

    TimerEventContainer _timer_events;

    std::condition_variable _cv_timer_events;
    std::mutex _mutex_timer_events;

    int _current_time;

    bool _stop_flag;
};

extern Timer TIMER;

#endif//_TIMER_H__
