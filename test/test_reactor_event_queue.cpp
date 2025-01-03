#include <stdio.h>

#include "reactor_event_queue.h"
#include "thread_manager.h"

//thread_local int tid = 0;
ReactorEventQueue req;
void writer_nw1r(int i) {
    //tid = i;
    while ( "hahahahahahahahaha" ) {
        //std::this_thread::sleep_for(std::chrono::seconds(1));

        req.push_nw1r(ReactorEvent(0, i));
    }
}


void reader_nw1r() {
    while ( "hello world !" ) {
        //std::this_thread::sleep_for(
        //    std::chrono::seconds(1)
        //);
        ReactorEvent re;
        re._event = -1;
        if ( req.pop_nw1r(re) > 0 ) {
            printf("%d\n", re._event);
        }
    }
}

int main(const int argc, const char **argv) {

    for (int i = 0; i < 10; ++i) {
        RUN_TASK(std::function<void(int)>(
            std::bind(&writer_nw1r, std::placeholders::_1)
        ), i);
    }

    //for (int i = 0; i < 10; ++i) {
    RUN_TASK(std::function<void()>(
        &reader_nw1r
    ));
    //}


    THREAD_MANAGER.join();


    return 0;
}
