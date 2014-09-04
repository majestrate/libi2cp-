#ifndef I2CP_MESSAGE_HPP
#define I2CP_MESSAGE_HPP
#include <i2cp/common.hpp>
#include <memory>

namespace i2cp
{
    enum message_type_t 
    {
        NO_MSG_TYPE = 0,
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
    
    
    class Message
    {
    public:
        Message() : m_type(NO_MSG_TYPE) {}
        Message(message_type_t type) : m_type(type) {}
        virtual ~Message() {}
        virtual buffer_t GetRaw() { return buffer_t(); }
        virtual buffer_t Pack() {return buffer_t(); }
        buffer_t Serialize();
        message_type_t Type() { return m_type; }
    protected:
        message_type_t m_type;
    };

    typedef std::shared_ptr<Message> Message_ptr;

}

#endif
