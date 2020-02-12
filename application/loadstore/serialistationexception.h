#pragma once

#include <QString>
#include <QStringList>
#include <exception>

using std::exception;

enum ErrorLevel
{
    WARNING = 0,
    ERROR = 1,
    FATAL = 2
};
class SerialistationException : public exception
{
public:

    QStringList errorLevelString = {"warning","error","fatal"};
    SerialistationException(ErrorLevel errorLevel, QString callingClass, QString message)
        :errorLevel(errorLevel),callingClass(callingClass),message(message)
    {}
    virtual const char* what() const throw()
    {
        return QString("%1 serialisation exception  from %2: \"%3\"").arg(errorLevelString.at(errorLevel), callingClass, message).toLatin1();
    }
private:
    ErrorLevel errorLevel;
    QString callingClass;
    QString message;
};

