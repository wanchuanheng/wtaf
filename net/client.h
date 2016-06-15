

#ifndef WTAF__NET__CLIENT
#define WTAF__NET__CLIENT

#include "net/poller.h"
#include "net/parser.h"
#include "net/message.h"

namespace wtaf {
namespace net {

class Client
{
public:
    Client(const Addr &addr,
           std::function<void(std::shared_ptr<Connection>)> init_cb,
           std::function<void(std::unique_ptr<Message>)> dispatch_cb,
           std::function<void(std::shared_ptr<Connection>)> close_cb,
           std::function<void(std::shared_ptr<Connection>)> be_closed_cb,
           std::shared_ptr<Poller> poller, std::shared_ptr<Parser> parser);
    bool connect();
    uint64 id();
    
private:
    uint64 m_id;
    Addr m_addr;
    std::shared_ptr<Poller> m_poller;
    std::shared_ptr<Parser> m_parser;
    std::function<void(std::shared_ptr<Connection>)> m_close_cb;
    std::function<void(std::shared_ptr<Connection>)> m_be_closed_cb;
    std::function<void(std::shared_ptr<Connection>)> m_init_cb;
    std::function<void(std::unique_ptr<Message>)> m_dispatch_cb;
};

}
}

#endif
