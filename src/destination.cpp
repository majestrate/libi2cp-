#include "i2cp/destination.hpp"
#include <i2cp/log.hpp>
#include "internal_util.hpp"


namespace i2cp
{

    certificate_t::certificate_t() :
        m_type(cert_type_t::NUL),
        m_length(0) {}

    certificate_t::certificate_t(buffer_t::iterator & itr) 
    {
        m_type = static_cast<cert_type_t>(*itr++);
        m_length = (*itr++) << 8 | *itr++;
        std::copy(itr, itr+m_length, m_data);
        I2CP_LOG("cert type ", m_type);
        I2CP_LOG("cert len ", m_length);
        
    }

    buffer_t certificate_t::Serialize() 
    {
        buffer_t ret(sizeof(m_length) + 1 + m_length);
        std::fill(ret.begin(), ret.end(), 0);
        ret[0] = m_type;
        i2cp::util::put_uint16(ret.data(), 1, m_length);
        std::copy(ret.data() + 3, ret.data() + 3 + m_length, m_data);
        return ret;
    }

    destination_t::destination_t(buffer_t & data) 
    {
        I2CP_LOG("dest size=", data.size());
        if(data.size() < 387 ) {
            throw std::runtime_error("invalid dest size: "+std::to_string(data.size()));
        }
        auto itr = data.begin();
        std::copy(itr, itr + 256, m_enckey.data());
        itr +=  256;
        std::copy(itr, itr + 128, m_sigkey.data());
        itr += 128;
        m_cert = certificate_t(itr);
        
    }

    destination_t::destination_t() 
    {
        m_enckey.fill(0);
        m_sigkey.fill(0);
    }

    destination_t::~destination_t() 
    {

    }

    buffer_t destination_t::Serialize() 
    {
        buffer_t cert = m_cert.Serialize();
        size_t dlen = cert.size() + 128 + 256;
        I2CP_LOG("serialize to ", dlen, " bytes");
        buffer_t ret(dlen);
        std::fill(ret.begin(), ret.end(), 0);
        auto itr = ret.begin();
        std::copy(m_enckey.begin(), m_enckey.end(), itr);
        itr += sizeof(m_enckey);
        std::copy(m_sigkey.begin(), m_sigkey.end(), itr);
        itr += sizeof(m_sigkey);
        std::copy(cert.begin(), cert.end(), itr);
        return ret;
    }

    std::string destination_t::Base32()
    {
        auto _dest = Serialize();
        I2CP_LOG("dest serialized ", i2cp::util::tohex(_dest.data(), _dest.size()));
        auto dest = i2cp::crypto::SHA256(_dest);
        
        buffer_t buff(dest.size() * 4);
        std::fill(buff.begin(), buff.end(), 0);
        auto len = i2cp::util::base32_encode(dest.data(), dest.size(),(char *) buff.data(), buff.size());
        return std::string((char * )buff.data(), len) + ".b32.i2p";
    }

}
