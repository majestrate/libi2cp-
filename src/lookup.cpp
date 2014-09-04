#include <i2cp/log.hpp>
#include <i2cp/lookup.hpp>
#include <i2cp/net.hpp>
#include "internal_message.hpp"
#include "internal_common.hpp"
#include "internal_util.hpp"


namespace i2cp
{
    bool lookup(std::string name, destination_ptr & ptr, std::string i2cp_host, uint16_t i2cp_port)
    {

        I2CP_LOG("resolve ", name);
        i2cp::DestinationLookupMessage msg(name);

        I2CP_LOG("connect to ", i2cp_host, " port ", i2cp_port);
        net::socket_t sock(i2cp_host, i2cp_port);

        buffer_t data = msg.Serialize();

        sock.Send(&PROTOCOL_BYTE, 1);
        sock.Send(data.data(), data.size());

        buffer_t hdr(5);
        std::fill(hdr.begin(), hdr.end(), 0);
        sock.Recv(hdr.data(), 5);
        uint32_t msgsize = i2cp::util::get_uint32(hdr.data(),0);
        buffer_t msg_body(msgsize);
        sock.Recv(msg_body.data(), msg_body.size());
        message_type_t type = static_cast<message_type_t>(hdr[4]);
        
        I2CP_LOG("got message of size ", msgsize);
        I2CP_LOG("got message of type ", message_type_name(type));
        HostReplyMessage rpl;
        destination_ptr dest = nullptr;
        switch(type) {
        case message_type_t::DISCONNECT:
            I2CP_LOG("disconnected: ", i2cp::util::get_i2cp_string(msg_body.data(), 0));
            break;
        case message_type_t::HOST_REPLY:
            rpl = HostReplyMessage(msg_body);
            if (rpl.Success()) {
                dest = std::make_shared<destination_t>(rpl.GetDestination());
                std::swap(ptr, dest);
            }
        default:
            break;
        }

        return rpl.Success();
    }

}
