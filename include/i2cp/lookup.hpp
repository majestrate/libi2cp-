#ifndef I2CP_LOOKUP_HPP
#define I2CP_LOOKUP_HPP
#include <i2cp/destination.hpp>
#include <string>


namespace i2cp 
{
    bool lookup(std::string name, destination_ptr & ptr, std::string i2cp_host="127.0.0.1", uint16_t i2cp_port=7654);

}

#endif
