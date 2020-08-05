#pragma once

#include <QJsonObject>

#include "nodesettingsbase.h"

#define SOURCE_NODE
//#define PROCESSING_NODE
//#define OUTPUT_NODE

#if defined (SOURCE_NODE) || defined (PROCESSING_NODE)
    #define OUTPUTNODE
#endif
#if defined (OUTPUT_NODE) || defined (PROCESSING_NODE)
    #define INPUTNODE
#endif

class TamplateNodeSettings : public NodeSettingsBase
{
    Q_OBJECT
public:
    TamplateNodeSettings(DbgLogger* dbgLogger);

    QJsonObject *serialize(SerializationHandler &handler);

    void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler);
    void notifySettingsChanged(DataValid dataValid, SaveSettings saveSettings, SettingsChangeSource source, int event);


private:
    bool enabled = true;

signals:

};
