#include "serialization_handler.h"

SerializationHandler::SerializationHandler(DeserializationSettings_t settings)
    :settings(settings)
{
}

void SerializationHandler::logWaring(QString callingClass, QString message, QJsonObject jsonObject)
{
    DeserialistationException exception(ErrorLevel::WARNING, callingClass, message, jsonObject);
    occuredErrors.append(exception);
    anyErrorOccured = true;
}

void SerializationHandler::logError(QString callingClass, QString message, QJsonObject jsonObject)
{
    DeserialistationException exception(ErrorLevel::ERROR, callingClass, message, jsonObject);
    occuredErrors.append(exception);
    anyErrorOccured = true;
    if(settings.exceptionOnError)
    {
        throw exception;
    }
}

void SerializationHandler::logFatal(QString callingClass, QString message, QJsonObject jsonObject)
{
    DeserialistationException exception(ErrorLevel::FATAL, callingClass, message, jsonObject);
    occuredErrors.append(exception);
    anyErrorOccured = true;
    if(settings.exceptionOnFatal)
    {
        throw exception;
    }
}

void SerializationHandler::printMessages(bool printJson)
{
    qDebug("---serialisation error log---");
    QListIterator<DeserialistationException> it(occuredErrors);
    while(it.hasNext())
    {
        DeserialistationException exception = it.next();
        qDebug(exception.what());
    }
}

bool SerializationHandler::errorOccured()
{
    return anyErrorOccured;
}

bool SerializationHandler::restoreContext()
{
    return settings.restoreContext;
}

bool SerializationHandler::restoreData()
{
    return settings.restoreData;
}

QString SerializationHandler::findStringSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
{
    QJsonValue value = jsonObject.find(element).value();
    if(value.isString())//works for both not found and not a string
    {
        return value.toString();
    }
    else
    {
        QString message;
        if(jsonObject.contains(element))
        {
            message = QString("element %1 os not a string").arg(element);
        }
        else
        {
            message = QString("element %1 not found").arg(element);
        }

        if(errorLevel == ErrorLevel::WARNING)
        {
            logWaring(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::ERROR)
        {
            logError(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::FATAL)
        {
            logFatal(callingClass, message, jsonObject);
        }
        return "nullptr";
    }
}

int SerializationHandler::findIntSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
{
    QJsonValue value = jsonObject.find(element).value();
    if(value.isDouble())//works for both not found and not a string
    {
        return value.toInt();
    }
    else
    {
        QString message;
        if(jsonObject.contains(element))
        {
            message = QString("element %1 os not a int or double").arg(element);
        }
        else
        {
            message = QString("element %1 not found").arg(element);
        }

        if(errorLevel == ErrorLevel::WARNING)
        {
            logWaring(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::ERROR)
        {
            logError(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::FATAL)
        {
            logFatal(callingClass, message, jsonObject);
        }
        return 0;
    }
}

bool SerializationHandler::findBoolSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
{
    QJsonValue value = jsonObject.find(element).value();
    if(value.isBool())//works for both not found and not a string
    {
        return value.toBool();
    }
    else
    {
        QString message;
        if(jsonObject.contains(element))
        {
            message = QString("element %1 os not a boolean").arg(element);
        }
        else
        {
            message = QString("element %1 not found").arg(element);
        }

        if(errorLevel == ErrorLevel::WARNING)
        {
            logWaring(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::ERROR)
        {
            logError(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::FATAL)
        {
            logFatal(callingClass, message, jsonObject);
        }
        return false;
    }
}

QJsonObject SerializationHandler::findObjectSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
{
    QJsonValue value = jsonObject.find(element).value();
    if(value.isObject())//works for both not found and not a string
    {
        return value.toObject();
    }
    else
    {
        QString message;
        if(jsonObject.contains(element))
        {
            message = QString("element %1 os not a object").arg(element);
        }
        else
        {
            message = QString("element %1 not found").arg(element);
        }

        if(errorLevel == ErrorLevel::WARNING)
        {
            logWaring(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::ERROR)
        {
            logError(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::FATAL)
        {
            logFatal(callingClass, message, jsonObject);
        }
        return QJsonObject();
    }
}

QJsonArray SerializationHandler::findArraySafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
{
    QJsonValue value = jsonObject.find(element).value();
    if(value.isArray())//works for both not found and not a string
    {
        return value.toArray();
    }
    else
    {
        QString message;
        if(jsonObject.contains(element))
        {
            message = QString("element %1 os not a array").arg(element);
        }
        else
        {
            message = QString("element %1 not found").arg(element);
        }

        if(errorLevel == ErrorLevel::WARNING)
        {
            logWaring(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::ERROR)
        {
            logError(callingClass, message, jsonObject);
        }
        else if(errorLevel == ErrorLevel::FATAL)
        {
            logFatal(callingClass, message, jsonObject);
        }
        return QJsonArray();
    }
}


