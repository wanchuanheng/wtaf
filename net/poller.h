

#ifndef WTAF__NET__POLLER_H_
#define WTAF__NET__POLLER_H_

#include <vector>
#include "task/scheduler.h"
#include "net/poller_task.h"

namespace wtaf {
namespace net {

class Poller
{
public:
    Poller(uint32 num);
    void wait();
    void start();
    void register_connection(std::shared_ptr<Connection> connection);
    
private:
    std::unique_ptr<wtaf::task::Scheduler> m_scheduler;
    std::vector<Poller_Task*> m_poller_tasks;
};

}
}

#endif
