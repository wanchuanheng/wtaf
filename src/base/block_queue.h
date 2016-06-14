#ifndef WTAF_BASE_BLOCK_QUEUE_
#define WTAF_BASE_BLOCK_QUEUE_


#include <mutex>
#include <deque>
#include <condition_variable>

namespace wtaf{
namespace base{



template<typename T>
class Block_Queue{
public:
	Block_Queuen(const Block_Queue& rhs) = deleted;
	Block_Queuen& operator=(const Block_Queue& rhs) = deleted; 
	

	void push(T element)
	{
		
		
		std::unique_lock<std::mutex> locker(m_mutex);
		bool empty = m_queue.empty();
		m_queue.push_back(element);
		
		if(empty)
		{
			locker.unlock();
			m_cond.notify_one();
		}
		else{
			locker.unlock();
		}
	}

	T pop()
	{
		std::unique_lock<std::mutex> locker(m_mutex);
       		m_cond.wait(locker, [&]{return !m_queue.empty();});
       		T element = m_queue.front();
        	m_queue.pop_front();

		return element;
	}
	
	size_t size() const
	{
		std::lock_guard<std::mutex> locker (_mutex);  
        	return m_queue.size(); 
	}
	
	private:
		std::deque<T> m_queue;
    		mutable std::mutex m_mutex;
		std::condition_variable m_cond;
};

}
}

#endif
