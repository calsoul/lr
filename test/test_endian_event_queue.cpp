#include <stdio.h>

#include "endian_event_queue.h"
#include "thread_manager.h"

//thread_local int tid = 0;
EndianEventQueue req;
void writer_1wnr(int i) {
    //tid = i;
    while ( "hahahahahahahahaha" ) {
        //std::this_thread::sleep_for(std::chrono::seconds(1));

        req.push_1wnr(ReactorEvent(0, ++i));
    }
}


void reader_1wnr(int i) {
    while ( "hello world !" ) {
        //std::this_thread::sleep_for(
        //    std::chrono::seconds(1)
        //);
        ReactorEvent re;
        re._event = -1;
        if ( req.pop_1wnr(re) > 0 ) {
            printf("%d\n", re._event);
        }
    }
}

int main(const int argc, const char **argv) {

    //for (int i = 0; i < 10; ++i) {
    int i = 0;
    RUN_PROC(writer_1wnr, i);

    //RUN_TASK(std::function<void(int)>(
    //    std::bind(&writer_1wnr, std::placeholders::_1)
    //), i);
    //}

    for (int i = 0; i < 10; ++i) {
        RUN_PROC(reader_1wnr, i);
        //RUN_TASK(std::function<void()>(
        //    &reader_1wnr
        //));
    }


    THREAD_MANAGER.join();


    return 0;
}
