#include "i2cp/util.hpp"
#include <chrono>
#include <array>
#include <cstring>
#include <netdb.h>
#include <sys/types.h>

std::string i2cp::util::utcnow()
{
    auto t = std::time(nullptr);
    std::array<char, 1024> buff;
    buff.fill(0);
    std::strftime(buff.data(), buff.size(), "%T", std::gmtime(&t));
    return std::string(buff.data());
}

bool i2cp::util::nslookup(std::string name, sockaddr * addr, bool v6)
{
    addrinfo hint;
    addrinfo * res = nullptr;
    std::memset(&hint, 0, sizeof(hint));
    hint.ai_family = v6 ? AF_INET6 : AF_INET;
    if(getaddrinfo(name.c_str(), nullptr, &hint, &res) == 0) {
        std::memcpy(addr, res->ai_addr, sizeof(*res->ai_addr));
        freeaddrinfo(res);
        return true;
    }
    return false;
}
