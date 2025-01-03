#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <iostream>
#include <thread>
#include <chrono>

#include "socket_buffer.h"
#include "bi_cache_pool.h"
#include "thread_manager.h"









SocketBuffer sb;

void writer() {
    char word[16] = {0};
    unsigned int counter = 0;

    while (  "writer" ) {
        memset(word, 0x0, sizeof(word));
        sprintf(word, "%07u", counter++);
        int wlen = 0;
        while ( wlen < 7 ) {
            wlen += sb.push_back(word + wlen, 7 - wlen);
        }

std::this_thread::sleep_for(
    std::chrono::milliseconds(300)
);
    }
}


void reader() {
    char word[16] = {0};
    while (  "reader" ) {
        memset(word, 0x0, sizeof(word));
        int rlen = 0;
        while ( rlen < 7 ) {
            rlen += sb.pop_front(word + rlen, 7 - rlen);
        }
        if ( rlen > 0 ) {
            printf("%s\n", word);
        }

std::this_thread::sleep_for(
    std::chrono::milliseconds(300)
);
    }


}

void tester() {
    srandom(time(0));
    unsigned counter = 0;
    unsigned checker = 0;
    char word[32] = {0};

    while ( "tester" )  {
        int end = 1;// random() % 100 + 1;
        for (int i = 0; i < end; ++i) {
            memset(word, 0x0, sizeof(word));
            sprintf(word, "%07u", counter);
            int len = sb.push_back(word, 7);
printf("%d put -[%s]\n", counter, word);

            ++counter;
            if ( len != 7 ) {
                printf("%s %s %d\n",
                    __FILE__, __func__, __LINE__
                );
            }
            ;
        }
        //end = random() % 100 + 1;
        for (int i = 0; i < end; ++i) {
            memset(word, 0x0, sizeof(word));
            int len = sb.pop_front(word, 7);
            //if ( len != 7 ) {
            //    printf("%s %s %d, %d\n",
            //        __FILE__, __func__, __LINE__,
            //        len
            //    );
            //}
            if ( len > 0 ) {

printf("%d get -[%s]\n",checker++,  word);
                //int n = atoi(word);

                //printf("(%d-%d)\n",
                //    n, checker++
                //);
            }
        }

//std::this_thread::sleep_for(
//    std::chrono::seconds(1)
//);

    }

}

int main(const int argc, const char **argv ) {
    RUN_TASK(std::function<void()>(
        &writer
    ));


    RUN_TASK(std::function<void()>(
        &reader
    ));
    //RUN_TASK(std::function<void()>(
    //    &tester
    //));



    THREAD_MANAGER.join();


    return 0;

    /*
    char word[16] = {0};
    word[0] = '1';

    BufferItem *bi = BI_CACHE_POOL.get();
    if ( !bi ) {
        std::cout << "null bi " << std::endl;
        return -1;
    }

    bi->write(word, 1);

    sb.push_back(bi);
    //for (int i = 0; i < 1000; ++i) {
    //    sprintf(word, "%03d,", i);

    //    int s = sb.write(word, 4);
    //    if ( s != 4 ) {
    //        printf("%s %s %d %s\n",
    //            __FILE__, __func__, __LINE__, "error sb write."
    //        );
    //    }
    //    printf("%s - %d\n", word, sb.size());
    //}


    //for (int i = 0; i < 1000; ++i) {
    //    sb.remove(word, 4);
    //    printf("%s - %d\n", word, sb.size());
    //}


    while ( true ) {

std::this_thread::sleep_for(std::chrono::seconds(1));

        BufferItem *bi = sb.front();

        if ( !bi ) {
            break;
        }

        memset(word, 0x0, sizeof(word));
        bi->remove(word, sizeof(word));
        std::cout <<"remove " << word << std::endl;

        sb.pop_front();
        BI_CACHE_POOL.put(bi);
    }


    std::cout << "stop." << std::endl;

    return 0;
    */
}
