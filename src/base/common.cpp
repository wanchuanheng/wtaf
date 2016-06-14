#include <random>
#include "base/common.hpp"
#include <limits> 

namespace wtaf{
namespace base{

uint64 ID_Allocator::new_id()
{
    if(m_id.load(std::memory_order_relaxed) >=  std::numeric_limits<unsigned long int>::max())
    {
        m_id.store(1, std::memory_order_relaxed);
    }
    
    return m_id.fetch_add(1, std::memory_order_relaxed);
}

uint32 random_32()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());

    return mt();
}

uint64 random_64()
{
    static std::random_device rd;
    static std::mt19937_64 mt(rd());
    
    return mt();
}

uint32 random_between(uint32 min, uint32 max)
{
    if(min == max)
    {
        return min;
    }

    if(min > max)
    {
        std::swap(min, max);
    }
    
    const uint32 diff = max - min + 1;
    
    return min + random_32() % diff;
}

bool rate_by_percent(uint32 rate)
{
    return random_between(1, 100) <= rate;
}

bool rate_by_thousand(uint32 rate)
{
    return random_between(1, 1000) <= rate;
}




}


}
#endif
