#include <i2cp/net.hpp>
#include <i2cp/util.hpp>
#include <i2cp/log.hpp>
#include <stdexcept>
#include <unistd.h>
#include "internal_util.hpp"

namespace i2cp
{
    namespace net
    {
        socket_t::socket_t() : fd(-1) {}
        socket_t::socket_t(std::string name, uint16_t port) {

            addr4 addr;
            I2CP_LOG("net lookup name ", name);
            if(!util::nslookup(name, addr)) { throw std::runtime_error("cannot resolve host: "+name); }
            addr.set_port(port);
            I2CP_LOG("socket()");
            fd = socket(addr.af(), SOCK_STREAM, 0);
            if(fd == -1 ) {
                I2CP_LOG("failed socket()");
                throw std::runtime_error("cannot make socket");
            } else {
                I2CP_LOG("connect()");
                if ( connect(fd, addr, addr.size()) == -1) {
                    close(fd);
                    I2CP_LOG("failed connect()");
                    throw std::runtime_error("cannot connect to "+name+std::to_string(port));
                }
            } 
        }

        socket_t::~socket_t() 
        { 
            Close(); 
            I2CP_LOG("~socket_t");
        }

        size_t socket_t::Recv(uint8_t * dataptr, size_t datalen)
        {
            I2CP_LOG("recv ", datalen, " bytes");
            size_t len = recv(fd, dataptr, datalen, 0);
            auto str = i2cp::util::tohex(dataptr, len);
            I2CP_LOG("got ", str);
            return len;
        }
        
        void socket_t::Send(uint8_t * dataptr, size_t datalen)
        {
            I2CP_LOG("send ",datalen, " bytes");
            auto str = i2cp::util::tohex(dataptr, datalen);
            I2CP_LOG("send ", str);
            send(fd, dataptr, datalen, 0);
        }

        void socket_t::Close()
        {            
            I2CP_LOG("Close()");
            if(fd != -1) { 
                I2CP_LOG("closing");
                close(fd); 
                I2CP_LOG("closed");
                fd = -1; 
            }
        }

    }

}
