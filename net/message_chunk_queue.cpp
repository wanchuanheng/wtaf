

#include "net/message_chunk_queue.h"

namespace wtaf {
namespace net {

void Message_Chunk_Queue::push_back(Message_Chunk *message_chunk)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_queue.push_back(message_chunk);
    m_length += message_chunk->length();
}

void Message_Chunk_Queue::push_front(Message_Chunk *message_chunk)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_queue.push_front(message_chunk);
    m_length += message_chunk->length();
}

uint32 Message_Chunk_Queue::length()
{
    return m_length;
}

Message_Chunk* Message_Chunk_Queue::pop()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    
    if(m_queue.empty())
    {
        return nullptr;
    }
    
    Message_Chunk* message_chunk = m_queue.front();
    m_queue.pop_front();
    m_length -= message_chunk->length();
    
    return message_chunk;
}

}
}
