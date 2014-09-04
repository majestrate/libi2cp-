#ifndef I2CP_UTIL_HPP
#define I2CP_UTIL_HPP
#include <string>
#include <sys/socket.h>

namespace i2cp
{
    namespace util
    {        
        std::string utcnow();
        bool nslookup(std::string name, sockaddr * addr, bool v6=false);
    }
}




#endif
