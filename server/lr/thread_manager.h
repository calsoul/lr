#ifndef _THREAD_MANAGER_H__
#define _THREAD_MANAGER_H__

#include <list>
#include <mutex>
#include <thread>

#define RUN_PROC THREAD_MANAGER.run_proc

typedef void(*p_void_void)(void);
typedef void(*p_void_int)(int);
typedef void(*p_void_pvoid)(void*);

class ThreadManager {
public:

    void run_proc(p_void_int proc, int i, bool detach = false);

    void run_proc(p_void_pvoid proc, void *v, bool detach = false);

    template<typename T>
    void run_proc(T *obj, bool detach = false) {
        if ( detach ) {
            std::thread th(
                &T::_proc, obj
            );
            th.detach();
            return;
        }

        std::thread *t = new std::thread(
            &T::_proc, obj
        );
        std::unique_lock<std::mutex> l(_mutex_threads);
        _threads.push_back(t);

    }


    void join();

private:
    std::list<std::thread *> _threads;
    std::mutex _mutex_threads;

};

extern ThreadManager THREAD_MANAGER;

#endif //_THREAD_MANAGER_H__
