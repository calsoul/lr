#include "socket.h"

#include "plt/net-inc.h"
#include "reactor_event.h"
#include "socket_buffer.h"


Socket::Socket(): _type(PROTO::NUL),
                  _fd(-1),
                  _status(STATUS_NULL),
                  _flag_w_buffer( 0 ),
                  _endian(0) {

}

Socket::~Socket() {
  //_socket_status = SOCKET_STATUS_CLOSE;
  //if (_fd > 0) {
  //  //close(_fd);
  //  socket_close(_fd);
  //}
}

//SOCKETID Socket::sign_socket_id() {
//  return PSIDSET->get();
//}

int Socket::nonblock(bool nb) {
  return socket_nonblock(_fd, nb);
}

int Socket::reuseaddr(bool ra) {
  return socket_reuse(_fd, ra);
}

int Socket::push_w(char *buf, int len) {
  return _w_buffer.push_back(buf, len);
}

int Socket::push_w(BufferItem *bi) {
    return _w_buffer.push_back(bi);
}

int Socket::push_r(char *buf, int len) {
  return _r_buffer.push_back(buf, len);
}

int Socket::read_r(char *dst, int len) {
  return _r_buffer.read_front(dst, len);
}

int Socket::move_r(char *dst, int len) {
  return _r_buffer.pop_front(dst, len);
}

BufferItem *Socket::move_r() {
    return _r_buffer.pop_front();
}

int Socket::read_w(char *dst, int len) {
  return _w_buffer.read_front(dst, len);
}

int Socket::move_w(char *dst, int len) {
  return _w_buffer.pop_front(dst, len);
}

BufferItem *Socket::move_w() {
    return _w_buffer.pop_front();
}

void Socket::clear_w() {
    _w_buffer.clear();
}

void Socket::clear_r() {
    _r_buffer.clear();
}
