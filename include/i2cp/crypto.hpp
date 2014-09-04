#ifndef I2CP_CRYPTO_HPP
#define I2CP_CRYPTO_HPP

#include <cryptopp/dsa.h>
#include <cryptopp/dh.h> 

#include <i2cp/types.hpp>

#include <array>

namespace i2cp
{
    namespace crypto 
    {

        
        
        typedef std::array<i2cp::i2cp_byte_t, 128> PublicSigningKey;
        typedef std::array<i2cp::i2cp_byte_t, 20> PrivateSigningKey;

        typedef std::array<i2cp::i2cp_byte_t, 40> DSA_Signature_t;

        /**
           sign data with i2p's dsa sha1
        */
        DSA_Signature_t DSA_SHA1_SIGN(PrivateSigningKey & privkey, i2cp::buffer_t & data);

        /**
           verify i2p dsa sha1 signature
         */
        bool DSA_SHA1_VERIFY(PublicSigningKey & pubkey, i2cp::buffer_t & data, DSA_Signature_t & sig);

        typedef std::tuple<PublicSigningKey, PrivateSigningKey> DSAKeyPair;
        typedef std::shared_ptr<DSAKeyPair> DSAKeyPair_ptr;

        DSAKeyPair_ptr DSA_GENERATE();
        
        /**
           load dsa keypair from buffer
         */
        DSAKeyPair_ptr DSA_KP_LOAD(i2cp::buffer_t & data);
        
        /**
           dump dsa keypair to buffer
         */
        i2cp::buffer_t DSA_KP_DUMP(DSAKeyPair_ptr keypair);

        typedef std::array<i2cp::i2cp_byte_t, 20> SHA1_Digest_t;
        typedef std::array<i2cp::i2cp_byte_t, 32> SHA256_Digest_t;
        
        /**
           sha1 wrapper
         */
        SHA1_Digest_t SHA1(i2cp::buffer_t & data);

        /**
           sha256 wrapper
         */
        SHA256_Digest_t SHA256(i2cp::buffer_t & data);


        typedef std::array<i2cp_byte_t, 256> PublicEncryptionKey;
        typedef std::array<i2cp_byte_t, 256> PrivateEncryptionKey;

        typedef std::tuple<PublicEncryptionKey, PrivateEncryptionKey> EGLKeyPair;
        typedef std::shared_ptr<EGLKeyPair> EGLKeyPair_ptr;

        EGLKeyPair_ptr EGL_GENERATE();

        bool EGL_DECRYPT(PublicEncryptionKey & pubkey, buffer_t & data, buffer_t & result);
        buffer_t EGL_ENCRYPT(PrivateEncryptionKey & privkey, buffer_t & data);
        

        void RANDOMIZE(i2cp::buffer_t & buffer);

        i2cp::buffer_t RANDOM(size_t len);

    }
}


#endif
