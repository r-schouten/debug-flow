#include "deserialization_handler.h"

DeserializationHandler::DeserializationHandler(DeserializationSettings_t settings)
    :settings(settings)
{
}

void DeserializationHandler::logWaring(QString callingClass, QString message, QJsonObject jsonObject)
{
    DeserialistationException exception(ErrorLevel::WARNING, callingClass, message, jsonObject);
    occuredErrors.append(exception);
    anyErrorOccured = true;
}

void DeserializationHandler::logError(QString callingClass, QString message, QJsonObject jsonObject)
{
    DeserialistationException exception(ErrorLevel::ERROR, callingClass, message, jsonObject);
    occuredErrors.append(exception);
    anyErrorOccured = true;
    if(settings.exceptionOnError)
    {
        throw exception;
    }
}

void DeserializationHandler::logFatal(QString callingClass, QString message, QJsonObject jsonObject)
{
    DeserialistationException exception(ErrorLevel::FATAL, callingClass, message, jsonObject);
    occuredErrors.append(exception);
    anyErrorOccured = true;
    if(settings.exceptionOnFatal)
    {
        throw exception;
    }
}

void DeserializationHandler::printMessages(bool printJson)
{
    qDebug("---deserialisation error log---");
    QListIterator<DeserialistationException> it(occuredErrors);
    while(it.hasNext())
    {
        DeserialistationException exception = it.next();
        qDebug(exception.what());
        if(printJson)
        {
            exception.printJson();
        }
    }
}

bool DeserializationHandler::errorOccured()
{
    return anyErrorOccured;
}

bool DeserializationHandler::restoreContext()
{
    return settings.restoreContext;
}

bool DeserializationHandler::restoreData()
{
    return settings.restoreData;
}

QString DeserializationHandler::findStringSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
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
int DeserializationHandler::findIntSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
{
    return findInt64Safe(callingClass, element, jsonObject, errorLevel);
}

int64_t DeserializationHandler::findInt64Safe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
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

bool DeserializationHandler::findBoolSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
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

QJsonObject DeserializationHandler::findObjectSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
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

QJsonArray DeserializationHandler::findArraySafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel)
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


