#include <string.h>

#include <iostream>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <list>
#include <thread>

#include "buffer_item.h"

#include "bi_cache_pool.h"

#include "thread_manager.h"


std::condition_variable _cv_proc_put;
std::mutex _mutex_proc_put;
std::list<BufferItem *> _list_proc_put;



void proc_get(int i) {
    while ( 1 ) {

//printf("%s %s %d\n",
//    __FILE__, __func__, __LINE__
//);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        BufferItem *bi = BI_CACHE_POOL.get();
        if ( !bi ) {
            continue;
        }
printf("[%d] get one bi\n", i);
        char word[8] = {'h', 'e', 'l', 'l', 'o', 0};
        bi->write(word, 6);


        {
            std::lock_guard<std::mutex> l(_mutex_proc_put);

            _list_proc_put.push_back(bi);
printf("[%d] send one bi\n", i);
        }

        _cv_proc_put.notify_one();

    }
}
void proc_put(int i) {
    while ( true ) {
//printf("%s %s %d\n",
//    __FILE__, __func__, __LINE__
//);


        BufferItem *bi;
        {
            std::unique_lock<std::mutex> l(_mutex_proc_put);
            if ( _list_proc_put.size() < 1 ) {
                _cv_proc_put.wait(l);

                if ( _list_proc_put.size() < 1 ) {
                    continue;
                }
            }
printf("[%d] receive one bi\n", i);
            bi = _list_proc_put.front();
            _list_proc_put.pop_front();
        }
     
        if ( bi ) {

//printf("%s", bi->_data);
            BI_CACHE_POOL.put(bi);
printf("[%d] put one bi\n", i);
        }

    }
}

int main(const int argc, const char **argv) {

    for (int i = 0; i < 100; ++i ) {
        RUN_PROC(
            proc_put, i
        );
    }


    for (int i = 0; i < 100; ++i) {
        RUN_PROC(
            proc_get, i
        );
    }

    THREAD_MANAGER.join();

    return 0;

}
