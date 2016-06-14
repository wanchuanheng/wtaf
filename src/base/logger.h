
#ifndef WTAF__BASE__LOGGER
#define WTAF__BASE__LOGGER

#include <cstdio>
#include <atomic>
#include <string>
#include <mutex>
#include <sys/time.h>
#include "base/common.h"
#include "base/singleton.h"

namespace wtaf {
namespace base {

enum LOG_LEVEL
{
    INFO,
	DEBUG,
    WARN,
    ERROR,
    FATAL
};

#define START_YEAR 1970
#define MAX_LINE_LOG 10240

class Logger : public Singleton<Logger>
{
public:
    void init(LOG_LEVEL level, const std::string &app, const std::string &path);
    void _log(uint32 year, uint32 month, uint32 day, const char *format, ...);
    
    bool _enter(LOG_LEVEL level)
    {
        if(level < m_level)
        {
            return false;
        }
        
        m_enter_num.fetch_add(1, std::memory_order_relaxed);

        return true;
    }
	
	void log_print(LOG_LEVEL level, format, ...)
	{
		if(wtaf::base::Logger::instance()->_enter(level)) 
		{ 
			char _format[MAX_LINE_LOG]; 
			struct timeval _tv; 
			gettimeofday(&_tv, NULL); 
			struct tm _tm; 
			localtime_r(&_tv.tv_sec, &_tm); 
			sprintf(_format, "%d-%02d-%02d %02d:%02d:%02d.%06ld |debug| %s:%d {%s}\n", START_YEAR + _tm.tm_year, 1 + _tm.tm_mon, _tm.tm_mday, _tm.tm_hour, 
					_tm.tm_min, _tm.tm_sec, _tv.tv_usec, __FILE__, __LINE__, format); 
			_log(START_YEAR + _tm.tm_year, 1 + _tm.tm_mon, _tm.tm_mday, _format, ##__VA_ARGS__); 
		}
	}
    
private:
    LOG_LEVEL m_level;
    std::string m_file_name;
    std::string m_file_full_name;
    FILE *m_file;
    std::atomic<uint32> m_year;
    std::atomic<uint32> m_month;
    std::atomic<uint32> m_day;
    std::atomic<uint32> m_enter_num {0};
    std::mutex m_mutex;
};

}
}

#define LOG_DEBUG(format, ...) wtaf::base::Logger::instance()->log_print(wtaf::base::DEBUG,format, ... );
#define LOG_INFO(format, ...)  wtaf::base::Logger::instance()->log_print(wtaf::base::INFO,format, ... );
#define LOG_WARN(format, ...)  wtaf::base::Logger::instance()->log_print(wtaf::base::WARN,format, ... );
#define LOG_ERROR(format, ...)  wtaf::base::Logger::instance()->log_print(wtaf::base::ERROR,format, ... );
#define LOG_FATAL(format, ...)  wtaf::base::Logger::instance()->log_print(wtaf::base::FATAL,format, ... );


#endif
