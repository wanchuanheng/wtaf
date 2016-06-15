

#ifndef WTAF__NET__ADDR_H_
#define WTAF__NET__ADDR_H_

#include <string>
#include "base/common.h"

namespace wtaf {
namespace net {

struct Addr
{
    std::string m_host;
    uint16 m_port;

    Addr() = default;
	
	Addr(std::string && host, uint16 port)
    {
        m_host = host;
        m_port = port;
    }
};

}
}

#endif
