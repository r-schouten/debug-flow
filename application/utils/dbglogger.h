#pragma once

#include <QDebug>
#include <iostream>

#define CLASSNAME (staticMetaObject.className())

//#define fatalf(classname,function, ...) {std::cout << "[fatal][" << classname << "][" << function << "] "; printf(__VA_ARGS__);std::cout << std::endl;fflush(stdout);}
//#define errorf(classname,function, ...) {std::cout << "[error][" << classname << "][" << function << "] "; printf(__VA_ARGS__);std::cout << std::endl;fflush(stdout);}
//#define warningf(classname,function, ...) {std::cout << "[warning][" << classname << "][" << function << "] "; printf(__VA_ARGS__);std::cout << std::endl;fflush(stdout);}
//#define debugf(classname,function, ...) {std::cout << "[debug][" << classname << "][" << function << "] "; printf(__VA_ARGS__);std::cout << std::endl;fflush(stdout);}
//#define verbosef(classname,function, ...) {std::cout << "[verbose][" << classname << "][" << function << "] "; printf(__VA_ARGS__);std::cout << std::endl;fflush(stdout);}


using std::string;
class DbgLogger
{
public:
    DbgLogger();
    static DbgLogger* getStaticLogger();
    void printf(const char *format,...);

    void verbose(const char *classname, const char *functionName, const char *format...);
    void debug(const char *classname, const char *functionName, const char *format...);
    void warning(const char *classname, const char *functionName, const char *format,...);
    void error(const char *classname, const char *functionName, const char *format...);
    void fatal(const char *classname, const char *functionName, const char *format...);
private:
    static DbgLogger staticDBGLogger;
    string flowName;
    bool hasFlowName = false;
};

