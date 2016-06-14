#include <cstdarg>
#include <unistd.h>
#include <chrono>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include "base/logger.h"

namespace wtaf {
namespace base {

void Logger::init(LOG_LEVEL level, const std::string &app, const std::string &path)
{
    m_level = level;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);
    m_year.store(1900 + tm.tm_year, std::memory_order_relaxed);
    m_month.store(1 + tm.tm_mon, std::memory_order_relaxed); 
    m_day.store(tm.tm_mday, std::memory_order_relaxed);
    m_file_name = path + app;
    m_file_full_name = path + app + ".log";
    m_file = fopen(m_file_full_name.c_str(), "rb");
    
    if(m_file != NULL)
    {
        int32 fd = fileno(m_file);
        struct stat st;
        fstat(fd, &st);
        struct tm tm_1;
        localtime_r(&st.st_mtim.tv_sec, &tm_1);
        uint32 year = 1900 + tm_1.tm_year;
        uint32 month = 1 + tm_1.tm_mon;
        uint32 day = tm_1.tm_mday;
        
        if(year != m_year.load(std::memory_order_relaxed) 
		   || month != m_month.load(std::memory_order_relaxed) 
		   || day != m_day.load(std::memory_order_relaxed))
        {
            char file_name[64];
            sprintf(file_name, "%s_%d-%02d-%02d.log", m_file_name.c_str(), year, month, day);
            fclose(m_file);
            std::rename(m_file_full_name.c_str(), file_name);
        }
    }
    
    m_file = fopen(m_file_full_name.c_str(), "ab");
}

void Logger::_log(uint32 year, uint32 month, uint32 day, const char *format, ...)
{    
    if(year != m_year.load(std::memory_order_relaxed) || month != m_month.load(std::memory_order_relaxed)
       || day != m_day.load(std::memory_order_relaxed))
    {
        m_enter_num.fetch_sub(1, std::memory_order_relaxed);
        
        while(m_enter_num.load(std::memory_order_relaxed) > 0)
        {
            std::this_thread::yield();
        };
        
        std::lock_guard<std::mutex> guard(m_mutex);
        uint32 y = m_year.load(std::memory_order_relaxed);
        uint32 m = m_month.load(std::memory_order_relaxed);
        uint32 d = m_day.load(std::memory_order_relaxed);
        
        //double-checked
        if(year != y || month != m || day != d)
        {
            char file_name[64];
            sprintf(file_name, "%s_%d-%02d-%02d.log", m_file_name.c_str(), y, m, d);
            fclose(m_file);
            std::rename(m_file_full_name.c_str(), file_name);
            m_file = fopen(m_file_full_name.c_str(), "ab");
            m_year.store(year, std::memory_order_relaxed);
            m_month.store(month, std::memory_order_relaxed);
            m_day.store(day, std::memory_order_relaxed);
        }
        
        va_list args;
        va_start(args, format);
        vfprintf(m_file, format, args);
        va_end(args);
        fflush(m_file);
    }
    else
    {
        va_list args;
        va_start(args, format);
        vfprintf(m_file, format, args);
        va_end(args);
        fflush(m_file);
        m_enter_num.fetch_sub(1, std::memory_order_relaxed);
    }

    /**************** for debug ******************/
    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);
    /******************* for debug ******************/
}

}
}
