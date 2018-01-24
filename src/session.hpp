#ifndef _LIBI2CP_SESSION_HPP
#define _LIBI2CP_SESSION_HPP
#include "buffer.hpp"


struct i2cp_session
{
  i2cp_client * client;
  i2cp_session_config * config;
  int fd;
  bool connected;
  i2cp_buffer_queue sendq;
  i2cp_buffer_queue recvq;

  ~i2cp_session();

  int CreateSocket(int af);
  void Close();
  int Recv();
  int Send();
  void GotMessage(uint8_t * ptr, size_t sz);
};



#endif
