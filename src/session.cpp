#include <i2cp/i2cp.h>
#include "session.hpp"
#include "client.hpp"
#include <unistd.h>

i2cp_session::~i2cp_session()
{
  if(config)
    free_i2cp_session_config(config);
}

int i2cp_session::CreateSocket(int af)
{
  fd = socket(af, SOCK_STREAM, SOCK_NONBLOCK);
  return fd;
}

void i2cp_session::Close()
{
  if(fd == -1) return;
  close(fd);
  fd = -1;
}

int i2cp_session::Recv()
{
  return 0;
}

int i2cp_session::Send()
{
  if(sendq.size())
  {
    i2cp_buffer buffer = sendq.front();
    sendq.pop_front();
    return send(fd, buffer.data(), buffer.size(), 0);
  }
  return 0;
}

extern "C" {

  struct i2cp_session * i2cp_new_session(struct i2cp_client * cl, struct i2cp_session_config * conf)
  {
    i2cp_session_config * c = copy_i2cp_session_config(conf);
    auto s = new i2cp_session{cl, c, -1, false};
    cl->sessions.push_back(s);
    return s;
  }

  void free_i2cp_session(struct i2cp_session * s)
  {
    delete s;
  }
}
