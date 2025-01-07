#include "tcp_socket.h"

#include <string.h>

#include "addr_info.h"
#include "buffer_item.h"
#include "plt/net-inc.h"
#include "socket_buffer.h"
#include "bi_cache_pool.h"

TcpSocket::TcpSocket() {
    _type = PROTO::TCP;
}

int TcpSocket::init(AddrInfo *addr) {
    _addr = *addr;
    struct socket_create_param scp;
    scp.protocol = PROTO::TCP;
    scp.overlapped = true;

    _fd = socket_create(&scp);
    if (_fd < 0) {
        printf("%s %s %d %d\n",
            __FILE__, __func__, __LINE__, _fd
        );
        return -1;
    }

    _status = STATUS_INIT;
    return 0;
}

Socket *TcpSocket::accept() {
    struct socket_accept_param sap;
    memset(&sap, 0x0, sizeof(sap));
    int fd = socket_accept(_fd, &sap);
    if ( fd < 0 ) {
        return NULL;
    }
    Socket *s = new TcpSocket();
    if ( !s ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error new."
        );
        return NULL;
    }
    s->_endian = _endian;
    s->_fd = fd;
    s->_addr._protocol = AddrInfo::PRO_TCP;
    s->_addr._ip = std::string(sap.ip);;
    s->_addr._port = sap.port;

    return s;
}


int TcpSocket::bind() {
    struct socket_bind_param sbp;
    memset(&sbp, 0x0, sizeof(sbp));
    sbp.protocol = PROTO::TCP;
    strcpy(sbp.ip, _addr._ip.c_str());
    sbp.port = _addr._port;

    int ret = socket_bind(_fd, &sbp);
    if ( ret < 0 ) {
        printf("%s %s %d %s: %s:%d\n",
            __FILE__, __func__, __LINE__,
            strerror(errno), sbp.ip, sbp.port
        );
        return -1;
    }

    return 0;
}

int TcpSocket::connect() {
    struct socket_connect_param scp;
    memset(&scp, 0x0, sizeof(scp));
    scp.protocol = PROTO::TCP;
    strncpy(scp.ip, _addr._ip.c_str(), _addr._ip.size());
    scp.port = _addr._port;

    int ret = socket_connect(_fd, &scp);
    if (ret < 0) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error socket_connect."
        );
        return -1;
    }

    _status = STATUS_ACTIVE;

    return 0;
}

int TcpSocket::listen() {
    struct socket_listen_param slp;
    slp.number = 1024;
    int ret = socket_listen(_fd, &slp);
    if ( ret < 0 ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "error socket_listen."
        );
        return ret;
    }

    return 0;
}

int TcpSocket::recv() {
    struct socket_recv_param srp;
    memset(&srp, 0x0, sizeof(srp));
    srp.protocol = PROTO::TCP;

    BufferItem *bi = BI_CACHE_POOL.get();
    if ( !bi ) {
        printf("%s %s %d %s\n",
            __FILE__, __func__, __LINE__,
            "null BI_CACHE_POOL.get."
        );

        return 0;
    }
    bi->clear();

    srp.buf  = bi->_end;
    srp.blen = bi->space();

//printf("pre socket_recv.blen[%d]\n", srp.blen);
    int ret = socket_recv(_fd, &srp);
//printf("aft socket_recv ret-[%d]: %s.\n",
//    ret, srp.buf
//);
    if ( ret < 0 ) {
        printf("%s %s %d %s\n",
           __FILE__, __func__, __LINE__,
          "error socket_recv"
        );

        BI_CACHE_POOL.put(bi);

        if ( ret == -1 ) {
            printf("%s %s %d %s\n",
                __FILE__, __func__, __LINE__,
                "socket read 0."
            );
        }
        return -1;
    }

    bi->_end = bi->_end + ret;

    _r_buffer.push_back(bi);

    return ret;
}

int TcpSocket::send() {
    struct socket_send_param ssp;
    memset(&ssp, 0x0, sizeof(ssp));
    ssp.protocol = PROTO::TCP;

    //int sent = 0;
    //while ( true ) {
    BufferItem *bi = _w_buffer.front();
    if ( !bi ) {
        return 0;
    }

    if ( bi->size() < 1 ) {
        _w_buffer.pop_front();

        BI_CACHE_POOL.put(bi);

        return 0;
    }

    ssp.buf = bi->_beg;
    ssp.blen = bi->size();

//printf("pre socket_send [%d]\n",
//    _w_buffer.size()
//);

    int ret = socket_send(_fd, &ssp);
    if ( ret < 0 ) {
        printf("%s %s %d %s",
            __FILE__, __func__, __LINE__,
            "socket_send error.\n"
        );
        return ret;
    }

    bi->_beg += ret;
    if ( bi->size() < 1 ) {
        _w_buffer.pop_front();

        BI_CACHE_POOL.put(bi);
    }

    return ret;
}

int TcpSocket::close() {
  _status = STATUS_CLOSE;
  return socket_close(_fd);
}

