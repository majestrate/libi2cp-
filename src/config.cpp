#include "config.hpp"


extern "C" {

  struct i2cp_session_config * new_i2cp_session_config()
  {
    return new i2cp_session_config;
  };

  void free_i2cp_session_config(struct i2cp_session_config * conf)
  {
    delete conf;
  }

  struct i2cp_session_config * copy_i2cp_session_config(struct i2cp_session_config * conf)
  {
    if(conf)
    {
      auto copy = new i2cp_session_config;
      for (const auto & entry : conf->options)
        copy->options[entry.first] = entry.second;
      return copy;
    }
    return nullptr;
  }
}
