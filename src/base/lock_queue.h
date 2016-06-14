

#ifndef WTAF__BASE__LOCK_QUEUE
#define WTAF__BASE__LOCK_QUEUE

#include <mutex>
#include <deque>

namespace wtaf {
namespace base {

template<typename T>
class Lock_Queue
{
public:
    void push(T element)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_queue.push_back(element);
    }
    
    T pop()
    {
        std::lock_guard<std::mutex> guard(m_mutex);

        if(m_queue.empty())
        {
            return T();
        }
        
        T element = m_queue.front();
        m_queue.pop_front();
        
        return element;
    }
    
private:
    std::deque<T> m_queue;
    std::mutex m_mutex;
};

}
}

#endif
