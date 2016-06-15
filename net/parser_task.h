

#ifndef WTAF__NET__PARSER_TASK_H_
#define WTAF__NET__PARSER_TASK_H_

#include "base/block_queue.h"
#include "task/task.h"
#include "net/connection.h"

namespace wtaf {
namespace net {

class Parser_Task : public wtaf::task::Task
{
public:
    Parser_Task(uint64 seq);
    virtual void run() override;
    void push_connection(std::shared_ptr<Connection> connection);
    
private:
    wtaf::base::Block_Queue< std::shared_ptr<Connection> > m_queue;
};

}
}

#endif
