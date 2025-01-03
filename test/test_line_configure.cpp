

#include <iostream>

#include "line_configure.h"

int main( const int argc, const char **argv ) {

    const char *fcfgpath = "line.conf";
    if ( CONFIGURE.load_line_conf(fcfgpath) < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "load config file error."
        );
        return -1;
    }

    int reactor = CONFIGURE.get_reactor();
    int left_thread_number = CONFIGURE.get_left_thread_number();
    int right_thread_number = CONFIGURE.get_right_thread_number();

    bool timer_enable = CONFIGURE.timer_enable();

    AddrInfo left_addr_info = CONFIGURE.get_left_addr_info();

    AddrInfo right_addr_info = CONFIGURE.get_right_addr_info();

    std::cout << "reactor" << reactor << std::endl;
    std::cout << "left_thread_number" << left_thread_number << std::endl;
    std::cout << "right_thread_number" << right_thread_number << std::endl;
    std::cout << "timer_enable" << timer_enable << std::endl;

    std::cout << left_addr_info._protocol << " " 
              << left_addr_info._port << " "
              << left_addr_info._ip  << std::endl;

    std::cout << right_addr_info._protocol << " " 
              << right_addr_info._port << " "
              << right_addr_info._ip  << std::endl;



    return 0;
}
