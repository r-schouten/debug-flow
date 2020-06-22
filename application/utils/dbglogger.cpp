#include "dbglogger.h"

DbgLogger DbgLogger::staticDBGLogger;

DbgLogger::DbgLogger()
{

}

DbgLogger *DbgLogger::getStaticLogger()
{
    return &staticDBGLogger;
}
void DbgLogger::verbose(const char *classname, const char *functionName, const char *format,...)
{
    std::cout << "[verbose][" << classname << "][" << functionName << "] ";
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
    std::cout << std::endl;
    fflush(stdout);
}
void DbgLogger::debug(const char *classname, const char *functionName, const char *format,...)
{
    std::cout << "[debug][" << classname << "][" << functionName << "] ";
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
    std::cout << std::endl;
    fflush(stdout);
}
void DbgLogger::warning(const char *classname, const char *functionName, const char *format,...)
{
    std::cout << "[warning][" << classname << "][" << functionName << "] ";
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
    std::cout << std::endl;
    fflush(stdout);
}
void DbgLogger::error(const char *classname, const char *functionName, const char *format,...)
{
    std::cout << "[error][" << classname << "][" << functionName << "] ";
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
    std::cout << std::endl;
    fflush(stdout);
}
void DbgLogger::fatal(const char *classname, const char *functionName, const char *format,...)
{
    std::cout << "[fatal][" << classname << "][" << functionName << "] ";
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
    std::cout << std::endl;
    fflush(stdout);
}
void DbgLogger::printf(const char *format,...)
{
    va_list arglist;
    va_start( arglist, format );
    vprintf( format, arglist );
    va_end( arglist );
}
