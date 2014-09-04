#include "internal_util.hpp"
#include <cstring>
#include <sstream>
#include <iomanip>

namespace i2cp
{
    // TODO: endiness
    namespace util
    {

        uint32_t get_uint32(uint8_t * dataptr, size_t offset)
        {
            return  ( dataptr[offset+3] ) | 
                ( dataptr[offset+2] << 8 ) | 
                ( dataptr[offset+1] << 16 ) | 
                ( dataptr[offset] << 24 );
        }
        
        uint16_t get_uint16(uint8_t * dataptr, size_t offset)
        {
            return  ( dataptr[offset+1] ) | ( dataptr[offset] << 8 ) ;
        }

        size_t put_uint16(uint8_t * dataptr, size_t offset, uint16_t i)
        {
            dataptr[offset+1] =  i & 0x00ff;
            dataptr[offset] =  (i & 0xff00) >> 8;
            return 2;
        }

        size_t put_uint32(uint8_t * dataptr, size_t offset, uint32_t i)
        {
            dataptr[offset+3] = i & 0x000000ff;
            dataptr[offset+2] = (uint8_t)((i & 0x0000ff00) >> 8);
            dataptr[offset+1] = (uint8_t)((i & 0x00ff0000) >> 16);
            dataptr[offset] = (uint8_t)((i & 0xff000000) >> 24);
            return 4;
        }

        size_t put_i2cp_string(uint8_t * dataptr, size_t offset, std::string str)
        {
            size_t len = str.size();
            dataptr[offset++] = (uint8_t) len;
            std::memcpy(dataptr+offset, str.c_str(), len);
            return len + 1;
        }

        std::string get_i2cp_string(uint8_t * dataptr, size_t offset)
        {
            uint8_t len = dataptr[offset];
            return std::string((char*)dataptr,len);
        }


        std::string tohex(uint8_t * dataptr, size_t datalen)
        {
            std::stringstream ss;
            size_t idx = 0;
            while(idx < datalen) {
                ss << std::setw(2) << std::setfill('0') << std::hex << (int) dataptr[idx++];
                ss << ' ';
            }
            return ss.str();
        }


        // veratum from i2pd
        size_t base32_encode (const uint8_t * inBuf, size_t len, char * outBuf, size_t outLen)
        {
            size_t ret = 0, pos = 1;
            int bits = 8, tmp = inBuf[0];
            while (ret < outLen && (bits > 0 || pos < len))
            { 	
                if (bits < 5)
                {
                    if (pos < len)
                    {
                        tmp <<= 8;
                        tmp |= inBuf[pos] & 0xFF;
                        pos++;
                        bits += 8;
                    }
                    else // last byte
                    {
                        tmp <<= (5 - bits);
                        bits = 5;
                    }
                }	
		
                bits -= 5;
                int ind = (tmp >> bits) & 0x1F;
                outBuf[ret] = (ind < 26) ? (ind + 'a') : ((ind - 26) + '2');
                ret++;
            }
            return ret;
	}
    }
}
