#ifndef _LIBI2CP_CONFIG_HPP
#define _LIBI2CP_CONFIG_HPP
#include <i2cp/i2cp.h>
#include <map>

struct i2cp_session_config
{
  std::map<std::string, std::string> options;
};


#endif
