#include <i2cp/client.hpp>
#include <i2cp/log.hpp>
#include <memory>
#include <functional>
#include "internal_message.hpp"
#include "common.hpp"

namespace i2cp
{

    client::client(std::string i2cp_host, uint16_t i2cp_port) 
    {
        I2CP_LOG("client() host="+i2cp_host+" port="+std::to_string(i2cp_port));      
        m_socket = net::socket_t(i2cp_host, i2cp_port);
        m_thread = std::thread(std::bind(&client::mainloop, this));
    }
    client::~client() 
    {
        I2CP_LOG("~client()");
    }

    void client::mainloop()
    {
    }
    
    void client::load_keys(std::string fname)
    {
        I2CP_LOG("load_keys() fname=",fname);
        std::ifstream ifs(fname, std::ifstream::binary);
        if (ifs && ifs.is_open())
        {
            ifs.read((char*)m_priv_sigkey.data(), sizeof(m_priv_sigkey));
        } else {
            throw std::runtime_error("cannot load key "+fname); 
        }
        I2CP_LOG("loaded keys");
    }
 
    void client::Open(std::string keyfile) 
    {
        I2CP_LOG("Open()");
        load_keys(keyfile);
        Message_ptr msg = std::make_shared<GetDateMessage>();
    }

    void client::Close()
    {
        I2CP_LOG("thread.join()");
        m_thread.join();
        I2CP_LOG("socket.close()");
        m_socket.Close();
        
    }
    
}
