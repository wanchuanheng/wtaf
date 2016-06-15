
#ifndef WTAF__NET__CONNECTION_H_
#define WTAF__NET__CONNECTION_H_

#include <memory>
#include "net/addr.h"
#include "net/message.h"
#include "net/message_chunk_queue.h"

namespace wtaf {
namespace net {

class Poller_Task;
class Parser_Task;
class Server;
class Message;

class Connection : public std::enable_shared_from_this<Connection>
{
    friend class Parser;
    friend class Poller_Task;
    friend class Parser_Task;
    friend class Server;
    friend class Client;
    
public:
    Connection(int32 fd, const Addr &peer_addr);
    ~Connection();
    uint64 id();
    void close();
    void send(const void *data, uint32 size);
    void send(rapidjson::Document &doc);
    const Addr& peer_addr();
    
private:
    void parse();
    int32 m_fd;
    uint64 m_id = 0;
    uint32 m_cur_msg_length = 0;
    Addr m_peer_addr;
    std::atomic<bool> m_closed {false};
    std::shared_ptr<Connection> m_self; //add ref
    Message_Chunk_Queue m_recv_msg_queue;
    Message_Chunk_Queue m_send_msg_queue;
    Poller_Task *m_poller_task = nullptr;
    Parser_Task *m_parser_task = nullptr;
    static fly::base::ID_Allocator m_id_allocator;
    std::function<void(std::shared_ptr<Connection>)> m_close_cb;
    std::function<void(std::shared_ptr<Connection>)> m_be_closed_cb;
    std::function<void(std::shared_ptr<Connection>)> m_init_cb;
    std::function<void(std::unique_ptr<Message>)> m_dispatch_cb;
};

}
}

#endif
