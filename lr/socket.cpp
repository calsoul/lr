#include "socket.h"

#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string>
#include <unistd.h>

#include "data_buffer.h"
#include "base_type.h"
#include "zlog.h"
#include "utils.h"
#include "event.h"
#include "event_pool.h"
#include "listener.h"

Socket::Socket() {
  _r_db = MAKE_SHARED(DataBuffer);
  _w_db = MAKE_SHARED(DataBuffer);
  _socket_status = SOCKET_STATUS_NULL;
}

Socket::~Socket() {
  _socket_status = SOCKET_STATUS_CLOSE;
  close(_fd);
}

SOCKETID Socket::sign_socket_id() {
  static std::mutex _g_mutex_g_id;
  static SOCKETID _g_socket_id = 0;
  SOCKETID id;

  LOCK_GUARD_MUTEX_BEGIN(_g_mutex_g_id);
  id = ++_g_socket_id;
  if (id == 0) {
    id = ++_g_socket_id;
  }
  LOCK_GUARD_MUTEX_END
  
  return id;
}

int Socket::vinit(IPInfo &) { return 0; }
int Socket::vbind() { return 0; }
std::shared_ptr<Socket> Socket::vaccept() { return NULL; }
int Socket::vconnect() { return 0; }
int Socket::vlisten() { return 0; }
int Socket::vrecv() { return 0; }
int Socket::vsend(const char *buf, const int blen) { return 0; }
int Socket::vclose() { return 0;}

int Socket::nonblock(bool nb) {
  int fl = fcntl(_fd, F_GETFL, 0);
  if ( fl < 0 ) {
    ZLOG_ERROR(__FILE__, __LINE__, __func__, "fcntl error", _fd);
    return -1;
  }

  if (nb) {
    fl |= O_NONBLOCK;
  } else {
    fl &= ~O_NONBLOCK;
  }

  if (fcntl(_fd, F_SETFL, fl) < 0) {
    ZLOG_ERROR(__FILE__, __LINE__, __func__, "fcntl set error", _fd, fl);
    return -1;
  }

  return 0;
}

int Socket::reuseaddr(bool ra) {
  int on = 1;
  if ( ra == false) {
    on = 0;
  }

  return setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
}

int Socket::ssend() {
  int len;
  std::vector<char> d;
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  if (_w_db->_len < 1) {
    return 0;
  }

  if (_w_db->_len <= BufferItem::buffer_item_capacity) {
    BufferItem::ptr bi = _w_db->_data.front();
    if (bi) {
      len = vsend(bi->_buffer, bi->_len);
    }

  } else {

    _w_db->get(d);

    len = vsend(&(*d.begin()), d.size());
  }

  _w_db->drop(len);
  //_w_db->clear();

  LOCK_GUARD_MUTEX_END

  return len;
}

int Socket::esend() {
  return _line->notify_w_event(_id, _fd);
}

int Socket::esend(const char *buf, const int len) {
  add_w_data(buf, len);
  return _line->notify_w_event(_id, _fd);
}

int Socket::esend(const std::string &str) {
  add_w_data(str);
  return _line->notify_w_event(_id, _fd);
}

int Socket::esend(const DataBuffer &db) {
  add_w_data(db);
  return _line->notify_w_event(_id, _fd);
}

int Socket::esend(const std::shared_ptr<DataBuffer> &db) {
  add_w_data(db);
  return _line->notify_w_event(_id, _fd);
}

int Socket::esend(const std::shared_ptr<BufferItem> &bi) {
  add_w_data(bi);
  return _line->notify_w_event(_id, _fd);
}

int Socket::add_w_data(const char *buf, const int len) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  _w_db->add(buf, len);
  LOCK_GUARD_MUTEX_END
  return len;
}

int Socket::add_w_data(const std::string &str) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  _w_db->add(str);
  LOCK_GUARD_MUTEX_END
  return str.size();
}

int Socket::add_w_data(const DataBuffer &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  _w_db->add(db);
  LOCK_GUARD_MUTEX_END
  return db._len;
}

int Socket::add_w_data(const std::shared_ptr<DataBuffer> &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  _w_db->add(db);
  LOCK_GUARD_MUTEX_END
  return db->_len;
}

int Socket::add_w_data(const std::shared_ptr<BufferItem> &bi) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  _w_db->add(bi);
  LOCK_GUARD_MUTEX_END
  return bi->_len;
}

int Socket::get_w_data(char *buf, const int len) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  return _w_db->get(buf, len);
  LOCK_GUARD_MUTEX_END
}

int Socket::get_w_data(DataBuffer &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  return _w_db->get(db);
  LOCK_GUARD_MUTEX_END
}

int Socket::get_w_data(std::shared_ptr<DataBuffer> &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  return _w_db->get(db);
  LOCK_GUARD_MUTEX_END
}

int Socket::move_w_data(char *buf, const int len) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  return _w_db->move(buf, len);
  LOCK_GUARD_MUTEX_END
}

int Socket::move_w_data(std::vector<char> &v) {
  int ret;
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  ret = _w_db->get(v);
  _w_db->clear();
  LOCK_GUARD_MUTEX_END
  return ret;
}

void Socket::clear_w_data() {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_w_db)
  _w_db->clear();
  LOCK_GUARD_MUTEX_END
}

int Socket::move_r_data(char *buf, const int len) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->move(buf, len);
  LOCK_GUARD_MUTEX_END
}

void Socket::clear_r_data() {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  _r_db->clear();
  LOCK_GUARD_MUTEX_END
  return;
}

int Socket::get_r_data(char *buf, const int len) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->get(buf, len);
  LOCK_GUARD_MUTEX_END
}

int Socket::get_r_data(DataBuffer &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->get(db);
  LOCK_GUARD_MUTEX_END
}

int Socket::get_r_data(std::shared_ptr<DataBuffer> &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->get(db);
  LOCK_GUARD_MUTEX_END
}

int Socket::move_r_data(std::vector<char> &v) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->move(v);
  LOCK_GUARD_MUTEX_END
}

int Socket::move_r_data(DataBuffer &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->move(db);
  LOCK_GUARD_MUTEX_END
}

int Socket::move_r_data(std::shared_ptr<DataBuffer> &db) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  return _r_db->move(db);
  LOCK_GUARD_MUTEX_END
}

int Socket::add_r_data(const std::shared_ptr<BufferItem> &bi) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  _r_db->add(bi);
  LOCK_GUARD_MUTEX_END
  return bi->_len;
}

int Socket::add_r_data(const char *buf, const int len) {
  LOCK_GUARD_MUTEX_BEGIN(_mutex_r_db)
  _r_db->add(buf, len);
  LOCK_GUARD_MUTEX_END
  return len;
}