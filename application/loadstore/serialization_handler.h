#pragma once
#include <QJsonObject>
#include <QList>
#include <QJsonDocument>
#include <QJsonArray>
#include "serialistationexception.h"

//macro to make functions like findStringSafe easier to use
#define CLASSNAME (staticMetaObject.className())

struct SerializationSettings_t
{
public:
    bool saveContext = true;
    bool saveData = false; //if supported

    bool saveTempData = true;//used for memento

    bool exceptionOnError = true;
    bool exceptionOnFatal = true;

};

class SerializationHandler
{
public:
    SerializationHandler(SerializationSettings_t settings);
    void logWaring(QString callingClass, QString message);
    void logError(QString callingClass, QString message);
    void logFatal(QString callingClass, QString message);

    void printMessages();
    bool errorOccured();
    bool saveContext();
    bool saveData();
    bool saveTemp();

private:
    bool anyErrorOccured = false;

    SerializationSettings_t settings;

    QList<SerialistationException> occuredErrors;
};
