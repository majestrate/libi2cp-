#include <i2cp/i2cp.h>
#include "client.hpp"
#include "session.hpp"

#include <sys/epoll.h>

#ifndef MAX_EPOLL_EVENTS
#define MAX_EPOLL_EVENTS 32
#endif

#include <unistd.h>
#include <cstdio>
#include <errno.h>

void i2cp_client::mainloop()
{
  epoll_event ev, events[MAX_EPOLL_EVENTS];
  int nfds;
  int epollfd = epoll_create(0);
  socklen_t slen = 0;
  switch (addr.sa_family)
  {
  case AF_INET:
    slen = sizeof(sockaddr_in);
    break;
  case AF_INET6:
    slen = sizeof(sockaddr_in6);
  default:
    break;
  }
  auto itr = sessions.begin();
  while(itr != sessions.end())
  {
    i2cp_session * s = *itr;
    int fd = s->CreateSocket(addr.sa_family);
    ev.data.ptr = s;
    if(fd != -1)
    {
      ++itr;
      if(connect(s->fd, &addr, slen) == 0)
      {
        // connected
        ev.events = EPOLLIN;
        s->connected = true;
      }
      else if(errno == EINPROGRESS)
      {
        // waiting for connect
        ev.events = EPOLLOUT;
      }
      else
      {
        // some other error
        perror("connect()");
        continue;
      }
      if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1)
        perror("epoll_ctl()");
    }
    else
    {
      itr = sessions.erase(itr);
    }
  }
  
  for (;;) {
    nfds = epoll_wait(epollfd, events, MAX_EPOLL_EVENTS, -1);
    if(nfds == -1) break;
    for(int n = 0; n < nfds ; ++n)
    {
      i2cp_session * s = static_cast<i2cp_session*>(events[n].data.ptr);
      auto e = events[n].events;
      if(s->connected)
      {
        // handle connected state
        if(e & (EPOLLHUP | EPOLLERR))
        {
          // connection broken
          ev.data.ptr = s;
          ev.events = (EPOLLIN | EPOLLOUT);
          epoll_ctl(epollfd, EPOLL_CTL_DEL, s->fd, &ev);
          s->Close();
          continue;
        }
        if(e & EPOLLIN)
        {
          s->Recv();
        }
        if(e & EPOLLOUT)
        {
          s->Send();
        }
      }
      else
      {
        if(e & (EPOLLHUP | EPOLLERR))
        {
          // connection broken
          s->Close();
        }
        else if(e & EPOLLOUT)
        {
          // connection made
          s->connected = true;
          ev.data.ptr = s;
          ev.events = EPOLLIN;
          if(epoll_ctl(epollfd, EPOLL_CTL_MOD, s->fd, &ev) == -1)
          {
            perror("epoll_ctl(EPOLL_CTL_MOD)");
          }
        }
      }
    }
  }
}


extern "C" {
  void i2cp_mainloop(struct i2cp_client * cl)
  {
    cl->mainloop();
  }
}
