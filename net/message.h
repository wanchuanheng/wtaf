

#ifndef WTAF__NET__MESSAGE_H_
#define WTAF__NET__MESSAGE_H_

#include <memory>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "base/common.h"

namespace wtaf {
namespace net {

class Connection;

class Message
{
    friend class Connection;
    
public:
    Message(std::shared_ptr<Connection> connection);
    rapidjson::Document& doc();
    const std::string& raw_data();
    uint32 type();
    uint32 cmd();
    uint32 length();
    std::shared_ptr<Connection> get_connection();
    
private:
    rapidjson::Document m_doc;
    std::shared_ptr<Connection> m_connection;
    std::string m_raw_data;
    uint32 m_length;
    uint32 m_type;
    uint32 m_cmd;
};

}
}

#endif
