/*
  i2cp name lookup util
  copy wrong you're mom 2014 Jeff
 */
#include <i2cp/i2cp.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>


void handle_lookup(i2cp_session * s, void * u, const char * fulldest);

struct demo_app;

struct lookup_job
{
  demo_app * app;
  std::string name;
};

struct demo_app
{
  i2cp_client * cl = nullptr;
  i2cp_session * s = nullptr;

  demo_app(const std::string & addr, uint16_t port)
  {
    sockaddr_in a;
    a.sin_port = htons(port);
    inet_pton(AF_INET, addr.c_str(), &a.sin_addr.s_addr);
    cl = new_i2cp_client((sockaddr*)&a);
    if(cl)
      s = i2cp_new_session(cl, nullptr);
  }

  void lookup(const std::string & name)
  {
    i2cp_lookup_async(s, name.c_str(), new lookup_job{this, name}, handle_lookup);
  }

  void run()
  {
    if(cl)
      i2cp_mainloop(cl);
  }
  
  ~demo_app()
  {
    if(s)
      free_i2cp_session(s);
    if(cl)
      free_i2cp_client(cl);
  }
};


void handle_lookup(i2cp_session * s, void * u, const char * fulldest)
{
  lookup_job * job = static_cast<lookup_job*>(u);
  if(fulldest)
    std::cout << "name " << job->name << " resolved to " << fulldest;
  else
    std::cout << "name " << job->name << " not found";
  delete job;
}

int main(int argc, char * argv[])
{
    if ( argc == 1 ) {
        std::cout << "usage: " << argv[0] << " name [ name ... ]" << std::endl;
        return 0;
    }
    demo_app app("127.0.0.1", 7654);
    int arg = 1;
    while(arg < argc)
    {
      app.lookup(argv[arg]);
      arg++;
    }
    app.run();
}
