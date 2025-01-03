#include <iostream>

#include <functional>
#include <ctime>
#include <thread>

#include "../lr/timer.h"

void test_proc() {
    printf("%s %s %d %d\n",
        __FILE__, __func__, __LINE__,
        (int)time(0)
    );

    //std::chrono::system_clock::to_time_t(
    //    std::chrono::system_clock::now().seconds() 
    //)<< std::endl;
}

int main(const int argc, const char **argv) {

    Timer timer;
    int ret = timer.init();
    if ( ret < 0 ) {
        std::cout << "timer init" << std::endl;
        return -1;
    }

    ret = timer.start();
    if ( ret < 0 ) {
        std::cout << "timer start" << std::endl;
        return -1;
    }

    for ( int i = 0; i < 10; ++i ) {

        std::this_thread::sleep_for(std::chrono::seconds(10));
        printf("%s %s %d %d\n",
            __FILE__, __func__, __LINE__,
            (int)time(0)
        );

        timer.add(TimerEvent(
            time(0) + 5,
            test_proc
        ));

    }


    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}
