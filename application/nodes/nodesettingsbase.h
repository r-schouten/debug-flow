#pragma once
#include "serializable.h"

#include "nodebase.h"
enum SettingsChangeSource
{
    PROPERIES,
    NODE,
    VISUALNODE
};
enum DataValid
{
    DATA_VALID,
    DATA_INVALID
};
enum SaveSettings
{
    SAVE,
    DONT_SAVE
};

class NodeSettingsBase: public QObject, public Serializable
{
    Q_OBJECT
public:
    NodeSettingsBase();
    virtual void deserialize(QJsonObject &jsonObject, DeserializationHandler &handler) = 0;
    virtual void notifySettingsChanged(DataValid dataValid = DATA_VALID,SaveSettings saveSettings = SAVE, SettingsChangeSource source = PROPERIES, int event = 0)=0;
signals:
    void saveAbleChangeOccured();
};

