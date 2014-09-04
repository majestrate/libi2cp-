#ifndef I2CP_MESSAGE_HPP
#define I2CP_MESSAGE_HPP
#include "internal_common.hpp"
#include <i2cp/destination.hpp>
#include <string>

namespace i2cp
{
    typedef uint16_t session_id_t;
    typedef uint32_t request_id_t;

    enum message_type_t {
        CREATE_SESSION = 1,
        RECONFIG_SESSION = 2,
        DESTROY_SESSION = 3,
        CREATE_LS = 4,
        SEND_MSG = 5,
        RECV_BEGIN = 6,
        RECV_END = 7,
        GET_BW_LIMIT = 8,
        SESSION_STATUS = 20,
        REQ_LS = 21,
        MSG_STATUS = 22,
        BW_LIMITS = 23,
        ABUSE = 29,
        DISCONNECT = 30,
        MSG_PAYLOD = 31,
        GET_DATE = 32,
        SET_DATE = 33,
        DEST_LOOKUP = 34,
        DEST_REPLY = 35,
        SEND_MSG_EXPIRE = 36,
        REQ_VLS = 37,
        HOST_LOOKUP = 38,
        HOST_REPLY = 39

    };

    std::string message_type_name(message_type_t type);


    buffer_t pack_message(buffer_t &data, message_type_t type);

    class Message
    {
    public:
        Message(message_type_t type) : m_type(type) {}
        virtual ~Message() {}
        virtual buffer_t Pack() {return buffer_t(); }
        buffer_t Serialize();
    protected:
        message_type_t m_type;
    };

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
        bool Success() { return m_result == 0; }

    private:
        session_id_t m_sid;
        request_id_t m_rid;
        uint8_t m_result;
        destination_t m_dest;

    };

}

#endif
