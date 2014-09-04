#include "internal_message.hpp"
#include "internal_util.hpp"
#include <i2cp/log.hpp>

namespace i2cp
{
    
    std::string message_type_name(message_type_t type)
    {
        switch(type) {
        case CREATE_SESSION: return "CREATE_SESSION";
        case RECONFIG_SESSION: return "RECONFIG_SESSION";
        case DESTROY_SESSION: return "DESTROY_SESSION";
        case CREATE_LS: return "CREATE_LS";
        case SEND_MSG: return "SEND_MSG";
        case RECV_BEGIN: return "RECV_BEGIN";
        case RECV_END: return "RECV_END";
        case GET_BW_LIMIT: return "GET_BW_LIMIT";
        case SESSION_STATUS: return "SESSION_STATUS";
        case REQ_LS: return "REQ_LS";
        case MSG_STATUS: return "MSG_STATUS";
        case BW_LIMITS: return "BW_LIMITS";
        case ABUSE: return "ABUSE";
        case DISCONNECT: return "DISCONNECT";
        case MSG_PAYLOD: return "MSG_PAYLOAD";
        case GET_DATE: return "GET_DATE";
        case SET_DATE: return "SET_DATE";
        case DEST_LOOKUP: return "DEST_LOOKUP";
        case DEST_REPLY: return "DEST_REPLY";
        case SEND_MSG_EXPIRE: return "SEND_MSG_EXPIRE";
        case REQ_VLS: return "REQ_VLS";
        case HOST_LOOKUP: return "HOST_LOOKUP";
        case HOST_REPLY: return "HOST_REPLY";
        default: return "???";
        }
    }

    buffer_t pack_message(buffer_t & data, message_type_t type)
    {
        size_t len = data.size();
        I2CP_LOG("pack message of size ", len);
        I2CP_LOG("pack messgae of type ", message_type_name(type));
        buffer_t packed(len + 5);
        size_t idx = 0;
        std::fill(packed.begin(), packed.end(), 0);
        idx += i2cp::util::put_uint32(packed.data(), 0, (uint32_t) len);
        packed[idx++] = type;
        std::copy(data.begin(), data.end(), packed.begin() + idx);
        return packed;
    }
    
    buffer_t Message::Serialize() {            
        auto body = Pack(); 
        auto str = i2cp::util::tohex(body.data(), body.size());
        I2CP_LOG("serialize message body: ", str);
        return pack_message(body, m_type); 
    }



    DestinationLookupMessage::DestinationLookupMessage(std::string name, uint32_t timeout) : 
        Message(message_type_t::HOST_LOOKUP),
        m_name(name),
        m_timeout(timeout),
        m_sid(0xffff),
        m_rid(0),
        m_reqtype(1) {}

    buffer_t DestinationLookupMessage::Pack()
    {
        // TODO: HARD CODED
        buffer_t databuff(512);
        std::fill(databuff.begin(), databuff.end(), 0);
        size_t idx = 0;
        idx += i2cp::util::put_uint16(databuff.data(), idx, m_sid);
        idx += i2cp::util::put_uint32(databuff.data(), idx, m_rid);
        idx += i2cp::util::put_uint32(databuff.data(), idx, m_timeout);
        databuff[idx++] = 1;
        idx += i2cp::util::put_i2cp_string(databuff.data(), idx, m_name);
        databuff.resize(idx);
        return databuff;
    }


    bool HostReplyMessage::Success() 
    {
        return m_result == 0;
    }

    HostReplyMessage::HostReplyMessage(buffer_t & msg_body) : Message(message_type_t::HOST_REPLY)
    {
        m_sid = i2cp::util::get_uint16(msg_body.data(), 0);
        m_rid = i2cp::util::get_uint32(msg_body.data(), 2);
        m_result = msg_body[6];
        I2CP_LOG("host reply result ", (int)m_result);
        buffer_t dest_buffer(msg_body.size() - 7);
        std::copy(msg_body.begin() + 7, msg_body.end(), dest_buffer.begin());
        if (dest_buffer.size() > 0) { m_dest = destination_t(dest_buffer); }
    }

    GetDateMessage::GetDateMessage() {}

    GetDateMessage::GetDateMessage(buffer_t & data) {}

    GetDateMessage::~GetDateMessage() {}

}
