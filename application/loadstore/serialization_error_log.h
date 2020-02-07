#pragma once
#include <QJsonObject>
#include <QList>

enum ErrorSource
{
    NODES_SETTINGS,
    NODES_BASE,
    NODE_SPECIFIC,
    CONNECTIONS
};
class SerializationErrorLog
{
public:
    bool anyErrorOccured = false;

    bool errorOccured = false;
    bool fatalErrorOccured = false;

    bool nodesErrorOccured = false;
    bool connectionsErrorOccured = false;

    SerializationErrorLog();
    void LogWaring(ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject);
    void LogError(ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject);
    void LogFatal(ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject);

    void printMessages(bool printJson = false);
private:

    enum ErrorLevel
    {
        WARNING,
        ERROR,
        FATAL
    };
    struct SerialisationError_t
    {
        ErrorSource errorSource;
        QString callingClass;
        ErrorLevel errorLevel;
        QString message;
        QJsonObject jsonObject;
    };
    QList<SerialisationError_t> occuredErrors;
    void LogError(ErrorLevel errorLevel, ErrorSource errorSource, QString callingClass, QString message, QJsonObject jsonObject);

};
