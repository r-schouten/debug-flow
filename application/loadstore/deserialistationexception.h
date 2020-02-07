#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <exception>
#include <serialistationexception.h>
using std::exception;

class DeserialistationException : public exception
{
public:

    QStringList errorLevelString = {"warning","error","fatal"};
    DeserialistationException(ErrorLevel errorLevel, QString callingClass, QString message, QJsonObject jsonObject)
        :errorLevel(errorLevel),callingClass(callingClass),message(message),jsonObject(jsonObject)
    {}
    virtual const char* what() const throw()
    {
        return QString("%1 deserialisation exception  from %2: \"%3\"").arg(errorLevelString.at(errorLevel), callingClass, message).toLatin1();
    }
    void printJson()
    {
        QJsonDocument doc(jsonObject);
        QString strJson(doc.toJson(QJsonDocument::Indented));
        qDebug(strJson.toLatin1());
    }
private:
    QString callingClass;
    ErrorLevel errorLevel;
    QString message;
    QJsonObject jsonObject;
};

