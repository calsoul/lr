
#include <iostream>

#include "buffer_item.h"


int main(const int argc, const char **argv) {
    char rbuffer[1024];
    BufferItem bi;
    char word[2] = {0};
    //int ri = -1;
    word[0] = '0';
    word[1] = '1';


    //printf("buffer [%d]: %*s=\n", 1,
    //    1, &(word[1])
    //);
    //fwrite(
    //    &(word[1]), sizeof(char), 0,
    //stdout);


    //printf("\n=\n");

    //return 0;

    for (int i = 1; i <= 100; ++i) {
        int ret = bi.write(word, 1);
        std::cout << i <<  " write " << ret << " _ size " << bi.size() 
                  << " - space " << bi.space() << " - length " << bi.length()
        << std::endl;

        memset(rbuffer, 0x0, sizeof(rbuffer));
        ret = bi.read(rbuffer, sizeof(rbuffer));
        std::cout << rbuffer << std::endl;

    }    

    for (int i = 1; i <= 100; ++i) {
        int ret = bi.remove(word, 1);
        std::cout << i <<  " remove " << ret << " _ size " << bi.size() 
                  << " - space " << bi.space() << " - length " << bi.length()
        << std::endl;

        memset(rbuffer, 0x0, sizeof(rbuffer));
        ret = bi.read(rbuffer, sizeof(rbuffer));
        std::cout << rbuffer << std::endl;
    }    

    return 0;
}
