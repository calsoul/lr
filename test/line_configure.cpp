#include "line_configure.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_LEFT_THREAD_NUMBER 3
#define DEFAULT_RIGHT_THREAD_NUMBER 3
#define TIME_ENABLE 1
#define DEFAULT_REACTOR 0

LineConfigure CONFIGURE;

LineConfigure::LineConfigure(): _reactor(DEFAULT_REACTOR),
                 _left_thread_number(DEFAULT_LEFT_THREAD_NUMBER),
                 _right_thread_number(DEFAULT_RIGHT_THREAD_NUMBER),
                 _timer_enable(TIME_ENABLE) {

};

int LineConfigure::load_line_conf(const std::string &fname) {
    return load_line_conf(fname.c_str());
}

int LineConfigure::load_line_conf(const char *fname) {
    FILE *file = fopen(fname, "r");
    if ( !file ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            strerror(errno)
        );
        fclose(file);
        return -1;
    }

    std::map<std::string, std::string> kv_conf;
    char buf[1024] = {0};
    char *lineptr = buf;
    size_t sbuf = sizeof(buf);
    while ( 1 ) {
        ssize_t len = getline(&lineptr, &sbuf, file);
        if ( len < 0 ) {
            break;
        }
        if ( inter_one_line(lineptr, len, kv_conf) < 0 ) {
            fclose(file);
            return -1;
        }
    }
    fclose(file);


    std::string value;
    std::map<std::string, std::string>::iterator it = kv_conf.find("reactor");
    if ( it != kv_conf.end()) {
        value = it->second;
        char c = value.at(0);
        if ( c < '0' || c > '4' ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "reactor value error."
            );
            return -1;
        }

        _reactor = c - '0';
    }

    it = kv_conf.find("timer_enable");
    if ( it !=  kv_conf.end() ) {
        value = it->second;
        char c = value.at(0);
        if ( c != '0' && c != '1' ) {
             printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "timer_enable value error."
            );
            return -1;
        }

        _timer_enable = c - '0';
    }

    it = kv_conf.find("left_thread_number");
    if ( it != kv_conf.end() ) {
        value = it->second;

        int v = std::atoi(value.c_str());
        if ( v > 0 ) {
            _left_thread_number = v;
        } else {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "error left thread number."
            );
            return -1;
        }
    }

    it = kv_conf.find("right_thread_number");
    if ( it != kv_conf.end() ) {
        value = it->second;

        int v = std::atoi(value.c_str());
        if ( v > 0 ) {
            _right_thread_number = v;
        } else {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "error right thread number."
            );
            return -1;
        }
    }

    it = kv_conf.find("left_endian");
    if ( it != kv_conf.end() ) {
        value = it->second;
        if ( inter_addrinfo(value.c_str(), _left_endian) < 0) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "error left endian info."
            );
            return -1;
        }
    }

    it = kv_conf.find("right_endian");
    if ( it != kv_conf.end() ) {
        value = it->second;
        if ( inter_addrinfo(value.c_str(), _right_endian) < 0 ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "error right endian info."
            );
            return -1;
        }
    }
   
    return 0;
}

int LineConfigure::inter_one_line(const char *line, ssize_t len, std::map<std::string, std::string> &kv_map) {
    const char *beg = line;
    ssize_t i = 0;

    while ( i < len && ' ' == *(beg + i)) {
        ++i;
    }

    if ( *(beg + i) == '\n' ) {
        return 0;
    }

    if ( len - i < 2 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid conf."
        );
        return -1;
    }

    if (
        (*(beg + i) == '/') &&
        (*(beg + i + 1) == '/')
    ) {
        return 0;
    }
    char c = 0;
    std::string key;
    while ( 1 ) {
        if (i > len ) {
            break;
        }
        c = *(beg + i);
        if ( !valid_char(c) ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "invalid char."
            );
            return -1;
        }
        if ( c == '\r' || c == '\n' ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "invalid conf."
            );
            return -1;
        }

        if ( c == '=' ) {
            break;
        }

        if ( c != ' ' && c != '\t' && c != '\r' && c != '\n' ) {
            key.push_back(c);
        }

        ++i;
    }

    if ( c != '=' || key.length() < 1 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid conf."
        );
        return -1;
    }

    ++i;

    while ( i < len && ' ' == *(beg + i)) {
        ++i;
    }

    std::string value;
    while ( 1 ) {
        if (i > len ) {
            break;
        }
        char c = *(beg + i);
        if ( !valid_char(c) ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "invalid char."
            );
            return -1;
        }
        if ( c == '\r' || c == '\n' ) {
            break;
        }

        if ( c != ' ' && c != '\t' && c != '\r' && c != '\n' ) {
            value.push_back(c);
        }

        ++i;
    }

    if ( value.length() < 1 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid conf."
        );
        return -1;
    }

    kv_map[key] = value;

    return 0;
}

