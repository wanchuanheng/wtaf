

#include "net/message_chunk.h"

namespace wtaf {
namespace net {

Message_Chunk::Message_Chunk(uint32 size)
{
    m_data.resize(size + 1, 0);
}

uint32 Message_Chunk::length()
{
    return m_write_pos - m_read_pos;
}

char* Message_Chunk::read_ptr()
{
    return &m_data[m_read_pos];
}

void Message_Chunk::read_ptr(uint32 count)
{
    m_read_pos += count;
}

char* Message_Chunk::write_ptr()
{
    return &m_data[m_write_pos];
}

void Message_Chunk::write_ptr(uint32 count)
{
    m_write_pos += count;
}

}
}
