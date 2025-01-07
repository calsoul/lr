#ifndef _LINE_CONFIGURE_H__
#define _LINE_CONFIGURE_H__

#include <string>
#include <map>

#include "addr_info.h"



class LineConfigure {
public:
    LineConfigure();

    LineConfigure(const LineConfigure &) = delete;
    LineConfigure(const LineConfigure &&) = delete;
    LineConfigure& operator=(const LineConfigure &) = delete;
public:

    int load_line_conf(const std::string &fname);
    int load_line_conf(const char *fname);

    int get_reactor();
    int get_left_thread_number();
    int get_right_thread_number();
    bool timer_enable();

    AddrInfo &get_left_addr_info();
    AddrInfo &get_right_addr_info();

private:
    int inter_one_line(const char *line, ssize_t len, std::map<std::string, std::string> &kv_map);
    int inter_addrinfo(const char *line, AddrInfo &addr);
    char *drop_space(char *line, int len);

    bool valid_char(char c);
    bool valid_ip(const char *ip);
private:
    int _reactor;
    int _left_thread_number;
    int _right_thread_number;
    int _timer_enable;

    AddrInfo _left_endian;
    AddrInfo _right_endian;
};

extern LineConfigure CONFIGURE;

#endif//_LINE_CONFIGURE_H__
