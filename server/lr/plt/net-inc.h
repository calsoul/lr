#ifndef _NET_INC_H__
#define _NET_INC_H__

enum PROTO{
    NUL = 0,
    TCP = 1,
    UDP = 2
};

struct socket_create_param {
    int protocol;
    bool overlapped;
};
int socket_create(struct socket_create_param *scp);

struct socket_bind_param {
    int protocol;
    int port;
    char ip[64];
};
int socket_bind(int socket, struct socket_bind_param *sbp);

struct socket_connect_param {
    int protocol;
    int port;
    char ip[64];
};
int socket_connect(int socket, struct socket_connect_param *scp);

struct socket_accept_param {
    char ip[64];
    int port;
    int socket;
};
int socket_accept(int socket, struct socket_accept_param *sap);

struct socket_listen_param {
    int number;
};
int socket_listen(int socket, struct socket_listen_param *slp);

struct socket_recv_param {
    int protocol; 
    char *buf;
    int blen;
    int port;
    char ip[64];
};
int socket_recv(int socket, struct socket_recv_param *srp);

struct socket_send_param {
    int protocol;

    char *buf;
    int blen;
    int socket;
    int port;
    char ip[64];
};
int socket_send(int socket, struct socket_send_param *ssp);

int socket_nonblock(int socket, bool nb);

int socket_reuse(int socket, bool ru);

int socket_close(int socket);

#endif
