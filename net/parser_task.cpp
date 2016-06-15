
#include "net/parser_task.h"

namespace wtaf {
namespace net {

Parser_Task::Parser_Task(uint64 seq) : Task(seq)
{
}

void Parser_Task::push_connection(std::shared_ptr<Connection> connection)
{
    m_queue.push(connection);
}

void Parser_Task::run()
{
    while(std::shared_ptr<Connection> connection = m_queue.pop())
    {
        connection->parse();
    }
}

}
}
