#ifndef I2CP_DESTINATION_HPP
#define I2CP_DESTINATION_HPP
#include <string>
#include <memory>
#include <i2cp/common.hpp>
#include <i2cp/crypto.hpp>

namespace i2cp
{
    class destination_t;
    
    typedef std::shared_ptr<destination_t> destination_ptr;

    constexpr size_t MAX_CERT_SIZE = pow(2, 8);

    enum cert_type_t {
        NUL = 0,
        HASHCASH = 1,
        HIDDEN = 2,
        SIGNED = 3,
        MULTIPLE = 4,
        KEY = 5
    };

    class certificate_t {

    public:
        certificate_t(); // null cert
        certificate_t(buffer_t::iterator & itr);
        /**
           convert to buffer_t
         */
        buffer_t Serialize();
        
    private:
        cert_type_t m_type;
        uint16_t m_length;
        uint8_t m_data[MAX_CERT_SIZE];
    };

    class destination_t
    {
    public:
        destination_t();
        destination_t(buffer_t & data);
        ~destination_t();
        std::string Base32();
        static destination_ptr LoadFile(std::string fname);
        static destination_ptr LoadB64(std::string b64);
        
        /**
           convert to buffer_t
         */
        buffer_t Serialize();

    private:
        i2cp::crypto::PublicEncryptionKey m_enckey;
        i2cp::crypto::PublicSigningKey m_sigkey;
        certificate_t m_cert;
    };

}

#endif
