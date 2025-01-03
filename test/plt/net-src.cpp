#include "net-inc.h"

#include <stdio.h>

#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int socket_create(struct socket_create_param *scp) {
    switch ( scp->protocol ) {
    case PROTO::TCP:
      return ::socket(AF_INET, SOCK_STREAM, 0);
    
    case PROTO::UDP:
      return ::socket(AF_INET, SOCK_DGRAM, 0);
    }
    return -1;
}

int socket_bind(int socket, struct socket_bind_param *sbp) {
    sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr(sbp->ip);
    addrin.sin_port = htons(sbp->port);
    return ::bind(socket, (struct sockaddr *)&addrin, sizeof(addrin));
}

int socket_connect(int socket, struct socket_connect_param *scp) {
    sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr(scp->ip);
    addrin.sin_port = htons(scp->port);
    return ::connect(socket, (struct sockaddr *)&addrin, sizeof(addrin));
}

int socket_accept(int socket, struct socket_accept_param *sap) {
    struct sockaddr_in addrin;
    socklen_t addrlen = sizeof(addrin);
    int s = -1;
    while ( true ) {
        s = ::accept(socket, (struct sockaddr*)&addrin, &addrlen);
        if ( sap ) {
            memset(sap->ip, 0x0, sizeof(sap->ip));
            strcpy(sap->ip, inet_ntoa(addrin.sin_addr));
            sap->port = ntohs(addrin.sin_port);
            sap->socket = s;
        }

        if ( s < 0 ) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        return s;
    }
    return s;
}

int socket_listen(int socket, struct socket_listen_param *slp) {
    return ::listen(socket, slp->number);
}

int _tcp_socket_recv(int socket, struct socket_recv_param *srp) {
//printf("pre recv [blen-%d].\n", srp->blen);
    int srecv = 0;
    int ret = 0;
    while ("heading..." && (srecv < srp->blen)) {
        ret = recv(
            socket, srp->buf + srecv, srp->blen - srecv, 0
        );
        if ( ret < 0 ) {
            if ( errno == EINTR || 
                 errno == EAGAIN ||
                 errno == EWOULDBLOCK
            ) {
                break;
            }
            return -2;
        }

        if ( ret == 0 ) {
            return -1;
        }
printf("recv [ret-%d] [%s]\n", ret, srp->buf);

        srecv += ret;
    }
    return srecv;
}

int _udp_socket_recv(int socket, struct socket_recv_param *srp) {
    int ret;
    struct sockaddr_in addrin;
    socklen_t addrlen = sizeof(addrin);
    memset(&addrin, 0x0, sizeof(addrin));
    while ( true ) {
        ret = ::recvfrom(socket, srp->buf, srp->blen, 0, (struct sockaddr*)&addrin, &addrlen);
        if ( ret < 0 ) {
            if ( errno == EINTR ) {
                continue;
            }
            return -1;
        }
        break;
    }

    memset(srp->ip, 0x0, sizeof(srp->ip));
    strcpy(srp->ip, inet_ntoa(addrin.sin_addr));
    srp->port = ntohs(addrin.sin_port);
    srp->blen = ret;

    return ret;
}

int socket_recv(int socket, struct socket_recv_param *srp) {
    switch (srp->protocol) {
    case PROTO::TCP:
        return _tcp_socket_recv(socket, srp);

    case PROTO::UDP:
        return _udp_socket_recv(socket, srp);
    }

    return -1;
}

int _tcp_socket_send(int socket, struct socket_send_param *ssp) {
    int ret;
    int sent = 0;
    while ( sent < ssp->blen ) {
//printf("pre send [len-%d]:[%s].\n", ssp->blen, ssp->buf);
        ret = send(socket, ssp->buf + sent, ssp->blen - sent, MSG_NOSIGNAL);

        if ( ret < 0 ) {
            if ( errno == EINTR || 
                 errno == EAGAIN ||
                 errno == EWOULDBLOCK
            ) {
                break;
            }
            return -1;
        }
printf("send [ret-%d]:[%s]\n", ret, ssp->buf);

        sent += ret;
    }
    return sent;
}

int _udp_socket_send(int socket, struct socket_send_param *ssp) {
    struct sockaddr_in addrin;
    addrin.sin_family = AF_INET;
    addrin.sin_addr.s_addr = inet_addr(ssp->ip);
    addrin.sin_port = htons(ssp->port);
    int ret;
    while ( true ) {
        ret = sendto(socket, ssp->buf, ssp->blen, MSG_NOSIGNAL, (struct sockaddr*)&addrin, sizeof(addrin));
        if ( ret < 0 ) {
            if (errno == EINTR) {
                continue;
            }
            return -1;
        }
        break;
    }
    return ret;
}


int socket_send(int socket, struct socket_send_param *ssp) {
  switch (ssp->protocol) {
  case PROTO::TCP:
      return _tcp_socket_send(socket, ssp);

  case PROTO::UDP:
      return _udp_socket_send(socket, ssp);
  }

  return -1;
}

int socket_nonblock(int socket, bool nb) {
    int flags = ::fcntl(socket, F_GETFL, 0);
    if (flags < 0) {
        return -1;
    }

    if (nb) {
        flags |= O_NONBLOCK;
    } else {
        flags &= ~O_NONBLOCK;
    }

    return ::fcntl(socket, F_SETFL, flags);
}

int socket_reuse(int socket, bool ru) {
    int val = 0;
    if (ru) {
        val = 1;
    }
    return ::setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
}

int socket_close(int socket) {
    return ::close(socket);
}
