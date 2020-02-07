#include "serialization_error_log.h"

#include <QJsonDocument>

SerializationErrorLog::SerializationErrorLog()
{

}
void SerializationErrorLog::LogWaring(ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject)
{
    LogError(ErrorLevel::WARNING, errorSource, callingClass, message, jsonObject);
}

void SerializationErrorLog::LogError(ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject)
{
    errorOccured = true;
    LogError(ErrorLevel::ERROR, errorSource, callingClass, message, jsonObject);
}

void SerializationErrorLog::LogFatal(ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject)
{
    fatalErrorOccured = true;
    LogError(ErrorLevel::FATAL, errorSource, callingClass, message, jsonObject);
}

void SerializationErrorLog::LogError(SerializationErrorLog::ErrorLevel errorLevel, ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject)
{
    SerialisationError_t error;
    error.errorLevel = errorLevel;
    error.errorSource = errorSource;
    error.message = message;
    error.callingClass = callingClass;
    error.jsonObject = jsonObject;
    occuredErrors.append(error);

    anyErrorOccured = true;
    if((error.errorSource == ErrorSource::NODES_BASE) || (error.errorSource == ErrorSource::NODE_SPECIFIC) || (error.errorSource == ErrorSource::NODES_SETTINGS))
    {
        nodesErrorOccured = true;
    }
    else if(error.errorSource == ErrorSource::CONNECTIONS)
    {
        connectionsErrorOccured = true;
    }
}

void SerializationErrorLog::printMessages(bool printJson)
{
    qDebug("---serialisation error log---");
    QListIterator<SerialisationError_t> it(occuredErrors);
    while(it.hasNext())
    {
        SerialisationError_t error = it.next();
        if(error.errorLevel == ErrorLevel::WARNING)
        {
            qDebug("- debug message from %s: \"%s\"",error.callingClass.toStdString().c_str(), error.message.toStdString().c_str());
        }
        else if(error.errorLevel == ErrorLevel::ERROR)
        {
            qDebug("- error occured from %s: \"%s\"",error.callingClass.toStdString().c_str(), error.message.toStdString().c_str());
        }
        else if(error.errorLevel == ErrorLevel::FATAL)
        {
            qDebug("- fatal error occured from %s: \"%s\"",error.callingClass.toStdString().c_str(), error.message.toStdString().c_str());
        }

        if(printJson)
        {
            QJsonDocument doc(error.jsonObject);
            QString strJson(doc.toJson(QJsonDocument::Indented));
            qDebug(strJson.toStdString().c_str());
        }
    }
}


