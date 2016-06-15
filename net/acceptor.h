
#ifndef WTAF__NET__ACCEPTOR_H_
#define WTAF__NET__ACCEPTOR_H_

#include <memory>
#include <thread>
#include "net/connection.h"

namespace fly {
namespace net {

class Acceptor
{
public:
    Acceptor(const Addr &addr, std::function<void(std::shared_ptr<Connection>)> cb);
    bool start();
    void wait();
    
private:
    std::function<void(std::shared_ptr<Connection>)> m_cb;
    Addr m_listen_addr;
    std::thread m_thread;
};

}
}

#endif
