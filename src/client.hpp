#ifndef _LIBI2CP_CLIENT_HPP
#define _LIBI2CP_CLIENT_HPP
#include <i2cp/i2cp.h>
#include <netinet/in.h>
#include "session.hpp"

#include <list>

struct i2cp_client
{
  i2cp_client(sockaddr a);
  ~i2cp_client();

  void mainloop();
  
  sockaddr addr;

  std::list<i2cp_session *> sessions;
};


#endif
