#ifndef I2CP_NET_HPP
#define I2CP_NET_HPP
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace i2cp
{
    namespace net
    {
        struct addr4 
        {
            addr4() {
                std::memset(&addr, 0, sizeof(addr));
            }

            void set_port(uint16_t port) {
                addr.sin_port = htons(port);
            }
            
            uint16_t get_port() {
                return ntohs(addr.sin_port);
            }

            operator sockaddr_in * () {
                return &addr;
            }
            
            operator sockaddr * () {
                return (sockaddr *) &addr;
            }
            
            operator in_addr * () {
                return &addr.sin_addr;
            }
            
            size_t size() {
                return sizeof(addr);
            }

            int af() {
                return AF_INET;
            }

            sockaddr_in addr;

        };

        struct addr6
        {

            addr6() {
                std::memset(&addr, 0, sizeof(addr));
            }

            void set_port(uint16_t port) {
                addr.sin6_port = htons(port);
            }
            
            uint16_t get_port() {
                return ntohs(addr.sin6_port);
            }

            operator sockaddr_in6 * () {
                return &addr;
            }
            
            operator sockaddr * () {
                return (sockaddr *) &addr;
            }
            
            operator in6_addr * () {
                return &addr.sin6_addr;
            }
            
            size_t size() {
                return sizeof(addr);
            }
            
            int af() {
                return AF_INET6;
            }

            sockaddr_in6 addr;

        };
        
        class socket_t
        {
        public:
            socket_t();
            socket_t(std::string name, uint16_t port);
            ~socket_t();

            size_t Recv(uint8_t * dataptr, size_t dlen);
            void Send(uint8_t * dataptr, size_t dlen);
            void Close();
            
        private:
            int fd;
        };
    }
}

#endif
