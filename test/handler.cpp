#include "handler.h"

#include <stdio.h>

#include "line.h"
#include "reactor.h"
#include "reactor_event.h"
#include "socket.h"

int Handler::handle(ReactorEvent re) {
//printf("%s %s %d %d %d\n",
//    __FILE__, __func__, __LINE__,
//    re._sock->_fd, re._event
//);

    switch ( re._event ) {
    case EV_ACCEPT: {
        printf("fd-%d, ev: accept.\n", re._sock->_fd);
    } break;

    case EV_READ: {
        while ( true ) {
            BufferItem * bi = re._sock->move_r();
            if ( !bi ) {
                break;
            }

            re._sock->push_w(bi);
        }
        //char word[16] = {0};
        //re._sock->move_r(word, 7);
        //printf(
        //    "fd-%d, read:[%s]\n",
        //    re._sock->_fd, word
        //);
        //re._sock->push_w(word, 7);
        send_back(re._sock);
    } break;

    case EV_WRITE: {
        printf(
            "fd-%d, ev: write.\n",
            re._sock->_fd
        );
    } break;

    case EV_CLOSE: {
        printf(
            "fd-%d, ev: close.\n",
            re._sock->_fd
        );
    } break;

    default: {
        printf("fd-%d, unknown ev: [%d].\n",
            re._sock->_fd, re._event
        );

        return -1;
    } }

    return 0;
}

void Handler::send_back(Socket *sock) {
    _line->_i_reactor->add_socket(sock, EV_WRITE);
}

