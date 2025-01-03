#ifndef _TCP_SOCKET_H__
#define _TCP_SOCKET_H__

#include "socket.h"

class AddrInfo;
class TcpSocket: public Socket {
public:
  TcpSocket();

  virtual ~TcpSocket() { }

public:
  virtual int init(AddrInfo *addr);
  virtual int bind();
  virtual Socket *accept();
  virtual int connect();
  virtual int listen();
  virtual int recv();
  virtual int send();
  virtual int close();

};

#endif //_TCP_SOCKET_H__
