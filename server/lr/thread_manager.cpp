#include "thread_manager.h"

ThreadManager  THREAD_MANAGER;

void ThreadManager::run_proc(p_void_int proc, int i, bool detach) {
    if ( detach ) {
        std::thread th(
            proc, i
        );
        th.detach();
        return;
    }

    std::thread *t = new std::thread(
        proc, i
    );
    std::unique_lock<std::mutex> l(_mutex_threads);
    _threads.push_back(t);
}

void ThreadManager::run_proc(p_void_pvoid proc, void *v, bool detach) {
    if ( detach ) {
        std::thread th(
            proc, v
        );
        th.detach();
        return ;
    }

    std::thread * t = new std::thread(
        proc, v
    );
    std::unique_lock<std::mutex> l(_mutex_threads);
    _threads.push_back(t);
}

void ThreadManager::join() {
    std::list<std::thread *> tt;
    {
        std::unique_lock<std::mutex> l(_mutex_threads);
        tt = _threads;
    }

    for (std::list<std::thread *>::iterator it = tt.begin();
        it != tt.end(); ++it ) {

        (*it)->join();
    }
}
