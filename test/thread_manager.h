#ifndef _THREAD_MANAGER_H__
#define _THREAD_MANAGER_H__

#include <functional>
#include <list>
#include <mutex>
#include <thread>

#define RUN_TASK THREAD_MANAGER.run_task

class ThreadManager {
public:
    int run_task(std::function<void()> func, bool detach = false);
    int run_task(std::function<void(int)> func, int i, bool detach = false);
    int run_task(std::function<void(void*)> func, void *v, bool detach = false);

    void join();

private:
    std::list<std::thread *> _threads;
    std::mutex _mutex_threads;

};

extern ThreadManager THREAD_MANAGER;

#endif //_THREAD_MANAGER_H__
