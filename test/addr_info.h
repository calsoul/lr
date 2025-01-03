#ifndef _IPINFO_H__
#define _IPINFO_H__

#include <string>

class AddrInfo {
public:
    enum {
        PRO_NULL = 0,
        PRO_TCP  = 1,
        PRO_UDP  = 2
    };

    AddrInfo() {
      _protocol = PRO_NULL;
      _port     = 0;
      _ip       = "";
    }

    int _protocol;
    int _port;
    std::string _ip;
};

#endif//_IPINFO_H__
