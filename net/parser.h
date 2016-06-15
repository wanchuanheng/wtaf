

#ifndef WTAF__NET__PARSER_H_
#define WTAF__NET__PARSER_H_

#include <vector>
#include " task/scheduler.h "
#include " net/parser_task.h"

namespace wtaf {
namespace net {

class Parser
{
public:
    Parser(uint32 num);
    void wait();
    void start();
    void register_connection(std::shared_ptr<Connection> connection);
    
private:
    std::unique_ptr<wtaf::task::Scheduler> m_scheduler;
    std::vector<Parser_Task*> m_parser_tasks;
};

}
}

#endif
