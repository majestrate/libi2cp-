#ifndef I2CP_INTERNAL_MESSAGE_HPP
#define I2CP_INTERNAL_MESSAGE_HPP
#include <i2cp/message.hpp>
#include <i2cp/destination.hpp>
#include <string>
#include <fstream>
#include "internal_common.hpp"

namespace i2cp
{
    typedef uint16_t session_id_t;
    typedef uint32_t request_id_t;


    std::string message_type_name(message_type_t type);

    buffer_t pack_message(buffer_t &data, message_type_t type);


    class DestinationLookupMessage : public Message
    {
    public:
        DestinationLookupMessage(std::string name, uint32_t timeout=10000);
        virtual ~DestinationLookupMessage() {}
        virtual buffer_t Pack();
    private:
        std::string m_name;
        uint32_t m_timeout;
        session_id_t m_sid;
        request_id_t m_rid;
        uint8_t m_reqtype;
    };
    
    class HostReplyMessage : public Message 
    {
    public:
        HostReplyMessage(buffer_t & msg_body);
        HostReplyMessage() : Message(message_type_t::HOST_REPLY) {}

        destination_t GetDestination() { return m_dest; }
        request_id_t GetRequestID() { return m_rid; }
        session_id_t GetSessionID() { return m_sid; }
        bool Success();

    private:
        session_id_t m_sid;
        request_id_t m_rid;
        uint8_t m_result;
        destination_t m_dest;

    };

    class GetDateMessage : public Message
    {
    public:
        GetDateMessage();
        GetDateMessage(buffer_t & data);
        virtual ~GetDateMessage();
    };

}

#endif
