#ifndef I2CP_LOG_HPP
#define I2CP_LOG_HPP
#include <iostream>
#include <chrono>
#include <sstream>
#include <array>
#include <i2cp/util.hpp>

namespace i2cp 
{ 
    
    template<typename Val> void _log(std::stringstream & ss, Val arg)
    {
        ss << arg;
    }
        
    template<typename Val, typename... Args> void _log(std::stringstream & ss, Val arg, Args ... args)
    {
        _log(ss, arg);
        _log(ss, args...);
    }
    
    template <typename... Args> void _log(std::ostream & out, Args... args)
    {
        std::stringstream ss;
        _log(ss, args...);
        out << ss.str() << std::flush;
    }
    
    
    template <typename... Args> void __log(std::ostream & out, Args... args) 
    {
        std::stringstream ss;
        ss << "[" << util::utcnow() << "] ";
        _log(out, ss.str());
        _log(out, args...);
        _log(out, "\n");
    }

    template <typename... Args> void __log(Args... args)
    {
        __log(std::cerr, args...);
    }


}
#ifndef DEBUG_I2CP
#define I2CP_LOG(x...) 
#else
#define I2CP_LOG(x...) i2cp::__log(__FILE__, ":", __LINE__, " ", x)
#endif

#endif
