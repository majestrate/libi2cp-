#include "client.hpp"
#include <cstring>

i2cp_client::i2cp_client(sockaddr a) : addr(a)
{
}

i2cp_client::~i2cp_client()
{
  sessions.clear();
}


extern "C" {
  struct i2cp_client * new_i2cp_client(struct sockaddr * addr)
  {
    struct sockaddr a;
    memcpy(&a, addr, sizeof(struct sockaddr));
    return new i2cp_client(a);
  }

  void free_i2cp_client(struct i2cp_client * cl)
  {
    delete cl;
  }
  
}
