#ifndef I2CP_CLIENT_HPP
#define I2CP_CLIENT_HPP
#include <memory>
#include <string>
#include <thread>
#include <future>
#include <i2cp/crypto.hpp>
#include <i2cp/message.hpp>
#include <i2cp/destination.hpp>
#include <i2cp/net.hpp>

namespace i2cp
{

    class client
    {
    public:
        client(std::string i2cp_host = "127.0.0.1", uint16_t i2cp_port = 7654);
        ~client();
        void Open(std::string keyfile);
        void Close();
    private:

        i2cp::crypto::PrivateSigningKey m_priv_sigkey;
        net::socket_t m_socket;
        std::thread m_thread;
        std::future<Message> m_msg_future;

        void mainloop();
        void load_keys(std::string fname);
    };

}

#endif
