

#ifndef WTAF__NET__POLLER_TASK_H_
#define WTAF__NET__POLLER_TASK_H_

#include "task/loop_task.h"
#include "net/connection.h"
#include "base/lock_queue.h"

namespace wtaf {
namespace net {

class Poller_Task : public wtaf::task::Loop_Task
{
public:
    Poller_Task(uint64 seq);
    void register_connection(std::shared_ptr<Connection> connection);
    virtual void run_in_loop() override;
    void close_connection(std::shared_ptr<Connection> connection);
    void write_connection(std::shared_ptr<Connection> connection);
    
private:
    void do_close();
    void do_write();
    void do_write(std::shared_ptr<Connection> connection);
    int32 m_fd;
    int32 m_close_event_fd;
    int32 m_write_event_fd;
    std::unique_ptr<Connection> m_close_udata;
    std::unique_ptr<Connection> m_write_udata;
    fly::base::Lock_Queue< std::shared_ptr<Connection> > m_close_queue;
    fly::base::Lock_Queue< std::shared_ptr<Connection> > m_write_queue;
};

}
}

#endif
