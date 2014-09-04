#include "base_test.hpp"
#include <i2cp/crypto.hpp>

int main(int argc, char * argv[])
{
    std::cout << "generate" << std::endl;
    auto keys = i2cp::crypto::DSA_GENERATE();

    std::cout << "get pubkey" << std::endl;
    auto pubkey = std::get<0>(*keys);

    std::cout << "get privkey" << std::endl;
    auto privkey = std::get<1>(*keys);

    std::cout << "gen random data" << std::endl;
    auto data = i2cp::crypto::RANDOM(128);

    std::cout << "sign" << std::endl;
    auto sig = i2cp::crypto::DSA_SHA1_SIGN(privkey, data);

    std::cout << "verify" << std::endl;
    if (! i2cp::crypto::DSA_SHA1_VERIFY(pubkey, data, sig) ) {
        std::cout << "FAILED TO VERIFY" << std::endl;
        return 1;
    }
    std::cout << "done" << std::endl;
    return 0;
}
