#include "serialization_handler.h"

SerializationHandler::SerializationHandler(SerializationSettings_t settings)
    :settings(settings)
{
}

void SerializationHandler::logWaring(QString callingClass, QString message)
{
    SerialistationException exception(ErrorLevel::WARNING, callingClass, message);
    occuredErrors.append(exception);
    anyErrorOccured = true;
}

void SerializationHandler::logError(QString callingClass, QString message)
{
    SerialistationException exception(ErrorLevel::ERROR, callingClass, message);
    occuredErrors.append(exception);
    anyErrorOccured = true;
    if(settings.exceptionOnError)
    {
        throw exception;
    }
}

void SerializationHandler::logFatal(QString callingClass, QString message)
{
    SerialistationException exception(ErrorLevel::FATAL, callingClass, message);
    occuredErrors.append(exception);
    anyErrorOccured = true;
    if(settings.exceptionOnFatal)
    {
        throw exception;
    }
}

void SerializationHandler::printMessages()
{
    qDebug("---serialisation error log---");
    QListIterator<SerialistationException> it(occuredErrors);
    while(it.hasNext())
    {
        SerialistationException exception = it.next();
        qDebug(exception.what());
    }
}

bool SerializationHandler::errorOccured()
{
    return anyErrorOccured;
}

bool SerializationHandler::saveContext()
{
    return settings.saveContext;
}

bool SerializationHandler::saveData()
{
    return settings.saveData;
}

bool SerializationHandler::saveTemp()
{
    return settings.saveTempData;
}



