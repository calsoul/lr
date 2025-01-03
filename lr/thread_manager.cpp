#include "thread_manager.h"

ThreadManager  THREAD_MANAGER;

int ThreadManager::run_task(std::function<void()> func, bool detach) {
    //if ( _stop_flag ) {
    //    printf("%s %d %s %s\n",
    //        __FILE__, __LINE__, __func__,
    //        "thead manager has stopped."
    //    );
    //    return -1;
    //}

    if ( detach ) {
        std::thread th(func);
        th.detach();
        return 0;
    }

    std::thread * t = new std::thread(func);

    std::unique_lock<std::mutex> l(_mutex_threads);
    _threads.push_back(t);

    return 0;
}

int ThreadManager::run_task(std::function<void(int i)> func, int i, bool detach) {
    if ( detach ) {
        std::thread th(func, i);
        th.detach();
        return 0;
    }

    std::thread * t = new std::thread(func, i);

    std::unique_lock<std::mutex> l(_mutex_threads);
    _threads.push_back(t);

    return 0;
}


int ThreadManager::run_task(std::function<void(void *)> func, void *v, bool detach) {
    if ( detach ) {
        std::thread th(func, v);
        th.detach();
        return 0;
    }

    std::thread * t = new std::thread(func, v);

    std::unique_lock<std::mutex> l(_mutex_threads);
    _threads.push_back(t);

    return 0;
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
