

#ifndef WTAF__NET__SERVER
#define WTAF__NET__SERVER

#include "net/acceptor.h"
#include "net/poller.h"
#include "net/parser.h"
#include "net/message.h"

namespace wtaf {
namespace net {

class Server
{
public:
    Server(const Addr &addr,
           std::function<bool(std::shared_ptr<Connection>)> allow_cb,
           std::function<void(std::shared_ptr<Connection>)> init_cb,
           std::function<void(std::unique_ptr<Message>)> dispatch_cb,
           std::function<void(std::shared_ptr<Connection>)> close_cb,
           std::function<void(std::shared_ptr<Connection>)> be_closed_cb,
           std::shared_ptr<Poller> poller, std::shared_ptr<Parser> parser);
    Server(const Addr &addr,
           std::function<bool(std::shared_ptr<Connection>)> allow_cb,
           std::function<void(std::shared_ptr<Connection>)> init_cb,
           std::function<void(std::unique_ptr<Message>)> dispatch_cb,
           std::function<void(std::shared_ptr<Connection>)> close_cb,
           std::function<void(std::shared_ptr<Connection>)> be_closed_cb,
           uint32 poller_num = 1, uint32 parser_num = 1);
    void wait();
    bool start();
    
private:
    std::unique_ptr<Acceptor> m_acceptor;
    std::shared_ptr<Poller> m_poller;
    std::shared_ptr<Parser> m_parser;
};

}
}

#endif
