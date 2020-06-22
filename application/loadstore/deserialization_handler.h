#pragma once
#include <QJsonObject>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include "deserialistationexception.h"

//macro to make functions like findStringSafe easier to use
#define CLASSNAME (staticMetaObject.className())

struct DeserializationSettings_t
{
public:
    bool restoreContext = true;
    bool restoreData = false;//if supported

    bool exceptionOnError = true;
    bool exceptionOnFatal = true;
};

class DeserializationHandler
{
public:
    DeserializationHandler(DeserializationSettings_t settings, DbgLogger *_dbgLogger);
    void logWaring(QString callingClass, QString message, QJsonObject jsonObject);
    void logError(QString callingClass, QString message, QJsonObject jsonObject);
    void logFatal(QString callingClass, QString message, QJsonObject jsonObject);

    void printMessages(bool printJson = false);
    bool errorOccured();
    bool restoreContext();
    bool restoreData();

    QString findStringSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel = ErrorLevel::ERROR);
    int64_t findInt64Safe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel = ErrorLevel::ERROR);
    int findIntSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel = ErrorLevel::ERROR);
    bool findBoolSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel = ErrorLevel::ERROR);
    QJsonObject findObjectSafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel = ErrorLevel::ERROR);
    QJsonArray findArraySafe(QString callingClass, QString element, QJsonObject &jsonObject, ErrorLevel errorLevel = ErrorLevel::ERROR);
private:
    bool anyErrorOccured = false;

    DeserializationSettings_t settings;
    DbgLogger* dbgLogger = nullptr;
    QList<DeserialistationException> occuredErrors;
};
