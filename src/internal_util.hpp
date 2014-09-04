#ifndef I2CP_INTERNAL_UTIL_HPP
#define I2CP_INTERNAL_UTIL_HPP
#include <string>

namespace i2cp
{
    namespace util
    {
        uint16_t get_uint16(uint8_t * data, size_t offset);
        uint32_t get_uint32(uint8_t * data, size_t offset);
        
        size_t put_uint16(uint8_t * data, size_t offset, uint16_t i);
        size_t put_uint32(uint8_t * data, size_t offset, uint32_t i);


        std::string get_i2cp_string(uint8_t * data, size_t offset);
        size_t put_i2cp_string(uint8_t * data, size_t offset, std::string str);


        std::string tohex(uint8_t * data, size_t datalen);

        // taken from i2pd
        size_t base32_encode(const uint8_t * dataptr, size_t len, char * outptr, size_t outlen);
    }
}

#endif
