

#ifndef WTAF__NET__MESSAGE_CHUNK_H_
#define WTAF__NET__MESSAGE_CHUNK_H_

#include <vector>
#include " base/common.h"

namespace wtaf {
namespace net {

class Message_Chunk
{
public:
    Message_Chunk(uint32 size);
    char* read_ptr();
    void read_ptr(uint32 count);
    char* write_ptr();
    void write_ptr(uint32 count);
    uint32 length();
    
private:
    std::vector<char> m_data;
    uint32 m_write_pos = 0;
    uint32 m_read_pos = 0;
};

}
}

#endif