int LineConfigure::inter_addrinfo(const char *line, AddrInfo &addr) {
    const char *beg = line;

    std::string sp;
    while ( *beg && *beg != '/' ) sp.push_back(*beg++);

    if ( !(*beg) ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid address info."
        );
        return -1;
    }

    ++beg;

    std::string sip;
    while ( *beg && *beg != ':' ) sip.push_back(*beg++);

    if ( !valid_ip(sip.c_str()) ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid address info."
        );
        return -1;
    }

    if ( !(*beg) ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid address info."
        );
        return -1;
    }
    ++beg;

    std::string sport;
    while ( *beg ) sport.push_back(*beg++);

    int iport = std::atoi(sport.c_str());
    if ( iport <= 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid address info."
        );
        return -1;
    }

    sp = sp.substr(0, 3);
    for (auto &x:sp ) x = tolower(x);
    if ( sp != "tcp" && sp != "udp" ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "invalid address info."
        );
        return -1;
    }

    if ( sp == "tcp" ) {
        addr._protocol = AddrInfo::PRO_TCP;
    } else {
        addr._protocol = AddrInfo::PRO_UDP;
    }
    addr._port = iport;
    addr._ip = sip;

    return 0;
}

bool LineConfigure::valid_char(char c) {
    return (
        (c <= 'z' && c >= 'a') ||
        (c <= 'Z' && c >= 'A') ||
        (c <= '9' && c >= '0') ||
        (c == '/') || (c == ' ') ||
        (c == ':') || (c == '.') ||
        (c == '_') || (c == '\r') ||
        (c == '\n') || (c == '=')
    );
}

bool LineConfigure::valid_ip(const char *ip) {
    std::string sec;
    while ( *ip && *ip != '.' ) {
        if ( !isdigit(*ip) ) {
            return false;
        }
        sec.push_back(*ip++);
    }
    int isec = std::atoi(sec.c_str());
    if ( isec < 0 || isec > 255 ) {
        return false;
    }

    sec = "";
    if ( *ip == 0 ) {
        return false;
    }
    ++ip;
    while ( *ip && *ip != '.' ) {
        if ( !isdigit(*ip) ) {
            return false;
        }
        sec.push_back(*ip++);
    }
    isec = std::atoi(sec.c_str());
    if ( isec < 0 || isec > 255 ) {
        return false;
    }

    sec = "";
    if ( *ip == 0 ) {
        return false;
    }
    ++ip;
    while ( *ip  && (*ip != '.') ) {
        if ( !isdigit(*ip) ) {
            return false;
        }
        sec.push_back(*ip++);
    }
    isec = std::atoi(sec.c_str());
    if ( isec < 0 || isec > 255 ) {
        return false;
    }
    sec = "";
    if ( *ip == 0 ) {
        return false;
    }
    ++ip;

    while ( *ip ) {
        if ( !isdigit(*ip) ) {
            return false;
        }
        sec.push_back(*ip++);
    }
    isec = std::atoi(sec.c_str());
    if ( isec < 0 || isec > 255 ) {
        return false;
    }

    return true;
}

int LineConfigure::get_reactor() {
    return _reactor;
}

int LineConfigure::get_left_thread_number() {
    return _left_thread_number;
}

int LineConfigure::get_right_thread_number() {
    return _right_thread_number;
}

AddrInfo &LineConfigure::get_left_addr_info() {
    return _left_endian;
}

AddrInfo &LineConfigure::get_right_addr_info() {
    return _right_endian;
}

bool LineConfigure::timer_enable() {
    return _timer_enable;
}

