

#include "net/message.h"

namespace wtaf {
namespace net {

Message::Message(std::shared_ptr<Connection> connection)
{
    m_connection = connection;
}

rapidjson::Document& Message::doc()
{
    return m_doc;
}

uint32 Message::type()
{
    return m_type;
}

uint32 Message::cmd()
{
    return m_cmd;
}

uint32 Message::length()
{
    return m_length;
}

const std::string& Message::raw_data()
{
    return m_raw_data;
}

std::shared_ptr<Connection> Message::get_connection()
{
    return m_connection;
}

}
}
